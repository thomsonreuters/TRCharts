/*******************************************************************************
 * Copyright 2015 Thomson Reuters
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *******************************************************************************/

#import "ChartController.h"
#import "DependentRightAxisLayout.h"
#import "Loupe.h"

#import <TRChartsObjc/Charts.h>

/*@interface PointSeriesSelectionDelegate : NSObject<TRContinuousSeriesDelegate>

@property (strong, nonatomic) TRLineDecoration * crosshair;
@property (strong, nonatomic) TRPointDecoration * cursor;

-(BOOL)select:(TRSeries*)series index:(long)index value:(id)value;

@end*/

/*@implementation PointSeriesSelectionDelegate

-(BOOL)select:(TRSeries*)series index:(long)index value:(id)value
{
    NSLog(@"Select %d", (int)index);
    TRScalarDatum * datum = value;
    return TRUE;
}

@end
 */

@interface SimpleDataSource : NSObject<TRContinuousDataSource, TRColorSource, TRLineStyleSource>

-(SimpleDataSource *)init;

-(void)addDatum:(id)datum;

-(void)addDatum:(id)datum color:(TRColor *)color;

-(TRIndexRange *)getDatumRange:(TRContinuousSeries *)series;

-(NSArray *)getDatums:(TRContinuousSeries *)series range:(TRIndexRange *)range;

-(NSArray *)getColors:(TRSeries *)series range:(TRIndexRange *)range defaultColor:(TRColor*)defaultColor;

-(NSArray *)getLineStyles:(TRSeries *)series range:(TRIndexRange *)range defaultLineStyle:(TRLineStyle *)defaultLineStyle;

@end

@interface SimpleDataSource () {
}
@property (strong, nonatomic) NSMutableArray * data;
@property (strong, nonatomic) NSMutableArray * colors;
@end

@implementation SimpleDataSource

-(NSRange)convertRangeToHost:(TRIndexRange *)range
{
    return NSMakeRange([range begin], [range end] - [range begin]);
}

-(SimpleDataSource *)init
{
    self = [super init];
    self.data = [[NSMutableArray alloc] init];
    self.colors = [[NSMutableArray alloc] init];
    return self;
}

-(void)addDatum:(id)datum
{
    [self.data addObject:datum];
    [self.colors addObject:[TRColor red:0 green:0 blue:0 alpha:0]];
}

-(void)addDatum:(id)datum color:(TRColor*)color
{
    [self.data addObject:datum];
    [self.colors addObject:color];
}

-(TRIndexRange *)getDatumRange:(TRSeries *)series
{
    return [TRIndexRange begin:0 end:self.data.count];
}

-(NSArray *)getDatums:(TRSeries *)series range:(TRIndexRange *)range
{
    return [self.data subarrayWithRange:[self convertRangeToHost:range]];
}

-(NSArray *)getColors:(TRSeries *)series range:(TRIndexRange *)range defaultColor:(TRColor*)defaultColor
{
    NSMutableArray * result = [[NSMutableArray alloc] init];
    for(int i = 0; i != self.data.count; ++i) {
        if((i % 5 == 0) || ((i + 1) % 5 == 0)) {
            [result addObject:[TRColor red:defaultColor.red green:defaultColor.green blue:defaultColor.blue alpha:defaultColor.alpha * 0.5]];
        } else {
            [result addObject:defaultColor];
        }
    }
    return result;
}

-(NSArray *)getLineStyles:(TRSeries *)series range:(TRIndexRange *)range defaultLineStyle:(TRLineStyle *)defaultLineStyle
{
    NSMutableArray * result = [[NSMutableArray alloc] init];
    for(int i = 0; i != self.data.count; ++i) {
        if((i % 5 == 0) || ((i + 1) % 5 == 0)) {
            [result addObject:[TRLineStyle thickness:[defaultLineStyle thickness] mode:TR_LINEMODE_DASHED]];
        } else {
            [result addObject:defaultLineStyle];
        }
    }
    return result;
}

@end

@interface ChartController () {
}
@property (strong, nonatomic) TRChart *chart;

@property (strong, nonatomic) EAGLContext *context;

@property (strong, nonatomic) TRPointSeries *pointSeries;

@property (strong, nonatomic) UILongPressGestureRecognizer * longPressRecognizer;

/*@property CGPoint panStartLocation;
@property CGPoint pinchStartLocation;
@property CGPoint pinchPrimaryAxis;
@property CGFloat pinchScale;*/

@property (strong, nonatomic) Loupe * loupe;
@end

@implementation ChartController

