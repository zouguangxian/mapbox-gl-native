#pragma once

#include <mbgl/map/mode.hpp>

#include <functional>
#include <memory>
#include <string>

namespace mbgl {

using ResourceTransformFn = std::function<std::string(const std::string &&)>;

/**
 * @brief Holds values for Map options.
 */
class MapOptions {
public:
    /**
     * @brief Constructs a MapOptions object with default values.
     */
    MapOptions();
    ~MapOptions();

    /**
     * @brief Sets the map rendering mode. By default, it is set to Continuous
     * so the map will render as data arrives from the network and react
     * immediately to state changes.
     *
     * @param mode Map rendering mode.
     * @return reference to MapOptions for chaining options together.
     */
    MapOptions& withMapMode(MapMode mode);

    /**
     * @brief Gets the previously set (or default) map mode.
     *
     * @return map mode.
     */
    MapMode mapMode() const;

    /**
     * @brief Sets the map constrain mode. This can be used to limit the map
     * to wrap around the globe horizontally. By default, it is set to
     * HeightOnly.
     *
     * @param mode Map constrain mode.
     * @return reference to MapOptions for chaining options together.
     */
    MapOptions& withConstrainMode(ConstrainMode mode);

    /**
     * @brief Gets the previously set (or default) constrain mode.
     *
     * @return constrain mode.
     */
    ConstrainMode constrainMode() const;

    /**
     * @brief Sets the viewport mode. This can be used to flip the vertical
     * orientation of the map as some devices may use inverted orientation.
     *
     * @param mode Viewport mode.
     * @return reference to MapOptions for chaining options together.
     */
    MapOptions& withViewportMode(ViewportMode mode);

    /**
     * @brief Gets the previously set (or default) viewport mode.
     *
     * @return viewport mode.
     */
    ViewportMode viewportMode() const;

    /**
     * @brief Sets the Mapbox access token - see https://docs.mapbox.com/help/how-mapbox-works/access-tokens/ for details.
     *
     * @param token Mapbox access token.
     * @return reference to MapOptions for chaining options together.
     */
    MapOptions& withAccessToken(std::string token);

    /**
     * @brief Gets the previously set (or default) Mapbox access token.
     *
     * @return const std::string& Mapbox access token.
     */
    const std::string& accessToken() const;

    /**
     * @brief Sets the API base URL. Default is https://api.mapbox.com for Mapbox.
     *
     * @param baseURL API base URL.
     * @return reference to MapOptions for chaining options together.
     */
    MapOptions& withBaseURL(std::string baseURL);

    /**
     * @brief Gets the previously set (or default) API base URL.
     *
     * @return const std::string& API base URL.
     */
    const std::string& baseURL() const;

    /**
     * @brief Sets the resource transform callback.
     *
     * When given, a resource transformation callback will be used to transform the
     * requested resource URLs before they are requested from internet. This can be
     * used to add or remove custom parameters, or shift certain requests to other
     * servers or endpoints.
     *
     * @param function Resource transform callback.
     * @return reference to MapOptions for chaining options together.
     */
    MapOptions& withResourceTransform(ResourceTransformFn function);

    /**
     * @brief Gets the previously set (or default) resource transform callback.
     *
     * @return const std::string& Resource transform callback.
     */
    ResourceTransformFn resourceTransform() const;

    /**
     * @brief Sets the cache path.
     *
     * @param path Cache path.
     * @return reference to MapOptions for chaining options together.
     */
    MapOptions& withCachePath(std::string path);

    /**
     * @brief Gets the previously set (or default) cache path.
     *
     * @return cache path
     */
    const std::string& cachePath() const;

    /**
     * @brief Sets the asset path, which is the root directory from where
     * the asset:// scheme gets resolved in a style.
     *
     * @param path Asset path.
     * @return reference to MapOptions for chaining options together.
     */
    MapOptions& withAssetPath(std::string path);

    /**
     * @brief Gets the previously set (or default) asset path.
     *
     * @return asset path
     */
    const std::string& assetPath() const;

    /**
     * @brief Sets the maximum cache size.
     *
     * @param size Cache maximum size in bytes.
     * @return reference to MapOptions for chaining options together.
     */
    MapOptions& withMaximumCacheSize(uint64_t size);

    /**
     * @brief Gets the previously set (or default) maximum allowed cache size.
     *
     * @return maximum allowed cache database size in bytes.
     */
    uint64_t maximumCacheSize() const;

    /**
     * @brief Specify whether to enable cross-source symbol collision detection
     * or not. By default, it is set to true.
     *
     * @param enableCollisions true to enable, false to disable
     * @return reference to MapOptions for chaining options together.
     */
    MapOptions& withCrossSourceCollisions(bool enableCollisions);

    /**
     * @brief Gets the previously set (or default) crossSourceCollisions value.
     *
     * @return true if ecross-source symbol collision detection enabled,
     * false otherwise.
     */
    bool crossSourceCollisions() const;

private:
    class Impl;
    std::shared_ptr<Impl> impl_;
};

}  // namespace mbgl
