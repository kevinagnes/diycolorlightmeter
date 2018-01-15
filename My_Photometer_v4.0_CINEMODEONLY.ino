
///////////////////////////////////////////////////
// INCLUDE||DEFINE SECTION
#include <SPI.h>                        // Library necessary                      
#include <Wire.h>                       // Library necessary
#include <Adafruit_GFX.h>               // Library for Graphics||Bitmaps||Fonts
#include <Adafruit_SSD1306.h>           // Library for (not only) the 128x64 OLED display
#include <Adafruit_Sensor.h>            // Library necessary
#include "Adafruit_TCS34725.h"
#define SCL_PORT PORTC
#define SCL_PIN 3
#define SDA_PORT PORTC
#define SDA_PIN 2
#include <SoftI2CMaster.h>
#include "Adafruit_TSL2591Soft.h"
#include <EEPROM.h>                     // Library for using the EEPROM memory
#define OLED_RESET 8                    // OLED reset pin set to digitalPin 4 // I2C ONLY
Adafruit_SSD1306 display(OLED_RESET);   // I2C ONLY
///// Constants for calibration
#define TCS34725_R_Coef 0.136
#define TCS34725_G_Coef 1.000
#define TCS34725_B_Coef -0.444
#define TCS34725_GA 1.0
#define TCS34725_DF 310.0
#define TCS34725_CT_Coef 3810.0
#define TCS34725_CT_Offset 1391.0
#define C_const 129                     // Calibration constant for the TSL2591
#define DomeMultiplier 2.17             // Multiplier when using a white translucid Dome covering the TSL2591
//#define DomeSum                       // More test required but the difference in first test was around 100K
///////////////////////////////////////////////////
// INT||FLOAT||STRING||BOOLEAN
uint8_t Rp = 2;                         // Metering button pin
uint8_t Bn1p = 3;                       // + increment button pin
uint8_t Bn2p = 4;                       // - increment button pin
uint8_t Tdisplay;                       // State of shutter speed value display (fractional, seconds, minutes)
uint8_t Tfr;
uint8_t taddr = 0;                      // Address to write tcm to EEPROM
uint8_t Am = 15;                        // Starts Photo Mode with f4
uint8_t tca;                            // Shutter angle selector
uint8_t Saddr = 1;                      // Address to write Sv to EEPROM
uint8_t Buzzer = 9;                     // Buzzer for Button confirmation
uint8_t x_vmode = 0;                    // X Position - cine/video/...
uint8_t y_vmode = 32;                   // Y Position - cine/video/...
uint8_t Astring;
uint8_t t;
uint8_t ndStop = 0;


///////////////////////////////////////////////////
float lux;                              // Lux value from TSL2591
float ct;                               // Color Temp value from TCS34725
float ISOND;
//float EV;                             // EV value for PhotoMode // not using anymore
//float Tmin;                             // Time in minutes
///////////////////////////////////////////////////
boolean Bn1;                            // + increment button state
boolean Bn2;                            // - increment button state
boolean R;                              // Metering button state
boolean ISOmode = 0;                    // ISO mode state
boolean Shuttermode = 0;                // Shutter mode state for Cine or Photo
boolean save = 0;                       // Save to EEPROM state
boolean freeze = 0;                     // Freezes the Shutter (CINE) || Aperture (Photo)
boolean State = 0;                      // Activate Shuttermode Animation
boolean Anglemode = 0 ;                 // Activate shutter angle mode at 24fps
boolean needHigh = 0 ;                  // if needHigh = 1 , High gain is applied (428x gain) and display "Hi"
boolean Overflow = 0;                   // Sensor got Saturated and Display "Overflow"
boolean NDmode = 0;
///////////////////////////////////////////////////
// ARRAYS for Cine values
int S [] = {100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600}; //ISO array
float A [] = {0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.5, 2.8, 3.2, 3.5, 4, 4.5, 5.0, 5.6, 6.3, 7.1, 8, 9, 10, 11, 13, 14, 16, 18, 20, 22, 25, 29, 32, 36, 40, 45, 51, 57, 64, 72, 80, 90}; // Aperture array
int t_cine [] = {8, 16, 24, 25, 30, 48, 50, 60, 96, 100, 120}; // fps Cine/video array obs: making double time at the equation
int t_angle [] = {360, 270, 180, 172, 144, 90, 72, 45}; // shutter angle @ 24fps
int ND[] =     {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48}; // ex: 1) 0.3 ND = -1 stop = 2^2 = 4; 2) 0.9 ND = -3 stop = 2^3 = 16;
///////////////////////////////////////////////////
// EEPROM for memory recording
uint8_t Sm =          EEPROM.read(1);
uint8_t tcm =         EEPROM.read(0);
///////////////////////////////////////////////////
// TCS 34725
class ColorSensor {
  public:

