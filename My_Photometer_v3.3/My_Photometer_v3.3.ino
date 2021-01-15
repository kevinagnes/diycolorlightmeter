//BITMAP IMAGES FOR INTRO ANIMATION
const unsigned char PROGMEM fstop_logo [] = {
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE6, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0,
  0x00, 0x00, 0x00, 0x00, 0x03, 0xF0, 0x7C, 0xFC, 0x78, 0x7C, 0x03, 0xF0, 0xC6, 0x30, 0xCC, 0x66,
  0x01, 0xC0, 0xC6, 0x31, 0x86, 0x66, 0x01, 0xC0, 0x70, 0x31, 0x86, 0x66, 0x01, 0xC0, 0x0C, 0x31,
  0x86, 0x7C, 0x01, 0xC0, 0xC6, 0x31, 0x86, 0x60, 0x01, 0x80, 0xC6, 0x30, 0xCC, 0x60, 0x01, 0x80,
  0x7C, 0x30, 0x78, 0x60, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x37, 0x42, 0x2C, 0x20,
  0x30, 0x78, 0x45, 0x30, 0x2C, 0x20, 0x30, 0x78,
};

static const unsigned char PROGMEM battery_full [] =
{ 0x7F, 0xE0, 0x40, 0x20, 0x5F, 0xB8, 0x5F, 0xB8, 0x5F, 0xB8, 0x5F, 0xB8, 0x40, 0x20, 0x7F, 0xE0 };

static const unsigned char PROGMEM battery_threequarters [] =
{ 0x7F, 0xE0, 0x40, 0x20, 0x5C, 0x38, 0x5E, 0x38, 0x5E, 0x38, 0x5F, 0x38, 0x40, 0x20, 0x7F, 0xE0 };

static const unsigned char PROGMEM battery_half [] =
{ 0x7F, 0xE0, 0x40, 0x20, 0x58, 0x38, 0x58, 0x38, 0x5C, 0x38, 0x5C, 0x38, 0x40, 0x20, 0x7F, 0xE0 };

static const unsigned char PROGMEM battery_low [] =
{ 0x7F, 0xE0, 0x40, 0x20, 0x50, 0x38, 0x50, 0x38, 0x50, 0x38, 0x50, 0x38, 0x40, 0x20, 0x7F, 0xE0 };

static const unsigned char PROGMEM battery_empty [] =
{ 0x7F, 0xE0, 0x40, 0x20, 0x40, 0x38, 0x40, 0x38, 0x40, 0x38, 0x40, 0x38, 0x40, 0x20, 0x7F, 0xE0 };

// INCLUDE||DEFINE SECTION
#include <SPI.h>                        // Library necessary                      
#include <Wire.h>                       // Library necessary
#include <Adafruit_GFX.h>               // Library for Graphics||Bitmaps||Fonts
#include <Adafruit_SSD1306.h>           // Library for (not only) the 128x64 OLED display
#include <Adafruit_Sensor.h>            // Library necessary
#include <Adafruit_TCS34725.h>
#define SCL_PORT PORTC
#define SCL_PIN 3
#define SDA_PORT PORTC
#define SDA_PIN 2
#include <SoftI2CMaster.h>
#include <Adafruit_TSL2591Soft.h>
#include <EEPROM.h>                     // Library for using the EEPROM memory
#include <Vcc.h>

///// Constants for calibration
#define TCS34725_R_Coef 0.136
#define TCS34725_G_Coef 1.000
#define TCS34725_B_Coef -0.444
#define TCS34725_GA 1.0
#define TCS34725_DF 310.0
#define TCS34725_CT_Coef 3810.0
#define TCS34725_CT_Offset 1391.0
#define C_const 129
#define DomeMultiplier 2.17             // Multiplier when using a white translucid Dome covering the Sensor
//#define DomeSum
/*#define OLED_RESET 8*/                    // OLED reset pin set to digitalPin 4 // I2C ONLY

Adafruit_SSD1306 display(8);   // I2C ONLY

// INT||FLOAT||STRING||BOOLEAN
uint8_t Rp = 2;                             // Metering button pin
uint8_t Bn1p = 3;                           // + increment button pin
uint8_t Bn2p = 4;                           // - increment button pin
uint8_t Tdisplay;                           // State of shutter speed value display (fractional, seconds, minutes)
uint8_t taddr = 0;                          // Address to write tcm to EEPROM
uint8_t Am = 15;                            // Starts Photo Mode with f2.8
uint8_t tca;                                // Shutter angle selector
uint8_t Saddr = 1;                          // Address to write Sv to EEPROM
/*uint8_t Buzzer = 9;*/                     // Buzzer for Button confirmation

