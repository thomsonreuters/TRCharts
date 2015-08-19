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

#import "DependentRightAxisLayout.h"

@implementation DependentRightAxisLayout

-(TRRange*)totalOrdinateRangeForAbscissaRange:(TRRange*)abscissaRange forSeriesList:(NSArray*)seriesList
{
    TRRange * totalRange = [TRRange identity];
    for(TRContinuousSeries * series in seriesList) {
        if([series enabled]) {
            TRRange * tmp = [series getOrdinateRangeWithinAbscissaRange:abscissaRange];
            totalRange = [TRRange merge:totalRange otherRange:tmp];
        }
    }
    return totalRange;
}

-(TRDataTransform *)rangeToDataTransform:(TRRange*)dataRange
{
    NSAssert([TRRange positive:dataRange], @"Invalid range");
    TRDataTransform * result = [TRDataTransform new];
    result.scale = 1.0 / [TRRange length:dataRange];
    result.offset = -dataRange.min * result.scale;
    return result;
}

double intpart(double v)
{
    double tmp = 0;
    modf(v, &tmp);
    return tmp;
}

double fracpart(double v)
{
    double tmp = 0;
    return modf(v, &tmp);
}

-(TRDataTransform *)calculateTransform:(TRContinuousAxis*)axis dataRange:(TRRange *)dataRange screenLength:(double)screenLength renderTransform:(TRDataTransform *)renderTransform
{
    TRRange * abscissaRange = [self.bottomAxis screenDataRange];
    TRRange * leftAxisScreenRange = [self.leftAxis screenDataRange];
    TRRange * leftAxisVisibleDataRange = [self totalOrdinateRangeForAbscissaRange:abscissaRange forSeriesList:self.leftAxisSeriesList];
    leftAxisVisibleDataRange = [TRRange clamp:leftAxisVisibleDataRange withinRange:leftAxisScreenRange];
    if([TRRange positive:leftAxisScreenRange] && [TRRange positive:leftAxisVisibleDataRange]) {
        double leftAxisTickInterval = [self.leftAxis tickInterval];
        double leftAxisTickCount = [TRRange length:leftAxisScreenRange] / leftAxisTickInterval;
        double leftAxisTickOffset = fracpart(leftAxisScreenRange.min / leftAxisTickInterval);
        TRRange * rightAxisVisibleDataRange = [self totalOrdinateRangeForAbscissaRange:abscissaRange forSeriesList:self.rightAxisSeriesList];
        if(![TRRange positive:rightAxisVisibleDataRange]) {
            rightAxisVisibleDataRange.min -= 1.0;
            rightAxisVisibleDataRange.max += 1.0;
        }
        if([TRRange positive:rightAxisVisibleDataRange]) {
            TRRange * rightAxisTargetRange = [rightAxisVisibleDataRange copy];
            double visibleDataFactor = [TRRange length:rightAxisVisibleDataRange] / [TRRange length:leftAxisVisibleDataRange];
            double minDiff = leftAxisVisibleDataRange.min - leftAxisScreenRange.min;
            if(minDiff > 0) {
                rightAxisTargetRange.min -= minDiff * visibleDataFactor;
            }
            double maxDiff = leftAxisScreenRange.max - leftAxisVisibleDataRange.max;
            if(maxDiff > 0) {
                rightAxisTargetRange.max += maxDiff * visibleDataFactor;
            }
            double rightAxisTickInterval = [self.rightAxisTickCalculator calculateTickInterval:dataRange visibleDataRange:rightAxisTargetRange screenLength:screenLength];
            double midpoint = (rightAxisTargetRange.min + rightAxisTargetRange.max) * 0.5;
            double rightAxisTargetRangeLength = ((leftAxisTickCount) * rightAxisTickInterval);
            rightAxisTargetRange.min = midpoint - (rightAxisTargetRangeLength * 0.5);
            rightAxisTargetRange.min = (intpart(rightAxisTargetRange.min / rightAxisTickInterval) + leftAxisTickOffset) * rightAxisTickInterval;
            rightAxisTargetRange.max = rightAxisTargetRange.min + rightAxisTargetRangeLength;
            TRDataTransform * rightAxisTransform = [self rangeToDataTransform:rightAxisTargetRange];
            TRDataTransform * renderUntransform = renderTransform;
            renderUntransform = [TRDataTransform concatenate:[TRDataTransform offset:0 scale:1.0 / screenLength] otherDataTransform:renderUntransform];
            renderUntransform = [TRDataTransform invert:renderUntransform];
            rightAxisTransform = [TRDataTransform concatenate:renderUntransform otherDataTransform:rightAxisTransform];
            return rightAxisTransform;
        }
    }
    // failed, return the old transform
    return [axis valueTransform];
}

@end
