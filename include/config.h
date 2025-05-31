#define X_PIN 9     // pin controlling the X servo
#define Y_PIN 10    // pin controlling the Y servo

#define X_MIN 544   // calibrate the min/max for your servos
#define X_MAX 2400  // default min is 544, max is 2400
#define Y_MIN 544   // 500-2500 is probably close to the limit
#define Y_MAX 2400  // make sure the servos dont hit endstop

#define EL_MIN 20   // limit the minimum elevation, angle up from horizontal
#define SPEED 20    // maximum moving speed, speed commands can limit this further
