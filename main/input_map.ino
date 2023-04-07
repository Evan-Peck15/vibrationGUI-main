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


  // Read from the Serial Port
//  if (Serial.available() > 0){
//  ser_int = Serial.parseInt();
//  if (ser_int == 1){
//    output_pist = !output_pist;
//  }
//  else if (ser_int == 69){
//    output_motor = !output_motor;
//  }
//  else if (ser_int == 70){
//    forward_motor = !forward_motor;
//  }
//  else{
//    change_speed = !change_speed;
//  }
//}

  // Read all data coming from the serial port
//  bool switcher = true;
//  while (Serial.available() > 0){
//    if (switcher){
//      String input_string = Serial.readStringUntil(':');
//    }
//      String input_string = Serial.readStringUntil(',');
//      Serial.print(input_string);
      
//    ser_pist = Serial.parseInt();
//    if (ser_pist == 1){
//      output_pist = !output_pist;
//    }
//  }
  
}
