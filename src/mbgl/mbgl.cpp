#include <mbgl/mbgl.hpp>

#include <mbgl/util/globals.hpp>

#include <cassert>
#include <memory>

namespace mbgl {

std::unique_ptr<Globals> g_globals;

void Init() {
    assert(!g_globals);
    g_globals.reset(new Globals());
}

void Cleanup() {
    assert(g_globals);
    g_globals.reset();
}

} // namespace mbgl