- (void) viewDidLoad {
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    NSAssert(self.context,@"Failed to create ES context");
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableColorFormat = GLKViewDrawableColorFormatRGB565;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    view.drawableMultisample = GLKViewDrawableMultisample4X;
    view.drawableStencilFormat = GLKViewDrawableStencilFormat8;
    view.multipleTouchEnabled = YES;
    
    self.preferredFramesPerSecond = 60;
    
    self.longPressRecognizer = [[UILongPressGestureRecognizer alloc] initWithTarget:self action:@selector(handleLongPress:)];
    self.longPressRecognizer.delegate = self;
    [self.view addGestureRecognizer:self.longPressRecognizer];
    
    /*self.panRecognizer = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(handlePan:)];
    self.panRecognizer.delegate = self;
    [self.view addGestureRecognizer:self.panRecognizer];
    
    self.pinchRecognizer = [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(handlePinch:)];
    self.pinchRecognizer.delegate = self;
    [self.view addGestureRecognizer:self.pinchRecognizer];*/
    
    self.longPressRecognizer.cancelsTouchesInView = NO;
    /*self.panRecognizer.cancelsTouchesInView = NO;
    self.panRecognizer.minimumNumberOfTouches = 1;
    self.pinchRecognizer.cancelsTouchesInView = NO;*/
    
    [self setupGL];
    
    self.loupe = [[Loupe alloc] initWithContext:self.context chart:self.chart];
    [self.view addSubview:self.loupe];
}

- (void) viewDidAppear: (BOOL) animated
{
    [super viewDidAppear:animated];
    double width = self.view.bounds.size.width;
    double height = self.view.bounds.size.height;
    [self.chart resize:[TRSize width:width height:height] contentScaleFactor:self.view.contentScaleFactor];
}

