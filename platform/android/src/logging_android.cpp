#include <mbgl/util/logging.hpp>

#include <android/log.h>
#include "timber.hpp"
#include "attach_env.hpp"

namespace mbgl {

namespace {

int severityToPriority(EventSeverity severity) {
    switch(severity) {
    case EventSeverity::Debug:
        return ANDROID_LOG_DEBUG;

    case EventSeverity::Info:
        return ANDROID_LOG_INFO;

    case EventSeverity::Warning:
        return ANDROID_LOG_WARN;

    case EventSeverity::Error:
        return ANDROID_LOG_ERROR;

    default:
        return ANDROID_LOG_VERBOSE;
    }
}

} // namespace

void Log::platformRecord(EventSeverity severity, const std::string &msg) {
    __android_log_print(severityToPriority(severity), "mbgl", "%s", msg.c_str());
    if(severity == EventSeverity::Error) {
        auto env{ android::AttachEnv() };
        android::Timber::logError(*env, jni::Make<jni::String>(*env, msg.c_str()));
    }
}
}
