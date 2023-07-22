#include <avr/pgmspace.h>

#pragma region Functions
// Reading and displaying battery percentage
void readButtons() {
    Bn1 = digitalRead(Bn1p);
    Bn2 = digitalRead(Bn2p);
    R = digitalRead(Rp);
}

// Saving settings and displaying current mode
void saveAndDisplaySettings() {
    freeze = true;
      
    // Switching between Angle mode
    if (tcm == 2) { 
        Anglemode = true;
        tca = 2;
    } else {    
        Anglemode = false;
    }
    
    // Saving settings to EEPROM
    EEPROM.write(taddr, tcm); 
    EEPROM.write(Saddr, Sm);  

    // Beeping the buzzer
    tone(Buzzer, 800, 50);    
    
    displayModeWindow(0);
    
    Bn1 = true;
    Bn2 = true;
}

// Function to calculate lux
float calculateLux() {
    float lux;
    Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);
  
    sensor_t sensor;
    tsl.getSensor(&sensor);
  
    // Setting gain based on the light intensity
    if (needHigh) {
        tsl.setGain(TSL2591_GAIN_HIGH); 
    } else {
        tsl.setGain(TSL2591_GAIN_LOW); 
    }
    
    tsl.setTiming(TSL2591_INTEGRATIONTIME_200MS); 
    tsl.begin(); 
    sensors_event_t event;
    tsl.getEvent(&event);
    lux = event.light;
    
    // Checking for light overflow
    if ((event.light == 0) || (event.light > 4294966000.0) || (event.light < -4294966000.0)) {
        lux = 201;
        Overflow = true;
    } else {
        Overflow = false;
    }

    lux *= DomeMultiplier;
    
    // Adjusting gain based on the lux value
    if (lux < 40) {
        needHigh = true;
    } 
    if (lux > 200) {
        needHigh = false;
    }
    if (needHigh) {
        lux *= .26;
    }
    
    return lux;
}

struct EvValue {
    double lower_bound;
    double upper_bound;
    const char* ev_str;
    int ev_plus;
};

const EvValue ev_values[] PROGMEM= {
    {0.5, 0.8, "0.7", 2},
    {0.8, 0.9, "0.7", 0},
    {0.9, 1.0, "0.7", 1},
    {1.0, 1.1, "1", 2},
    {1.1, 1.2, "1", 0},
    {1.2, 1.4, "1", 1},
    {1.4, 1.6, "1.4", 2},
    {1.6, 1.8, "1.4", 0},
    {1.8, 2.0, "1.4", 1},
    {2.0, 2.2, "2", 2},
    {2.2, 2.5, "2", 0},
    {2.5, 2.8, "2", 1},
    {2.8, 3.2, "2.8", 2},
    {3.2, 3.5, "2.8", 0},
    {3.5, 4.0, "2.8", 1},
    {4.0, 4.5, "4", 2},
    {4.5, 5.0, "4", 0},
    {5.0, 5.6, "4", 1},
    {5.6, 6.3, "5.6", 2},
    {6.3, 7.1, "5.6", 0},
    {7.1, 8.0, "5.6", 1},
    {8.0, 9.0, "8", 2},
    {9.0, 10.0, "8", 0},
    {10.0, 11.0, "8", 1},
    {11.0, 13.0, "11", 2},
    {13.0, 14.0, "11", 0},
    {14.0, 16.0, "11", 1},
    {16.0, 18.0, "16", 2},
    {18.0, 20.0, "16", 0},
    {20.0, 22.0, "16", 1},
    {22.0, 25.0, "22", 2},
    {25.0, 29.0, "22", 0},
    {29.0, 32.0, "22", 1},
    {32.0, 36.0, "32", 2},
    {36.0, 40.0, "32", 0},
    {40.0, 45.0, "32", 1},
    {45.0, 51.0, "45", 2},
    {51.0, 57.0, "45", 0},
    {57.0, 64.0, "45", 1},
    {64.0, 72.0, "64", 2},
    {72.0, 80.0, "64", 0},
    {80.0, 90.0, "64", 1}
};


