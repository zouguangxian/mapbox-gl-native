#pragma once

#include <mbgl/util/run_loop.hpp>
#include <mbgl/util/thread_pool.hpp>

#include <cstdint>
#include <memory>

namespace mbgl {

class TaskScheduler final {
public:
    static std::shared_ptr<TaskScheduler> GetInstance();

    static Scheduler& GetBackground();

private:
    TaskScheduler();

    std::shared_ptr<ThreadPool> background;
};

} // namespace mbgl
