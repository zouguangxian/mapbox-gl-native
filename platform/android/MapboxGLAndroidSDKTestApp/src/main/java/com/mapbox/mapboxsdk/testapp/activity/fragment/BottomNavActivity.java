package com.mapbox.mapboxsdk.testapp.activity.fragment;

import android.graphics.Color;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.design.widget.BottomNavigationView;
import android.support.v4.app.Fragment;
import android.support.v7.app.AppCompatActivity;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.TextView;
import com.google.gson.JsonObject;
import com.google.gson.JsonPrimitive;
import com.mapbox.geojson.Feature;
import com.mapbox.geojson.FeatureCollection;
import com.mapbox.geojson.Point;
import com.mapbox.mapboxsdk.maps.MapView;
import com.mapbox.mapboxsdk.maps.MapboxMap;
import com.mapbox.mapboxsdk.maps.OnMapReadyCallback;
import com.mapbox.mapboxsdk.maps.SupportMapFragment;
import com.mapbox.mapboxsdk.style.layers.Property;
import com.mapbox.mapboxsdk.style.layers.SymbolLayer;
import com.mapbox.mapboxsdk.style.sources.GeoJsonSource;
import com.mapbox.mapboxsdk.testapp.R;
import timber.log.Timber;

import java.util.ArrayList;
import java.util.List;

import static com.mapbox.mapboxsdk.style.expressions.Expression.get;
import static com.mapbox.mapboxsdk.style.layers.PropertyFactory.iconAllowOverlap;
import static com.mapbox.mapboxsdk.style.layers.PropertyFactory.iconAnchor;
import static com.mapbox.mapboxsdk.style.layers.PropertyFactory.iconColor;
import static com.mapbox.mapboxsdk.style.layers.PropertyFactory.iconIgnorePlacement;
import static com.mapbox.mapboxsdk.style.layers.PropertyFactory.iconImage;
import static com.mapbox.mapboxsdk.style.layers.PropertyFactory.textAllowOverlap;
import static com.mapbox.mapboxsdk.style.layers.PropertyFactory.textAnchor;
import static com.mapbox.mapboxsdk.style.layers.PropertyFactory.textColor;
import static com.mapbox.mapboxsdk.style.layers.PropertyFactory.textField;
import static com.mapbox.mapboxsdk.style.layers.PropertyFactory.textIgnorePlacement;
import static com.mapbox.mapboxsdk.style.layers.PropertyFactory.textSize;

public class BottomNavActivity extends AppCompatActivity {

