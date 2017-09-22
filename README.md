
# BlueRange SDK


[![CI Status](https://travis-ci.org/mwaylabs/BlueRange-SDK-iOS.svg?branch=master)](https://travis-ci.org/mwaylabs/BlueRange-SDK-iOS)


## Overview
The BlueRange SDK is a library for Android and iOS that enables apps to interact with [Relution SmartBeacons](https://www.relution.io/de/beacon-management-plattform/). SmartBeacons can be managed, monitored, updated and configured remotely with the Relution IoT platform by building up a BLE network (mesh) based on the [FruityMesh](https://github.com/mwaylabs/fruitymesh/wiki) beacon firmware making them constantly connected to the cloud.

## Features
Currently the BlueRange SDK supports iOS devices that run at least on iOS 8.0 and Android devices with API level 18 or higher. Features that are based on BLE advertising, however, require the Bluetooth LE peripheral mode on Android devices (API level 21).

The BlueRange SDK is build up of a core and a service layer.

The **core layer** contains a set of components that simplify beacon message stream processing (e.g. iBeacon or Eddystone messages). These message processing components can be combined resulting in a flexible event driven architecture.

The **service layer** builds on top of the core layer and connects your app with Relution. 

More specifically, the following features are supported:

### Core
#### Advertising
- Sending BLE advertising messages of arbitrary data.
- Sending advertising messages for heatmap generation.

#### Scanning
- Scanning beacon messages of different formats:
    - **iBeacon** message: Apple's standardized iBeacon format for BLE advertising which contains an identifier triple (UUID, major and minor).
    - **Eddystone UID** message: One of Google's standardized BLE beacon formats which consists of a 10-byte namespace UID and a 6-byte instance identifier.
    - **Eddystone URL** message: Another Eddystone beacon format containing a URL.
    - **Join Me** message: Beacons based on FruityMesh broadcast these messages to establish a beacon network. Each packet holds the beacon ID, its connectivity and some more information that can be used to identify and analyze Relution SmartBeacons.
    - **Relution Tag** message: An advertising message format only supported by Relution IoT. It contains a list of tags used for offline proximity marketing scenarios.
	- **Asset tracking** message: The advertising message format used by Relution AssetBeacons. Asset beacons can be used for asset localization and tracking.
- Scanning will be continued when the app is running in **background**. This feature, however, is limited due to Apple restrictions.
- **Energy efficiency**: can be controlled by changing the scan cycle duration and sleep interval.

#### Logging
- Messages can **logged persistently and postprocessed at a later time**.
- Useful for collecting training and validation data for indoor localization.

#### Reporting
- Messages logged over a long period of time can be summed up to **status reports** and published to the cloud. 
- The cloud could evaluate these reports for **heatmaps generation** or server-side **indoor localization**.

#### Aggregating
- Most proximity messaging use cases require stable signal strengths (RSSI) to correctly estimate distances to beacons. Message aggregators can be used to **average RSSI measurements** of beacon message streams.

#### Triggering
- A message trigger can be used to implement **proximity marketing** scenarios. Whenever a beacon message arrives, the trigger executes an action, if the predefined time or location conditions are fulfilled and notifies your app about the action execution. Currently supported action parameters are:
  - Action delay: Actions will be executed after a predefined delay.
  - Action lock: Actions will be locked for a specific amount of time after they have been triggered.
  - Activation distance: Actions will only be triggered, if the device has a distance to the beacon which falls below a predefined threshold.
  - Validation period: An action can have a start and end validation time.

### Service

#### Relution SmartBeacon Calibration
- Since each beacon varies in its radio characteristics, distance estimation can be improved by calibrating the RSSI.

#### Relution Proximity marketing
- Realization of proximity marketing (also called "Relution Campaigns" in Relution IoT).

#### Relution Heatmaps
- The device will send advertising messages being collected by the beacons for heatmap generation in the cloud. 

## API reference
- Use the API reference in the ```docs``` folder for more information about the specific classes.

## Installation


#### CocoaPods
The easiest way to import the BlueRangeSDK is to use [CocoaPods](https://cocoapods.org/). Install CocoaPods with the following command:
```bash
gem install cocoapods
```
Add the BlueRange SDK to your ```Podfile```:
```ruby
platform :ios, '8.0'
use_frameworks!

pod 'BlueRangeSDK'
```
To install the SDK, run:
```bash
pod install
```

#### Manual
Include the ```BlueRangeSDK.framework``` generated by the build command (as described below) to the "Embedded Binaries" of your target. To do this, select your Xcode project target, and press the "+" button in the "Embedded Binaries" section in the "General" tab. Then, click on "Add Other" and add the ```BlueRangeSDK.framework``` file.

The header files of the BlueRange SDK can be imported using the following import scheme:
```objective-c
#import <BlueRangeSDK/<HeaderFile>.h>
```


## Build


### Build


To build a universal (fat) binary containing symbols for both ARM and Intel architectures:
```bash
./Build.sh
```
The SDK binary can be found in ```BlueRangeSDK-<VERSION>/ios/BlueRangeSDK.framework```.

To build only for ARM architecture:
```bash
./Build_ARM_only.sh
```
The SDK binary can be found in ```build/Debug-iphoneos/BlueRangeSDK.framework```.


### Generate Javadoc

```bash
./GenerateDocs.sh
```


## Sample code
The following section shows you some code samples that may help you to integrate the library into your app.

### Relution IoT Services
#### Service configuration
If your app should be connected to Relution, use the ```RelutionIoTService```. As can be seen below, you must configure the service before you start it.
- **Campaigns**: Turn on this feature, if you want to use Relution proximity marketing and get notified about executed actions that you defined in the Relution "campaigns" section.
- **Analytics**: Turn on this feature, if you want the SDK to periodically send reports to Relution, which could later be used for analytics.
- **Heatmap**: Turn on this feature, if you want the device to send out heatmap messages. The Relution SmartBeacons will estimate the number of devices next to them and send heatmap reports to the cloud.
- **Logging**: Turn logging on, if you want the SDK to log to the console. Turn this off to increase the app's overall performance.


```objective-c
// .h
#import <BlueRangeSDK/BRRelutionIoTService.h>
@interface <YourClass> : NSObject<BRLoginObserver>
@property BRRelutionIoTService* relutionIoTService;
@end

// .m
#import <BlueRangeSDK/BRRelutionIoTService.h>

- (void) startRelutionIoTService {
    NSString* baseUrl = @"http://iot.relution.io";
    NSString* username = @"your_relution_username";
    NSString* password = @"your_relution_password";
    
    self->_relutionIoTService = [[BRRelutionIoTService alloc] init];
    [self->_relutionIoTService setLoginData:baseUrl 
        andUsername:username andPassword:password andLoginObserver:self];
    [self->_relutionIoTService setLoggingEnabled:true]; // Logging
    [self->_relutionIoTService setCampaignActionTriggerEnabled:true]; // Campaigns
    [self->_relutionIoTService setHeatmapGenerationEnabled:true]; // Heatmap
    [self->_relutionIoTService setHeatmapReportingEnabled:true]; // Analytics
    [self->_relutionIoTService start];
}

- (void) onLoginSucceeded {
    
}

- (void) onLoginFailed {
    
}

- (void) onRelutionError {
    
}
```


#### Relution SmartBeacon calibration
To calibrate the RSSI value of an iBeacon message, just place the device 1 meter away from the beacon
and send the mean RSSI value (based on measurements of approximately 10 seconds) to Relution by calling ```calibrateIBeacon```, as shown below:

```objective-c
// .h
#import <BlueRangeSDK/BRRelutionIoTService.h>
@interface <YourClass> : NSObject<BRBeaconMessageObserver>
@property BRRelutionIoTService* relutionIoTService;
@end

// .m
#import <BlueRangeSDK/BRRelutionIoTService.h>
#import <BlueRangeSDK/BRIBeaconMessage.h>

- (void) registerBeaconMessageObserver {
    [BRRelutionIoTService addBeaconMessageObserver:self];
}

- (void) onMessageReceived: (BRBeaconMessage*) message {
    // Do something with the message.
    if ([message isKindOfClass:BRIBeaconMessage]) {
        // Get the iBeacon message
        BRIBeaconMessage* iBeaconMessage = (BRIBeaconMessage*)message;
        // User moves to a place 1 meter away from the beacon that sends the iBeacon message...
        // Calibrate the iBeacon message.
        [BRRelutionIoTService calibrateIBeacon:iBeaconMessage.iBeacon withTxPower:iBeaconMessage.rssi];
    }
}

```

#### Relution Proximity messaging
Register event listeners for the actions defined in the Relution "campaigns" section.

```objective-c
// .h
#import <BlueRangeSDK/BRRelutionIoTService.h>
@interface <YourClass> : NSObject<
    BRBeaconNotificationActionObserver,
    BRBeaconContentActionObserver,
    BRBeaconTagActionObserver>
@property BRRelutionIoTService* relutionIoTService;
@end

// .m
#import <BlueRangeSDK/BRRelutionIoTService.h>

- (void) registerCampaignActionObservers {
    // Get informed about to campaign actions.
    [BRRelutionIoTService addBeaconNotificationActionObserver:self];
    [BRRelutionIoTService addBeaconContentActionObserver:self];
    [BRRelutionIoTService addBeaconTagActionObserver:self];
}

- (void) onNotificationActionExecuted: (BRBeaconNotificationAction*) notificationAction {
    
}

- (void) onContentActionExecuted: (BRBeaconContentAction*) contentAction {
    
}

- (void) onTagActionExecuted: (BRBeaconTagAction*) tagAction {
    
}
```


#### Relution Heatmaps
To enable heatmap reporting, just start advertising the discovery message using the ```BeaconAdvertiser``` class.


```objective-c
// .m
#import <BlueRangeSDK/BRBeaconAdvertiser.h>
// ...
[[[BRBeaconAdvertiser alloc] init] startAdvertisingDiscoveryMessage];
// ...
```
>

#### Relution tags
If you use Relution Tags for proximity messaging, register a ```RelutionTagObserver``` to get informed about all received Relution Tags. If you need to have access to the name or description of a Relution Tag, just call ```getTagInfoForTag```:

```objective-c
// .h
#import <BlueRangeSDK/BRRelutionIoTService.h>
@interface <YourClass> : NSObject<
    BRRelutionTagObserver>
@property BRRelutionIoTService* relutionIoTService;
@end

// .m
#import <BlueRangeSDK/BRRelutionIoTService.h>
#import <BlueRangeSDK/BRRelutionTagInfoRegistry.h>
#import <BlueRangeSDK/BRRelutionTagMessage.h>

- (void) registerRelutionTagObserver {
    [BRRelutionIoTService addRelutionTagObserver:self];
}

- (void) onTagReceived: (long) tag message: (BRRelutionTagMessage*) message {
    @try {
        [BRRelutionIoTService getTagInfoForTag:tag];
    } @catch(BRRelutionTagInfoRegistryNoInfoFound* exception) {
        // ...
    }
}
```
>

### Core
Use the core layer, if you want to build beacon-aware apps that are independent of Relution.

#### Scanning
Start the scanner, as shown below. You can change the scanner's configuration even if it already running.

```objective-c
// .h
#import <BlueRangeSDK/BRBeaconMessageScanner.h>
#import <BlueRangeSDK/BRBeaconMessageScannerConfig.h>

@interface SystemTestsApplication : NSObject<BRBeaconMessageStreamNodeReceiver>
@property (strong) BRIBeaconMessageScanner* scanner;
@end

// .m
#import <BlueRangeSDK/BRBeaconMessageScanner.h>
#import <BlueRangeSDK/BRBeaconMessageScannerConfig.h>

- (void) startScanning {
    self->_scanner = [[BRBeaconMessageScanner alloc] initWithTracer:[BRTracer getInstance]];
    BRBeaconMessageScannerConfig *config = [self->_scanner config];
    [config scanIBeacon:@"b9407f30-f5f8-466e-aff9-25556b57fe6d" major:45 minor:1];
    [config scanIBeacon:@"c9407f30-f5f8-466e-aff9-25556b57fe6d" major:46 minor:2];
    [config scanRelutionTagsV1:[[NSArray alloc] initWithObjects:
                                [NSNumber numberWithLong:13], [NSNumber numberWithLong:2], nil]];
    [config scanJoinMeMessages];
    [self->_scanner addReceiver:self];
    [self->_scanner startScanning];
}

- (void) onMeshActive: (BRBeaconMessageStreamNode *) senderNode {
    // Do something
}

- (void) onReceivedMessage: (BRBeaconMessageStreamNode *) senderNode withMessage: (BRBeaconMessage*) message {
    // Do something
}

- (void) onMeshInactive: (BRBeaconMessageStreamNode *) senderNode {
    // Do something
}
```


#### Logging
If you want to process beacon messages at a later time, it might be useful to save them on the device persistently and read them out later. To do this, you can use the ```BeaconMessageLogger``` which provides an easy-to-use and thread-safe interface for this purpose. In most cases you will pass the scanner to the logger's constructor. However, if your message processing pipeline is more complex, you can pass any message processing component implementing the ```BeaconMessageStreamNode``` interface. The received messages will be passed to all receivers that have attached to the logger. Thus, you can use the logger as a silent message persistor:


```objective-c
// .h
#import <BlueRangeSDK/BRBeaconMessageScanner.h>
#import <BlueRangeSDK/BRBeaconMessageScannerConfig.h>
#import <BlueRangeSDK/BRBeaconMessageLogger.h>

@interface SystemTestsApplication : NSObject<BRBeaconMessageStreamNodeReceiver>
@property (strong) BRIBeaconMessageScanner* scanner;
@property (strong) BRBeaconMessageLogger* logger;
@end

// .m
#import <BlueRangeSDK/BRBeaconMessageScanner.h>
#import <BlueRangeSDK/BRBeaconMessageScannerConfig.h>
#import <BlueRangeSDK/BRBeaconMessageLogger.h>

- (void) startLogging {
    // Configure Beacon scanner
    self->_scanner = [[BRBeaconMessageScanner alloc] initWithTracer:[BRTracer getInstance]];
    BRBeaconMessageScannerConfig *config = [self->_scanner config];
    [config scanIBeacon:@"b9407f30-f5f8-466e-aff9-25556b57fe6d" major:45 minor:1];
    [config scanIBeacon:@"c9407f30-f5f8-466e-aff9-25556b57fe6d" major:46 minor:2];
    [config scanRelutionTagsV1:[[NSArray alloc] initWithObjects:
                                [NSNumber numberWithLong:13], [NSNumber numberWithLong:2], nil]];
    [config scanJoinMeMessages];
    
    // Configure BeaconMessageLogger
    self->_logger = [[BRBeaconMessageLogger alloc] initWithSender:self->_scanner];
    
    [self->_logger addReceiver:self];
    [self->_scanner startScanning];
}

- (void) onMeshActive: (BRBeaconMessageStreamNode *) senderNode {
    // Do something
}

- (void) onReceivedMessage: (BRBeaconMessageStreamNode *) senderNode withMessage: (BRBeaconMessage*) message {
    // Do something
}

- (void) onMeshInactive: (BRBeaconMessageStreamNode *) senderNode {
    // Do something
}
```


If you need to consume all messages saved in the log in one step, you can use the ```readLog``` method. However, if your log contains a large number of messages, better use the log iterator or a for each loop to reduce memory consumption. The iterator will load the messages in the order they have been saved. It is optimized for thread-safety and performance.

```objective-c
id<BRLogIterator>* logIterator = [self->_logger getLogIterator];
while ([logIterator hasNext]) {
    BRBeaconMessage* message = [logIterator next];
    // Do something
}
```


#### Aggregating
Message aggregation can be useful, if you want to reduce the overall message throughput or if you want to average the received signal strength (RSSI). Currently the ```BeaconMessageAggregator``` supports two modes, a packet mode and a sliding window mode. The packet mode combines a stream of equivalent messages received for a specific amount of time, whereas the sliding window mode keeps the same number of messages in the stream while averaging the RSSI using a moving average filter:

```objective-c
// .h
#import <BlueRangeSDK/BRBeaconMessageScanner.h>
#import <BlueRangeSDK/BRBeaconMessageScannerConfig.h>
#import <BlueRangeSDK/BRBeaconMessageAggregator.h>
#import <BlueRangeSDK/BRLinearWeightedMovingAverageFilter.h>

- (void) startAggregating {
    // Configure scanner
    self->_scanner = [[BRBeaconMessageScanner alloc] initWithTracer:[BRTracer getInstance]];
    BRBeaconMessageScannerConfig *config = [self->_scanner config];
    [config scanIBeacon:@"b9407f30-f5f8-466e-aff9-25556b57fe6d" major:45 minor:1];
    [config scanIBeacon:@"c9407f30-f5f8-466e-aff9-25556b57fe6d" major:46 minor:2];
    [config scanRelutionTagsV1:[[NSArray alloc] initWithObjects:
                                [NSNumber numberWithLong:13], [NSNumber numberWithLong:2], nil]];
    [config scanJoinMeMessages];

    // Configure aggregator
    BRBeaconMessageAggregator* aggregator = [[BRBeaconMessageAggregator alloc]
                                           initWithTracer:[BRTracer getInstance] andSender:self->_scanner];
    [aggregator setAggregationMode:AGGREGATION_MODE_SLIDING_WINDOW];
    [aggregator setAggregateDurationInMs:5*1000];
    [aggregator setAverageFilter:[[BRLinearWeightedMovingAverageFilter alloc] initWithC:0.3]];
}
```



#### Advertising
To periodically send advertising messages, just call one of the ```start``` methods of the ```BeaconAdvertiser``` class:

```objective-c
// .m
#import <BlueRangeSDK/BRBeaconAdvertiser.h>

- (void) startAdvertising {
    self.beaconAdvertiser = [[BRBeaconAdvertiser alloc] init];
    [self.beaconAdvertiser startAdvertisingDiscoveryMessage];
}
```


## License
```
* Copyright (c) 2017, M-Way Solutions GmbH
* All rights reserved.

* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*     http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
```
