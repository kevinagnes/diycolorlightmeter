
/*
 * ADDED THE BATTERY PERCENTAGE CALCULATOR FUNCTIONS IN THE LOOP 
 */
 
void readAll() {
  
    Bn1 = digitalRead(Bn1p);
    Bn2 = digitalRead(Bn2p);
    R = digitalRead(Rp);

    batteryPerc();
}

void saveSettings() {

    freeze = true;
      
    if (tcm == 2) { 
           
        Anglemode = true;
        tca = 2;
    } 
    else {    
          
        Anglemode = false;
    }
    
    EEPROM.write(taddr, tcm); //saving settings
    EEPROM.write(Saddr, Sm);  //saving settings
    
    //tone(Buzzer, 800, 50);    //SOUND
    
    modeWindow(0);
    
    Bn1 = true;
    Bn2 = true;
}

float getLux() {

    float lux;
    Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);
  
    sensor_t sensor;
    tsl.getSensor(&sensor);
  
    if (needHigh) {
      
        tsl.setGain(TSL2591_GAIN_HIGH);   // 428x gain
    }
    else {
      
        tsl.setGain(TSL2591_GAIN_LOW);    /* 1x gain (bright light)*/
    }
    
    tsl.setTiming(TSL2591_INTEGRATIONTIME_200MS);     /*shortest integration time (bright light)*/
  
    tsl.begin(); 
    sensors_event_t event;
    tsl.getEvent(&event);
    lux = event.light;
    
    if ((event.light == 0) || (event.light > 4294966000.0) || (event.light < -4294966000.0)) {
      
        lux = 201;
        Overflow = true;
    } 
    else {
      
        Overflow = false;
    }

    lux *= DomeMultiplier; // DomeMultiplier = 2.17
    
    if (lux < 40) {
      
        needHigh = true;
    } // 1 +1/3 de erro
    
    if (lux > 200) {
      
        needHigh = false;
    }
    
    if (needHigh) {

        lux *= .26;
    }
    
    return lux;
}

/*
 * CHANGED A LOT OF 'IF' IN 'ELSE IF' BECAUSE IS NOT NECESSARY USING ONLY 'IF'
 * AND ALSO THEY CAUSE A LOT OF MEANINGLESS AND USELESS CALCULATIONS.
 */

