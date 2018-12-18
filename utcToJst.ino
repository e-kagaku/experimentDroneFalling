/*
 * Convert UTC time to JST time
*/

String utcToJst(int utcDay, int utcHour){
  int jstDay = 0;
  int jstHour = 0;
  String jstData;

  if(utcHour+9 < 24){
    jstDay = utcDay;
    jstHour = utcHour+9;    
  }
  else{
    jstDay = utcDay + 1;
    jstHour = utcHour - 15;
  }

  jstData = String(jstDay) + "_" +  String(jstHour);
  return jstData;
  
  }
