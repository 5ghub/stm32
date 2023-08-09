/* TSL2591 Digital Light Sensor */
/* Dynamic Range: 600M:1 */
/* Maximum Lux: 88K */


#include <STM32_board.h>

_5GHUB_TSL25911 tsl = _5GHUB_TSL25911(25911); // pass in a number for the sensor identifier (for your use later)

//**************************************************************************/
//    Displays basic information 
//**************************************************************************/

void DisplaySensorDetails(void)
{
  sensor_t sensor;
  tsl.GetSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.print  (F("Sensor:     ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver: ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:  ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:  ")); Serial.print(sensor.max_value); Serial.println(F(" lux"));
  Serial.print  (F("Min Value:  ")); Serial.print(sensor.min_value); Serial.println(F(" lux"));
  Serial.print  (F("Resolution: ")); Serial.print(sensor.resolution, 4); Serial.println(F(" lux"));  
  Serial.println(F("------------------------------------"));
  Serial.println(F(""));
  delay(1000);
}

///**************************************************************************/
//
//    Configures the gain and integration time for the TSL2591
//
//**************************************************************************/
void ConfigureSensor(void)
{
  // You can change the gain on the fly, to adapt to brighter/dimmer light situations
  
  //tsl.SetGain(TSL2591_GAIN_LOW);    // 1x gain (bright light)
  tsl.SetGain(TSL25911_GAIN_MED);      // 25x gain
  //tsl.SetGain(TSL25911_GAIN_HIGH);   // 428x gain
  
  // Changing the integration time gives you a longer time over which to sense light
  // longer timelines are slower, but are good in very low light situtations!
  // shortest integration time (bright light)
  
  //tsl.SetTiming(TSL25911_INTEGRATIONTIME_100MS);  
  // tsl.SetTiming(TSL25911_INTEGRATIONTIME_200MS);
  tsl.SetTiming(TSL25911_INTEGRATIONTIME_300MS);
  // tsl.SetTiming(TSL25911_INTEGRATIONTIME_400MS);
  // tsl.SetTiming(TSL25911_INTEGRATIONTIME_500MS);
  // tsl.SetTiming(TSL25911_INTEGRATIONTIME_600MS);  // longest integration time (dim light)

  // Display the gain and integration time for reference sake 
  Serial.println(F("------------------------------------"));
  Serial.print  (F("Gain:         "));
  tsl25911Gain_t gain = tsl.GetGain();
  
  switch(gain)
  {
    case TSL25911_GAIN_LOW:
      Serial.println(F("1x (Low)"));
      break;
    case TSL25911_GAIN_MED:
      Serial.println(F("25x (Medium)"));
      break;
    case TSL25911_GAIN_HIGH:
      Serial.println(F("428x (High)"));
      break;
    case TSL25911_GAIN_MAX:
      Serial.println(F("9876x (Max)"));
      break;
  }
  Serial.print  (F("Timing:       "));
  Serial.print((tsl.GetTiming() + 1) * 100, DEC); 
  Serial.println(F(" ms"));
  Serial.println(F("------------------------------------"));
  Serial.println(F(""));
}

//**************************************************************************/
//    Shows how to perform a basic read on visible, full spectrum or
//    infrared light (returns raw 16-bit ADC values)
//**************************************************************************/
void BasicRead(void)
{
  // Simple data read example. Just read the infrared, fullspecrtrum diode 
  // or 'visible' (difference between the two) channels.
  // This can take 100-600 milliseconds! Uncomment whichever of the following you want to read
  
  uint16_t x = tsl.GetLuminosity(TSL25911_VISIBLE);
  //uint16_t x = tsl.GetLuminosity(TSL25911_FULLSPECTRUM);
  //uint16_t x = tsl.GetLuminosity(TSL25911_INFRARED);

  Serial.print(F("[ ")); Serial.print(millis()); Serial.print(F(" ms ] "));
  Serial.print(F("Luminosity: "));
  Serial.println(x, DEC);
}

//**************************************************************************/
//    Show how to read IR and Full Spectrum at once and convert to lux
//**************************************************************************/
void AdvancedRead(void)
{
  // More advanced data read example. Read 32 bits with top 16 bits IR, bottom 16 bits full spectrum
  // That way you can do whatever math and comparisons you want!
  uint32_t lum = tsl.GetFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;
  Serial.print(F("[ ")); Serial.print(millis()); Serial.print(F(" ms ] "));
  Serial.print(F("IR: ")); Serial.print(ir);  Serial.print(F("  "));
  Serial.print(F("Full: ")); Serial.print(full); Serial.print(F("  "));
  Serial.print(F("Visible: ")); Serial.print(full - ir); Serial.print(F("  "));
  Serial.print(F("Lux: ")); Serial.println(tsl.CalculateLux(full, ir), 6);
}

void setup(void) 
{
  Wire.setSDA(PB11);
  Wire.setSCL(PB10);

  Serial.begin(115200);
  while (Serial.read() >= 0);
  
  delay(3000);
  Serial.println(F("TSL25911 test"));
    
  if (tsl.Begin()) 
  {
    Serial.println(F("Found a TSL25911 sensor"));
  } 
  else 
  {
    Serial.println(F("No sensor found ... check your wiring?"));
    while (1);
  }
    
  DisplaySensorDetails();
  
  ConfigureSensor();
}

void loop(void) 
{ 
  AdvancedRead();
  
  delay(500);
}
