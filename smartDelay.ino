static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    // If data has come in from the GPS module
    while (gps.available())
      tinyGPS.encode(gps.read()); // Send it to the encode function
  // tinyGPS.encode(char) continues to "load" the tinGPS object with new
  // data coming in from the GPS module. As full NMEA strings begin to come in
  // the tinyGPS library will be able to start parsing them for pertinent info
  } while (millis() - start < ms);
}
