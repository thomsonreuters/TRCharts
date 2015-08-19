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

package com.thomsonreuters.charts.trchartsandroidsandbox.chartlib;

import android.opengl.GLSurfaceView.Renderer;

import com.thomsonreuters.corptech.charts.Chart;
import com.thomsonreuters.corptech.charts.Touch;

import java.util.List;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public abstract class TRChartsAbsRenderer implements Renderer, TRChartsRenderer {
    private Chart mChart;

    public TRChartsAbsRenderer() {
        try {
            mChart = new Chart();
            onInit(mChart);
        } catch (Exception e) {
            wrapException("[TRCharts] Exception starting renderer", e);
        }
    }

    @Override
    public final void onSurfaceCreated(GL10 gl, EGLConfig config) {
    }

    @Override
    public final void onSurfaceChanged(GL10 gl, int width, int height) {
        try {
            onResize(width, height, mChart);
        } catch (Exception e) {
            wrapException("[TRCharts] Exception on surface resize", e);
        }
    }

    @Override
    public final void onDrawFrame(GL10 gl) {
        try {
            onPreUpdate(mChart);
            mChart.update();
            onPostUpdate(mChart);
            onPreRender(mChart);
            mChart.render();
            onPostRender(mChart);
        } catch (Exception e) {
            wrapException("[TRCharts] Exception drawing frame", e);
        }
    }

    public void handleTouches(List<Touch> touches) {
        mChart.handleTouches(touches);
        onTouch(mChart, touches);
    }

    private void wrapException(String message, Exception e) {
        final TRChartsException chartException = new TRChartsException(message);
        chartException.initCause(e);
        onError(chartException);
    }
}