- (void)setupGL
{
    [TRCharts setLogLevel:TR_LOGLEVEL_DEBUG];
    self.chart = [[TRChart alloc]init];
    [self.chart setBackgroundColor:[TRColor red:50 green:50 blue:50 alpha:255]];
    [self.chart setMargin:[TRMargin left:10 right:10 bottom:10 top:10]];
    TRBasicNumberFormatter * numberFormatter = [[TRSuffixNumberFormatter alloc] init];
    [numberFormatter setDecimalPlaces:1];
    TRPerUnitDateFormatter * dateFormatter = [[TRPerUnitDateFormatter alloc] init];
    [dateFormatter setUnitFormat:TR_DATEUNIT_YEAR format:@"yyyy"];
    [dateFormatter setUnitFormat:TR_DATEUNIT_MONTH format:@"MMM-yyyy"];
    [dateFormatter setUnitFormat:TR_DATEUNIT_DAY format:@"d-MMM-yy"];
    [dateFormatter setUnitFormat:TR_DATEUNIT_HOUR format:@"d-MMM-yy HH:mm"];
    [dateFormatter setUnitFormat:TR_DATEUNIT_MINUTE format:@"d-MMM-yy HH:mm"];
    [dateFormatter setUnitFormat:TR_DATEUNIT_SECOND format:@"d-MMM-yy HH:mm"];
    
    [dateFormatter setSyntax:TR_FORMATSYNTAX_PLATFORM];
    TRNumberAxis * leftAxis = [[TRNumberAxis alloc] init];
    [leftAxis setGridVisible:YES];
    [leftAxis setTickLabelFont:[TRFont name:@"Arial MT" size:16 hint:TR_FONTHINT_ACCURATE]];
    [leftAxis setEdge:TR_EDGE_LEFT];
    [leftAxis setAxisColor:[TRColor red:255 green:255 blue:255 alpha:255]];
    [leftAxis setTickLabelColor:[TRColor red:255 green:255 blue:255 alpha:255]];
    TRPaddingRangeCalculator * paddingRangeCalculator = [[TRPaddingRangeCalculator alloc] init];
    [paddingRangeCalculator setPadding:[TRRange min:1000 max:1000]];
    [leftAxis setRangeCalculator:paddingRangeCalculator];
    //TRTickAligningRangeCalculator * leftRangeCalculator = [[TRTickAligningRangeCalculator alloc] init];
    //[leftRangeCalculator setRangeCalculator:leftRangeCalculatorBase];
    TRDataFittingAxisLayout * leftLayout = [[TRDataFittingAxisLayout alloc] init];
    [leftAxis setLayout:leftLayout];
    TRAutomaticNumberTickCalculator * leftTickGenerator = [[TRAutomaticNumberTickCalculator alloc] init];
    [leftTickGenerator setTargetScreenInterval:50];
    [leftAxis setTickFormatter:numberFormatter];
    [leftAxis setTickCalculator:leftTickGenerator];
    [leftAxis setGridVisible:YES];
    [leftAxis setGridLineStyle:[TRLineStyle thickness:0.5 mode:TR_LINEMODE_SOLID]];
    [leftAxis setAxisLineStyle:[TRLineStyle thickness:2.0 mode:TR_LINEMODE_SOLID]];
    [leftAxis setTickSize:5];
    [leftAxis setTickLineStyle:[TRLineStyle thickness:2.0 mode:TR_LINEMODE_SOLID]];
    [leftAxis setTickColor:[TRColor red:255.0 green:255.0 blue:255.0 alpha:255.0]];
    [leftAxis setGridColor:[TRColor red:255.0 green:255.0 blue:255.0 alpha:127.0]];
    [leftAxis setTickLabelOffset:5];
    [leftAxis setTickLabelMaxSize:45];
    TRLabel * leftAxisLabel = [[TRLabel alloc] init];
    [leftAxisLabel setText:@"XYZABCDEFGHIJKLMNOP"];
    [leftAxisLabel setFont:[TRFont name:@"Arial MT" size:18 hint:TR_FONTHINT_ACCURATE]];
    [leftAxisLabel setMargin:[TRMargin left:0 right:0 bottom:15 top:10]];
    [leftAxisLabel setSize:[TRSize width:0 height:20]];
    [leftAxisLabel setColor:[TRColor red:255.0 green:255.0 blue:255.0 alpha:255.0]];
    [leftAxis setTitle:leftAxisLabel];
    [self.chart addAxis:leftAxis];
    TRDateAxis * bottomAxis = [[TRDateAxis alloc] init];
    [bottomAxis setOffsetSeconds:3600];
    [bottomAxis setGridVisible:YES];
    [bottomAxis setTickLabelFont:[TRFont name:@"Arial MT" size:16 hint:TR_FONTHINT_ACCURATE]];
    [bottomAxis setEdge:TR_EDGE_BOTTOM];
    [bottomAxis setAxisColor:[TRColor red:255 green:255 blue:255 alpha:255]];
    [bottomAxis setTickLabelColor:[TRColor red:255 green:255 blue:255 alpha:255]];
    [bottomAxis setRangeCalculator:paddingRangeCalculator];
    TRFixedRangeCalculator * bottomRangeCalculator = [[TRFixedRangeCalculator alloc] init];
    double t = time(NULL);
    [bottomRangeCalculator setRange:[TRRange min:t + 20000 max:t + 30000]];
    TRDataFittingAxisLayout * bottomLayout = [[TRDataFittingAxisLayout alloc] init];
    [bottomLayout setRangeCalculator:bottomRangeCalculator];
    [bottomAxis setLayout:bottomLayout];
    //TRAutomaticNumberTickCalculator * bottomTickGenerator = [[TRAutomaticNumberTickCalculator alloc] init];
    //[bottomTickGenerator setTargetVisibleTicks:5];
    TRAutomaticDateTickCalculator * bottomTickGenerator = [[TRAutomaticDateTickCalculator alloc] init];
    [bottomTickGenerator setTargetScreenInterval:200];
    [bottomAxis setTickFormatter:dateFormatter];
    [bottomAxis setTickCalculator:bottomTickGenerator];
    [bottomAxis setAxisLineStyle:[TRLineStyle thickness:2.0 mode:TR_LINEMODE_SOLID]];
    [bottomAxis setTickSize:5];
    [bottomAxis setTickLineStyle:[TRLineStyle thickness:2.0 mode:TR_LINEMODE_SOLID]];
    [bottomAxis setTickColor:[TRColor red:255.0 green:255.0 blue:255.0 alpha:255.0]];
    [bottomAxis setGridColor:[TRColor red:50.0 green:50.0 blue:50.0 alpha:255.0]];
    [bottomAxis setTickLabelOffset:5];
    [bottomAxis setTickLabelMaxSize:15];
    TRLabel * bottomAxisLabel = [[TRLabel alloc] init];
    [bottomAxisLabel setText:@"XYZABCDEFGHIJKLMNOP"];
    [bottomAxisLabel setFont:[TRFont name:@"Arial MT" size:18 hint:TR_FONTHINT_ACCURATE]];
    [bottomAxisLabel setMargin:[TRMargin left:0 right:0 bottom:10 top:10]];
    [bottomAxisLabel setSize:[TRSize width:0 height:20]];
    [bottomAxisLabel setColor:[TRColor red:255.0 green:255.0 blue:255.0 alpha:255.0]];
    [bottomAxis setTitle:bottomAxisLabel];
    [self.chart addAxis:bottomAxis];
    TRNumberAxis * rightAxis = [[TRNumberAxis alloc] init];
    [rightAxis setTickLabelFont:[TRFont name:@"Arial MT" size:16 hint:TR_FONTHINT_ACCURATE]];
    [rightAxis setEdge:TR_EDGE_RIGHT];
    [rightAxis setAxisColor:[TRColor red:255 green:255 blue:255 alpha:255]];
    [rightAxis setTickLabelColor:[TRColor red:255 green:255 blue:255 alpha:255]];
    TRAutomaticNumberTickCalculator * rightTickGenerator = [[TRAutomaticNumberTickCalculator alloc] init];
    [rightTickGenerator setTargetScreenInterval:50];
    [rightAxis setTickFormatter:numberFormatter];
    //TRAutomaticRangeCalculator * rightRangeCalculatorBase = [[TRAutomaticRangeCalculator alloc] init];
    //[rightRangeCalculatorBase setIncludeZero:YES];
    //TRTickAligningRangeCalculator * rightRangeCalculator = [[TRTickAligningRangeCalculator alloc] init];
    //[rightRangeCalculator setRangeCalculator:rightRangeCalculatorBase];
    DependentRightAxisLayout * rightLayout = [[DependentRightAxisLayout alloc] init];
    [rightLayout setLeftAxis:leftAxis];
    [rightLayout setBottomAxis:bottomAxis];
    [rightLayout setRightAxisTickCalculator:rightTickGenerator];
    [rightAxis setTickCalculator:rightTickGenerator];
    [rightAxis setLayout:rightLayout];
    [rightAxis setAxisLineStyle:[TRLineStyle thickness:2.0 mode:TR_LINEMODE_SOLID]];
    [rightAxis setTickSize:5];
    [rightAxis setGridVisible:YES];
    [rightAxis setTickLineStyle:[TRLineStyle thickness:2.0 mode:TR_LINEMODE_SOLID]];
    [rightAxis setTickColor:[TRColor red:255.0 green:255.0 blue:255.0 alpha:255.0]];
    [rightAxis setGridColor:[TRColor red:255.0 green:255.0 blue:255.0 alpha:255.0]];
    [rightAxis setGridLineStyle:[TRLineStyle thickness:0.5 mode:TR_LINEMODE_SOLID]];
    [rightAxis setTickLabelOffset:5];
    [rightAxis setTickLabelMaxSize:20];
    TRLabel * rightAxisLabel = [[TRLabel alloc] init];
    [rightAxisLabel setText:@"XYZABCDEFGHIJKLMNOP"];
    [rightAxisLabel setFont:[TRFont name:@"Arial MT" size:18 hint:TR_FONTHINT_ACCURATE]];
    [rightAxisLabel setMargin:[TRMargin left:0 right:0 bottom:10 top:10]];
    [rightAxisLabel setSize:[TRSize width:0 height:20]];
    [rightAxisLabel setColor:[TRColor red:255.0 green:255.0 blue:255.0 alpha:255.0]];
    [rightAxis setTitle:rightAxisLabel];
    [self.chart addAxis:rightAxis];
    /*TRNumberAxis * rightAxis2 = [[TRNumberAxis alloc] init];
    [rightAxis2 setTickLabelFont:[TRFont name:@"Arial MT" size:16 hint:TR_FONTHINT_ACCURATE]];
    [rightAxis2 setPosition:TR_AXISPOSITION_RIGHT];
    [rightAxis2 setAxisColor:[TRColor red:255 green:255 blue:255 alpha:255]];
    [rightAxis2 setTickLabelColor:[TRColor red:255 green:0 blue:0 alpha:255]];
    TRAutomaticRangeCalculator * rightRangeCalculator2Base = [[TRAutomaticRangeCalculator alloc] init];
    [rightRangeCalculator2Base setIncludeZero:YES];
    TRTickAligningRangeCalculator * rightRangeCalculator2 = [[TRTickAligningRangeCalculator alloc] init];
    [rightRangeCalculator2 setRangeCalculator:rightRangeCalculator2Base];
    [rightAxis2 setRangeCalculator:rightRangeCalculator2];
    TRAutomaticNumberTickCalculator * rightTickGenerator2 = [[TRAutomaticNumberTickCalculator alloc] init];
    [rightTickGenerator2 setTargetScreenInterval:50];
    [rightAxis2 setGridVisible:YES];
    [rightAxis2 setTickFormatter:numberFormatter];
    [rightAxis2 setTickCalculator:rightTickGenerator];
    [rightAxis2 setAxisLineStyle:[TRLineStyle thickness:2.0 mode:TR_LINEMODE_SOLID]];
    [rightAxis2 setTickSize:5];
    [rightAxis2 setTickLineStyle:[TRLineStyle thickness:2.0 mode:TR_LINEMODE_SOLID]];
    [rightAxis2 setGridLineStyle:[TRLineStyle thickness:0.5 mode:TR_LINEMODE_SOLID]];
    [rightAxis2 setTickColor:[TRColor red:255.0 green:0.0 blue:0.0 alpha:255.0]];
    [rightAxis2 setGridColor:[TRColor red:255.0 green:255.0 blue:255.0 alpha:127.0]];
    [rightAxis2 setTickOffset:50];
    [rightAxis2 setTickLabelOffset:5];
    [rightAxis2 setTickLabelMaxSize:20];
    TRLabel * rightAxis2Label = [[TRLabel alloc] init];
    [rightAxis2Label setText:@"XYZABCDEFGHIJKLMNOP"];
    [rightAxis2Label setFont:[TRFont name:@"Arial MT" size:18 hint:TR_FONTHINT_ACCURATE]];
    [rightAxis2Label setMargin:[TRMargin left:0 right:0 bottom:10 top:10]];
    [rightAxis2Label setSize:[TRSize width:0 height:20]];
    [rightAxis2 setTitle:rightAxis2Label];
    [self.chart addAxis:rightAxis2];*/
    SimpleDataSource * dataSourceA = [[SimpleDataSource alloc]init];
    SimpleDataSource * dataSourceB = [[SimpleDataSource alloc]init];
    SimpleDataSource * dataSourceC = [[SimpleDataSource alloc]init];
    SimpleDataSource * dataSourceD = [[SimpleDataSource alloc]init];
    for(int i = 0; i != 50; ++i) {
        {
        const double value = 50 + (((double)rand() / RAND_MAX) * 270.0);
            [dataSourceB addDatum:[TRScalarDatum abscissa:t + (i * 1000) ordinate:value] color:[TRColor red:0 green:0 blue:0 alpha:127 + (((double)rand() / RAND_MAX) * 127)]];
        //[dataSourceA addDatum:[TRRangeDatum abscissa:t + (i * 1000) ordinate:[TRRange min:value - (0.8 + ((double)rand() / RAND_MAX) * 0.5) max:value + (0.8 + ((double)rand() / RAND_MAX) * 0.5)]]];
        }
        {
            const double value = (((double)rand() / RAND_MAX));
            [dataSourceA addDatum:[TRRangeDatum abscissa:t + (i * 1000) ordinate:[TRRange min:value - (0.8 + ((double)rand() / RAND_MAX) * 0.5) max:value + (0.8 + ((double)rand() / RAND_MAX) * 0.5)]]];
        }
        {
            const double value = 3 + (((double)rand() / RAND_MAX) * 50);
            [dataSourceD addDatum:[TRScalarDatum abscissa:t + (i * 1000) ordinate:value]];
            [dataSourceC addDatum:[TRRangeDatum abscissa:t + (i * 1000) ordinate:[TRRange min:value - (0.8 + ((double)rand() / RAND_MAX) * 0.5) max:value + (0.8 + ((double)rand() / RAND_MAX) * 0.5)]]];
        }
    }
    /*double maxX = 0;
    double maxY = 0;
    while(maxX < 10000) {
        maxX += (((double)rand() / RAND_MAX) * 200);
        maxY += (((double)rand() / RAND_MAX) * 0.05);
        [dataSourceC addDatum:[TRScalarDatum abscissa:MIN(maxX, 10000) ordinate:maxY]];
    }*/
    TRSteppedLineSeries * seriesA = [[TRSteppedLineSeries alloc] init];
    //[seriesA setStroke:2.0];
    [seriesA setColor:[TRColor red:0.0 green:255.0 blue:0.0 alpha:127.0]];
    [seriesA setOrdinateAxis:leftAxis];
    [seriesA setAbscissaAxis:bottomAxis];
    [seriesA setDataSource:dataSourceB];
    [seriesA setColorSource:dataSourceB];
    [seriesA setLineStyleSource:dataSourceB];
    [seriesA setLineStyle:[TRLineStyle thickness:4.0 mode:TR_LINEMODE_SOLID]];
    [self.chart addSeries:seriesA];
    TRLineSeries * seriesB = [[TRLineSeries alloc] init];
    [seriesB setLineStyle:[TRLineStyle thickness:1.0 mode:TR_LINEMODE_SOLID]];
    [seriesB setColor:[TRColor red:255.0 green:0.0 blue:0.0 alpha:255.0]];
    [seriesB setOrdinateAxis:rightAxis];
    [seriesB setAbscissaAxis:bottomAxis];
    [seriesB setDataSource:dataSourceD];
    [seriesB setColorSource:dataSourceD];
    [seriesB setEnabled:NO];
    [self.chart addSeries:seriesB];
    //[seriesB setEnabled:NO];
    /*[self.chart addSeries:seriesB];
    TRBandSeries * seriesC = [[TRSteppedBandSeries alloc] init];
    //[seriesA setStroke:2.0];
    [seriesC setColor:[TRColor red:255.0 green:0.0 blue:0.0 alpha:127.0]];
    [seriesC setOrdinateAxis:rightAxis];
    [seriesC setAbscissaAxis:bottomAxis];
    [seriesC setDataSource:dataSourceC];
    //[self.chart addSeries:seriesC];
    TRLineSeries * seriesD = [[TRLineSeries alloc] init];
    [seriesD setLineStyle:[TRLineStyle thickness:2.0 mode:TR_LINEMODE_SOLID]];
    [seriesD setColor:[TRColor red:0.0 green:0.0 blue:255.0 alpha:255.0]];
    [seriesD setOrdinateAxis:leftAxis];
    [seriesD setAbscissaAxis:bottomAxis];
    [seriesD setDataSource:dataSourceB];
    //[self.chart addSeries:seriesD];
    TRLineSeries * seriesF = [[TRLineSeries alloc] init];
    [seriesF setColor:[TRColor red:0.0 green:127.0 blue:0.0 alpha:255.0]];
    [seriesF setLineStyle:[TRLineStyle thickness:2 mode:TR_LINEMODE_SOLID]];
    [seriesF setOrdinateAxis:rightAxis];
    [seriesF setAbscissaAxis:bottomAxis];
    [seriesF setDataSource:dataSourceB];
    [seriesF setLineStyleSource:dataSourceB];
    [seriesF setDrawOrder:5];
   // [seriesF setColorSource:dataSourceB];
    //[seriesF setColorBlend:[TRColor red:0.0 green:0.0 blue:0.0 alpha:255.0]];
   // [seriesF setEnabled:NO];
    [self.chart addSeries:seriesF];
    TRAreaSeries * seriesE = [[TRAreaSeries alloc] init];
    //[seriesE setPointSize:6.0];
    [seriesE setColor:[TRColor red:0.0 green:255.0 blue:0.0 alpha:255.0]];
    [seriesE setOrdinateAxis:rightAxis];
    [seriesE setAbscissaAxis:bottomAxis];
    [seriesE setDataSource:dataSourceB];
    [seriesE setColorSource:dataSourceB];
    //[seriesE setSelectable:YES];
    //PointSeriesSelectionDelegate * selectionDelegate = [[PointSeriesSelectionDelegate alloc] init];
    //[seriesE setDelegate:selectionDelegate];
    [seriesE setDrawOrder:0];*/
  //  [seriesE setEnabled:NO];
  //  [self.chart addSeries:seriesE];
    TRLineDecoration * crosshair = [[TRLineDecoration alloc]init];
    [crosshair setAxis:bottomAxis];
    [crosshair setLineStyle:[TRLineStyle thickness:2 mode:TR_LINEMODE_DASHED]];
    [crosshair setColor:[TRColor red:255 green:255 blue:255 alpha:255]];
    [crosshair setVisible:YES];
    [crosshair setEnabled:YES];
    [crosshair setValue:t];
    //[selectionDelegate setCrosshair:crosshair];
    [crosshair setDrawOrder:1];
    [self.chart addDecoration:crosshair];
    /*TRPointDecoration * cursor = [[TRPointDecoration alloc]init];
    [cursor setAbscissaAxis:bottomAxis];
    [cursor setOrdinateAxis:rightAxis2];
    [cursor setPointStyle:[TRPointStyle diameter:10.0]];
    [cursor setColor:[TRColor red:255 green:255 blue:255 alpha:255]];
    [cursor setEnabled:NO];
    [cursor setVisible:YES];
    //[selectionDelegate setCursor:cursor];
    [cursor setDrawOrder:1];*/
    [self.chart setFillColor:[TRColor red:255 green:255 blue:255 alpha:16]];
    //[self.chart addDecoration:cursor];
    [self.chart relayout];
    
    /*TRFadeInAnimation * animation = [TRFadeInAnimation new];
    [animation setDuration:5];
    [animation setDrawableList:[self.chart seriesList]];
    [animation setDelegate:self];
    [self.chart applyAnimation:animation];*/
    
    [rightLayout setLeftAxisSeriesList:@[seriesA]];
    [rightLayout setRightAxisSeriesList:@[seriesB]];
    
    TRConstraint * scaleConstraint = [TRConstraint new];
    TRDataScaleConstraintBehaviour * scaleBehaviour = [TRDataScaleConstraintBehaviour new];
    [scaleBehaviour setAxes:@[leftAxis, bottomAxis]];
    [scaleConstraint setBehaviour:scaleBehaviour];
    [self.chart addConstraint:scaleConstraint];
    
    TRConstraint * offsetConstraint = [TRConstraint new];
    TRDataOffsetConstraintBehaviour * offsetBehaviour = [TRDataOffsetConstraintBehaviour new];
    [offsetBehaviour setAxes:@[leftAxis, bottomAxis]];
    [offsetBehaviour setMultiplier:0.75];
    [offsetConstraint setBehaviour:offsetBehaviour];
    [self.chart addConstraint:offsetConstraint];
    
    NSLog(@"Created chart");
}

