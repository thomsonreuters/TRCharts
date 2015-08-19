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

import com.thomsonreuters.corptech.charts.AutomaticNumberTickCalculator;
import com.thomsonreuters.corptech.charts.BasicNumberFormatter;
import com.thomsonreuters.corptech.charts.Chart;
import com.thomsonreuters.corptech.charts.Color;
import com.thomsonreuters.corptech.charts.ContinuousAxis;
import com.thomsonreuters.corptech.charts.ContinuousDataSource;
import com.thomsonreuters.corptech.charts.ContinuousSeries;
import com.thomsonreuters.corptech.charts.Edge;
import com.thomsonreuters.corptech.charts.Font;
import com.thomsonreuters.corptech.charts.FontHint;
import com.thomsonreuters.corptech.charts.IndexRange;
import com.thomsonreuters.corptech.charts.LineMode;
import com.thomsonreuters.corptech.charts.LineSeries;
import com.thomsonreuters.corptech.charts.LineStyle;
import com.thomsonreuters.corptech.charts.Margin;
import com.thomsonreuters.corptech.charts.NumberAxis;
import com.thomsonreuters.corptech.charts.ScalarDatum;

import java.util.ArrayList;
import java.util.List;

public class Example {
    private Chart createChart() {
        final Chart chart = new Chart();
        chart.setBackgroundColor(new Color(50, 50, 50, 255));
        chart.setMargin(new Margin(50, 50, 10, 50));
        final NumberAxis leftAxis = createAxis(Edge.LEFT);
        chart.addAxis(leftAxis);
        final NumberAxis bottomAxis = createAxis(Edge.BOTTOM);
        chart.addAxis(bottomAxis);
        final LineSeries series = createLineSeries(new SineDataSource(1000, 0.1), bottomAxis,
                leftAxis);
        chart.addSeries(series);
        return chart;
    }

    private LineSeries createLineSeries(final ContinuousDataSource<ScalarDatum> datasource,
            final ContinuousAxis abscissaAxis, final ContinuousAxis ordinateAxis) {
        final LineSeries series = new LineSeries();
        series.setDataSource(datasource);
        series.setOrdinateAxis(ordinateAxis);
        series.setAbscissaAxis(abscissaAxis);
        series.setColor(new Color(255, 0, 0, 255));
        series.setLineStyle(new LineStyle(5, LineMode.SOLID));
        return series;
    }

    private NumberAxis createAxis(final Edge edge) {
        final NumberAxis axis = new NumberAxis();
        axis.setEdge(edge);
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
        final AutomaticNumberTickCalculator tickCalculator = new AutomaticNumberTickCalculator();
        tickCalculator.setTargetScreenInterval(50);
        axis.setTickCalculator(tickCalculator);
        final BasicNumberFormatter numberFormatter = new BasicNumberFormatter();
        axis.setTickFormatter(numberFormatter);
        return axis;
    }

    private static class SineDataSource implements ContinuousDataSource<ScalarDatum> {
        private final int points;

        private final double step;

        public SineDataSource(final int points, final double step) {
            this.points = points;
            this.step = step;
        }

        @Override
        public IndexRange getDatumRange(final ContinuousSeries<ScalarDatum> series) {
            return new IndexRange(0, points);
        }

        @Override
        public List<ScalarDatum> getDatums(final ContinuousSeries<ScalarDatum> series,
                final IndexRange range) {
            final List<ScalarDatum> result = new ArrayList<ScalarDatum>();
            for (long i = range.getBegin(); i != range.getEnd(); ++i) {
                final double abscissa = step * i;
                final double ordinate = Math.sin(abscissa);
                result.add(new ScalarDatum(abscissa, ordinate));
            }
            return result;
        }
    }
}