void cineMode() {

    int intCinefps = t_cine[tcm];                // FPS
        float t_final;                               // shutter speed/ shutter angle
        float N;
        float Fc;
        String Ev;                                   // F stop
        int Evplus;                                  // Thirds of stop
        String Fplus[] {F("+1/3") , F("+2/3")};      // String Array of Thirds of stop
        
        // Formula
        if (Anglemode) {
          
            t_final = pow((8640 / t_angle[tca]), -1);
        }
        else {
          
            t_final = pow(((intCinefps) * 2), -1);    // Shutter Speed // Formula because intCinefps is frames per second
        }
        
        N = sqrt((lux * S[Sm] * t_final) / C_const); // APERTURE in full value // eg: 2.845 -> 2.8
        
        Fc = lux * 0.0929;                     // FootCandle (lux_fc)

        // Translation for printing the Display
        if ((N >= 0.5) && (N < 0.8)) {
          
            Ev = F("0.7");
            Evplus = 2;
        }
        else if ((N >= 0.8) && (N < 0.9)) {
          
            Ev = F("0.7");
            Evplus = 0;
        }
        else if ((N >= 0.9) && (N < 1.0)) {
          
            Ev = F("0.7");
            Evplus = 1;
        }
        else if ((N >= 1.0) && (N < 1.1)) {
          
            Ev = F("1");
            Evplus = 2;
        }
        else if ((N >= 1.1) && (N < 1.2)) {
          
            Ev = F("1");
            Evplus = 0;
        }
        else if ((N >= 1.2) && (N < 1.4)) {
          
            Ev = F("1");
            Evplus = 1;
        }
        else if ((N >= 1.4) && (N < 1.6)) {
          
            Ev = F("1.4");
            Evplus = 2;
        }
        else if ((N >= 1.6) && (N < 1.8)) {
          
            Ev = F("1.4");
            Evplus = 0;
        }
        else if ((N >= 1.8) && (N < 2)) {
          
            Ev = F("1.4");
            Evplus = 1;
        }
        else if ((N >= 2.0) && (N < 2.2)) {
          
            Ev = F("2");
            Evplus = 2;
        }
        else if ((N >= 2.2) && (N < 2.5)) {
          
            Ev = F("2");
            Evplus = 0;
        }
        else if ((N >= 2.5) && (N < 2.8)) {
          
            Ev = F("2");
            Evplus = 1;
        }
        else if ((N >= 2.8) && (N < 3.2)) {
          
            Ev = F("2.8");
            Evplus = 2;
        }
        else if ((N >= 3.2) && (N < 3.5)) {
          
            Ev = F("2.8");
            Evplus = 0;
        }
        else if ((N >= 3.5) && (N < 4)) {
          
            Ev = F("2.8");
            Evplus = 1;
        }
        else if ((N >= 4.0) && (N < 4.5)) {
          
            Ev = F("4");
            Evplus = 2;
        }
        else if ((N >= 4.5) && (N < 5.0)) {
          
            Ev = F("4");
            Evplus = 0;
        }
        else if ((N >= 5.0) && (N < 5.6)) {
          
            Ev = F("4");
            Evplus = 1;
        }
        else if ((N >= 5.6) && (N < 6.3)) {
          
            Ev = F("5.6");
            Evplus = 2;
        }
        else if ((N >= 6.3) && (N < 7.1)) {
          
            Ev = F("5.6");
            Evplus = 0;
        }
        else if ((N >= 7.1) && (N < 8)) {
          
            Ev = F("5.6");
            Evplus = 1;
        }
        else if ((N >= 8.0) && (N < 9.0)) {
          
            Ev = F("8");
            Evplus = 2;
        }
        else if ((N >= 9) && (N < 10)) {
          
            Ev = F("8");
            Evplus = 0;
        }
        else if ((N >= 10) && (N < 11)) {
          
            Ev = F("8");
            Evplus = 1;
        }
        else if ((N >= 11) && (N < 13)) {
          
            Ev = F("11");
            Evplus = 2;
        }
        else if ((N >= 13) && (N < 14)) {
          
            Ev = F("11");
            Evplus = 0;
        }
        else if ((N >= 14) && (N < 16)) {
          
            Ev = F("11");
            Evplus = 1;
        }
        else if ((N >= 16) && (N < 18)) {
          
            Ev = F("16");
            Evplus = 2;
        }
        else if ((N >= 18) && (N < 20)) {
          
            Ev = F("16");
            Evplus = 0;
        }
        else if ((N >= 20) && (N < 22)) {
          
            Ev = F("16");
            Evplus = 1;
        }
        else if ((N >= 22) && (N < 25)) {
          
            Ev = F("22");
            Evplus = 2;
        }
        else if ((N >= 25) && (N < 29)) {
          
            Ev = F("22");
            Evplus = 0;
        }
        else if ((N >= 29) && (N < 32)) {
          
            Ev = F("22");
            Evplus = 1;
        }
        else if ((N >= 32) && (N < 36)) {
          
            Ev = F("32");
            Evplus = 2;
        }
        else if ((N >= 36) && (N < 40)) {
          
            Ev = F("32");
            Evplus = 0;
        }
        else if ((N >= 40) && (N < 45)) {
          
            Ev = F("32");
            Evplus = 1;
        }
        else if ((N >= 45) && (N < 51)) {
          
            Ev = F("45");
            Evplus = 2;
        }
        else if ((N >= 51) && (N < 57)) {
          
            Ev = F("45");
            Evplus = 0;
        }
        else if ((N >= 57) && (N < 64)) {
          
            Ev = F("45");
            Evplus = 1;
        }
        else if ((N >= 64) && (N < 72)) {
          
            Ev = F("64");
            Evplus = 2;
        }
        else if ((N >= 72) && (N < 80)) {
          
            Ev = F("64");
            Evplus = 0;
        }
        else if ((N >= 80) && (N < 90)) {
          
            Ev = F("64");
            Evplus = 1;
        } 
        
        //DISPLAY PRINTING, F STOP AND THIRDS
        
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        
        if ((N < 0.5) || (N > 90)) { 
          
            outOfrange();
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
        displayHighGain();

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

        refreshtiming(0);
}

/*
 * SAME THINGS AS ABOVE.
 */

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
        displayHighGain();
        
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
        
        refreshtiming(0);
}

/*
 * I MODULARIZED THIS FUNCTIONS IN TWO.
 */

void refresh() {              //This function gives a new calculation based on the last illuminance value, and refreshes the display.
  
    if (!Shuttermode) {   // CINEMODE
      
        cineMode();
    }  
    else {          //PHOTO MODE 
      
        photoMode();
    }
}
