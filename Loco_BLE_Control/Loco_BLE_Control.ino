//==============================================================================================

// Add the libraries to your Arduino IDE, can be added from the inbuilt library manager

//https://github.com/Dlloydev/ESP32-ESP32S2-AnalogWrite
#include <pwmWrite.h>    // ESP32-ESP32S2-AnalogWrite

//https://github.com/bxparks/AceRoutine
#include <AceRoutine.h>  // AceRoutine
using namespace ace_routine;

#include "defaultLoco.h"
#include "remotexyConfigs.h"

//==============================================================================================
// Uncomment below options for DEBUG purposes
//#define MOTOR_DEBUG  // Debug info of DC motor driver
//#define ACCEL_DEBUG  // Visualize Acceleration with Serial Plotter

//==============================================================================================

int8_t Throttle = 0;
int8_t Direction = 0;
int8_t Light = 0;
int8_t Horn = 0;
int8_t Coupler = 0; //  Not implemented

Pwm pwm = Pwm();
//==============================================================================================
void setup() {
#ifdef ESPNOW_DEBUG || MOTOR_DEBUG || ACCEL_DEBUG
  Serial.begin(115200);
  Serial.println("Dragon Railway BLE control");
#endif

  RemoteXY_Init();                          
  pinMode(HeadLightPin, OUTPUT);
  pinMode(HeadLight2Pin, OUTPUT);
  pinMode(AuxLightPin, OUTPUT);
  CoroutineScheduler::setup();      //  Required for COROUTINE FUNCTIONS, used for non-blocking delay
}

//==============================================================================================
void loop() {
  RemoteXY_Handler();
  CoroutineScheduler::loop();
}

COROUTINE(LightControl) {
  COROUTINE_LOOP() {
    digitalWrite(AuxLightPin, (RemoteXY.hornBTN == 0) ? LOW : HIGH); // AUX light is currently controlled by the Horn Button

    if (RemoteXY.lightSW == 1) {
      if (Direction == 1) {
        digitalWrite(HeadLightPin, HIGH);
        digitalWrite(HeadLight2Pin, HIGH);
        digitalWrite(RearLightPin, LOW);
      }
      if (Direction == 0) {
        digitalWrite(HeadLightPin, LOW);
        digitalWrite(HeadLight2Pin, HIGH);
        digitalWrite(RearLightPin, HIGH);
      }
    } else {
      digitalWrite(HeadLightPin, LOW);
      digitalWrite(HeadLight2Pin, LOW);
      digitalWrite(RearLightPin, LOW);
      
    }
    COROUTINE_DELAY(200);  //  Read received Data 5 times/second
  }
}

COROUTINE(ConnectStatus) {
  COROUTINE_LOOP() {
    if (RemoteXY.connect_flag == 0) {
      Throttle = 0;

      bool status;
      digitalWrite(HeadPin, status);
      digitalWrite(Lpin, !status);
      digitalWrite(Rpin, !status);
      status = !status;
    }
    COROUTINE_DELAY(500);  //  Check connection 2 times/second
  }
}