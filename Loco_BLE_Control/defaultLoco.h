//==============================================================================================

//    LOCOMOTIVE CONFIG

//  Engine Inertia
#define LocoInertia 2       //  HighSpeed Metro trains: 2, Sluggish Frieght Trains: 8

#define LocoAcc 5           //  Fine Tune Acceleration/Deceleration
#define LocoDec 5

//    Driver Settings
#define HbridgeA            // H bridge is used to control the N20 motors in the bogies

#define MinPwm 0            // Set Min & Max DutyCycle (in Percentage) for motor driver
#define MaxPwm 100          

#define PwmFrequency 200    // Set PWM Frequency, Higher frequencies (like 20khz) can be silent but inefficient
#define PwmResolution 10    // Set PWM Resolution (8-12); 10 is optimal

//  RemoteXY connection settings
#define REMOTEXY_BLUETOOTH_NAME "BLE Loco"
#define REMOTEXY_ACCESS_PASSWORD "1234"

//==============================================================================================

//    PIN CONFIGS
// Refer: https://randomnerdtutorials.com/esp32-pinout-reference-gpios/

// Light Pins
#define HeadLightPin 12        // Headlight
#define HeadLight2Pin 14       // Secondary headlight (Top Headlight, only present in F7 loco)

#define RearLight 27           // Rearlight

#define AuxLightPin 26         // Extra light (rear lights are available in GP7 loco)


// H bridges
#define MotorA1 33             // H bridge pins
#define MotorA2 32             // L293 and compatible H bridges are supported

//==============================================================================================