#pragma once

#include <jni/jni.hpp>

#include "bitmap.hpp"

namespace mbgl {
namespace android {

class Timber {
public:
    static constexpr auto Name() {
        return "timber/log/Timber";
    };
    static void registerNative(jni::JNIEnv&);

    static void logError(jni::JNIEnv&, jni::String error);

    private:
      static jni::Class<Timber> _class;
    };

} // namespace android
} // namespace mbgl
