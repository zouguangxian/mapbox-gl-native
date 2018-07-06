package com.mapbox.mapboxsdk.maps.style;

import android.support.test.runner.AndroidJUnit4;

import com.mapbox.mapboxsdk.maps.activity.BaseActivityTest;
import com.mapbox.mapboxsdk.maps.activity.style.RuntimeStyleTimingTestActivity;

import org.junit.Test;
import org.junit.runner.RunWith;

/**
 * Basic smoke tests for adding Layer and Source as early as possible (in onCreate)
 */
@RunWith(AndroidJUnit4.class)
public class RuntimeStyleTimingTests extends BaseActivityTest {

  @Override
  protected Class getActivityClass() {
    return RuntimeStyleTimingTestActivity.class;
  }

  @Test
  public void testGetAddRemoveLayer() {
    validateTestSetup();
    // We're good if it didn't crash
  }
}