-(void)animationCompleted:(TRAnimation*)animation
{
}

-(void)animationCancelled:(TRAnimation*)animation
{
}

double x = 0.0;
double y = 1.0;

double ceilPowerOfTen(const double v)
{
    return pow(10, ceil(log10(v)));
}

double floorPowerOfTen(const double v)
{
    return pow(10, floor(log10(v)));
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    if(self.chart) {
        double width = self.view.bounds.size.width;
        double height = self.view.bounds.size.height;
        [self.chart resize:[TRSize width:width height:height] contentScaleFactor:self.view.contentScaleFactor];
        if(![self.chart update]) {
        }
        //[self.chart preRender];
        [self.chart render];
    }
}

-(TRPoint *)convertPoint:(CGPoint)point
{
    return [TRPoint x:point.x y:point.y];
}

-(NSArray*)convertTouches:(NSSet *)touches
{
    NSMutableArray * result = [NSMutableArray new];
    for(UITouch * touch in touches) {
        TRPoint * position = [self convertPoint:[touch locationInView:[touch view]]];
        TRPoint * lastPosition = [self convertPoint:[touch previousLocationInView:[touch view]]];
        [result addObject:[TRTouch position:position lastPosition:lastPosition]];
        
    }
    return result;
}

/*-(TRTouch *)convertTouch:(UITouch*)touch
{
    TRPoint * startPosition = [self convertPoint:[touch previousLocationInView:touch.view]];
    TRPoint * currentPosition = [self convertPoint:[touch locationInView:touch.view]];
    return [TRTouch startPosition:startPosition currentPosition:currentPosition];
}

-(NSArray *)convertTouches:(NSSet*)touches
{
    NSMutableArray * nativeTouches = [[NSMutableArray alloc] init];
    for(UITouch * touch in touches) {
        [nativeTouches addObject:[self convertTouch:touch]];
    }
    return nativeTouches;
    
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    if(self.chart) {
        [self.chart touchesBegan:[self convertTouches:touches]];
    }
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    if(self.chart) {
        [self.chart touchesMoved:[self convertTouches:touches]];
    }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    if(self.chart) {
        [self.chart touchesEnded:[self convertTouches:touches]];
    }
}*/

