#pragma once

#include <jni/jni.hpp>

#include "local.hpp"

namespace mbgl {
namespace android {

class Locale {
public:
    static constexpr auto Name() {
        return "java/util/Locale";
    };
    static void registerNative(jni::JNIEnv&);

    static jni::Object<Locale> ForLanguageTag(jni::JNIEnv&, jni::String languageTag);

private:
    static jni::Class<Locale> _class;
};

} // namespace android
} // namespace mbgl
