/**************************************************************************/
/*! 
 @file     Adafruit_TSL2591.h
 @author   KT0WN (adafruit.com)
 
 This is a library for the Adafruit TSL2591 breakout board
 This library works with the Adafruit TSL2591 breakout 
 ----> https://www.adafruit.com/products/1980
 	
 Check out the links above for our tutorials and wiring diagrams 
 These chips use I2C to communicate
 
 Adafruit invests time and resources providing this open source code, 
 please support Adafruit and open-source hardware by purchasing 
 products from Adafruit!
 
 @section LICENSE
 
 Software License Agreement (BSD License)
 
 Copyright (c) 2014 Adafruit Industries
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 1. Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 3. Neither the name of the copyright holders nor the
 names of its contributors may be used to endorse or promote products
 derived from this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
 EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**************************************************************************/

#ifndef _TSL2591_H_
#define _TSL2591_H_

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <Adafruit_Sensor.h>
//#include <Wire.h>

#define TSL2591_VISIBLE           (2)       // channel 0 - channel 1
#define TSL2591_INFRARED          (1)       // channel 1
#define TSL2591_FULLSPECTRUM      (0)       // channel 0

#define TSL2591_ADDR              (0x52)
#define TSL2591_READBIT           (0x01)

#define TSL2591_COMMAND_BIT       (0xA0)    // 1010 0000: bits 7 and 5 for 'command normal'
#define TSL2591_CLEAR_INT         (0xE7)
#define TSL2591_TEST_INT          (0xE4)
#define TSL2591_WORD_BIT          (0x20)    // 1 = read/write word (rather than byte)
#define TSL2591_BLOCK_BIT         (0x10)    // 1 = using block read/write

#define TSL2591_ENABLE_POWEROFF   (0x00)
#define TSL2591_ENABLE_POWERON    (0x01)
#define TSL2591_ENABLE_AEN        (0x02)    // ALS Enable. This field activates ALS function. Writing a one activates the ALS. Writing a zero disables the ALS.
#define TSL2591_ENABLE_AIEN       (0x10)    // ALS Interrupt Enable. When asserted permits ALS interrupts to be generated, subject to the persist filter.
#define TSL2591_ENABLE_NPIEN      (0x80)    // No Persist Interrupt Enable. When asserted NP Threshold conditions will generate an interrupt, bypassing the persist filter

#define TSL2591_LUX_DF            (408.0F)
#define TSL2591_LUX_COEFB         (1.64F)  // CH0 coefficient 
#define TSL2591_LUX_COEFC         (0.59F)  // CH1 coefficient A
#define TSL2591_LUX_COEFD         (0.86F)  // CH2 coefficient B

enum
{
  TSL2591_REGISTER_ENABLE             = 0x00,
  TSL2591_REGISTER_CONTROL            = 0x01,
  TSL2591_REGISTER_THRESHOLD_AILTL    = 0x04, // ALS low threshold lower byte
  TSL2591_REGISTER_THRESHOLD_AILTH    = 0x05, // ALS low threshold upper byte
  TSL2591_REGISTER_THRESHOLD_AIHTL    = 0x06, // ALS high threshold lower byte
  TSL2591_REGISTER_THRESHOLD_AIHTH    = 0x07, // ALS high threshold upper byte
  TSL2591_REGISTER_THRESHOLD_NPAILTL  = 0x08, // No Persist ALS low threshold lower byte
  TSL2591_REGISTER_THRESHOLD_NPAILTH  = 0x09, // etc
  TSL2591_REGISTER_THRESHOLD_NPAIHTL  = 0x0A,
  TSL2591_REGISTER_THRESHOLD_NPAIHTH  = 0x0B,
  TSL2591_REGISTER_PERSIST_FILTER     = 0x0C,
  TSL2591_REGISTER_PACKAGE_PID        = 0x11,
  TSL2591_REGISTER_DEVICE_ID          = 0x12,
  TSL2591_REGISTER_DEVICE_STATUS      = 0x13,
  TSL2591_REGISTER_CHAN0_LOW          = 0x14,
  TSL2591_REGISTER_CHAN0_HIGH         = 0x15,
  TSL2591_REGISTER_CHAN1_LOW          = 0x16,
  TSL2591_REGISTER_CHAN1_HIGH         = 0x17
};

