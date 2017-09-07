//
//  MonitorSocketObject.h
//  iHealthBaby
//
//  Created by Rey on 2017/8/1.
//  Copyright © 2017年 chunwei. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JFRWebSocket.h"
//@class GCDAsyncSocket;
@interface MonitorSocketObject : NSObject<JFRWebSocketDelegate>
@property (nonatomic,strong)JFRWebSocket *webscClient;

@property (nonatomic,copy) void(^connectCB)(NSInteger status);
+(instancetype)shared;
- (void)startSocket;
-(void)cancelConnect;
-(void)writeData:(NSString *)str;
@end
