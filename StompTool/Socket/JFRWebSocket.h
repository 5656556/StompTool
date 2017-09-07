/////////////////////////////////////////////////////////////////////////////
//
//  JFRWebSocket.h
//
//  Created by Austin and Dalton Cherry on 5/13/14.
//  Copyright (c) 2014 Vluxe. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import "JFRSecurity.h"

@class JFRWebSocket;

/**
 It is important to note that all the delegate methods are put back on the main thread.
 This means if you want to do some major process of the data, you need to create a background thread.
 */
@protocol JFRWebSocketDelegate <NSObject>

@optional
/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
-(void)websocketDidConnect:(nonnull JFRWebSocket*)socket;

/**
 The websocket was disconnected from its host.
 @param socket is the current socket object.
 @param error  is return an error occured to trigger the disconnect.
 */
-(void)websocketDidDisconnect:(nonnull JFRWebSocket*)socket error:(nullable NSError*)error;

/**
 The websocket got a text based message.
 @param socket is the current socket object.
 @param string is the text based data that has been returned.
 */
-(void)websocket:(nonnull JFRWebSocket*)socket didReceiveMessage:(nonnull NSString*)string;

/**
 The websocket got a binary based message.
 @param socket is the current socket object.
 @param data   is the binary based data that has been returned.
 */
-(void)websocket:(nonnull JFRWebSocket*)socket didReceiveData:(nullable NSData*)data;

@end

@interface JFRWebSocket : NSObject

@property(nonatomic,weak, nullable)id<JFRWebSocketDelegate>delegate;
@property(nonatomic, readonly, nonnull) NSURL *url;

/**
 constructor to create a new websocket.
 @param url       the host you want to connect to.
 @param protocols the websocket protocols you want to use (e.g. chat,superchat).
 @return a newly initalized websocket.
 */
- (nonnull instancetype)initWithURL:(nonnull NSURL *)url protocols:(nullable NSArray*)protocols;

/**
 connect to the host.
 */
- (void)connect;

/**
 disconnect to the host. This sends the close Connection opcode to terminate cleanly.
 */
- (void)disconnect;

/**
 write binary based data to the socket.
 @param data the binary data to write.
 */
- (void)writeData:(nonnull NSData*)data;

/**
 write text based data to the socket.
 @param string the string to write.
 */
- (void)writeString:(nonnull NSString*)string;

-(void)writeString:(nonnull NSString *)string toDestination:(nonnull NSString *)destination;


/**
 write ping to the socket.
 @param data the binary data to write (if desired).
 */
- (void)writePing:(nonnull NSData*)data;

/**
 Add a header to send along on the the HTTP connect.
 @param value the string to send
 @param key   the HTTP key name to send
 */
- (void)addHeader:(nonnull NSString*)value forKey:(nonnull NSString*)key;

/**
 returns if the socket is conneted or not.
 */
@property(nonatomic, assign, readonly)BOOL isConnected;

/**
 Enable VOIP support on the socket, so it can be used in the background for VOIP calls.
 Default setting is No.
 */
@property(nonatomic, assign)BOOL voipEnabled;

/**
 Allows connection to self signed or untrusted WebSocket connection. Useful for development.
 Default setting is No.
 */
@property(nonatomic, assign)BOOL selfSignedSSL;

/**
 Use for SSL pinning.
 */
@property(nonatomic, strong, nullable)JFRSecurity *security;

/**
 Set your own custom queue.
 Default setting is dispatch_get_main_queue.
 */
@property(nonatomic, strong, nullable)dispatch_queue_t queue;

/**
 Block property to use on connect.
 */
@property(nonatomic, strong, nullable)void (^onConnect)(void);

/**
 Block property to use on disconnect.
 */
@property(nonatomic, strong, nullable)void (^onDisconnect)(NSError*_Nullable);

/**
 Block property to use on receiving data.
 */
@property(nonatomic, strong, nullable)void (^onData)(NSData*_Nullable);

/**
 Block property to use on receiving text.
 */
@property(nonatomic, strong, nullable)void (^onText)(NSString*_Nullable);

@end
