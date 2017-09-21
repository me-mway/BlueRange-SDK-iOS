//
//  BRTracer.m
//  BlueRangeSDK
//
// Copyright (c) 2016-2017, M-Way Solutions GmbH
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the M-Way Solutions GmbH nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY M-Way Solutions GmbH ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL M-Way Solutions GmbH BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#import "BRTracer.h"
#import "BRConstants.h"

@implementation BRTracer

static BOOL enabled = true;

// Singleton implementation
+ (BRTracer *) getInstance {
    static BRTracer *tracer = nil;
    @synchronized(self) {
        if (tracer == nil)
            tracer = [[self alloc] init];
    }
    return tracer;
}

+ (BOOL) isEnabled {
    return enabled;
}

+ (void) setEnabled: (BOOL) _enabled {
    enabled = _enabled;
}

- (id) init {
    if (self = [super init]) {
    }
    return self;
}

- (void) logInfoWithTag: (NSString *) tag andMessage: (NSString *) message {
    if (enabled) {
        NSString* completeLogTag = [self getCompleteLogTag:tag];
        NSLog(@"%@:%@", completeLogTag, message);
    }
}

- (void) logDebugWithTag: (NSString *) tag andMessage: (NSString *) message {
    if (enabled) {
        NSString* completeLogTag = [self getCompleteLogTag:tag];
        NSLog(@"%@:%@", completeLogTag, message);
    }
}

- (void) logWarningWithTag: (NSString *) tag andMessage: (NSString *) message {
    if (enabled) {
        NSString* completeLogTag = [self getCompleteLogTag:tag];
        NSLog(@"%@:%@", completeLogTag, message);
    }
}

- (void) logErrorWithTag: (NSString *) tag andMessage: (NSString *) message {
    if (enabled) {
        NSString* completeLogTag = [self getCompleteLogTag:tag];
        NSLog(@"%@:%@", completeLogTag, message);
    }
}

- (NSString*) getCompleteLogTag: (NSString*) logTag {
     NSString *completeLogTag = [NSString stringWithFormat:@"%@:%@", TAG, logTag];
    return completeLogTag;
}

@end
