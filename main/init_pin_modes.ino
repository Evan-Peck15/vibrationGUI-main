void init_pin_modes(){
  
  pinMode(piston_analog, OUTPUT); // ANALOG PIN -- CONTROL VFD
  pinMode(VFD_read, INPUT); // ANALOG INPUT FROM VFD
  ConnectorIO1.Mode(Connector::OUTPUT_DIGITAL); // Digital PIN -- ENGAGE PISTON
  ConnectorIO2.Mode(Connector::OUTPUT_DIGITAL); // Digital PIN -- FORWARD ROTATION MOTOR
  ConnectorIO3.Mode(Connector::OUTPUT_DIGITAL); // Digital PIN -- ENGAGE ROTATION MOTOR
  ConnectorIO4.Mode(Connector::OUTPUT_DIGITAL); // Pressure regulator relay

}
