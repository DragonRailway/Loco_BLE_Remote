/*
   -- Loco_BLE --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.8 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.11.1 or later version;
     - for iOS 1.9.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP32CORE_BLE
#include <BLEDevice.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_BLUETOOTH_NAME "Train Control"
#define REMOTEXY_ACCESS_PASSWORD "1234"


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 81 bytes
  { 255,4,0,0,0,74,0,16,172,1,4,0,39,17,14,71,79,111,2,1,
  4,76,26,12,173,79,16,31,62,0,60,0,10,114,9,26,13,12,95,160,
  76,76,105,103,104,116,0,31,1,1,9,50,13,13,188,31,72,111,114,110,
  0,129,0,13,7,37,6,31,76,111,99,111,32,67,111,110,116,114,111,108,
  0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  int8_t speedSlider; // =0..100 slider position 
  uint8_t dirSW; // =1 if switch ON and =0 if OFF 
  uint8_t lightSW; // =1 if state is ON, else =0 
  uint8_t hornBTN; // =1 if button pressed, else =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)