    void getColorTemp();
    uint16_t r, g, b, c, ir;
    uint16_t ct, lux, r_comp, g_comp, b_comp;
    float cpl;
};

void ColorSensor::getColorTemp() {


  Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_101MS, TCS34725_GAIN_1X);

  tcs.getRawData(&r, &g, &b, &c);
  //lux = tcs.calculateLux(r, g, b);
  // DN40 calculations
  ir = (r + g + b > c) ? (r + g + b - c) / 2 : 0;
  r_comp = r - ir;
  g_comp = g - ir;
  b_comp = b - ir;
  //c_comp = c - ir;

  ////////cpl = (700) / (TCS34725_GA * TCS34725_DF);
  ////////lux = (TCS34725_R_Coef * float(r_comp) + TCS34725_G_Coef * float(g_comp) + TCS34725_B_Coef * float(b_comp)) / cpl;
  ct = TCS34725_CT_Coef * float(b_comp) / float(r_comp) + TCS34725_CT_Offset;


  //////BETA////////
  // Kelvin compensation using Formatt-Hightech PROSTOP IRND 0.9 & 2.1
  // if (ndStop == 2) {ct = ct + 100;} if (ndStop == 7) {ct = ct + 180;} // TEST BASE 2700K 60W 50hz 220V UK Incandecent bulb
  // Need more testing in Daylight, Fluorescent light and High temperature dawn
  ///////////////////

}
ColorSensor rgb_sensor;
///////////////////////////////////////////////////
// SETUP
///////////////////////////////////////////////////
void setup() {
  // PINMODE
  pinMode(Bn1p, INPUT_PULLUP);
  pinMode(Bn2p, INPUT_PULLUP);
  pinMode(Rp, INPUT_PULLUP);
  //pinMode(Buzzer, OUTPUT);                    // not necessary (analog output)
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  //Initialize with the I2C addr 0x3D (for the 128x64 OLED)
  display.clearDisplay();                     // Clean display before Intro Animation
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  introanimation();                           // intro ANIMATION
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  // IF NO MEMORY WAS RECORDED BEFORE, START WITH THIS VALUES otherwise it will read "255"
  if (tcm > (sizeof(t_cine) / sizeof(int) - 1))
  {
    tcm = 2;
  }
  //if (Am > (sizeof(A)/sizeof(float)-1))
  //{Am = 4;}
  if (Sm > (sizeof(S) / sizeof(int) - 1))
  {
    Sm = 2;
  }

  lux = getLux();   // MAIN command to get a new exposure
  rgb_sensor.getColorTemp(); // MAIN command to get a new WB Value

}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void readAll() {
  Bn1 = digitalRead(Bn1p);
  Bn2 = digitalRead(Bn2p);
  R = digitalRead(Rp);
} // Check if any buttons were pressed.