  private final List<Fragment> fragments = new ArrayList<>(5);
  private Fragment currentFragment;

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_bottom_nav);

    BottomNavigationView navigation = findViewById(R.id.navigation);

    fragments.add(CustomFragment.newInstance(1));
    fragments.add(new CustomMapFragment());
    fragments.add(CustomFragment.newInstance(3));
    fragments.add(SupportMapFragment.newInstance());
    fragments.add(CustomFragment.newInstance(5));

    // add initial fragment
    currentFragment = fragments.get(0);
    getSupportFragmentManager().beginTransaction().add(R.id.fragment_container, currentFragment).commit();

    // add tab listener to change fragments
    navigation.setOnNavigationItemSelectedListener(item -> {
      switch (item.getItemId()) {
        case R.id.navigation_home:
          currentFragment = fragments.get(0);
          break;
        case R.id.navigation_map_one:
          currentFragment = fragments.get(1);
          break;
        case R.id.navigation_notifications:
          currentFragment = fragments.get(2);
          break;
        case R.id.navigation_map_two:
          currentFragment = fragments.get(3);
          break;
        case R.id.navigation_car:
          currentFragment = fragments.get(4);
          break;
      }
      // replace current fragment with tab selected one
      getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, currentFragment).commit();
      return true;
    });
  }

  @Override
  public boolean onCreateOptionsMenu(Menu menu) {
    getMenuInflater().inflate(R.menu.menu_bottom, menu);
    return true;
  }

  @Override
  public boolean onOptionsItemSelected(MenuItem item) {
    int itemId = item.getItemId();
    if (itemId == R.id.menu_action_show) {
      getSupportFragmentManager().beginTransaction().show(currentFragment).commit();
      return true;
    } else if (itemId == R.id.menu_action_hide) {
      getSupportFragmentManager().beginTransaction().hide(currentFragment).commit();
      return true;
    } else if (itemId == R.id.menu_action_detach) {
      getSupportFragmentManager().beginTransaction().detach(currentFragment).commit();
      return true;
    } else if (itemId == R.id.menu_action_attach) {
      getSupportFragmentManager().beginTransaction().attach(currentFragment).commit();
      return true;
    }
    return super.onOptionsItemSelected(item);
  }

  public static class CustomFragment extends Fragment {

    public static final String COUNTER = "counter";

    public static CustomFragment newInstance(int counter) {
      Bundle args = new Bundle();
      args.putInt(COUNTER, counter);
      CustomFragment fragment = new CustomFragment();
      fragment.setArguments(args);
      return fragment;
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
      TextView textView = new TextView(inflater.getContext());
      textView.setLayoutParams(new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT, Gravity.CENTER));
      textView.setTextSize(20);
      textView.setText(String.format("Fragment number: %s", getArguments().getInt("counter")));
      return textView;
    }
  }

  public static class CustomMapFragment extends Fragment {

    private MapView mapView;

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
      Timber.e("OnCreateView Map");
      return mapView = new MapView(inflater.getContext());
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
      super.onViewCreated(view, savedInstanceState);
      mapView.getMapAsync(new OnMapReadyCallback() {
        @Override
        public void onMapReady(MapboxMap mapboxMap) {
          // Add a source
          FeatureCollection markers = FeatureCollection.fromFeatures(new Feature[] {
            Feature.fromGeometry(Point.fromLngLat(4.91638, 52.35673), featureProperties("Marker 1")),
            Feature.fromGeometry(Point.fromLngLat(4.91638, 52.34673), featureProperties("Marker 2"))
          });
          mapboxMap.addSource(new GeoJsonSource("source-id", markers));

          // Add the symbol-layer
          mapboxMap.addLayer(
            new SymbolLayer("layer-id", "source-id")
              .withProperties(
                iconImage("car-15"),
                iconIgnorePlacement(true),
                iconAllowOverlap(true),
                iconAnchor(Property.ICON_ANCHOR_BOTTOM),
                iconColor(Color.RED),
                textField(get("title")),
                textColor(Color.RED),
                textAllowOverlap(true),
                textIgnorePlacement(true),
                textAnchor(Property.TEXT_ANCHOR_TOP),
                textSize(10f)
              )
          );
        }
      });
    }

    private JsonObject featureProperties(String title) {
      JsonObject object = new JsonObject();
      object.add("title", new JsonPrimitive(title));
      return object;
    }

    @Override
    public void onStart() {
      super.onStart();
      Timber.e("OnStart Map");
      mapView.onStart();
    }

    @Override
    public void onResume() {
      super.onResume();
      Timber.e("OnResume Map");
      mapView.onResume();
    }

    @Override
    public void onPause() {
      super.onPause();
      Timber.e("OnPause Map");
      mapView.onPause();
    }

    @Override
    public void onStop() {
      super.onStop();
      Timber.e("OnStop Map");
      mapView.onStop();
    }

    @Override
    public void onDestroyView() {
      super.onDestroyView();
      Timber.e("OnDestroy Map");
      mapView.onDestroy();
    }

    @Override
    public void onSaveInstanceState(@NonNull Bundle outState) {
      super.onSaveInstanceState(outState);
      Timber.e("OnSaveInstanceState Map");
      mapView.onSaveInstanceState(outState);
    }

    @Override
    public void onLowMemory() {
      super.onLowMemory();
      Timber.e("OnLowMemory Map");
      mapView.onLowMemory();
    }
  }
}
