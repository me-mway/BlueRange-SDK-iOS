//
//  BRBeaconNotificationAction.h
//  BlueRangeSDK
//
// Copyright (c) 2016-2017, M-Way Solutions GmbH
// All rights reserved.
//
// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
//

#import <Foundation/Foundation.h>
#import "BRBeaconAction.h"

@interface BRBeaconNotificationAction : BRBeaconAction

// BRConstants
extern NSString* const TYPE_VARIABLE_NOTIFICATION;
extern NSString* const NOTIFICATION_CONTENT_PARAMETER;
extern NSString* const ICON_PARAMETER;

// Instance variables
@property NSString* iconUrl;
@property NSString* content;

- (id) init;
- /* Override */ (NSString*) type;
- /* Override */ (BRBeaconAction*) newCopy;
- /* Override */ (NSUInteger) hash;

@end
