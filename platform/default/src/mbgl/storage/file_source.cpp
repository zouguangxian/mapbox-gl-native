#include <mbgl/map/map_options.hpp>
#include <mbgl/storage/default_file_source.hpp>
#include <mbgl/util/string.hpp>

#include <mutex>
#include <unordered_map>

namespace mbgl {

std::shared_ptr<FileSource> FileSource::platformFileSource(const MapOptions& options) {
    static std::mutex mutex;
    static std::unordered_map<std::string, std::weak_ptr<mbgl::DefaultFileSource>> fileSources;

    std::lock_guard<std::mutex> lock(mutex);

    // Purge entries no longer in use.
    for (auto it = fileSources.begin(); it != fileSources.end();) {
        if (it->second.expired()) { fileSources.erase(it); } else { it++; };
    }

    const std::string key = options.baseURL() + '|' + options.accessToken() + '|' + options.cachePath();

    std::shared_ptr<mbgl::DefaultFileSource> fileSource;
    auto tuple = fileSources.find(key);
    if (tuple != fileSources.end()) {
        fileSource = tuple->second.lock();
    } else {
        fileSources[key] = fileSource = std::make_shared<DefaultFileSource>(options.cachePath(), options.assetPath());
        fileSource->setAccessToken(options.accessToken());
        fileSource->setAPIBaseURL(options.baseURL());
    }

    assert(fileSource);
    return fileSource;
}

} // namespace mbgl
