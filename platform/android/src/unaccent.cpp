#include <unaccent.hpp>
#include <string>
#include <src/java/lang.hpp>
#include "attach_env.hpp"
#include "text/collator_jni.hpp"

namespace mbgl {
namespace platform {

std::string unaccent(const std::string& str) {
    android::UniqueEnv env = android::AttachEnv();
    jni::String normalized = android::Normalizer::normalize(*env,jni::Make<jni::String>(*env, str));
    jni::String unaccented = android::java::lang::String::replaceAll(*env, normalized,
                                                                     jni::Make<jni::String>(*env, "\\p{InCombiningDiacriticalMarks}+"),
                                                                     jni::Make<jni::String>(*env, ""));
    return jni::Make<std::string>(*env, unaccented);
}

} // namespace platform
} // namespace mbgl
