// include libraries
//Current 4/19/23
#include "ClearCore.h"

// initialize pins
const int piston_analog = IO0;
const int VFD_read = A12;

// initialize some variables
int allowed_time = 2000;
int start_time = millis();
int output_i = 0;
int current_time = 0;
int vfd_analog_in = 0;
bool output_pist = false;
bool output_motor = false;
bool forward_motor = false;
int ser_int = 0;
bool change_speed = false;
bool operating = false;
int16_t reed;
int16_t oldreed;

// Initialize for comms
String incomingString;
float setForce;
float setRotation;
float setRunTime;
bool input_switcher = false;
int switcher_var;
bool test_start = false;
bool test_stop = false;
bool rotOscil = false;
float oscilTime = 0;
bool timeStop = false;
bool pistonActive = false;
bool rotateActive = false;
int T;
float startTime;
float runTime;
float lastOscil = 0;

void setup() {

  Serial.begin(9600);
  // initialize pin modes
  init_pin_modes();

  // initialize pin values
  ConnectorIO1.State(false);
  ConnectorIO2.State(false);
  ConnectorIO3.State(false);
  ConnectorIO4.State(false);
  analogWrite(piston_analog, 0, CURRENT);
  reed = false;
  oldreed = false;
  T = micros();

  
}

void loop() {

  // read input signals
  input_map();
  
  // perform operations
  operations();
  
  // output signals
  output_map();

  if (Serial.available() > 0){
    receive_comm();
  }
}
