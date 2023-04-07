void output_map(){

  // Set the piston to up or down
  ConnectorIO1.State(output_pist);

  // Turn the rotation motor on or off
  ConnectorIO3.State(output_motor);

  // Change the direction of rotation of the rotation motor
  ConnectorIO2.State(forward_motor);
  
  // If it is told to, change the speed of the vibration motor
  if (change_speed){
    analogWrite(VFD_analog, ser_int, CURRENT);
    change_speed = !change_speed;
  }

  
//  output_i = 2047;
//  if (millis()- start_time < 20000){
//    analogWrite(VFD_analog, output_i, CURRENT);
//    Serial.print(vfd_analog_in);
//    Serial.print(",");
//    Serial.print(output_i);
//    Serial.println(",");
//  }
//  else{
//    analogWrite(VFD_analog, 0, CURRENT);
//  }



  // analogWrite(VFD_analog, 2047, CURRENT); // 26.7 Hz value here can take a range of 410 to 2047. This corresponds to 4-20 mA output
}
