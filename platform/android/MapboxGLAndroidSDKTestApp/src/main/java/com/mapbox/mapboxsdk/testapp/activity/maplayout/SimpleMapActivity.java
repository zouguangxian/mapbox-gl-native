package com.mapbox.mapboxsdk.testapp.activity.maplayout;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import android.view.Menu;
import android.view.MenuItem;
import com.mapbox.mapboxsdk.constants.Style;
import com.mapbox.mapboxsdk.maps.MapView;
import com.mapbox.mapboxsdk.maps.MapboxMap;
import com.mapbox.mapboxsdk.maps.OnMapReadyCallback;
import com.mapbox.mapboxsdk.style.layers.SymbolLayer;
import com.mapbox.mapboxsdk.testapp.R;
import timber.log.Timber;

import java.util.Locale;

import static com.mapbox.mapboxsdk.style.expressions.Expression.*;
import static com.mapbox.mapboxsdk.style.layers.PropertyFactory.textField;

/**
 * Test activity showcasing a simple MapView without any MapboxMap interaction.
 */
public class SimpleMapActivity extends AppCompatActivity {

  private MapView mapView;
  private MapboxMap mapboxMap;
  private String language;

  private static final String[] LAYER_IDS = new String[] {
    "poi-scalerank3", "road-label-small", "road-label-medium", "road-label-large", "poi-scalerank2-ethan",
    "rail-label-minor", "rail-label-major", "poi-scalerank1-ethan", "airport-label",
    "place-islet-archipelago-aboriginal",    "place-neighbourhood", "place-suburb", "place-hamlet", "place-village",
    "place-town", "place-island", "place-city-sm", "place-city-md-s", "place-city-md-n", "place-city-lg-s",
    "place-city-lg-n", "marine-label-sm-ln", "marine-label-sm-pt", "marine-label-md-ln", "marine-label-md-pt",
    "marine-label-lg-ln", "marine-label-lg-pt", "state-label-sm", "state-label-md", "state-label-lg",
    "country-label-sm", "country-label-md", "country-label-lg"
  };

  private static final String NAME_TEMPLATE = "{name_%s}";
  private static final String ERROR_TEMPLATE = "Layer unavailable %s";

  private long startExecutionTime;
  private long endExecutionTime;

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_map_simple);
    mapView = findViewById(R.id.mapView);
    mapView.setStyleUrl("asset://style.json");
    mapView.onCreate(savedInstanceState);
    mapView.getMapAsync(map -> {
      mapboxMap = map;
      language = Locale.getDefault().getLanguage();
      changeLocale();
    });
  }

  private void changeLocale() {
    startExecutionTime = android.os.SystemClock.uptimeMillis();
    for (String layerId : LAYER_IDS) {
      convertLayerLocale(layerId);
    }
    endExecutionTime = android.os.SystemClock.uptimeMillis();
    long totalExecutionTime = endExecutionTime - startExecutionTime;
    Timber.e("Converting Locale for %s took: %s ms", language, totalExecutionTime);
  }

  private void convertLayerLocale(String layerId) {
    SymbolLayer symbolLayer = mapboxMap.getLayerAs(layerId);
    if (symbolLayer != null) {
      symbolLayer.setProperties(
        textField(String.format(NAME_TEMPLATE, language))
      );
    } else {
      Timber.e(ERROR_TEMPLATE, layerId);
    }
  }

  @Override
  public boolean onCreateOptionsMenu(Menu menu) {
    getMenuInflater().inflate(R.menu.menu_language_select, menu);
    return true;
  }

  @Override
  public boolean onOptionsItemSelected(MenuItem item) {
    if (item.getItemId() == R.id.menu_action_spanish) {
      language = "es";
    } else if (item.getItemId() == R.id.menu_action_german) {
      language = "ru";
    } else if (item.getItemId() == R.id.menu_action_english) {
      language = "en";
    } else {
      return super.onOptionsItemSelected(item);
    }
    changeLocale();
    return true;
  }

  @Override
  protected void onStart() {
    super.onStart();
    mapView.onStart();
  }

  @Override
  protected void onResume() {
    super.onResume();
    mapView.onResume();
  }

  @Override
  protected void onPause() {
    super.onPause();
    mapView.onPause();
  }

  @Override
  protected void onStop() {
    super.onStop();
    mapView.onStop();
  }

  @Override
  public void onLowMemory() {
    super.onLowMemory();
    mapView.onLowMemory();
  }

  @Override
  protected void onDestroy() {
    super.onDestroy();
    mapView.onDestroy();
  }

  @Override
  protected void onSaveInstanceState(Bundle outState) {
    super.onSaveInstanceState(outState);
    mapView.onSaveInstanceState(outState);
  }
}