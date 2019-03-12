#pragma once

#include <mbgl/actor/scheduler.hpp>
#include <mbgl/util/thread_pool.hpp>

#define mbgl_ (&mbgl::Globals::GetInstance())

namespace mbgl {

class Globals final {
public:
    static Globals& GetInstance();

    Scheduler& GetBackgroundScheduler();

private:
    Globals();

    ThreadPool background{ 4 };

    friend void mbgl::Init();
};

} // namespace mbgl