/*- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer
{
    if(gestureRecognizer == self.panRecognizer) {
        return otherGestureRecognizer == self.pinchRecognizer;
    } else if(gestureRecognizer == self.pinchRecognizer) {
        return otherGestureRecognizer == self.panRecognizer;
    } else {
        return NO;
    }
}*/

/*-(TRGestureState)convertGestureRecognizerState:(UIGestureRecognizerState)state
{
    switch(state) {
        case UIGestureRecognizerStateBegan:
            return TR_GESTURESTATE_BEGAN;
        case UIGestureRecognizerStateEnded:
            return TR_GESTURESTATE_ENDED;
        case UIGestureRecognizerStateCancelled:
            return TR_GESTURESTATE_CANCELLED;
        default:
            return TR_GESTURESTATE_MOVED;
    }
}*/

- (void)handleLongPress:(UILongPressGestureRecognizer *)sender
{
    
    /*
    TRContinuousAxis * primaryAxis = (TRContinuousAxis*)[self.chart axisList][0];
    TRContinuousAxis * bottomAxis = (TRContinuousAxis*)[self.chart axisList][1];
    TRContinuousAxis * secondaryAxis = (TRContinuousAxis*)[self.chart axisList][2];
    TRContinuousSeries * primarySeries = (TRContinuousSeries*)[self.chart seriesList][0];
    TRContinuousSeries * secondarySeries = (TRContinuousSeries*)[self.chart seriesList][1];
    
    TRRange * range = [secondarySeries getOrdinateRangeWithinAbscissaRange:[bottomAxis screenDataRange]];
    TRFixedRangeCalculator * fixedRangeCalculator = [TRFixedRangeCalculator new];
    [fixedRangeCalculator setRange:range];
    [secondaryAxis setRangeCalculator:fixedRangeCalculator];
    
    NSLog(@"Ordinate range %f %f", range.min, range.max);*/
    return;
    //CGRect frame = self.view.frame;
    //frame.size.height -= 10;
    //self.view.frame = frame;
    /*TRContinuousSeries * series = (TRContinuousSeries*)[self.chart seriesList][0];
    switch (sender.state) {
        case UIGestureRecognizerStateBegan: {
            [self.loupe show];
            [series markRangeDirty:[TRIndexRange begin:5 end:6]];
            break;
        }
        case UIGestureRecognizerStateEnded: {
            [self.loupe hide];
            break;
        }
        default: {
            break;
        }
    }
    for(TRContinuousSeries * series in [self.chart seriesList]) {
        [series setDataSource:[series dataSource]];
    }
    return;
    TRPointDecoration * cursor = (TRPointDecoration*)[self.chart decorationList][1];
    TRPoint * screenPoint = [self convertPoint:[sender locationInView:[sender view]]];
    [self.loupe updatedPosition:[sender locationInView:sender.view]];
    TRCoordinates * dataCoordinates = [series screenPositionToValue:screenPoint];
    long index = [series getIndexNearestAbscissaValue:dataCoordinates.abscissa];
    if(index >= 0) {
        TRScalarDatum * datum = (TRScalarDatum*)[series getDatum:index];
        [cursor setValue:[TRCoordinates abscissa:datum.abscissa ordinate:datum.ordinate]];
        [cursor setEnabled:YES];
    } else {
        [cursor setEnabled:NO];
    }*/
}

