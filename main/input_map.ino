void input_map(){
  // Read the analog signal coming from the VFD
  vfd_analog_in = analogRead(VFD_read);

  // Get current time
  current_time = millis();



  // Read the state of the reed switch
  if (ConnectorDI6.State()){
    reed = true;
  }
  else{
    reed = false;
  }

  
}
