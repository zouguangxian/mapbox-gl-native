#include "local.hpp"

namespace mbgl {
namespace android {

void Locale::registerNative(jni::JNIEnv& env) {
    _class = *jni::Class<Locale>::Find(env).NewGlobalRef(env).release();
}

jni::Class<Locale> Locale::_class;

jni::Object<Locale> Locale::ForLanguageTag(jni::JNIEnv& env, jni::String languageTag) {
    using Signature = jni::Object<Locale>(jni::String);
    auto method = _class.GetStaticMethod<Signature>(env, "forLanguageTag");
    return _class.Call(env, method, languageTag);
}

} // namespace android
} // namespace mbgl
