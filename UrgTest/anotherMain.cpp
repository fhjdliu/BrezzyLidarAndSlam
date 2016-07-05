////
////  anotherMain.cpp
////  UrgTest
////
////  Created by 郭龙 on 16/6/27.
////  Copyright © 2016年 690193240@qq.com. All rights reserved.
////
//
//// SinglePositionSLAM params: gives us a nice-size map
//static const int MAP_SIZE_PIXELS        = 800;//400;//800;
//static const double MAP_SIZE_METERS     =  32;//5;//32;
//static const int SCAN_SIZE 		        = 682;
//static const char * DEVICE = "/dev/cu.usbmodem1411";
//
//// Arbitrary maximum length of line in input logfile
//#define MAXLINE 10000
//
//#include <iostream>
//#include <vector>
//using namespace std;
//
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <math.h>
//#include <time.h>
//
//#include "Position.hpp"
//#include "Laser.hpp"
//#include "WheeledRobot.hpp"
//#include "Velocities.hpp"
//#include "algorithms.hpp"
//#include "Scan.hpp"
//
//#include "URG04LX2.hpp"
//#include "MapSearchNode.hpp"
//
//// Helpers ----------------------------------------------------------------
//
//int coords2index(double x,  double y)
//{
//    return y * MAP_SIZE_PIXELS + x;
//}
//
//int mm2pix(double mm)
//{
//    return (int)(mm / (MAP_SIZE_METERS * 1000. / MAP_SIZE_PIXELS));
//}
//
//
//// Class for Mines verison of URG-04LX Lidar -----------------------------------
//
//class MinesURG04LX : public URG04LX
//{
//    
//public:
//    MinesURG04LX(void): URG04LX(
//                                70,          // detectionMargin
//                                145)         // offsetMillimeters
//    {
//    }
//};
//
//
//int main( int argc, const char** argv )
//{
//    // Bozo filter for input args
//    
////    if (argc < 3)
////    {
////        fprintf(stderr,
////                "Usage:   %s <dataset> <use_odometry> <random_seed>\n",
////                argv[0]);
////        fprintf(stderr, "Example: %s exp2 1 9999\n", argv[0]);
////        exit(1);
////    }
//    
//    // Grab input args
//    const char * dataset = "/Users/guolong/Documents/1SlamDev/BreezySLAM-master/examples/exp2";//argv[1];
//    bool use_odometry    =  0;//atoi(argv[2]) ? true : false;
//    int random_seed =  9999;//argc > 3 ? atoi(argv[3]) : 0;
//
//    // Load the Lidar and odometry data from the file
//    vector<int *> scans;
//    vector<long *> odometries;
//    
//    URG04LX2 laser2;
//    cout << "===============================================================" << endl;
//    laser2.connect(DEVICE, 115200);
//    cout << "===============================================================" << endl;
//    cout << laser2 << endl;
//    cout << "===============================================================" << endl;
//
//    // Create a byte array to receive the computed maps
//    unsigned char * mapbytes = new unsigned char[MAP_SIZE_PIXELS * MAP_SIZE_PIXELS];
//    
//    // Create SLAM object
//    MinesURG04LX laser;
//    SinglePositionSLAM * slam = random_seed ?
//    (SinglePositionSLAM*)new RMHC_SLAM(laser, MAP_SIZE_PIXELS, MAP_SIZE_METERS, random_seed) :
//    (SinglePositionSLAM*)new Deterministic_SLAM(laser, MAP_SIZE_PIXELS, MAP_SIZE_METERS);
//
//    printf("Processing with%s odometry / with%s particle filter...\n",
//        use_odometry ? "" : "out", random_seed ? "" : "out");
//    
//    // Start with an empty trajectory of positions
//    vector<double *> trajectory;
//    
//    // Loop over scans
//    int tt = 0;
//    while ( tt < 100) {
//        tt++;
//        int lidar[690] ;
//        int range = laser2.getScan(lidar);
//        
//        if (range != SCAN_SIZE) {
//            printf("Iteration: %3d: ", range);
//        }
//        
//        slam->update(lidar);
//        
//        Position position = slam->getpos();
//        //printf("%.1f_%.1f_%.1f  ", position.x_mm, position.y_mm, position.theta_degrees);
//        
//        // Add new coordinates to trajectory
//        double * v = new double[2];
//        v[0] = position.x_mm;
//        v[1] = position.y_mm;
//        trajectory.push_back(v);
//        
//        fflush(stdout);
//    }
//    
//    // Get final map
//    slam->getmap(mapbytes);
//    
//    printf("trajectory size: %d", (int)trajectory.size());
//    
//    // Put trajectory into map as black pixels
//    for (int k=0; k<(int)trajectory.size(); ++k)
//    {
//        double * v = trajectory[k];
//        int x = mm2pix(v[0]);
//        int y = mm2pix(v[1]);
//        delete v;
//        mapbytes[coords2index(x, y)] = 0;
//    }
//    
//    //A* searching the shortest path
//    vector<double *> path;
//    MapSearchNode mapSearch = MapSearchNode(mapbytes, 128);
//    path = mapSearch.StartSearching(350, 400, 550, 200);
//    if (path.size() == 0) {
//        printf("....zero path num");
//    } else {
//        printf("path num: %lu", path.size());
//        for (int k=0; k<(int)path.size(); ++k)
//        {
//            double * v = path[k];
//            int x = v[0];
//            int y = v[1];
//            delete v;
//            mapbytes[coords2index(x, y)] = 0;
//        }
//    }
//    
//    // Save map and trajectory as PGM file
//    char filename[100];
//    sprintf(filename, "/Users/guolong/Desktop/guolong.pgm");
//    printf("\nSaving map to file %s\n", filename);
//    
//    FILE * output = fopen(filename, "wt");
//    
//    if (!output) {
//        printf("connot open file");
//        exit(2);
//    }
//    
//    fprintf(output, "P2\n%d %d 255\n", MAP_SIZE_PIXELS, MAP_SIZE_PIXELS);
//    
//    for (int y=0; y<MAP_SIZE_PIXELS; y++)
//    {
//        for (int x=0; x<MAP_SIZE_PIXELS; x++)
//        {
//            fprintf(output, "%d ", mapbytes[coords2index(x, y)]);
//            //printf("%d ", mapbytes[coords2index(x, y)]);
//        }
//        fprintf(output, "\n");
//    }
//    printf("\n");
//    
//    //free maloc
//    if (random_seed)
//    {
//        delete ((RMHC_SLAM *)slam);
//    }
//    else
//    {
//        delete ((Deterministic_SLAM *)slam);
//    }
//    
//    delete[] mapbytes;
//    
//    fclose(output);
//    
//    
//    /*
//    char filename[100];
//    sprintf(filename, "/Users/guolong/Desktop/123.txt");
//    printf("\nSaving map to file %s\n", filename);
//    FILE * output = fopen(filename, "wt");
//    
//    if (!output) {
//        printf("connot open file");
//        exit(2);
//    }
//    
//    fprintf(output, "P2\n%d %d 255\n", MAP_SIZE_PIXELS, MAP_SIZE_PIXELS);
//    
//    for (int y=0; y<MAP_SIZE_PIXELS; y++)
//    {
//        for (int x=0; x<MAP_SIZE_PIXELS; x++)
//        {
//            fprintf(output, "%d ", mapbytes[coords2index(x, y)]);
//            printf("%d ", mapbytes[coords2index(x, y)]);
//        }
//        fprintf(output, "\n");
//    }
//    printf("\n");
//    fclose(output);
//    */
//    
//    return 0;
//    
//}
//
//
//
