void errorCheck(){
  if (!statusGps) {
    Serial.println("Could not find a valid GPS sensor, check wiring!");
    while (1);
  } 
  if (!statusBme) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }   
  if (!statusTherm) {
    Serial.println("Could not find a valid MLX90614 sensor, check wiring!");
    while (1);
  } 
//  if (!statusBno) {
//    Serial.println("Could not find a valid bno055 sensor, check wiring!");
//    while (1);
//  } 
  if (!statusSD){
    Serial.println("Card failed,or not present");
    while(1);
  }


  
  }
