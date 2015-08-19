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

package com.thomsonreuters.charts.trchartsandroidsandbox.chart;

import android.content.Context;
import android.os.SystemClock;

import com.thomsonreuters.charts.trchartsandroidsandbox.chartlib.TRChartsAbsRenderer;
import com.thomsonreuters.charts.trchartsandroidsandbox.chartlib.TRChartsException;
import com.thomsonreuters.corptech.charts.AutomaticNumberTickCalculator;
import com.thomsonreuters.corptech.charts.Axis;
import com.thomsonreuters.corptech.charts.BasicNumberFormatter;
import com.thomsonreuters.corptech.charts.Chart;
import com.thomsonreuters.corptech.charts.Color;
import com.thomsonreuters.corptech.charts.ContinuousDataSource;
import com.thomsonreuters.corptech.charts.ContinuousSeries;
import com.thomsonreuters.corptech.charts.Edge;
import com.thomsonreuters.corptech.charts.Font;
import com.thomsonreuters.corptech.charts.FontHint;
import com.thomsonreuters.corptech.charts.IndexRange;
import com.thomsonreuters.corptech.charts.Label;
import com.thomsonreuters.corptech.charts.LineMode;
import com.thomsonreuters.corptech.charts.LineSeries;
import com.thomsonreuters.corptech.charts.LineStyle;
import com.thomsonreuters.corptech.charts.Margin;
import com.thomsonreuters.corptech.charts.NumberAxis;
import com.thomsonreuters.corptech.charts.ScalarDatum;
import com.thomsonreuters.corptech.charts.Size;
import com.thomsonreuters.corptech.charts.Touch;

import java.util.ArrayList;
import java.util.List;

public class LineChartRenderer extends TRChartsAbsRenderer {
    private final Context mContext;

    private Label fpsLabel;

    private int mWidth;

    private int mHeight;

    private long time = 0;

    private double fps = 0;

    private void themeAxis(final Axis axis) {
        axis.setAxisColor(new Color(255, 255, 255, 255));
        axis.setGridVisible(true);
        axis.setGridColor(new Color(255, 255, 255, 10));
        axis.setTickColor(new Color(255, 255, 255, 10));
        axis.setGridLineStyle(new LineStyle(1.0, LineMode.SOLID));
        axis.setTickLineStyle(new LineStyle(2.0, LineMode.SOLID));
        axis.setTickSize(5.0);
        axis.setAxisLineStyle(new LineStyle(5.0, LineMode.SOLID));
        axis.setTickLabelFont(new Font("DEFAULT", 16, FontHint.ACCURATE));
        axis.setTickLabelColor(new Color(255, 255, 255, 255));
    }

    public LineChartRenderer(Context context) {
        super();
        mContext = context;
    }

    @Override
    public void onInit(Chart chart) {
        // chart.setTitle("Chart example");
        final NumberAxis leftAxis = new NumberAxis();
        leftAxis.setEdge(Edge.LEFT);
        // leftAxis.setTickLength(10.0);
        // final AutomaticRangeCalculator leftRangeCalculator = new AutomaticRangeCalculator();
        // leftRangeCalculator.setIncludeZero(false);
        // leftAxis.setRangeCalculator(leftRangeCalculator);
        final AutomaticNumberTickCalculator leftTickGenerator = new AutomaticNumberTickCalculator();
        final BasicNumberFormatter leftTickNumberFormatter = new BasicNumberFormatter();
        leftAxis.setTickFormatter(leftTickNumberFormatter);
        leftTickGenerator.setTargetScreenInterval(50);
        leftAxis.setTickCalculator(leftTickGenerator);
        themeAxis(leftAxis);
        chart.addAxis(leftAxis);
        final NumberAxis bottomAxis = new NumberAxis();
        bottomAxis.setEdge(Edge.BOTTOM);
        // bottomAxis.setRangeCalculator(leftRangeCalculator);
        bottomAxis.setTickFormatter(leftTickNumberFormatter);
        bottomAxis.setTickCalculator(leftTickGenerator);
        themeAxis(bottomAxis);
        fpsLabel = new Label();
        fpsLabel.setFont(new Font("DEFAULT", 16, FontHint.ACCURATE));
        fpsLabel.setColor(new Color(255, 255, 255, 255));
        fpsLabel.setSize(new Size(0, 16));
        bottomAxis.setTitle(fpsLabel);
        bottomAxis.setTickLabelMaxSize(20);
        // bottomAxis.setTickLength(10.0);
        chart.addAxis(bottomAxis);
        final LineSeries series = new LineSeries();
        series.setDataSource(new ContinuousDataSource<ScalarDatum>() {
            static final int POINTS = 1000;

            static final double STEP = 0.1;

            @Override
            public IndexRange getDatumRange(final ContinuousSeries<ScalarDatum> series) {
                return new IndexRange(0, POINTS);
            }

            @Override
            public List<ScalarDatum> getDatums(final ContinuousSeries<ScalarDatum> series,
                    final IndexRange range) {
                final List<ScalarDatum> result = new ArrayList<ScalarDatum>();
                for (long i = range.getBegin(); i != range.getEnd(); ++i) {
                    final double abscissa = STEP * i;
                    final double ordinate = Math.sin(abscissa);
                    result.add(new ScalarDatum(abscissa, ordinate));
                }
                return result;
                // return Arrays.asList(new ScalarDatum(0, 0), new ScalarDatum(10, 5), new
                // ScalarDatum(20, 10));
            }
        });
        series.setOrdinateAxis(leftAxis);
        series.setAbscissaAxis(bottomAxis);
        series.setColor(new Color(255, 0, 0, 255));
        series.setLineStyle(new LineStyle(5, LineMode.SOLID));
        chart.addSeries(series);
        // chart.removeAxis(axis);
        // chart.addAxis(axis);
        // Log.d("TRC3D", "" + chart.getAxisCount());
        Color color = new Color(50, 50, 50, 255);
        chart.setBackgroundColor(color);
        chart.setMargin(new Margin(50, 50, 10, 50));
    }

    @Override
    public void onResize(int width, int height, Chart chart) {
        mWidth = width;
        mHeight = height;
        chart.resize(new Size(mWidth, mHeight), 1.0);
    }

    @Override
    public void onPreUpdate(Chart chart) {
        final long newTime = SystemClock.elapsedRealtime();
        if (time == 0) {
            time = newTime;
        } else {
            final double frameTime = newTime - time;
            double immediateFps = (1.0 / frameTime) * 1000.0;
            fps = (immediateFps * 0.05) + (fps * 0.95);
            fpsLabel.setText((int)fps + " FPS");
            time = newTime;
        }
    }

    @Override
    public void onPostUpdate(Chart chart) {
    }

    @Override
    public void onPreRender(Chart chart) {
    }

    @Override
    public void onPostRender(Chart chart) {
    }

    @Override
    public void onTouch(Chart chart, List<Touch> touches) {
    }

    @Override
    public void onError(TRChartsException exception) {
        exception.printStackTrace();
    }
    /*
     * public void handleTranslation(GestureState state, Point startPosition, Point translation) {
     * mChart.handleTranslation(state, startPosition, translation); }
     */
}
