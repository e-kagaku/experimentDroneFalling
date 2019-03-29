
/* Outline *******************************************
 * Experiment that the robot was fallen from the drone.
 * And the robot also observes location, altitude, temperature, atitude.
*****************************************************/

/* Details *******************************************
 * I2C communication
 *  BME280 : Barometric Pressure, humidity, temperature
 *  MLX90614 : Temperature(Infrared temperature sensor)
 *  MPU9250 : Acceleration, Gyro
 *  no 9D-compass(bno055)
 * Serial communication
 *  GPS : Time, Longitude, Latitude
******************************************************/

#include <Wire.h> // I2C library

#include <Adafruit_Sensor.h> // Adafruit sensors library
#include <Adafruit_BME280.h> // BME280 library
#include <SparkFunMLX90614.h> // SparkFunMLX90614 Arduino library
//#include <Adafruit_BNO055.h> // BN055 library

#include <SoftwareSerial.h>
#include <TinyGPS++.h> // GPS library
#include <SPI.h>
#include <SD.h>

#define SEALEVELPRESSURE_HPA (1013.25)  //sea level air pressure

Adafruit_BME280 bme; // I2C
IRTherm therm; // Create an IRTherm object to interact with throughout
TinyGPSPlus tinyGPS;
SoftwareSerial gps(9,8);

const int chipSelect = 4;
bool statusBme,statusTherm,statusGps,statusSD;
String fileName;


void setup() {
/**********************************************
 * All sensors initialize and check the error.
**********************************************/
  Serial.begin(9600);
  gps.begin(9600);
  statusGps = gps.available();
  statusBme = bme.begin();
  statusSD = SD.begin(chipSelect);
  statusTherm = therm.begin(); // Initialize thermal IR sensor
  therm.setUnit(TEMP_C);
  //  status_bno055 = bno.begin();
  errorCheck;

/**********************************************
 * Set the file name and write the description in the file.
 *********************************************/
  smartDelay(1000);
  fileName = "Ts3"; // file name must be less than 8 characters.

  File dataFile = SD.open( fileName + ".txt", FILE_WRITE);
  if(dataFile){
    dataFile.println("Date,Time,Latitude,Longitude,Altitude_GPS,Altitude_BME280,Humidity,Temperature_bme,Temperature_therm,X-orientation,Y-orientation,Z-orientation");
    dataFile.close();
//    Serial.println("Time,Latitude,Longitude,Altitude_GPS,Altitude_BME280,Humidity,Temperature,X-orientation,Y-orientation,Z-orientation");
  }
  else{
    Serial.println("Why!!!!!!!!!!!");
    }
}

void loop() {
  
  smartDelay(100); // First(before the robot catch the GPS), the time is better longer than 1000ms
  therm.read();
/******************************************
 * Write the sensor information in the file
******************************************/
  File dataFile = SD.open( fileName + ".txt",FILE_WRITE);
  if(dataFile){
//    Serial.println("Now writing file");
    dataFile.print(tinyGPS.date.value()); // Date in DDMMYY format(GPS)
    dataFile.print(",");
    dataFile.print(tinyGPS.time.value()); // Time in HHMMSSCC format(GPS)
    dataFile.print(",");
    dataFile.print(tinyGPS.location.lat(),6);  // Latitude(GPS)
    dataFile.print(",");
    dataFile.print(tinyGPS.location.lng(),6);  // Longitude(GPS)
    dataFile.print(",");
    dataFile.print(tinyGPS.altitude.meters()); // Altitude(GPS)
    dataFile.print(",");
    dataFile.print(bme.readAltitude(SEALEVELPRESSURE_HPA)); // Altitude(BME280)
    dataFile.print(",");
    dataFile.print(bme.readHumidity());  // Humidity(BME280)
    dataFile.print(",");
    dataFile.print(bme.readTemperature());  // Temperature(BME280)
    dataFile.print(",");
    dataFile.print(therm.ambient()); // Temperature(MLX90614)
    dataFile.println("");
    // dataFile.print(tinyGPS.altitude.meters());  // Atitude(MPU9250)
    // dataFile.print(",");
    // dataFile.print(tinyGPS.altitude.meters());  // Atitude(MPU9250)
    // dataFile.print(",");
    // dataFile.println(tinyGPS.altitude.meters()); // Atitude(MPU9250)
  }
  dataFile.close();

/******************************************
 * Show the sensor information in Serial monitor.
******************************************/

  Serial.print(tinyGPS.date.value()); // Date in DDMMYY format(GPS)
  Serial.print(",");
  Serial.print(tinyGPS.time.value()); // Time in HHMMSSCC format(GPS)
  Serial.print(",");
  Serial.print(tinyGPS.location.lat(),6);
  Serial.print(",");
  Serial.print(tinyGPS.location.lng(),6);
  Serial.print(",");
  Serial.print(tinyGPS.altitude.meters());
  Serial.print(",");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.print(",");
  Serial.print(bme.readHumidity());
  Serial.print(",");
  Serial.print(bme.readTemperature());
  Serial.print(",");
  Serial.println(therm.ambient());

//  Serial.print(",");
//  Serial.print(tinyGPS.altitude.meters());
//  Serial.print(",");
//  Serial.print(tinyGPS.altitude.meters());
//  Serial.print(",");
//  Serial.println(tinyGPS.altitude.meters());
  Serial.print("OK!");

}
/*----------- End of main file  ---------------*/



/******************************************
 * Not used function (for debug or something)
******************************************/
// String convertUtcToJst(){
//   int day1,hour1;
//   String DTstring ="";
//
//   day1=tinyGPS.date.day();
//   hour1=tinyGPS.time.hour();
//   if(hour1+9>24){
//     day1=day1+1;
//     hour1=hour1-15;
//     }
//
//   DTstring += String(tinyGPS.date.year());
//   DTstring += String("/");
//   DTstring += String(tinyGPS.date.month());
//   DTstring += String("/");
//   DTstring += String(day1);
//   DTstring += String(",");
//   DTstring += String(hour1);
//   DTstring += String(":");
//   DTstring += String(tinyGPS.time.minute());
//   DTstring += String(":");
//   DTstring += String(tinyGPS.time.second());
//
//   return DTstring;
//
// }
/*
 * Convert UTC time to JST time
*/
//
// String utcToJst(int utcDay, int utcHour){
//   int jstDay = 0;
//   int jstHour = 0;
//   String jstData;
//
//   if(utcHour+9 < 24){
//     jstDay = utcDay;
//     jstHour = utcHour+9;
//   }
//   else{
//     jstDay = utcDay + 1;
//     jstHour = utcHour - 15;
//   }
//
//   jstData = String(jstDay) + "_" +  String(jstHour);
//   return jstData;
//
//   }
