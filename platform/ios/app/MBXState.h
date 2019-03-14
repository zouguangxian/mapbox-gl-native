#import <Foundation/Foundation.h>
#import <Mapbox/Mapbox.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXTERN NSString *const MBXCamera;
FOUNDATION_EXTERN NSString *const MBXUserTrackingMode;
FOUNDATION_EXTERN NSString *const MBXShowsUserLocation;
FOUNDATION_EXTERN NSString *const MBXShowsDebugMask;
FOUNDATION_EXTERN NSString *const MBXShowsZoomLevelHUD;
FOUNDATION_EXTERN NSString *const MBXShowsTimeFrameGraph;

@interface MBXState : NSObject

@property (nonatomic, nullable) NSMutableDictionary *state;

@property (nonatomic, nullable) MGLMapCamera *camera;
@property (nonatomic, nullable) MGLUserTrackingMode *userTrackingMode;
@property (nonatomic, nullable) BOOL *showsUserLocation;
@property (nonatomic, nullable) BOOL *showsDebugMask;
@property (nonatomic, nullable) BOOL *showsZoomLevelHUD;
@property (nonatomic, nullable) BOOL *showsTimeFrameGraph;

- (void)saveMapCameraState:(MGLMapCamera *)camera;
- (void)saveUserTrackingModeState:(NSInteger)trackingMode;
- (void)saveShowsUserLocationState:(BOOL)showUserLocation;
- (void)saveDebugMaskState:(NSInteger)showDebugMask;
- (void)saveZoomLevelHUDState:(BOOL)showsZoomLevelHUD;
- (void)saveDisplayTimeFrameGraphState:(BOOL)displayTimeFramGraphState;

@end

NS_ASSUME_NONNULL_END
