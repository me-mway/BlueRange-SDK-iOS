//
//  BRBeaconMessagePassingStreamNode.h
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

#import <Foundation/Foundation.h>
#import "BRBeaconMessageStreamNode.h"

/**
 * A beacon message passing stream node is a node in a message processing graph that passes the
 * incoming messages from all senders to all receivers. Before they are passed, however, an
 * instance of a subclass can override the {@link #preprocessMessage} method to modify or analyze
 * the data before passing it to its receivers. After the message has been passed to its
 * receivers, the {@link #postprocessMessage} method will be called (which can also be overridden
 * by a subclass) to do some postprocessing.
 */
@interface BRBeaconMessagePassingStreamNode : BRBeaconMessageStreamNode

- (id) init;
- (id) initWithSender:(BRBeaconMessageStreamNode *)sender;
- (id) initWithSenders:(NSArray *)senders;

// Override
- (void) onReceivedMessage: (BRBeaconMessageStreamNode *) senderNode withMessage: (BRBeaconMessage*) message;

// Protected
/**
 * This method is called right before a beacon message is passed to the receivers.
 * @param message The received message that is going to be passed to the receivers.
 */
- (void) preprocessMessage: (BRBeaconMessage*) message;

/**
 * This method is called right after a beacon message was passed to the receivers.
 * @param message The received message that was passed to the receivers.
 */
- (void) postprocessMessage: (BRBeaconMessage*) message;

@end
