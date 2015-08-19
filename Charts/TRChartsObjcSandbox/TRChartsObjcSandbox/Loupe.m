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

#import "Loupe.h"

@interface Loupe()
@property (strong, nonatomic) EAGLContext* context;
@property (weak, nonatomic) TRChart* chart;
@end

@implementation Loupe

- (instancetype)initWithContext:(EAGLContext*)context chart:(TRChart*)chart
{
    self = [super initWithFrame:CGRectMake(0,0,100,100)];
    if (self) {
        self.context = context;
        self.chart = chart;
        [self applyStyle];
        [self hide];
    }
    return self;
}

- (void)viewDidLoad
{
    if([EAGLContext setCurrentContext:self.context] == NO) {
        //TRLogTrace(TRLogContextCharts, @"<[%@ (%p)]: Failure to set current context: %d>", self, self, glGetError());
        abort();
    };
    
    self.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    self.drawableMultisample = GLKViewDrawableMultisample4X;
    self.drawableStencilFormat = GLKViewDrawableStencilFormat8;
    self.enableSetNeedsDisplay = YES;
    
    [self bindDrawable];
}

- (void)drawRect:(CGRect)rect
{
    CGPoint position = self.frame.origin;
    CGSize size = self.frame.size;
    [self.chart renderRegion:[TRPoint x:position.x y:position.y] size:[TRSize width:size.width height:size.height] scale:2.0];
}

- (void)show
{
    self.hidden = NO;
}

- (void)hide
{
    self.hidden = YES;
}

- (void)updatedPosition:(CGPoint)point
{
    CGRect frame = self.frame;
    
    point.x -= frame.size.width / 2;
    point.y -= frame.size.height / 2;
    
    frame.origin = point;
    self.frame = frame;
    
    [self display];
}

- (CGRect)position
{
    return self.frame;
}

#pragma mark - PrivateFunctions
- (void)applyStyle
{
    self.layer.borderColor = [UIColor whiteColor].CGColor;
    self.layer.cornerRadius = self.frame.size.width / 2.0f;
    self.layer.masksToBounds = YES;
    self.layer.borderWidth = 2.0f;
    self.layer.opaque = NO;
}


@end
