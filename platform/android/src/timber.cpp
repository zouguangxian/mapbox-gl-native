#include "timber.hpp"
#include "java_types.hpp"

namespace mbgl {
namespace android {

void Timber::registerNative(jni::JNIEnv& env) {
    _class = *jni::Class<Timber>::Find(env).NewGlobalRef(env).release();
}

jni::Class<Timber> Timber::_class;

void Timber::logError(jni::JNIEnv& env, jni::String error) {
     using Signature = void(jni::String, jni::Array<jni::Object<>>);
     auto method = _class.GetStaticMethod<Signature>(env, "e");
     return _class.Call(env, method, error, jni::Array<jni::Object<>>());
}

} // namespace android
} // namespace mbgl