short Tfr;

float lux;                              // Lux value from TSL2591
float ct;                               // Color Temp value from TCS34725
//float EV;                             // EV value for PhotoMode
float Tmin;                             // Time in minutes
const float VccMin = 0.0;               // Minimum expected Vcc level, in Volts.
const float VccMax = 5.0;               // Maximum expected Vcc level, in Volts.
const float VccCorrection = 9.51 / 9;   // Measured Vcc by multimeter divided by reported Vcc

boolean Bn1;                            // + increment button state
boolean Bn2;                            // - increment button state
boolean R;                              // Metering button state
boolean Shuttermode = true;             // Shutter mode state for Cine or Photo, it starts in PHOTOmode
boolean freeze = false;                 // Freezes the Shutter (CINE) || Aperture (Photo)
boolean Anglemode = false;              // Activate shutter angle mode at 24fps
boolean needHigh = false;
boolean Overflow = false;

Vcc vcc(VccCorrection);

// ARRAYS for Photo and Cine values
int S [] = {100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600}; //ISO array
float A [] = {0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 
              2.5, 2.8, 3.2, 3.5, 4, 4.5, 5.0, 5.6, 6.3, 7.1, 8, 9, 10, 11, 13, 
              14, 16, 18, 20, 22, 25, 29, 32, 36, 40, 45, 51, 57, 64, 72, 80, 90}; // Aperture array
int t_cine [] = {8, 16, 24, 25, 30, 48, 50, 60, 96, 100, 120}; // fps Cine/video array obs: making double time at the equation
int t_angle [] = {360, 270, 180, 172, 144, 90, 72, 45}; // shutter angle @ 24fps

// EEPROM for memory recording
uint8_t Sm = EEPROM.read(1);
uint8_t tcm = EEPROM.read(0);

// TCS 34725
class ColorSensor {
  
    public:
  
        void getColorTemp();
        uint16_t r, g, b, c, ir;
        uint16_t ct, lux, r_comp, g_comp, b_comp;
        float cpl;
} rgb_sensor;

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
  
    cpl = (700) / (TCS34725_GA * TCS34725_DF);
    lux = (TCS34725_R_Coef * float(r_comp) + TCS34725_G_Coef * float(g_comp) + TCS34725_B_Coef * float(b_comp)) / cpl;
    ct = TCS34725_CT_Coef * float(b_comp) / float(r_comp) + TCS34725_CT_Offset;
    //ct = ct*DomeSum;
}

/*
 * I've deleted 'x_vmode', 'y_vmode', 'Astring', 't', 'ISOmode' and 'save' 
 * because too much global variables make leaks on dynamic memory. 
 * In some cases I had to change the semantic of the code. Next you'll see.
 */

void setup() {

    //Serial.begin(9600);
    pinMode(Bn1p, INPUT_PULLUP);
    pinMode(Bn2p, INPUT_PULLUP);
    pinMode(Rp, INPUT_PULLUP);
    //pinMode(Buzzer, OUTPUT);                    // not necessary
    
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  //Initialize with the I2C addr 0x3D (for the 128x64 OLED)
    display.clearDisplay();                     // Clean display before Intro Animation
    
    introAnimation();                           // intro ANIMATION
    
    // IF NO MEMORY WAS RECORDED BEFORE, START WITH THIS VALUES otherwise it will read "255"
    if (tcm > (sizeof(t_cine) / sizeof(int) - 1)) {
      
        tcm = 2;
    }
    
    if (Sm > (sizeof(S) / sizeof(int) - 1)) {
      
        Sm = 2;
    }
    
    lux = getLux();   // MAIN command to get a new exposure
    rgb_sensor.getColorTemp(); // MAIN command to get a new WB Value
}

