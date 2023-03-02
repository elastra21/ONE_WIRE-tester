#include <M5Core2.h>
#include <OneWire.h>
#include <DallasTemperature.h>

void printAddress(DeviceAddress deviceAddress);
void printTemperature(DeviceAddress deviceAddress);

#define ONE_WIRE_BUS 33

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

DeviceAddress Thermometer;

int deviceCount = 0; 

void setup(void){
  Serial.begin(115200);
  M5.begin();
  M5.Lcd.begin();
  M5.Lcd.setTextSize(1);
  M5.Lcd.setFreeFont(&FreeMono9pt7b);
  M5.Lcd.setCursor(0,20);

  // Start up the library
  sensors.begin();
  // locate devices on the bus
  M5.Lcd.println("Locating devices...");
  M5.Lcd.print("Found ");
  deviceCount = sensors.getDeviceCount();
  M5.Lcd.print(deviceCount, DEC);
  M5.Lcd.println(" devices.");
  M5.Lcd.println("");
  
  M5.Lcd.println("Printing addresses...");
  for (int i = 0;  i < deviceCount;  i++)
  {
    M5.Lcd.print("Sensor ");
    M5.Lcd.print(i+1);
    M5.Lcd.println(" : ");
    sensors.getAddress(Thermometer, i);
  }

  
}

void loop(void){
  printAddress(Thermometer);
  printTemperature(Thermometer); // Index 1 cause we have only one sensor
  sleep(10);
  ESP.restart();
}

void printAddress(DeviceAddress deviceAddress)
{
  M5.lcd.setFreeFont(&FreeMono12pt7b); 
  M5.Lcd.println("");
  for (uint8_t i = 0; i < 8; i++)
  { 
    M5.Lcd.print("0x");
    if (deviceAddress[i] < 0x10) m5.Lcd.print("0");
    M5.Lcd.print(deviceAddress[i], HEX);
    if (i < 7) M5.Lcd.print(", ");
  }
  M5.Lcd.println("");
}

void printTemperature(DeviceAddress deviceAddress)
{
  sensors.requestTemperatures();
  M5.lcd.setFreeFont(&FreeMono12pt7b);
  M5.Lcd.println(""); 
  float tempC = sensors.getTempC(deviceAddress);
  M5.Lcd.print(tempC);
  M5.Lcd.print((char)176);
  M5.Lcd.print(" degC");
 
}
