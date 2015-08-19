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

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.SparseArray;
import android.view.GestureDetector.OnDoubleTapListener;
import android.view.GestureDetector.OnGestureListener;
import android.view.MotionEvent;

import com.thomsonreuters.corptech.charts.Point;
import com.thomsonreuters.corptech.charts.Touch;
import com.thomsonreuters.corptech.tr3dutils.TRChartsTextRenderer;

import java.util.ArrayList;
import java.util.List;

public class TRChartsView extends GLSurfaceView implements OnGestureListener, OnDoubleTapListener {

    private TRChartsAbsRenderer mRenderer;

    private SparseArray<Point> coords = new SparseArray<Point>();

    public TRChartsView(Context context, AttributeSet attrs) {
        super(context, attrs);
        TRChartsTextRenderer.initialize(context.getAssets());
        setEGLContextClientVersion(2);
        getHolder().setFormat(PixelFormat.RGBA_8888);
        setPreserveEGLContextOnPause(true);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
    }

    @Override
    public final void setRenderer(Renderer renderer) {
        if (renderer instanceof TRChartsAbsRenderer) {
            this.mRenderer = (TRChartsAbsRenderer)renderer;
            super.setRenderer(mRenderer);
        } else {
            throw new IllegalArgumentException("[TRCharts] Renderer is not of type "
                    + TRChartsAbsRenderer.class.getSimpleName());
        }
    }

    @Override
    public boolean onTouchEvent(MotionEvent e) {
        switch (e.getAction()) {
            case MotionEvent.ACTION_POINTER_UP: {
                final int count = e.getPointerCount();
                for (int i = 0; i != count; ++i) {
                    final int pointerId = e.getPointerId(i);
                    coords.remove(pointerId);
                }
                break;
            }
            case MotionEvent.ACTION_UP: {
                coords.clear();
                break;
            }
            case MotionEvent.ACTION_MOVE: {
                SparseArray<Point> newPoints = new SparseArray<Point>();
                final List<Touch> touches = new ArrayList<Touch>();
                final int count = e.getPointerCount();
                for (int i = 0; i != count; ++i) {
                    final MotionEvent.PointerCoords currentCoords = new MotionEvent.PointerCoords();
                    e.getPointerCoords(i, currentCoords);
                    final Point currentPoint = new Point(currentCoords.x, currentCoords.y);
                    final int pointerId = e.getPointerId(i);
                    final Point previousPoint = coords.get(pointerId);
                    if (previousPoint != null) {
                        touches.add(new Touch(currentPoint, previousPoint));
                    }
                    newPoints.put(pointerId, currentPoint);
                }
                if (!touches.isEmpty()) {
                    mRenderer.handleTouches(touches);
                }
                coords = newPoints;
                break;
            }
        }
        return true;
    }

    @Override
    public boolean onSingleTapConfirmed(MotionEvent e) {
        return false;
    }

    @Override
    public boolean onDoubleTap(MotionEvent e) {
        return false;
    }

    @Override
    public boolean onDoubleTapEvent(MotionEvent e) {
        return false;
    }

    @Override
    public boolean onDown(MotionEvent e) {
        return false;
    }

    @Override
    public void onShowPress(MotionEvent e) {
    }

    @Override
    public boolean onSingleTapUp(MotionEvent e) {
        return false;
    }

    @Override
    public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY) {
        return false;
    }

    @Override
    public void onLongPress(MotionEvent e) {
    }

    @Override
    public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX, float velocityY) {
        return false;
    }
}