void loop() {

    /*
     * HERE I'VE RE-SET THE BUTTON COMBINATIONS FUNCTIONS. 
     * HERE YOU HAD ALSO DIVIDED A LOT OF "IF-ELSE" THAT COULD BE
     * IN THE SAME SCOPE.
     */

     /*
      * I ALSO DELETED THE DELAY BUTTON FUNTIONCS THAT YOU MADE BECAUSE I NEEDED TO
      * SCROLL THE VALUES BY KEEPING THE BUTTON HOLD. THE INPUT ARE STILL PRECISE.
      * NO DEBUNCING OCCURS.
      */

    readAll();

    // IF BUTTON (-) AND (R) ARE BOTH PRESSED, SAVE SETTINGS mode 
    if (!Bn2 && !R) {  

        saveSettings();
    }

    //IF SAVE SETTINGS mode IS ACTIVATED, (+) AND (-) BUTTON ARE DISABLED 
    if (!freeze) {
      
        //READ BUTTON (+) AND INCREMENT SHUTTER VALUE
        if (!Bn1) {
          
            if (tcm >= (sizeof(t_cine) / sizeof(int) - 1)) {
              
                tcm = 0;
            }
            else {
              
                tcm++;
            }

            //READ BUTTON (+) AND INCREMENT APERTURE VALUE
            if (Am >= (sizeof(A) / sizeof(float) - 1)) {
              
                Am = false;
            }
            else {
              
                Am++;
            }
        }
        
        //READ BUTTON (-) AND INCREMENT SHUTTER VALUE
        if (!Bn2) {
          
            if (tcm == 0) {
              
                tcm = (sizeof(t_cine) / sizeof(int) - 1);
            }
            else {
              
                tcm--;
            }

            //READ BUTTON (-) AND INCREMENT APERTURE VALUE
            if (!Am) {
              
                Am = (sizeof(A) / sizeof(float) - 1);
            }
            else {
              
                Am--;
            }
        }
    }

    /*
     * HERE I CHANGED THE SEMANTIC AS YOU CAN SEE
     */

    // IF BUTTON (+) AND (R) ARE BOTH PRESSED, CHANGE SHUTTER MODE
    if (!Bn1 && !R) {  

        Shuttermode = !Shuttermode;
        
        modeWindow(3 + Shuttermode);
        delay(10); //100
    }

    if (Overflow) {
           
        delay(10); 
        getLux();
    }
    
    if (Anglemode) {
      
        //READ BUTTON (+) AND INCREMENT ANGLE VALUE
        if (!Bn1) {
            
            if (tca >= (sizeof(t_angle) / sizeof(int) - 1)) {
                 
                tca = 0;
            }
            else {
                      
                tca++;
            }
        }
        
        //READ BUTTON (-) AND INCREMENT ANGLE VALUE
        if (!Bn2) {
            
            if (!tca) {
              
                tca = (sizeof(t_angle) / sizeof(int) - 1);
            }
            else {
              
                tca--;
            }
        }
    }

    //IF BUTTON (+) AND (-) ARE BOTH PRESSED, ISOset MODE
    if (!Bn1 && !Bn2) {
      
        modeWindow(2);
        Bn1 = true;
        Bn2 = true;

        /*
         * LOOK CAREFULLY HERE. HERE YOU USED THE 'ISOMODE' VARIABLE
         * TO BREAK OUT FROM THE 'WHILE'. AS YOU CAN SEE THIS IS A MORE
         * CLEAR METHOD AND MORE EFFICIENT.
         */
    
        while (true) { 
          
            readAll();
            
            if (!Bn1 && !Bn2) {
              
                //tone(Buzzer, 400, 50); //SOUND
                freeze = false;
                Anglemode = false;
                modeWindow(1);

                break;
            }
          
            //READ BUTTON (+) AND INCREMENT SENSITIVITY VALUE
            if (!Bn1) {
              
                if (Sm >= (sizeof(S) / sizeof(int) - 1)) {
                  
                    Sm = 0;
                }
                else {
                  
                    Sm++;
                }
            }
            
            //READ BUTTON (-) AND INCREMENT SENSITIVITY VALUE
            if (!Bn2) { 
              
                if (Sm == 0) {
                  
                    Sm = (sizeof(S) / sizeof(int) - 1);
                }
                else {
                  
                    Sm--;
                }
            }
          
            refresh(); // While in ISO Mode, call function for refreshing the Display           
        }
    }
    
    refresh(); // While Shuttermode = 0 or 1, call function for refreshing the Display

    //IF (R) BUTTON IS PRESSED, GET A NEW LUX VALUE and COLOR TEMP VALUE
    if (!R) {
      
        lux = getLux();
        rgb_sensor.getColorTemp();
        //tone(Buzzer, 3000, 100);
    }
}
