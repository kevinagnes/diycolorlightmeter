#include <Config.h>

#pragma region LoopMethods

// Saves settings if buttons Bn2 and R are pressed (fyi: buttons are inverted).
void saveSettingsIfAppropriate() {
    if (!Bn2 && !R) {  
        saveAndDisplaySettings();
    }
}

// Adjusts a value based on the maximum size of an array and the increment flag.
int adjustValue(int val, const int size, bool isIncrement) {
    if (isIncrement) {
        if (val >= size - 1) {
            return 0;
        } else {
            return val + 1;
        }
    } else {
        if (val == 0) {
            return size - 1;
        } else {
            return val - 1;
        }
    }
}

// Adjusts tcm and Am values if system is not frozen.
void adjustValuesIfNotFrozen() {
    if (!freeze) {
        int t_cine_size = sizeof(t_cine) / sizeof(int);
        int A_size = sizeof(A) / sizeof(float);
        tcm = adjustValue(tcm, t_cine_size, !Bn1);
        Am = adjustValue(Am, A_size, !Bn1);
        tcm = adjustValue(tcm, t_cine_size, !Bn2);
        Am = adjustValue(Am, A_size, !Bn2);
    }
}

// Changes the shutter mode if buttons Bn1 and R are pressed (fyi: buttons are inverted).
void changeShutterModeIfButtonsPressed() {
    if (!Bn1 && !R) {  
        Shuttermode = !Shuttermode;
        displayModeWindow(3 + Shuttermode);
        delay(10);
    }
}

// Gets Lux if the Overflow flag is true.
void getLuxIfOverflow() {
    if (Overflow) {
        delay(10); 
        calculateLux();
    }
}

// Adjusts tca values if the Angle mode is active.
void adjustAngleValuesIfAngleMode() {
    if (Anglemode) {
        int t_angle_size = sizeof(t_angle) / sizeof(int);
        tca = adjustValue(tca, t_angle_size, !Bn1);
        tca = adjustValue(tca, t_angle_size, !Bn2);
    }
}

// Sets ISO mode if buttons Bn1 and Bn2 are pressed (fyi: buttons are inverted).
void ISOsetMode() {
    if (!Bn1 && !Bn2) {
        displayModeWindow(2);
        Bn1 = true;
        Bn2 = true;

        while (true) { 
            readButtons();

            if (!Bn1 && !Bn2) {
                //tone(Buzzer, 400, 50);
                freeze = false;
                Anglemode = false;
                displayModeWindow(1);

                break;
            }

            int S_size = sizeof(S) / sizeof(int);
            Sm = adjustValue(Sm, S_size, !Bn1);
            Sm = adjustValue(Sm, S_size, !Bn2);

            refresh();           
        }
    }
}

// Gets Lux and Color Temperature if the R button is pressed (fyi: buttons are inverted).
void getLuxAndColorTempIfRPressed() {
    if (!R) {
        lux = calculateLux();
        rgb_sensor.getColorTemp();
        //tone(Buzzer, 3000, 100);
    }
}
#pragma endregion

void setup() {
    // Set the mode of the pins to input pull-up
    pinMode(Bn1p, INPUT_PULLUP);
    pinMode(Bn2p, INPUT_PULLUP);
    pinMode(Rp, INPUT_PULLUP);

    // Initialize the display and clear it
    display.begin(SSD1306_SWITCHCAPVCC, 0x3D); 
    display.clearDisplay();  
    
    // Run the intro animation
    displayIntroAnimation();

    // Make sure the initial values of tcm and Sm are within their respective arrays' sizes
    if (tcm > (sizeof(t_cine) / sizeof(int) - 1)) {
        tcm = 2;
    }
    if (Sm > (sizeof(S) / sizeof(int) - 1)) {
        Sm = 2;
    }
    
    // Get the initial Lux and Color Temperature values
    lux = calculateLux();
    rgb_sensor.getColorTemp();
}

void loop() {
    // Call the functions that contain the main logic of the program in every loop iteration
    readButtons();
    displayBatteryPercentage();
    saveSettingsIfAppropriate();
    adjustValuesIfNotFrozen();
    changeShutterModeIfButtonsPressed();
    getLuxIfOverflow();
    adjustAngleValuesIfAngleMode();
    ISOsetMode();
    refresh();
    getLuxAndColorTempIfRPressed();
}
