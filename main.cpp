////
////  main.cpp
////  UrgTest
////
////  Created by 郭龙 on 16/6/22.
////  Copyright © 2016年 690193240@qq.com. All rights reserved.
////
//
////#include <iostream>
//
////int main(int argc, const char * argv[]) {
////    // insert code here...
////    std::cout << "Hello, World!\n";
////    return 0;
////}
//
//#include <stdio.h>
//#include <fcntl.h>
//#include "URG04LX2.hpp"
//
//static const char * DEVICE = "/dev/cu.usbmodem1411";
////static const char * DEVICE = "/dev/ttyACM0";
//
//static const int    NITER  = 20;
//
//int main()
//{
//
////    int op = open(DEVICE, O_RDWR | O_NOCTTY);
////    if (op < 0) {
////        printf("open failed: %d\n",op);
////    }else
////        printf("open success");
//    
//    URG04LX2 laser;
//    
//    cout << "===============================================================" << endl;
//    laser.connect(DEVICE, 115200);
//    cout << "===============================================================" << endl;
//    cout << laser << endl;
//    cout << "===============================================================" << endl;
//    
//    for (int i=1;i<=NITER;i++)
//    {
//        int data[1000];
//        
//        int ndata = laser.getScan(data);
//        
//        printf("Iteration: %3d: ", i);
//        
//        if (i == 1) {
//            for (int j = 0; j < ndata; j++) {
//                printf("%d,",data[j]);
//            }
//        }
//        
//        if (ndata)
//        {
//            printf("got %3d data points\n", ndata);
//        }
//        else
//        {
//            printf("=== SCAN FAILED ===\n");
//        }
//    }
//    
//    //laser.~URG04LX();
//    
//    return 0;
//}
