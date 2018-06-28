#pragma once

#include <mbgl/map/map_snapshotter.hpp>

#include <jni/jni.hpp>

#include "../geometry/lat_lng.hpp"
#include "../graphics/pointf.hpp"
#include "../geojson/feature.hpp"

#include <vector>
#include <string>

namespace mbgl {
namespace android {

class MapSnapshot {
public:

    using PointForFn = mbgl::MapSnapshotter::PointForFn;
    using QueryPointForFn = mbgl::MapSnapshotter::QueryPointForFn;

    static constexpr auto Name() { return "com/mapbox/mapboxsdk/snapshotter/MapSnapshot"; };

    static void registerNative(jni::JNIEnv&);

    static jni::Object<MapSnapshot> New(JNIEnv& env,
                                        PremultipliedImage&& image,
                                        float pixelRatio,
                                        std::vector<std::string> attributions,
                                        bool showLogo,
                                        PointForFn pointForFn,
                                        QueryPointForFn queryPointForFn);

    MapSnapshot(jni::JNIEnv&) {};
    MapSnapshot(float pixelRatio, PointForFn);
    ~MapSnapshot();

    jni::Object<PointF> pixelForLatLng(jni::JNIEnv&, jni::Object<LatLng>);
    jni::Array<jni::Object<geojson::Feature>> queryRenderedFeaturesForPoint(JNIEnv&, jni::jfloat, jni::jfloat,
                                                                            jni::Array<jni::String>,
                                                                            jni::Array<jni::Object<>> jfilter);

//    jni::Array<jni::Object<geojson::Feature>> queryRenderedFeaturesForBox(JNIEnv&, jni::jfloat, jni::jfloat, jni::jfloat,
//                                                                          jni::jfloat, jni::Array<jni::String>,
//                                                                          jni::Array<jni::Object<>> jfilter);
private:
    static jni::Class<MapSnapshot> javaClass;

    float pixelRatio;
    mbgl::MapSnapshotter::PointForFn pointForFn;
    mbgl::MapSnapshotter::QueryPointForFn queryPointForFn;
};

} // namespace android
} // namespace mbgl