typedef enum
{
  TSL2591_INTEGRATIONTIME_100MS     = 0x00,
  TSL2591_INTEGRATIONTIME_200MS     = 0x01,
  TSL2591_INTEGRATIONTIME_300MS     = 0x02,
  TSL2591_INTEGRATIONTIME_400MS     = 0x03,
  TSL2591_INTEGRATIONTIME_500MS     = 0x04,
  TSL2591_INTEGRATIONTIME_600MS     = 0x05,
}
tsl2591IntegrationTime_t;

typedef enum
{
  //  bit 7:4: 0
  TSL2591_PERSIST_EVERY             = 0x00, // Every ALS cycle generates an interrupt
  TSL2591_PERSIST_ANY               = 0x01, // Any value outside of threshold range
  TSL2591_PERSIST_2                 = 0x02, // 2 consecutive values out of range
  TSL2591_PERSIST_3                 = 0x03, // 3 consecutive values out of range
  TSL2591_PERSIST_5                 = 0x04, // 5 consecutive values out of range
  TSL2591_PERSIST_10                = 0x05, // 10 consecutive values out of range
  TSL2591_PERSIST_15                = 0x06, // 15 consecutive values out of range
  TSL2591_PERSIST_20                = 0x07, // 20 consecutive values out of range
  TSL2591_PERSIST_25                = 0x08, // 25 consecutive values out of range
  TSL2591_PERSIST_30                = 0x09, // 30 consecutive values out of range
  TSL2591_PERSIST_35                = 0x0A, // 35 consecutive values out of range
  TSL2591_PERSIST_40                = 0x0B, // 40 consecutive values out of range
  TSL2591_PERSIST_45                = 0x0C, // 45 consecutive values out of range
  TSL2591_PERSIST_50                = 0x0D, // 50 consecutive values out of range
  TSL2591_PERSIST_55                = 0x0E, // 55 consecutive values out of range
  TSL2591_PERSIST_60                = 0x0F, // 60 consecutive values out of range
}
tsl2591Persist_t;

typedef enum
{
  TSL2591_GAIN_LOW                  = 0x00,    // low gain (1x)
  TSL2591_GAIN_MED                  = 0x10,    // medium gain (25x)
  TSL2591_GAIN_HIGH                 = 0x20,    // medium gain (428x)
  TSL2591_GAIN_MAX                  = 0x30,    // max gain (9876x)
}
tsl2591Gain_t;

class Adafruit_TSL2591 : public Adafruit_Sensor
{
 public:
  Adafruit_TSL2591(int32_t sensorID = -1);
  
  boolean   begin   ( void );
  void      enable  ( void );
  void      disable ( void );
  void      write8  ( uint8_t r);
  void      write8  ( uint8_t r, uint8_t v );
  uint16_t  read16  ( uint8_t reg );
  uint8_t   read8   ( uint8_t reg );

  uint32_t  calculateLux  ( uint16_t ch0, uint16_t ch1 );
  void      setGain       ( tsl2591Gain_t gain );
  void      setTiming     ( tsl2591IntegrationTime_t integration );
  uint16_t  getLuminosity (uint8_t channel );
  uint32_t  getFullLuminosity ( );

  tsl2591IntegrationTime_t getTiming();
  tsl2591Gain_t            getGain();

  // Interrupt
  void    clearInterrupt(void);
  void    registerInterrupt(uint16_t lowerThreshold, uint16_t upperThreshold);
  void    registerInterrupt(uint16_t lowerThreshold, uint16_t upperThreshold, tsl2591Persist_t persist);
  uint8_t getStatus();
  
  /* Unified Sensor API Functions */  
  bool getEvent  ( sensors_event_t* );
  void getSensor ( sensor_t* );

 private:
  tsl2591IntegrationTime_t _integration;
  tsl2591Gain_t _gain;
  int32_t _sensorID;

  boolean _initialized;
};
#endif

