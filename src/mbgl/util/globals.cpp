#include <mbgl/util/globals.hpp>

#include <cassert>
#include <memory>

namespace mbgl {

extern std::unique_ptr<mbgl::Globals> g_globals;

// static
Globals& Globals::GetInstance() {
    assert(g_globals);
    return *g_globals;
}

Scheduler& Globals::GetBackgroundScheduler() {
    return background;
}

Globals::Globals() = default;

} // namespace mbgl