void cineMode() {

    int intCinefps = t_cine[tcm];                
    float t_final;                               
    float N;
    float Fc;
    String Ev;                                   
    int Evplus;                                  
    String Fplus[] {F("+1/3") , F("+2/3")};      
        
    // Formula to calculate final shutter speed or shutter angle
    if (Anglemode) {
        t_final = pow((8640 / t_angle[tca]), -1);
    } else {
        t_final = pow(((intCinefps) * 2), -1);    
    }
        
    // Calculate APERTURE in full value 
    N = sqrt((lux * S[Sm] * t_final) / C_const); 
    // Calculate FootCandle (lux_fc)
    Fc = lux * 0.0929;                     

    // Translation for printing the Display
    // Use a loop to find the matching condition
    for (uint8_t i = 0; i < sizeof(ev_values)/sizeof(EvValue); ++i) {
        EvValue ev_value;
        memcpy_P(&ev_value, &ev_values[i], sizeof(EvValue));
        if (N >= ev_value.lower_bound && N < ev_value.upper_bound) {
            Ev = ev_value.ev_str; // assign the C-string directly
            Evplus = ev_value.ev_plus;
            break;
        }
    }

    //DISPLAY PRINTING, F STOP AND THIRDS
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    
    if ((N < 0.5) || (N > 90)) { 
        
        displayOutOfRangeMessage();
    }
    else { 
        
        // ALL OTHER VALUES
        display.setTextSize(1);
        display.print(F("f/ "));
        display.setTextSize(2);
        //display.setTextColor(WHITE);
        display.print(Ev);
        
        if (Evplus < 2) {
            
            display.setTextSize(1);
            display.println(Fplus[Evplus]);
        }
    }
    
    display.setTextSize(0);
    display.setCursor(68, 16);
    
    //CINE MODES FPS SHUTTER SPEED
    if (intCinefps < 24) {
        
        //display.setTextColor(WHITE);
        display.println(F("super8"));
    }
    else if (intCinefps == 24) {
        
        //display.setTextColor(WHITE);
        display.println(F("cine"));
    }
    else if (intCinefps == 25) {
        
        //display.setTextColor(WHITE);
        display.println(F("video PAL"));
    }
    else if (intCinefps == 30) {
        
        //display.setTextColor(WHITE);
        display.println(F("video NTSC"));
    }
    else if (intCinefps > 30) {
        
        //display.setTextColor(WHITE);
        display.println(F("slow"));
    }

    display.setCursor(21, 24);
    //display.setTextColor(WHITE);
    
    if (Anglemode) {
        
        display.print(F("1/")); 
        display.println(8640/(t_angle[tca])); 
    }
    else {
        
        display.print(intCinefps, 1);
        //display.setTextColor(WHITE);
        display.println(F("fps"));
    }
    
    display.setCursor(21, 16);
    //display.setTextColor(WHITE);
    
    if (Anglemode) {
        
        display.print(t_angle[tca]);
        display.println(F(" angle"));
    } 
    else {
        
        display.print(F("1/"));
        display.println(intCinefps * 2);
    }

    display.drawLine(63, 9, 63, 64, WHITE); // LINE DIVISOR
    display.setTextSize(1);
    displayHighGainIfNeeded();

    display.setCursor(68, 24);
    display.print(F("ISO"));
    display.println(S[Sm]);  // ISO

    display.setCursor(54, 34);
    
    if (Overflow) {

        display.println(F("Overflow"));
    }
    else {
        
        display.print(F("f/"));
        display.println(N);
    }     // APERTURE FULL VALUE
        
    display.setCursor(68, 9);
    display.print(rgb_sensor.ct);
    display.println(F("K")); // KELVINS

    refreshDisplayWithDelay(0);
}

void photoMode() {

    float T = pow(A[Am], 2) * C_const / (lux * S[Sm]); //T = exposure time, in seconds
    
        if (T >= 60) {
          
            Tdisplay = 0;  //Exposure is now in minutes
            Tmin = T / 60;
        }
        else if (T < 0.75)
        {
          
            Tdisplay = 1;  //Exposure is now in fractional form
            
            if (T < 0.000125) {
              
                Tdisplay = 3;
            }
            else if ((T <= 0.000188) && (T > 0.000125)) {
              
                Tfr = 8000;
            }
            else if ((T <= 0.000375) && (T > 0.000188)) {
              
                Tfr = 4000;
            }
            else if ((T <= 0.00075) && (T > 0.000375)) {
              
                Tfr = 2000;
            }
            else if ((T <= 0.0015) && (T > 0.00075)) {
              
                Tfr = 1000;
            }
            else if ((T <= 0.003) && (T > 0.0015)) {
              
                Tfr = 500;
            }
            else if ((T <= 0.006) && (T > 0.003)) {
              
                Tfr = 250;
            }
            else if ((T <= 0.012333) && (T > 0.006)) {
              
                Tfr = 125;
            }
            else if ((T <= 0.025) && (T > 0.012333)) {
              
                Tfr = 60;
            }
            else if ((T <= 0.05) && (T > 0.025)) {
              
                Tfr = 30;
            }
            else if ((T <= 0.095833) && (T > 0.05)) {
              
                Tfr = 15;
            }
            else if ((T <= 0.1875) && (T > 0.095833)) {
              
                Tfr = 8;
            }
            else if ((T <= 0.375) && (T > 0.1875)) {
              
                Tfr = 4;
            }
            else if ((T <= 0.75) && (T > 0.375)) {
              
                Tfr = 2;
            }
        }
        else if ((T >= 0.75) && (T < 60)) {
          
            Tdisplay = 2;  //Exposure in seconds
        }
        
        if (lux == 0) {    //This happens if the sensor is overloaded or senses no light
          
            Tdisplay = 3;
        }
    
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        display.print(F("f/ "));
        display.setTextSize(2);
        display.println(A[Am], 1);
        display.setCursor(18, 18);
        display.setTextSize(1);
    
        if (Tdisplay == 0) {
          
            display.print(Tmin, 1);
            display.println(F("m"));
        }
        else if (Tdisplay == 1) {
          
            display.print(F("1/"));
            display.println(Tfr);
        }
        else if (Tdisplay == 2) {
          
            display.print(T, 1);
            display.println(F("s"));
        }
        else /*if (Tdisplay == 3)*/ {

            display.setCursor(17, 16);
            display.println(F("OUT OF"));
            display.setCursor(17, 25);
            display.print(F("RANGE!"));
        }
    
        display.drawLine(73, 5, 73, 35, WHITE);
        display.setTextSize(1);
        displayHighGainIfNeeded();
        
        display.setCursor(78, 6);
        display.print(lux, 1);
        display.println(F("Lx"));
     
        display.setCursor(78, 15);
        display.print(rgb_sensor.ct);
        display.println(F("K"));

        display.setCursor(78, 24);
        display.print(F("ISO"));
        display.println(S[Sm]);
        
        
        if (Overflow) {
          
            display.setCursor(17, 20);
            display.println(F("Overflow"));
        }
        
        refreshDisplayWithDelay(0);
}

void refresh() {              //This function gives a new calculation based on the last illuminance value, and refreshes the display.
  
    if (!Shuttermode) {   // CINEMODE
      
        cineMode();
    }  
    else {          //PHOTO MODE 
      
        photoMode();
    }
}

#pragma endregion
