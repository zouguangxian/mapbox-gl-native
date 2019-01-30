package com.mapbox.mapboxsdk.testapp.activity.geojson;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

import com.mapbox.geojson.FeatureCollection;
import com.mapbox.mapboxsdk.testapp.R;
import com.mapbox.mapboxsdk.testapp.utils.GeoParseUtil;

import java.io.IOException;

public class GeoJsonBenchActivity extends AppCompatActivity {

  @Override
  protected void onCreate(@Nullable Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_geojson_bench);

    try {
      final String onePointJsonString = GeoParseUtil.loadStringFromAssets(this, "one_point.geojson");
      findViewById(R.id.fab_one_point).setOnClickListener(v -> {
        FeatureCollection.fromJson(onePointJsonString);
      });

      final String largePointJsonString = GeoParseUtil.loadStringFromAssets(this, "points.geojson");
      findViewById(R.id.fab_many_point).setOnClickListener(v -> {
        FeatureCollection.fromJson(largePointJsonString);
      });

    } catch (IOException e) {
      e.printStackTrace();
    }

  }


}
