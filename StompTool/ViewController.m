//
//  ViewController.m
//  StompTool
//
//  Created by Rey on 2017/9/7.
//  Copyright © 2017年 Rey. All rights reserved.
//

#import "ViewController.h"
#import "MonitorSocketObject.h"
@interface ViewController ()
@property (nonatomic,strong)NSMutableArray *dataArr;
@property (nonatomic,assign)BOOL canSend;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}
- (IBAction)startConnect:(id)sender {
    MonitorSocketObject *obj = [MonitorSocketObject shared];
    [obj startSocket];
    self.dataArr = [NSMutableArray array];
    obj.connectCB = ^(NSInteger status) {
        if(status == 1){
            self.canSend = YES;
        }else{
            self.canSend = NO;
        }
    };
}

- (IBAction)sendData:(id)sender {
    NSString *jStr = @"Hello world";
    [[MonitorSocketObject shared] writeData:jStr];

}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
