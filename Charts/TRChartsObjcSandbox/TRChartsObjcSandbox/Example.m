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

#import "Example.h"
#include <TRChartsObjc/Charts.h>

// A datasource that returns points from the sine function

@interface SineDatasource : NSObject<TRContinuousDataSource>

@property int points;
@property double step;

-(SineDatasource*)initWithPoints:(int)points step:(double)step;

-(TRIndexRange *)getDatumRange:(TRContinuousSeries *)series;

-(NSArray *)getDatums:(TRContinuousSeries *)series range:(TRIndexRange *)range;

@end

@implementation SineDatasource

-(SineDatasource*)initWithPoints:(int)points step:(double)step
{
    self = [super init];
    if(self) {
        self.points = points;
        self.step = step;
    }
    return self;
}


-(TRIndexRange *)getDatumRange:(TRContinuousSeries *)series
{
    return [TRIndexRange begin:0 end:self.points];
}

-(NSArray *)getDatums:(TRContinuousSeries *)series range:(TRIndexRange *)range
{
    NSMutableArray * result = [[NSMutableArray alloc] init];
    for(long i = [range begin]; i != [range end]; ++i) {
        const double abscissa = self.step * i;
        const double ordinate = sin(abscissa);
        [result addObject:[TRScalarDatum abscissa:abscissa ordinate:ordinate]];
    }
    return result;
}

@end

@implementation Example

// Configure a chart
-(TRChart*)createChart
{
    TRChart * const chart = [[TRChart alloc] init];
    [chart setBackgroundColor:[TRColor red:50 green:50 blue:50 alpha:255]];
    [chart setMargin:[TRMargin left:50 right:50 bottom:50 top:50]];
    TRNumberAxis * const leftAxis = [self createAxisWithEdge:TR_EDGE_LEFT];
    [chart addAxis:leftAxis];
    TRNumberAxis * const bottomAxis = [self createAxisWithEdge:TR_EDGE_BOTTOM];
    [chart addAxis:bottomAxis];
    TRLineSeries * const series = [self createLineSeriesWithDatasource:[[SineDatasource alloc] initWithPoints:1000 step:0.1] abscissaAxis:bottomAxis ordinateAxis:leftAxis];
    [chart addSeries:series];
    return chart;
}

// Create a series with the provided datasource, associated with the provided axes
-(TRLineSeries*)createLineSeriesWithDatasource:(id<TRContinuousDataSource>)datasource abscissaAxis:(TRContinuousAxis*)abscissaAxis ordinateAxis:(TRContinuousAxis*)ordinateAxis
{
    TRLineSeries * const series = [[TRLineSeries alloc] init];
    [series setDataSource:datasource];
    [series setOrdinateAxis:ordinateAxis];
    [series setAbscissaAxis:abscissaAxis];
    [series setColor:[TRColor red:255 green:0 blue:0 alpha:255]];
    [series setLineStyle:[TRLineStyle thickness:5 mode:TR_LINEMODE_SOLID]];
    return series;
}

// Create an axis associated with the given edge
-(TRNumberAxis*) createAxisWithEdge:(TREdge)edge
{
    TRNumberAxis * const axis = [[TRNumberAxis alloc] init];
    [axis setEdge:edge];
    [axis setAxisColor:[TRColor red:255 green:255 blue:255 alpha:255]];
    [axis setGridVisible:YES];
    [axis setGridColor:[TRColor red:255 green:255 blue:255 alpha:10]];
    [axis setTickColor:[TRColor red:255 green:255 blue:255 alpha:10]];
    [axis setGridLineStyle:[TRLineStyle thickness:1.0 mode:TR_LINEMODE_SOLID]];
    [axis setTickLineStyle:[TRLineStyle thickness:2.0 mode:TR_LINEMODE_SOLID]];
    [axis setTickSize:5.0];
    [axis setAxisLineStyle:[TRLineStyle thickness:5.0 mode:TR_LINEMODE_SOLID]];
    [axis setTickLabelFont:[TRFont name:@"DEFAULT" size:16 hint:TR_FONTHINT_ACCURATE]];
    [axis setTickLabelColor:[TRColor red:255 green:255 blue:255 alpha:255]];
    TRAutomaticNumberTickCalculator * const tickCalculator = [[TRAutomaticNumberTickCalculator alloc] init];
    [tickCalculator setTargetScreenInterval:50];
    [axis setTickCalculator:tickCalculator];
    TRBasicNumberFormatter * const numberFormatter = [[TRBasicNumberFormatter alloc] init];
    [axis setTickFormatter:numberFormatter];
    return axis;

}

@end
