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

package com.thomsonreuters.charts.trchartsandroidsandbox;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;

import com.thomsonreuters.charts.trchartsandroidsandbox.chartlib.TRChartsAbsRenderer;
import com.thomsonreuters.charts.trchartsandroidsandbox.chartlib.TRChartsView;
import com.thomsonreuters.charts.trchartsandroidsandbox.chart.LineChartRenderer;
import com.thomsonreuters.corptech.charts.Point;

public class MainActivity extends ActionBarActivity {
    static {
        System.loadLibrary("TRChartsJNI");
    }

    private TRChartsAbsRenderer mRenderer;

    private PlaceholderFragment placeholderFragment;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mRenderer = new LineChartRenderer(this);
        if (savedInstanceState == null) {
            placeholderFragment = new PlaceholderFragment();
            getSupportFragmentManager().beginTransaction()
                    .add(R.id.container, placeholderFragment, "chart").commit();
        }
        Point p = Point.add(new Point(1, 2), new Point(2, 1));
        Log.d("lalala", p.getX() + " " + p.getY());
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        // noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    /**
     * A placeholder fragment containing a simple view.
     */
    public static class PlaceholderFragment extends Fragment {
        @Override
        public View onCreateView(LayoutInflater inflater, ViewGroup container,
                Bundle savedInstanceState) {
            View rootView = inflater.inflate(R.layout.fragment_main, container, false);
            TRChartsView view = (TRChartsView)rootView.findViewById(R.id.chart_gpv);
            /* For showcase purposes */
            final TRChartsAbsRenderer renderer = ((MainActivity)getActivity()).mRenderer;
            view.setRenderer(renderer);
            return rootView;
        }
    }
}
