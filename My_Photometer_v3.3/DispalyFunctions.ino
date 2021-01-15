void outOfrange() {
  
    display.setTextSize(1);
    display.print("OUT OF RANGE!");
}

void displayHighGain() {
  
    if (needHigh) {
      
        display.drawLine(0, 18, 12, 18, WHITE); // LINE DIVISOR
        display.drawLine(0, 28, 12, 28, WHITE); // LINE DIVISOR
        display.drawLine(12, 18, 12, 28, WHITE); // LINE DIVISOR
        display.setCursor(0, 20);  
        display.println(F("Hi"));
    }
}

/*
 * HERE I'VE DELETED THE ARRAY, AND I DECIDED TO PASS THE VALUE
 * THROUGH A PARAMETER.
 */
 
void refreshtiming(short t) {
    
    display.display();
    delay(t);
    display.clearDisplay();
}

/*
 * ADDED BATTERY PERCENTAGE CALCULATOR FUNCTION
 */

void batteryPerc() {

    float perc = vcc.Read_Perc(VccMin, VccMax);
    //Serial.println(vcc.Read_Perc(VccMin, VccMax));

    if(perc >= 80 && perc <= 100) {

        display.drawBitmap(115, 0, battery_full, 16, 8, WHITE);
    }
    else if(perc >= 60 && perc < 80) {

        display.drawBitmap(115, 0, battery_threequarters, 16, 8, WHITE);
    }
    else if(perc >= 40 && perc < 60) {

        display.drawBitmap(115, 0, battery_half, 16, 8, WHITE);
    }
    else if(perc >= 20 && perc < 40) {

        display.drawBitmap(115, 0, battery_low, 16, 8, WHITE);
    }
    else {

        display.drawBitmap(115, 0, battery_empty, 16, 8, WHITE);
    }
}

/*
 * HERE I REMOVED THE 'IF-ELSE' AND MODIFIED THE CODE ON LOOP FUNCTION AT LINE 284
 */

void modeWindow(uint8_t Astring) {
  
    String modeA[] = {F("Saved"), F("Selected"), F("ISO Set"), F("CINE Mode"), F("PHOTO Mode"),
                      F("Freezed"), F("Unfreezed"), F(""), F("Aperture Priority"), F("Shutter Priority")};
    
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(6, 10);
    display.println(modeA[Astring]);
    display.setCursor(5, 0);
    display.setTextSize(1);
    display.println(modeA[Astring + 5]);
    
    refreshtiming(500);  
}

/*
 * I CHANGED THE ANIMATIONS AT THE BEGGING. SORRY :) 
 */

void introAnimation() {

    display.drawBitmap(40, -8, fstop_logo, 48, 48, WHITE);
    
    refreshtiming(1000);
}
