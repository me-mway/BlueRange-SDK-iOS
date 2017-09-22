//
//  BRIBeaconMessageScanner.h
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
#import "BRBeaconMessageStreamNode.h"

@class BRBeaconMessageScannerConfig;

/**
 * This interface defines the specification of a beacon message scanner. In terms of the message
 * processing architecture, a scanner acts as a source of messages. Therefore, a scanner has no
 * senders but might have one or more receivers.
 */
@interface BRIBeaconMessageScanner : BRBeaconMessageStreamNode

- (void) setConfig: (BRBeaconMessageScannerConfig*) config;
- (BRBeaconMessageScannerConfig *) config;

- (BOOL) running;
- (void) startScanning;
- (void) stopScanning;

@end