/**************************************************************************/
/*! 
 @file     Adafruit_TSL2591.cpp
 @author   KT0WN (adafruit.com)
 
 This is a library for the Adafruit TSL2591 breakout board
 This library works with the Adafruit TSL2591 breakout 
 ----> https://www.adafruit.com/products/1980
 	
 Check out the links above for our tutorials and wiring diagrams 
 These chips use I2C to communicate
 	
 Adafruit invests time and resources providing this open source code, 
 please support Adafruit and open-source hardware by purchasing 
 products from Adafruit!
 
 @section LICENSE
 
 Software License Agreement (BSD License)
 
 Copyright (c) 2014 Adafruit Industries
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 1. Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 3. Neither the name of the copyright holders nor the
 names of its contributors may be used to endorse or promote products
 derived from this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
 EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**************************************************************************/
#if defined(ESP8266)
#include <pgmspace.h>
#else
#include <avr/pgmspace.h>
#endif
#if defined(__AVR__)
#include <util/delay.h>
#endif
#include <stdlib.h>

Adafruit_TSL2591::Adafruit_TSL2591(int32_t sensorID) 
{
  _initialized = false;
  _integration = TSL2591_INTEGRATIONTIME_100MS;
  _gain        = TSL2591_GAIN_MED;
  _sensorID    = sensorID;

  // we cant do wire initialization till later, because we havent loaded Wire yet
}

boolean Adafruit_TSL2591::begin(void) 
{
  //Wire.begin();
  i2c_init();
  /*
  for (uint8_t i=0; i<0x20; i++) 
   {
   uint8_t id = read8(0x12);
   Serial.print("$"); Serial.print(i, HEX); 
   Serial.print(" = 0x"); Serial.println(read8(i), HEX);
   }
*/
  uint8_t id = read8(0x12);
  if (id == 0x50 ) 
  {
//    Serial.println("Found Adafruit_TSL2591");
  } 
  else 
  {
    return false;
  }

  _initialized = true;

  // Set default integration time and gain
  setTiming(_integration);
  setGain(_gain);

  // Note: by default, the device is in power down mode on bootup
  disable();

  return true;
}

void Adafruit_TSL2591::enable(void)
{
  if (!_initialized)
  {
    if (!begin())
    {
      return;
    }
  }

  // Enable the device by setting the control bit to 0x01
  write8(TSL2591_COMMAND_BIT | TSL2591_REGISTER_ENABLE, TSL2591_ENABLE_POWERON | TSL2591_ENABLE_AEN | TSL2591_ENABLE_AIEN);
}

void Adafruit_TSL2591::disable(void)
{
  if (!_initialized)
  {
    if (!begin())
    {
      return;
    }
  }

  // Disable the device by setting the control bit to 0x00
  write8(TSL2591_COMMAND_BIT | TSL2591_REGISTER_ENABLE, TSL2591_ENABLE_POWEROFF);
}

void Adafruit_TSL2591::setGain(tsl2591Gain_t gain) 
{
  if (!_initialized)
  {
    if (!begin())
    {
      return;
    }
  }

  enable();
  _gain = gain;
  write8(TSL2591_COMMAND_BIT | TSL2591_REGISTER_CONTROL, _integration | _gain);  
  disable();
}

tsl2591Gain_t Adafruit_TSL2591::getGain()
{
  return _gain;
}

void Adafruit_TSL2591::setTiming(tsl2591IntegrationTime_t integration)
{
  if (!_initialized)
  {
    if (!begin())
    {
      return;
    }
  }

  enable();
  _integration = integration;
  write8(TSL2591_COMMAND_BIT | TSL2591_REGISTER_CONTROL, _integration | _gain);  
  disable();
}

tsl2591IntegrationTime_t Adafruit_TSL2591::getTiming()
{
  return _integration;
}

