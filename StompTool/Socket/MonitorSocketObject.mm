//
//  MonitorSocketObject.m
//  iHealthBaby
//
//  Created by Rey on 2017/8/1.
//  Copyright © 2017年 chunwei. All rights reserved.
//

#import "MonitorSocketObject.h"
#import "AppDelegate.h"



#define  WWW_PORT (8098)  // 0 => automatic
#define  WWW_HOST @"123.126.109.162"
#define CERT_HOST WWW_HOST
@implementation MonitorSocketObject
+(instancetype)shared
    {
        static MonitorSocketObject * sharedMyManager = nil;
        
        static dispatch_once_t onceToken;
        
        dispatch_once(&onceToken, ^{
            
            sharedMyManager = [[self alloc] init];
        });
        
        return sharedMyManager;
        
    }

-(void)cancelConnect{
    
    if(self.webscClient){
        [self.webscClient disconnect];
    }
}

-(void)writeData:(NSString *)str{
    if(self.webscClient){
        [_webscClient writeString:str toDestination:@"/app/sendMessage"];
    }
   
    
}
- (void)startSocket
{
    if(!_webscClient){
        _webscClient = [[JFRWebSocket alloc]initWithURL:
                        [NSURL URLWithString:@"http://xxx.xxx.xx.xxx:8098/webSocketServer"] protocols:@[@"chat",@"superchat"]];
        
        [_webscClient addHeader:@"101" forKey:@"userId"];
        [_webscClient addHeader:@"/app/sendMessage" forKey:@"destination"];

        _webscClient.delegate = self;
    }
    [_webscClient connect];


}



-(void)websocketDidConnect:(JFRWebSocket *)socket{
    NSLog(@"连接上了");
    if(self.connectCB){
        self.connectCB(1);
    }

}
-(void)websocketDidDisconnect:(JFRWebSocket *)socket error:(NSError *)error{

    NSLog(@"duankaile  %@",error);
    if(self.connectCB){
        self.connectCB(-1);
    }
}


-(void)websocket:(JFRWebSocket *)socket didReceiveMessage:(NSString *)string{
    NSLog(@"webMessage  %@",string);
}

-(void)websocket:(JFRWebSocket *)socket didReceiveData:(NSData *)data{
    NSLog(@"webRecieveData  %@",[[NSString alloc]initWithData:data encoding:NSUTF8StringEncoding]);

}



@end
