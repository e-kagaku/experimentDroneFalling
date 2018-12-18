String convertUtcToJst(){
  int day1,hour1;
  String DTstring ="";
  
  day1=tinyGPS.date.day();
  hour1=tinyGPS.time.hour();
  if(hour1+9>24){
    day1=day1+1;
    hour1=hour1-15;
    }
    
  DTstring += String(tinyGPS.date.year());
  DTstring += String("/");
  DTstring += String(tinyGPS.date.month());
  DTstring += String("/");
  DTstring += String(day1);
  DTstring += String(",");
  DTstring += String(hour1);
  DTstring += String(":");
  DTstring += String(tinyGPS.time.minute());
  DTstring += String(":");
  DTstring += String(tinyGPS.time.second());

  return DTstring;
  
  }
