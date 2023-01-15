int16_t TargetSpeed = 0;
int16_t CurrentSpeed = 0;
int16_t Difference = 0;

//==============================================================================================

COROUTINE(MotorDriver) {
  COROUTINE_LOOP() {

#ifdef HbridgeA
    uint16_t MinDuty = pow(2, PwmResolution) * MinPwm / 100;
    uint16_t MaxDuty = (pow(2, PwmResolution) * MaxPwm / 100 - 1);

    uint16_t Mduty = map(CurrentSpeed, 0, 10000, MinDuty, MaxDuty);
    Mduty = constrain(Mduty, MinDuty, MaxDuty);


    if (CurrentSpeed == 0) {
      Mduty = 0;
      pwm.write(MotorA2, 0, PwmFrequency, PwmResolution);
      pwm.write(MotorA1, 0, PwmFrequency, PwmResolution);
    } else {
      if (Direction > 0) {
        pwm.write(MotorA1, Mduty, PwmFrequency, PwmResolution);
        pwm.write(MotorA2, 0, PwmFrequency, PwmResolution);
      }
      if (Direction < 1) {
        pwm.write(MotorA1, 0, PwmFrequency, PwmResolution);
        pwm.write(MotorA2, Mduty, PwmFrequency, PwmResolution);
      }
    }
#ifdef MOTOR_DEBUG
    Serial.print("MotorControl    Speed:");
    Serial.print(CurrentSpeed);
    Serial.print("    Direction:");
    Serial.print(Direction);
    Serial.print("    PWM:");
    Serial.println(Mduty);
#endif
#endif
    COROUTINE_DELAY(10);
  }
}
//==============================================================================================
COROUTINE(RecvUpdate) {
  COROUTINE_LOOP() {

    Throttle = RemoteXY.speedSlider;
    TargetSpeed = map(Throttle, 0, 100, 0, 10000);

    Direction = RemoteXY.dirSW;
    Light = RemoteXY.lightSW;
    Horn = RemoteXY.hornBTN;
    // add coupler if needed

    COROUTINE_DELAY(100);  //  Read received Data 10 times/second
  }
}


COROUTINE(AccelControl) {
  COROUTINE_LOOP() {
    Difference = TargetSpeed - CurrentSpeed;

    if (TargetSpeed != CurrentSpeed) {
      if (TargetSpeed > CurrentSpeed) {
        CurrentSpeed = CurrentSpeed + (LocoAcc * 10 + abs(Difference) * LocoAcc / 500.0) / LocoInertia;
        CurrentSpeed = constrain(CurrentSpeed, 0, TargetSpeed);
      }
      if (TargetSpeed < CurrentSpeed) {
        CurrentSpeed = CurrentSpeed - (LocoDec + (abs(Difference) * LocoDec / 100.0)) / LocoInertia;
        CurrentSpeed = constrain(CurrentSpeed, TargetSpeed, 10000);
      }
    }

#ifdef ACCEL_DEBUG
    Serial.print(0);
    Serial.print("    TargetSpeed:");
    Serial.print(TargetSpeed);
    Serial.print("    CurrentSpeed:");
    Serial.print(CurrentSpeed);
    Serial.print("               Use SerialPlotter- Mx:");
    Serial.print(10000);
    Serial.print(" Mn:");
    Serial.println(0);
#endif

    COROUTINE_DELAY(10);
  }
}
//==============================================================================================