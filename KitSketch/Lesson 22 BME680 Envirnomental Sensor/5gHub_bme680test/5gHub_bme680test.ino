/*

  Copyright 2021, 5G HUB

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
  associated documentation files (the "Software"), to deal in the Software without restriction, including
  without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the
  following conditions:

  The above copyright notice and this permission notice shall be included in all copies or substantial
  portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
  TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.

*/

#include <STM32_board.h>

#define SEALEVELPRESSURE_HPA (1013.25)

// Using I2C Interface
_5GHUB_BME680 bme; 

void setup() 
{

  Wire.setSDA(PB11);
  Wire.setSCL(PB10);


  Serial.begin(115200);
  while (Serial.read() >= 0);
  Serial.println(F("BME680 async test"));

  if (!bme.Begin()) 
  {
    Serial.println(F("BME680 sensor can not be found. Check again!"));
    while (1);
  }

  // Configure BME680 oversampling and filter
  bme.SetTemperatureOversampling(BME680_OS_8X);
  bme.SetHumidityOversampling(BME680_OS_2X);
  bme.SetPressureOversampling(BME680_OS_4X);
  bme.SetIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.SetGasHeater(320, 150); // 320*C for 150 ms
}

void loop() 
{
  if (!bme.PerformReading()) 
  {
    Serial.println("Failed to perform reading :(");
    return;
  }
  Serial.print("Temperature = ");
  Serial.print(bme.temperature);
  Serial.println(" C");

  Serial.print("Humidity = ");
  Serial.print(bme.humidity);
  Serial.println(" %");
  
  Serial.print("Pressure = ");
  Serial.print(bme.pressure / 100.0);
  Serial.println(" hPa");

  Serial.print("Gas = ");
  Serial.print(bme.gas_resistance / 1000.0);
  Serial.println(" Kohms");

  Serial.print("Altitude = ");
  Serial.print(bme.ReadAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.println();
  delay(2000);
}