-(void)handleSecondaryAxisRelayout:(UIGestureRecognizer *)sender
{
    TRContinuousAxis * secondaryAxis = (TRContinuousAxis*)[self.chart axisList][2];
    TRContinuousSeries * secondarySeries = (TRContinuousSeries*)[self.chart seriesList][1];
    
    if([sender state] == UIGestureRecognizerStateBegan) {
        
        [secondaryAxis setOpacity:0.0];
        [secondarySeries setOpacity:0.0];
        for(TRAnimation * animation in [self.chart activeAnimationList]) {
            [animation complete];
        }
        
    } else if([sender state] == UIGestureRecognizerStateEnded) {
        
        TRContinuousAxis * secondaryAxis = (TRContinuousAxis*)[self.chart axisList][2];
        [secondaryAxis relayout];
        
        TRAnimation * animation = [TRAnimation new];
        [animation setDuration:0.5];
        TRFadeInEffect * effect = [TRFadeInEffect new];
        [effect setDrawableList:@[secondarySeries, secondaryAxis]];
        [animation setEffectList:@[effect]];
        [animation setDelegate:self];
        for(TRAnimation * animation in [self.chart activeAnimationList]) {
            [animation complete];
        }
        [self.chart applyAnimation:animation];
        
    }
}

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
}

