#import "MGLOfflineStorage.h"

#import "MGLOfflinePack.h"

#include <mbgl/storage/default_file_source.hpp>
#include <mbgl/map/map_options.hpp>

#include <memory>

NS_ASSUME_NONNULL_BEGIN

@interface MGLOfflineStorage (Private)

/**
 The shared map options object owned by the shared offline storage object.
 */
@property (nonatomic) mbgl::MapOptions mbglMapOptions;

/**
 The shared file source object initialized by the shared offline storage object.
 */
@property (nonatomic) std::shared_ptr<mbgl::DefaultFileSource> mbglFileSource;

@end

NS_ASSUME_NONNULL_END
