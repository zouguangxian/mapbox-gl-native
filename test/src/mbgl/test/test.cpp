#include <mbgl/test.hpp>

#include <mbgl/test/util.hpp>
#include <mbgl/util/task_scheduler.hpp>

#include <gtest/gtest.h>

namespace mbgl {

int runTests(int argc, char *argv[]) {
    auto scheduler = TaskScheduler::GetInstance();

#if TEST_HAS_SERVER
    auto server = std::make_unique<test::Server>("test/storage/server.js");
#endif

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

} // namespace mbgl