-(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self.chart handleTouches:[self convertTouches:touches]];
}

-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
}

-(void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
}

/*
- (void)handlePan:(UIPanGestureRecognizer *)sender
{
    if([sender state] == UIGestureRecognizerStateBegan) {
        self.panStartLocation = [sender locationInView:sender.view];
        CGPoint translation = [sender translationInView:sender.view];
    }
    CGPoint translation = [sender translationInView:sender.view];
    [self.chart handleTranslation:[self convertGestureRecognizerState:[sender state]] startPosition:[self convertPoint:self.panStartLocation] translation:[self convertPoint:translation]];
    //[self.view setNeedsDisplay];
    [self handleSecondaryAxisRelayout:sender];
}

- (CGPoint)gestureRecognizerPrimaryAxis:(UIGestureRecognizer *)sender
{
    const size_t n = [sender numberOfTouches];
    CGFloat sumX = 0;
    CGFloat sumY = 0;
    CGFloat sumXY = 0;
    CGFloat sumXX = 0;
    CGFloat sumYY = 0;
    for(size_t i = 0; i != n; ++i) {
        const CGPoint touchLocation = [sender locationOfTouch:i inView:sender.view];
        sumX += touchLocation.x;
        sumY += touchLocation.y;
        sumXY += touchLocation.x * touchLocation.y;
        sumXX += touchLocation.x * touchLocation.x;
        sumYY += touchLocation.y * touchLocation.y;
    }
    const CGFloat slopeX = (sumXY - ((sumX * sumY) / n)) / (sumXX - ((sumX * sumX) / n));
    const CGFloat slopeY = (sumXY - ((sumY * sumX) / n)) / (sumYY - ((sumY * sumY) / n));
    CGPoint axis;
    if(isnan(slopeY) || (fabs(slopeX) > fabs(slopeY))) {
        //const CGFloat intercept = (sumY / n) - (slopeX * (sumX / n));
        axis = CGPointMake(-1, slopeX);
    } else {
        //const CGFloat intercept = (sumX / n) - (slopeY * (sumY / n));
        axis = CGPointMake(slopeY, -1);
    }
    const CGFloat length = sqrt(axis.x * axis.x + axis.y * axis.y);
    axis.x /= length;
    axis.y /= length;
    if(isnan(axis.x) || isnan(axis.y) || isinf(axis.x) || isinf(axis.y)) {
        axis = CGPointMake(0, 1);
    }
    return axis;
}

#ifdef NDEBUG
#define TRVerify(cond, msg) (cond)
#else
#define TRVerify(cond, msg) ({ __typeof(cond) tmp = (cond); NSAssert(tmp, (msg)); tmp; })
#endif

- (void)handlePinch:(UIPinchGestureRecognizer *)sender
{
    if([sender state] == UIGestureRecognizerStateBegan) {
        const size_t n = [sender numberOfTouches];
        CGPoint mid = CGPointZero;
        for(size_t i = 0; i != n; ++i) {
            const CGPoint touchLocation = [sender locationOfTouch:i inView:sender.view];
            mid.x += touchLocation.x;
            mid.y += touchLocation.y;
        }
        mid.x /= n;
        mid.y /= n;
        self.pinchStartLocation = mid;//[sender locationInView:sender.view];
        self.pinchPrimaryAxis = CGPointMake(0, 1);
        self.pinchScale = 1.0;
    }
    if([sender numberOfTouches] > 1) {
        self.pinchPrimaryAxis = [self gestureRecognizerPrimaryAxis:sender];
        self.pinchScale = [sender scale];
    }
    [self.chart handleScale:[self convertGestureRecognizerState:[sender state]] startPosition:[self convertPoint:self.pinchStartLocation] scale:self.pinchScale axis:[self convertPoint:self.pinchPrimaryAxis]];
    [self handleSecondaryAxisRelayout:sender];
}*/

@end
