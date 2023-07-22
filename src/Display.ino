#pragma region Display Functions

// Displays an out-of-range message on the display.
void displayOutOfRangeMessage() {
    display.setTextSize(1);
    display.print("OUT OF RANGE!");
}

// Displays a high gain message on the display if necessary.
void displayHighGainIfNeeded() {
    if (needHigh) {
        display.drawLine(0, 18, 12, 18, WHITE); // Draws a horizontal line divisor.
        display.drawLine(0, 28, 12, 28, WHITE); // Draws a horizontal line divisor.
        display.drawLine(12, 18, 12, 28, WHITE); // Draws a vertical line divisor.
        display.setCursor(0, 20);  
        display.println(F("Hi"));
    }
}

// Refreshes the display with a delay.
void refreshDisplayWithDelay(short delayTime) {
    display.display();
    delay(delayTime);
    display.clearDisplay();
}

// Displays the current battery level as a percentage on the display.
void displayBatteryPercentage() {
    float percentage = vcc.Read_Perc(VccMin, VccMax);

    if (percentage >= 80 && percentage <= 100) {
        display.drawBitmap(115, 0, battery_full, 16, 8, WHITE);
    } else if (percentage >= 60 && percentage < 80) {
        display.drawBitmap(115, 0, battery_threequarters, 16, 8, WHITE);
    } else if (percentage >= 40 && percentage < 60) {
        display.drawBitmap(115, 0, battery_half, 16, 8, WHITE);
    } else if (percentage >= 20 && percentage < 40) {
        display.drawBitmap(115, 0, battery_low, 16, 8, WHITE);
    } else {
        display.drawBitmap(115, 0, battery_empty, 16, 8, WHITE);
    }
}

// Displays the current mode on the window.
void displayModeWindow(uint8_t modeIndex) {
    String modeList[] = {F("Saved"), F("Selected"), F("ISO Set"), F("CINE Mode"), F("PHOTO Mode"),
                         F("Freezed"), F("Unfreezed"), F(""), F("Aperture Priority"), F("Shutter Priority")};

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(6, 10);
    display.println(modeList[modeIndex]);
    display.setCursor(5, 0);
    display.setTextSize(1);
    display.println(modeList[modeIndex + 5]);

    refreshDisplayWithDelay(500);  
}

// Performs the introduction animation on the display.
void displayIntroAnimation() {
    display.drawBitmap(40, -8, fstop_logo, 48, 48, WHITE);
    refreshDisplayWithDelay(1000);
}
#pragma endregion