void loop() {

  readAll();
  
  //IF BUTTON (+) AND (M) ARE BOTH PRESSED, SAVE EEPROM DATA AND FREEZES THE SETTINGS
  if (Bn1 == 0 & R == 0)
  {
    save = 1;
    freeze = 1;
  }
  while (Bn1 == 0 & R == 0)
  {
    delay(100);
    readAll();
  }

  if (save == 1)
  {
    if (tcm == 2) {
      Anglemode = 1;
      tca = 2;
    } else {
      Anglemode = 0;
    }
    EEPROM.write(taddr, tcm); //saving settings
    EEPROM.write(Saddr, Sm);  //saving settings
    tone(Buzzer, 800, 50);    //SOUNDDD
    Astring = 0;
    modeWindow();
    save = 0;
    Bn1 = 1;
    Bn2 = 1;
  }

  if (Anglemode == 1)
  {
    //READ BUTTON (+) AND INCREMENT ANGLE VALUE
    if (Bn1 == 0)
    {
      if (tca >= (sizeof(t_angle) / sizeof(int) - 1))
      {
        tca = 0;
      }
      else {
        tca = tca + 1;
      }
    }
    //READ BUTTON (-) AND INCREMENT ANGLE VALUE
    if (Bn2 == 0)
    {
      if (tca == 0) {
        tca = (sizeof(t_angle) / sizeof(int) - 1);
      }
      else {
        tca = tca - 1;
      }
    }
  }

  if (freeze == 0)
  {
    //READ BUTTON (+) AND INCREMENT SHUTTER VALUE
    if (Bn1 == 0)
    {
      if (tcm >= (sizeof(t_cine) / sizeof(int) - 1))
      {
        tcm = 0;
      }
      else {
        tcm = tcm + 1;
      }
    }
    //READ BUTTON (-) AND INCREMENT SHUTTER VALUE
    if (Bn2 == 0)
    {
      if (tcm == 0) {
        tcm = (sizeof(t_cine) / sizeof(int) - 1);
      }
      else {
        tcm = tcm - 1;
      }
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  //IF BUTTON (-) AND (M) ARE BOTH PRESSED, CHANGE SHUTTER MODE
  /*
  if (Bn2 == 0 & R == 0)
  {
    State = 1 - State;
    
    delay(10); //100
  }
  if (State == 1)
  {
   
  }
  else
  {
   
  } 
  */
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  //IF BUTTON (-) AND (+) ARE BOTH PRESSED, ENTER ISO/ND MODE

  if (Bn1 == 0 & Bn2 == 0)
  {
    ISOmode = 1;
  }
  while (Bn1 == 0 & Bn2 == 0)
  {
    delay(100);
    readAll();
  }
  
  if (ISOmode == 1)
  {
    Astring = 2;
    modeWindow();
    save = 0;
    //Bn1 = 1;
    //Bn2 = 1;
  }
  while (ISOmode == 1)
  {
    readAll();
    
    if (Bn1 == 0 & Bn2 == 0)
    {
      tone(Buzzer, 400, 50); //SOUNDDD
      ISOmode = 0;
      NDmode = 0;
      freeze = 0;
      Anglemode = 0;
      Astring = 1;
      modeWindow();
    }

    if (R == 0) {

    NDmode = 1;
    //R = 0;
  }
 
  while (NDmode == 1)
  //
  {
    readAll();
    
    if (R == 0)
    {
      NDmode = 0;
    }

    //READ BUTTON (+) AND INCREMENT ND VALUE
    if (Bn1 == 0) 
    {
     if (ndStop >= (sizeof(ND) / sizeof(int) - 1))
      {
        ndStop = 0;
      }
      else {
        ndStop = ndStop + 1;
      } 
    }
    //READ BUTTON (-) AND INCREMENT ND VALUE
     if (Bn2 == 0)
    { 
      if (ndStop == 0)
      {
        ndStop = (sizeof(ND) / sizeof(int) - 1);
      }
      else {
        ndStop = ndStop - 1;
      }
    }
    
    refresh(); // While in NDmode, call function for refreshing the Display
    buttonDelay();
  }

    //READ BUTTON (+) AND INCREMENT SENSITIVITY VALUE
    if (Bn1 == 0)
    { if (Sm >= (sizeof(S) / sizeof(int) - 1))
      {
        Sm = 0;
      }
      else {
        Sm = Sm + 1;
      }
    }
    //READ BUTTON (-) AND INCREMENT SENSITIVITY VALUE
    if (Bn2 == 0)
    { if (Sm == 0)
      {
        Sm = (sizeof(S) / sizeof(int) - 1);
      }
      else {
        Sm = Sm - 1;
      }
    }

    refresh(); // While in ISO Mode, call function for refreshing the Display
    buttonDelay();
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  // REFRESH AND BUTTON DEBUG

  refresh(); // While Shuttermode = 0 or 1, call function for refreshing the Display

  buttonDelay();
  
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  //IF (M) BUTTON IS PRESSED, GET A NEW LUX VALUE and COLOR TEMP VALUE
  if (R == 0)
  {
    lux = getLux();
    rgb_sensor.getColorTemp();
    tone(Buzzer, 3000, 100);
  }

  if (Overflow == 1)
  {delay(10); getLux();}

} // END OF LOOP \\

//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////   FUNCTIONS   ////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
float getLux()
{
  Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);

  sensor_t sensor;
  tsl.getSensor(&sensor);

  if (needHigh == 1) {
  tsl.setGain(TSL2591_GAIN_HIGH);   // 428x gain
  }
  else {
  tsl.setGain(TSL2591_GAIN_LOW);    /* 1x gain (bright light)*/
  }
  tsl.setTiming(TSL2591_INTEGRATIONTIME_200MS); /*shortest integration time (bright light)*/

  tsl.begin();

  sensors_event_t event;
  tsl.getEvent(&event);
  
  float lux = event.light;
  if   ((event.light == 0) |              // When sensor gets saturated (normally in transition between Gain)
       (event.light > 4294966000.0) |     // Lux value is restored to 201 for a effective change in Gain (from 428x to 1x)
       (event.light <-4294966000.0))      // Overflow is displayed indicating that this value is not correct
       {lux = 201; Overflow = 1;} 
  else {Overflow = 0;}
    
  lux = lux * DomeMultiplier;             // DomeMultiplier = 2.17 (calibration)
  if (lux < 40) {needHigh = 1;}           // ~ 1 +1/3 OFFSET (*0.26 in lux calibration)
  if (lux > 200) {needHigh = 0;}          // Turns off High gain
  if (needHigh == 1) {lux = lux*.26;}     // OFFSET corrected
  
  return lux;
  
}

void buttonDelay() {
   //DELAYS FOR BUTTON HOLD
    while (Bn1 == 0)
    {
      delay(10);
      Bn1 = digitalRead(Bn1p);
    }
    while (Bn2 == 0)
    {
      delay(10);
      Bn2 = digitalRead(Bn2p);
    }
}

void refresh()  //This function gives a new calculation based on the last illuminance value, and refreshes the display.

{    //////////////////////////// CINE MODE //////////////////////

    int intCinefps = t_cine[tcm];                // FPS
    float t_final;                               // shutter speed/ shutter angle
    String Ev;                                   // F stop
    int Evplus;                                  // Thirds of stop
    String Fplus[] {F("+1/3") , F("+2/3")};      // String Array of Thirds of stop
    // Formula
    if (Anglemode == 1) {
      t_final = pow((8640 / t_angle[tca]), -1);
    }
    else {
      t_final = pow(((intCinefps) * 2), -1); // Shutter Speed // Formula because intCinefps is frames per second
    }
    if (ndStop > 0) { ISOND = S[Sm]/(pow(2,ndStop)); }   // ND filter altering the ISO
    else { ISOND = S[Sm]; }
    
    float N = sqrt((lux * ISOND * t_final) / C_const);       // float APERTURE 
    float Fc = lux * 0.0929;                                // FootCandle

    // Translation for printing the Display
    if ((N >= 0.5) && (N < 0.8)) {
      Ev = F("0.7");
      Evplus = 2;
    }
    if ((N >= 0.8) && (N < 0.9)) {
      Ev = F("0.7");
      Evplus = 0;
    }
    if ((N >= 0.9) && (N < 1))   {
      Ev = F("0.7");
      Evplus = 1;
    }
    if ((N >= 1.0) && (N < 1.1)) {
      Ev = F("1");
      Evplus = 2;
    }
    if ((N >= 1.1) && (N < 1.2)) {
      Ev = F("1");
      Evplus = 0;
    }
    if ((N >= 1.2) && (N < 1.4)) {
      Ev = F("1");
      Evplus = 1;
    }
    if ((N >= 1.4) && (N < 1.6)) {
      Ev = F("1.4");
      Evplus = 2;
    }
    if ((N >= 1.6) && (N < 1.8)) {
      Ev = F("1.4");
      Evplus = 0;
    }
    if ((N >= 1.8) && (N < 2))   {
      Ev = F("1.4");
      Evplus = 1;
    }
    if ((N >= 2.0) && (N < 2.2)) {
      Ev = F("2");
      Evplus = 2;
    }
    if ((N >= 2.2) && (N < 2.5)) {
      Ev = F("2");
      Evplus = 0;
    }
    if ((N >= 2.5) && (N < 2.8)) {
      Ev = F("2");
      Evplus = 1;
    }
    if ((N >= 2.8) && (N < 3.2)) {
      Ev = F("2.8");
      Evplus = 2;
    }
    if ((N >= 3.2) && (N < 3.5)) {
      Ev = F("2.8");
      Evplus = 0;
    }
    if ((N >= 3.5) && (N < 4))   {
      Ev = F("2.8");
      Evplus = 1;
    }
    if ((N >= 4.0) && (N < 4.5)) {
      Ev = F("4");
      Evplus = 2;
    }
    if ((N >= 4.5) && (N < 5.0)) {
      Ev = F("4");
      Evplus = 0;
    }
    if ((N >= 5.0) && (N < 5.6)) {
      Ev = F("4");
      Evplus = 1;
    }
    if ((N >= 5.6) && (N < 6.3)) {
      Ev = F("5.6");
      Evplus = 2;
    }
    if ((N >= 6.3) && (N < 7.1)) {
      Ev = F("5.6");
      Evplus = 0;
    }
    if ((N >= 7.1) && (N < 8))   {
      Ev = F("5.6");
      Evplus = 1;
    }
    if ((N >= 8.0) && (N < 9.0)) {
      Ev = F("8");
      Evplus = 2;
    }
    if ((N >= 9)   && (N < 10))  {
      Ev = F("8");
      Evplus = 0;
    }
    if ((N >= 10)  && (N < 11))  {
      Ev = F("8");
      Evplus = 1;
    }
    if ((N >= 11)  && (N < 13))  {
      Ev = F("11");
      Evplus = 2;
    }
    if ((N >= 13)  && (N < 14))  {
      Ev = F("11");
      Evplus = 0;
    }
    if ((N >= 14)  && (N < 16))  {
      Ev = F("11");
      Evplus = 1;
    }
    if ((N >= 16)  && (N < 18))  {
      Ev = F("16");
      Evplus = 2;
    }
    if ((N >= 18)  && (N < 20))  {
      Ev = F("16");
      Evplus = 0;
    }
    if ((N >= 20)  && (N < 22))  {
      Ev = F("16");
      Evplus = 1;
    }
    if ((N >= 22)  && (N < 25))  {
      Ev = F("22");
      Evplus = 2;
    }
    if ((N >= 25)  && (N < 29))  {
      Ev = F("22");
      Evplus = 0;
    }
    if ((N >= 29)  && (N < 32))  {
      Ev = F("22");
      Evplus = 1;
    }
    if ((N >= 32)  && (N < 36))  {
      Ev = F("32");
      Evplus = 2;
    }
    if ((N >= 36)  && (N < 40))  {
      Ev = F("32");
      Evplus = 0;
    }
    if ((N >= 40)  && (N < 45))  {
      Ev = F("32");
      Evplus = 1;
    }
    if ((N >= 45)  && (N < 51))  {
      Ev = F("45");
      Evplus = 2;
    }
    if ((N >= 51)  && (N < 57))  {
      Ev = F("45");
      Evplus = 0;
    }
    if ((N >= 57)  && (N < 64))  {
      Ev = F("45");
      Evplus = 1;
    }
    if ((N >= 64)  && (N < 72))  {
      Ev = F("64");
      Evplus = 2;
    }
    if ((N >= 72)  && (N < 80))  {
      Ev = F("64");
      Evplus = 0;
    }
    if ((N >= 80)  && (N < 90))  {
      Ev = F("64");
      Evplus = 1;
    } 
    // DISPLAY PRINTING ////////////////////////////////////////
    ///////////////////////////// F STOP AND THIRDS ////////////
    display.setTextColor(WHITE);
    display.setCursor(0, 6);
    if ((N < 0.5) || (N > 90))
    { outOfrange();}
    else
    { // ALL OTHER VALUES
      display.setTextSize(1);
      display.print(F("f/ "));
      display.setTextSize(3);
      //display.setTextColor(WHITE);
      display.print(Ev);
      if (Evplus < 2) {
        display.setTextSize(2);
        display.println(Fplus[Evplus]);
      }
    }
    display.setTextSize(0);
    /////////////////////////////
    display.setCursor(0, 42);
    //display.setTextColor(WHITE);
    if (Anglemode == 1) {
    display.print(F("1/")); 
    display.println(8640/(t_angle[tca])); 
    }
    else {
    display.setTextSize(2);
    }
    display.setCursor(x_vmode, y_vmode);
    display.print(rgb_sensor.ct);
    display.println(F("K"));     // KELVINS
    display.setTextSize(0);
    
    display.setCursor(0, 52);
    //display.setTextColor(WHITE);
    if (Anglemode == 1) {
      display.print(t_angle[tca]);
      display.println(F(" angle"));
    }
    if (Anglemode == 0) {
      display.print(F("1/"));
      display.println(intCinefps * 2);
     
    }
    //////////////////////// 
    display.drawLine(73, 24, 73, 62, WHITE); // LINE DIVISOR
    display.setTextSize(1);
    displayHighGain();
    ////////////////////////
    display.setCursor(75, 24);
    display.print(F("ISO"));
    display.println(S[Sm]);      // ISO
    ////////////////////////
    display.setCursor(75, 34);
    if (Overflow == 1) {display.println(F("Overflow"));}
    else {
    display.print(F("f/"));
    display.println(N);}         // APERTURE FULL VALUE
    ////////////////////////
    display.setCursor(75, 54);
    if (ndStop > 0) {
    display.print(F("ND "));
    display.println(ND[ndStop]);} // ND filtration
    else {
    display.print(lux, 1);
    if(lux<10000){
    display.println(F("Lx"));}
    else {display.println(F("L"));}
    }
    display.setCursor(75, 44);
    display.print(Fc);
    if(Fc<1000) {
    display.println(F("Fc"));}// FOOTCANDLES 
    else {display.println(F("F"));}
    ////////////////////////
    t=0;
    refreshtiming();

  }

void outOfrange() {
      display.setTextSize(1);
      display.print("OUT OF ");
      display.setTextSize(2);
      display.println(F("RANGE!"));
}

void displayHighGain(){
  if (needHigh == 1) {
    display.drawLine(0, 18, 12, 18, WHITE); // LINE DIVISOR
    display.drawLine(0, 28, 12, 28, WHITE); // LINE DIVISOR
    display.drawLine(12, 18, 12, 28, WHITE); // LINE DIVISOR
    display.setCursor(0,20);  
    display.println(F("Hi"));}
}
 
void refreshtiming() {
    int timing[] = {0,120,500};
    display.display();
    delay(timing[t]);
    display.clearDisplay();
}

void modeWindow() {
    String modeA[] = {F("Saved"), F("Selected"), F("ISO Set"), F("PHOTO Mode"), F("CINE Mode"), F("Freezed"), F("Unfreezed"), F(""), F("Aperture Priority"), F("Shutter Priority")};
    if ((State == 1) && (Shuttermode == 0))
    {Astring = 3;}
    if ((State == 0) && (Shuttermode == 1))
    {Astring = 4;}
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(5, 20);
    display.println(modeA[Astring]);
    display.setCursor(5, 40);
    display.setTextSize(1);
    display.println(modeA[Astring+5]);
    t=2;
    refreshtiming();  
}

void introanimation() {
  display.drawRoundRect(2, 22, 124, 28, 3, WHITE); //Show "2nd" splash screen
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(4, 26);
  display.println(F(" EXPOSURE METER v4 "));
  display.setCursor(7, 39);
  display.println(F("code by Kevin Agnes"));
  refreshtiming();
}



