#import "MBXState.h"

NSString *const MBXCamera = @"MBXCamera";
NSString *const MBXUserTrackingMode = @"MBXUserTrackingMode";
NSString *const MBXShowsUserLocation = @"MBXShowsUserLocation";
NSString *const MBXShowsDebugMask = @"MBXDebugMask";
NSString *const MBXShowsZoomLevelHUD =  @"MBXShowsZoomLevelHUD";
NSString *const MBXShowsTimeFrameGraph = @"MBXShowsFrameTimeGraph";


@implementation MBXState

- (instancetype) init {
    if ((self = super.self)) {
        NSMutableDictionary *dictionary = [NSMutableDictionary dictionaryWithObjectsAndKeys: @"", MBXCamera,
            @"", MBXUserTrackingMode,
            @"", MBXShowsUserLocation,
            @"", MBXShowsDebugMask,
            @"", MBXShowsZoomLevelHUD,
            @"", MBXShowsTimeFrameGraph,
            nil];

        _state = dictionary;
    }
    return self;
}

- (void)saveMapCameraState:(MGLMapCamera *)camera {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSData *archivedCamera = [NSKeyedArchiver archivedDataWithRootObject:camera];
    [self.state setValue:camera forKey:@"MBXCamera"];
    [defaults setObject:archivedCamera forKey:@"MBXCamera"];
    [defaults synchronize];
}

- (void)saveUserTrackingModeState:(NSInteger)trackingMode; {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [self.state setValue:@(trackingMode) forKey:@"MBXUserTrackingMode"];
    [defaults setInteger:trackingMode forKey:@"MBXUserTrackingMode"];
    [defaults synchronize];
}

- (void)saveShowsUserLocationState:(BOOL)showUserLocation {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [self.state setValue:@(showUserLocation) forKey:@"MBXShowsUserLocation"];
    [defaults setBool:showUserLocation forKey:@"MBXShowsUserLocation"];
    [defaults synchronize];
}

- (void)saveDebugMaskState:(NSInteger)showDebugMask {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [self.state setValue:@(showDebugMask) forKey:@"MBXDebugMask"];
    [defaults setInteger:showDebugMask forKey:@"MBXDebugMask"];
    [defaults synchronize];
}

- (void)saveZoomLevelHUDState:(BOOL)showsZoomLevelHUD {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [self.state setValue:@(showsZoomLevelHUD) forKey:@"MBXShowsZoomLevelHUD"];
    _showsZoomLevelHUD = &showsZoomLevelHUD;
    [defaults setBool:showsZoomLevelHUD forKey:@"MBXShowsZoomLevelHUD"];
    [defaults synchronize];
}

- (void)saveDisplayTimeFrameGraphState:(BOOL)displayTimeFramGraphState {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [self.state setValue:@(displayTimeFramGraphState) forKey:@"MBXShowsFrameTimeGraph"];
    [defaults setBool:displayTimeFramGraphState forKey:@"MBXShowsFrameTimeGraph"];
    [defaults synchronize];
}

@end