uint32_t Adafruit_TSL2591::calculateLux(uint16_t ch0, uint16_t ch1)
{
  uint16_t atime, again;
  float    cpl, lux1, lux2, lux;
  uint32_t chan0, chan1;

  // Check for overflow conditions first
  if ((ch0 == 0xFFFF) | (ch1 == 0xFFFF))
  {
    // Signal an overflow
    return 0;
  }

  // Note: This algorithm is based on preliminary coefficients
  // provided by AMS and may need to be updated in the future

  switch (_integration)
  {
  case TSL2591_INTEGRATIONTIME_100MS :
    atime = 100.0F;
    break;
  case TSL2591_INTEGRATIONTIME_200MS :
    atime = 200.0F;
    break;
  case TSL2591_INTEGRATIONTIME_300MS :
    atime = 300.0F;
    break;
  case TSL2591_INTEGRATIONTIME_400MS :
    atime = 400.0F;
    break;
  case TSL2591_INTEGRATIONTIME_500MS :
    atime = 500.0F;
    break;
  case TSL2591_INTEGRATIONTIME_600MS :
    atime = 600.0F;
    break;
  default: // 100ms
    atime = 100.0F;
    break;
  }

  switch (_gain)
  {
  case TSL2591_GAIN_LOW :
    again = 1.0F;
    break;
  case TSL2591_GAIN_MED :
    again = 25.0F;
    break;
  case TSL2591_GAIN_HIGH :
    again = 428.0F;
    break;
  case TSL2591_GAIN_MAX :
    again = 9876.0F;
    break;
  default:
    again = 1.0F;
    break;
  }

  // cpl = (ATIME * AGAIN) / DF
  cpl = (atime * again) / TSL2591_LUX_DF;

  lux1 = ( (float)ch0 - (TSL2591_LUX_COEFB * (float)ch1) ) / cpl;
  lux2 = ( ( TSL2591_LUX_COEFC * (float)ch0 ) - ( TSL2591_LUX_COEFD * (float)ch1 ) ) / cpl;
  lux = lux1 > lux2 ? lux1 : lux2;

  // Alternate lux calculation
  //lux = ( (float)ch0 - ( 1.7F * (float)ch1 ) ) / cpl;

  // Signal I2C had no errors
  return (uint32_t)lux;
}

uint32_t Adafruit_TSL2591::getFullLuminosity (void)
{
  if (!_initialized)
  {
    if (!begin())
    {
      return 0;
    }
  }

  // Enable the device
  enable();

  // Wait x ms for ADC to complete
  for (uint8_t d=0; d<=_integration; d++) 
  {
    delay(120);
  }

  uint32_t x;
  x = read16(TSL2591_COMMAND_BIT | TSL2591_REGISTER_CHAN1_LOW);
  x <<= 16;
  x |= read16(TSL2591_COMMAND_BIT | TSL2591_REGISTER_CHAN0_LOW);

  disable();

  return x;
}

uint16_t Adafruit_TSL2591::getLuminosity (uint8_t channel) 
{
  uint32_t x = getFullLuminosity();

  if (channel == TSL2591_FULLSPECTRUM) 
  {
    // Reads two byte value from channel 0 (visible + infrared)
    return (x & 0xFFFF);
  } 
  else if (channel == TSL2591_INFRARED) 
  {
    // Reads two byte value from channel 1 (infrared)
    return (x >> 16);
  } 
  else if (channel == TSL2591_VISIBLE) 
  {
    // Reads all and subtracts out just the visible!
    return ( (x & 0xFFFF) - (x >> 16));
  }

  // unknown channel!
  return 0;
}

void Adafruit_TSL2591::registerInterrupt(uint16_t lowerThreshold, uint16_t upperThreshold)
{
  if (!_initialized)
  {
    if (!begin())
    {
      return;
    }
  }

  enable();
  write8(TSL2591_COMMAND_BIT | TSL2591_REGISTER_THRESHOLD_NPAILTL, lowerThreshold);
  write8(TSL2591_COMMAND_BIT | TSL2591_REGISTER_THRESHOLD_NPAILTH, lowerThreshold >> 8);
  write8(TSL2591_COMMAND_BIT | TSL2591_REGISTER_THRESHOLD_NPAIHTL, upperThreshold);
  write8(TSL2591_COMMAND_BIT | TSL2591_REGISTER_THRESHOLD_NPAIHTH, upperThreshold >> 8);
  disable();
}

void Adafruit_TSL2591::registerInterrupt(uint16_t lowerThreshold, uint16_t upperThreshold, tsl2591Persist_t persist)
{
  if (!_initialized)
  {
    if (!begin())
    {
      return;
    }
  }

  enable();
  write8(TSL2591_COMMAND_BIT | TSL2591_REGISTER_PERSIST_FILTER,  persist);
  write8(TSL2591_COMMAND_BIT | TSL2591_REGISTER_THRESHOLD_AILTL, lowerThreshold);
  write8(TSL2591_COMMAND_BIT | TSL2591_REGISTER_THRESHOLD_AILTH, lowerThreshold >> 8);
  write8(TSL2591_COMMAND_BIT | TSL2591_REGISTER_THRESHOLD_AIHTL, upperThreshold);
  write8(TSL2591_COMMAND_BIT | TSL2591_REGISTER_THRESHOLD_AIHTH, upperThreshold >> 8);
  disable();
}

