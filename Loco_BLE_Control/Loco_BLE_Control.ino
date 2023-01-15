//==============================================================================================

//==============================================================================================

#include <pwmWrite.h>    //https://github.com/Dlloydev/ESP32-ESP32S2-AnalogWrite
#include <AceRoutine.h>  //https://github.com/bxparks/AceRoutine
using namespace ace_routine;

#include "boards/Test.h"
#include "defaultLoco.h"
#include "remotexyConfigs.h"

//==============================================================================================

//#define MOTOR_DEBUG  // Debug info of DC motor driver
//#define ACCEL_DEBUG  // Visualize Acceleration with Serial Plotter

//==============================================================================================

int8_t Throttle = 0;
int8_t Direction = 0;
int8_t Light = 0;
int8_t Horn = 0;
int8_t Coupler = 0;

Pwm pwm = Pwm();
//==============================================================================================
void setup() {
#ifdef ESPNOW_DEBUG || MOTOR_DEBUG || ACCEL_DEBUG
  Serial.begin(115200);
  Serial.println("Dragon Railway BLE control");
#endif

  RemoteXY_Init();

  pinMode(HeadPin, OUTPUT);
  pinMode(HeadPin2, OUTPUT);

  CoroutineScheduler::setup();
}

void loop() {
  RemoteXY_Handler();
  CoroutineScheduler::loop();
}

COROUTINE(LightControl) {
  COROUTINE_LOOP() {
    digitalWrite(HeadPin, (RemoteXY.lightSW == 0) ? LOW : HIGH);

    if (RemoteXY.lightSW == 1) {
      digitalWrite(HeadPin2, (RemoteXY.dirSW == 0) ? LOW : HIGH);
    } else {
      digitalWrite(HeadPin2, LOW);
    }
    COROUTINE_DELAY(100);  //  Read received Data 10 times/second
  }
}

COROUTINE(ConnectStatus) {
  COROUTINE_LOOP() {
    if (RemoteXY.connect_flag == 0) {
      Throttle = 0;
      
      bool status;
      digitalWrite(HeadPin, status);
      digitalWrite(HeadPin2, !status);
      status = !status;
    }
    COROUTINE_DELAY(500);  //  Read received Data 10 times/second
  }
}