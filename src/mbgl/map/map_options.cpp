#include <mbgl/map/map_options.hpp>
#include <mbgl/util/constants.hpp>

#include <cassert>

namespace mbgl {

class MapOptions::Impl {
public:
    MapMode mapMode = MapMode::Continuous;
    ConstrainMode constrainMode = ConstrainMode::HeightOnly;
    ViewportMode viewportMode = ViewportMode::Default;
    std::string accessToken;
    std::string baseURL = mbgl::util::API_BASE_URL;
    ResourceTransformFn resourceTransformFn;
    std::string cachePath;
    std::string assetPath;
    uint64_t maximumSize{mbgl::util::DEFAULT_MAX_CACHE_SIZE};
    bool crossSourceCollisions = true;
};

MapOptions::MapOptions() : impl_(std::make_shared<MapOptions::Impl>()) {}
MapOptions::~MapOptions() = default;

MapOptions& MapOptions::withMapMode(MapMode mode) {
    impl_->mapMode = mode;
    return *this;
}

MapMode MapOptions::mapMode() const {
    return impl_->mapMode;
}

MapOptions& MapOptions::withConstrainMode(ConstrainMode mode) {
    impl_->constrainMode = mode;
    return *this;
}

ConstrainMode MapOptions::constrainMode() const {
    return impl_->constrainMode;
}

MapOptions& MapOptions::withViewportMode(ViewportMode mode) {
    impl_->viewportMode = mode;
    return *this;
}

ViewportMode MapOptions::viewportMode() const {
    return impl_->viewportMode;
}

MapOptions& MapOptions::withAccessToken(std::string token) {
    impl_->accessToken = std::move(token);
    return *this;
}

const std::string& MapOptions::accessToken() const {
    return impl_->accessToken;
}

MapOptions& MapOptions::withBaseURL(std::string url) {
    impl_->baseURL = std::move(url);
    return *this;
}

const std::string& MapOptions::baseURL() const {
    return impl_->baseURL;
}

MapOptions& MapOptions::withResourceTransform(ResourceTransformFn function) {
    impl_->resourceTransformFn = std::move(function);
    return *this;
}

ResourceTransformFn MapOptions::resourceTransform() const {
    return impl_->resourceTransformFn;
}

MapOptions& MapOptions::withCachePath(std::string path) {
    impl_->cachePath = std::move(path);
    return *this;
}

const std::string& MapOptions::cachePath() const {
    return impl_->cachePath;
}

MapOptions& MapOptions::withAssetPath(std::string path) {
    impl_->assetPath = std::move(path);
    return *this;
}

const std::string& MapOptions::assetPath() const {
    return impl_->assetPath;
}

MapOptions& MapOptions::withMaximumCacheSize(uint64_t size) {
    impl_->maximumSize = size;
    return *this;
}

uint64_t MapOptions::maximumCacheSize() const {
    return impl_->maximumSize;
}

MapOptions& MapOptions::withCrossSourceCollisions(bool enableCollisions) {
    impl_->crossSourceCollisions = enableCollisions;
    return *this;
}

bool MapOptions::crossSourceCollisions() const {
    return impl_->crossSourceCollisions;
}

}  // namespace mbgl
