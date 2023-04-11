// include libraries
#include "ClearCore.h"

// initialize pins
const int VFD_analog = IO0;
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
int16_t reed;
int16_t oldreed;

// Initialize for comms
String incomingString;
float setForce;
float setRotation;
float setRunTime;
bool input_switcher = false;
int switcher_var;
bool test_start  false;
bool test_stop = false;

float freqResults[];
float forceResults[];
float heightResults[];
float timeResults[];

// initialize time variables
int T = micros();
int startTime;


void setup() {

  Serial.begin(9600);
  // initialize pin modes
  init_pin_modes();

  // initialize pin values
  ConnectorIO1.State(false);
  ConnectorIO2.State(false);
  ConnectorIO3.State(false);
  analogWrite(VFD_analog, 0, CURRENT);
  reed = false;
  oldreed = false;

  
}

void loop() {
  Serial.println("1 => Flip piston");
  Serial.println("69 => Flip motor");
  Serial.println("70 => Forward motor");
  Serial.print("Else change piston force");
  // read input signals
  input_map();
  
  // perform operations
  operations();
  
  // output signals
  output_map();

  if (Serial.available > 0){
    receive_comm();
  }
}
