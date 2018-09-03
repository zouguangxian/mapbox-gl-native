#pragma once

#include <mbgl/util/image.hpp>

#include <jni/jni.hpp>

/*
    android::Collator and android::Locale are
    the JNI wrappers of
    java/text/Collator and java/util/Locale

    mbgl::Collator is the portable interface
    Both implementations are in collator.cpp
 */

namespace mbgl {
namespace android {

class Locale {
public:
    static constexpr auto Name() { return "java/util/Locale"; };

    /* Requires API level 21+ in order to support script/variant
    static jni::Object<Locale> forLanguageTag(jni::JNIEnv&, jni::String);
    static jni::String toLanguageTag(jni::JNIEnv&, jni::Object<Locale>);
    */
    static jni::Object<Locale> getDefault(jni::JNIEnv&);
    static jni::String getLanguage(jni::JNIEnv&, jni::Object<Locale>);
    static jni::String getCountry(jni::JNIEnv&, jni::Object<Locale>);

    static jni::Object<Locale> New(jni::JNIEnv&, jni::String);
    static jni::Object<Locale> New(jni::JNIEnv&, jni::String, jni::String);

    static jni::Class<Locale> javaClass;

    static void registerNative(jni::JNIEnv&);

};

class Collator {
public:
    static constexpr auto Name() { return "java/text/Collator"; };

    static jni::Object<Collator> getInstance(jni::JNIEnv&, jni::Object<Locale>);

    static void setStrength(jni::JNIEnv&, jni::Object<Collator>, jni::jint);

    static jni::jint compare(jni::JNIEnv&, jni::Object<Collator>, jni::String, jni::String);

    static jni::Class<Collator> javaClass;

    static void registerNative(jni::JNIEnv&);

};

class Normalizer {
public:
    class Form {
    public:
        static constexpr auto Name() { return "java/text/Normalizer$Form"; };

        enum Value {
            NFC,
            NFD,
            NFKC,
            NFKD,
        };

        static jni::Object<Form> create(jni::JNIEnv&, Value);

        static jni::Class<Form> javaClass;

        static void registerNative(jni::JNIEnv&);
    };

    static constexpr auto Name() { return "java/text/Normalizer"; };

    static jni::String normalize(jni::JNIEnv&, jni::String);

    static jni::Class<Normalizer> javaClass;

    static void registerNative(jni::JNIEnv&);

};

} // namespace android
} // namespace mbgl