void Adafruit_TSL2591::clearInterrupt()
{
  if (!_initialized)
  {
    if (!begin())
    {
      return;
    }
  }

  enable();
  write8(TSL2591_CLEAR_INT);
  disable();
}


uint8_t Adafruit_TSL2591::getStatus()
{
  if (!_initialized)
  {
    if (!begin())
    {
      return 0;
    }
  }

  // Enable the device
  enable();
  uint8_t x;
  x = read8(TSL2591_COMMAND_BIT | TSL2591_REGISTER_DEVICE_STATUS);
  disable();
  return x;
}

uint8_t Adafruit_TSL2591::read8(uint8_t reg)
{
  /*
  Wire.beginTransmission(TSL2591_ADDR);
   Wire.write(0x80 | 0x20 | reg); // command bit, normal mode
   Wire.endTransmission();
   
   Wire.requestFrom(TSL2591_ADDR, 1);
   while (! Wire.available());
   return Wire.read();
   */
  uint8_t x;

  i2c_start(TSL2591_ADDR | I2C_WRITE);
  i2c_write(0x80 | 0x20 | reg);
  i2c_rep_start(TSL2591_ADDR | I2C_READ);  
  x = i2c_read(true);
  i2c_stop();

  return(x);
}

uint16_t Adafruit_TSL2591::read16(uint8_t reg)
{
  uint16_t x; 
  uint16_t t;
  /*
  Wire.beginTransmission(TSL2591_ADDR);
   #if ARDUINO >= 100
   Wire.write(reg);
   #else
   Wire.send(reg);
   #endif
   Wire.endTransmission();
   
   Wire.requestFrom(TSL2591_ADDR, 2);
   #if ARDUINO >= 100
   t = Wire.read();
   x = Wire.read();
   #else
   t = Wire.receive();
   x = Wire.receive();
   #endif
   */
  i2c_start(TSL2591_ADDR | I2C_WRITE);
  i2c_write(reg);
  i2c_rep_start(TSL2591_ADDR | I2C_READ);  
  t = i2c_read(false);
  x = i2c_read(true);
  i2c_stop();

  x <<= 8;
  x |= t;
  return x;
}

void Adafruit_TSL2591::write8 (uint8_t reg, uint8_t value)
{
  /* 
   Wire.beginTransmission(TSL2591_ADDR);
   #if ARDUINO >= 100
   Wire.write(reg);
   Wire.write(value);
   #else
   Wire.send(reg);
   Wire.send(value);
   #endif
   Wire.endTransmission();
   */
  i2c_start(TSL2591_ADDR | I2C_WRITE);
  i2c_write(reg);
  i2c_write(value);
  i2c_stop();
}

/**************************************************************************/
/*!
    @brief  Gets the most recent sensor event
*/
/**************************************************************************/
bool Adafruit_TSL2591::getEvent(sensors_event_t *event)
{
  uint16_t ir, full;
  uint32_t lum = getFullLuminosity();
  /* Early silicon seems to have issues when there is a sudden jump in */
  /* light levels. :( To work around this for now sample the sensor 2x */
  lum = getFullLuminosity();
  ir = lum >> 16;
  full = lum & 0xFFFF;

  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = SENSOR_TYPE_LIGHT;
  event->timestamp = millis();

  /* Calculate the actual lux value */
  /* 0 = sensor overflow (too much light) */
  event->light = calculateLux(full, ir);

  return true;
}

/**************************************************************************/
/*!
    @brief  Gets the sensor_t data
*/
/**************************************************************************/
void Adafruit_TSL2591::getSensor(sensor_t *sensor)
{
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, "TSL2591", sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = 1;
  sensor->sensor_id   = _sensorID;
  sensor->type        = SENSOR_TYPE_LIGHT;
  sensor->min_delay   = 0;
  sensor->max_value   = 88000.0;
  sensor->min_value   = 0.0;
  sensor->resolution  = 1.0;
}

