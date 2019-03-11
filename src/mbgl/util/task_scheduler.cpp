#include <mbgl/util/task_scheduler.hpp>

#include <mbgl/util/thread_local.hpp>

#include <cassert>
#include <memory>
#include <mutex>

namespace {

std::weak_ptr<mbgl::ThreadPool> g_background;

} // namespace

namespace mbgl {

// static
std::shared_ptr<TaskScheduler> TaskScheduler::GetInstance() {
    static thread_local std::weak_ptr<mbgl::TaskScheduler> scheduler;

    std::shared_ptr<mbgl::TaskScheduler> instance = scheduler.lock();

    if (!instance) {
        scheduler = instance = std::shared_ptr<TaskScheduler>(new TaskScheduler());
    }

    return instance;
}

// static
Scheduler& TaskScheduler::GetBackground() {
    return *(*TaskScheduler::GetInstance()).background;
}

TaskScheduler::TaskScheduler() {
    static std::mutex mutex;

    if (!(background = g_background.lock())) {
        std::lock_guard<std::mutex> lock(mutex);
        g_background = background = std::make_shared<ThreadPool>(4);
    }
}

} // namespace mbgl
