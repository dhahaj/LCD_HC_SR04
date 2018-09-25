#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ST_HW_HC_SR04.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
ST_HW_HC_SR04 ultrasonicSensor(5, 6); // ST_HW_HC_SR04(TRIG, ECHO)

void setup() {
    lcd.init(); // initialize the lcd
    lcd.backlight();
    lcd.clear();
    lcd.home();
    Serial.begin(9600);
    lcd.print("Sketch Starting!");
    delay(200);
}

//A bit more accurate distance formulas:
// * hitTime / 29.10 = distance [centimeters]
// * hitTime / 74.75 = distance [inches]
void loop() {
    float hitTime = ultrasonicSensor.getHitTime(); // In microseconds
    float distance = hitTime / 29.10;
    String message = "The hit time was " + String(hitTime) + " microseconds, distance = " + String(distance) + "\n";

    if( !hitTime && (ultrasonicSensor.getTimeout() == 5000) )
    {
        lcd.clear();
        lcd.home();
        lcd.print("Timeout!");
    }

    else
    {
        lcd.home();
        lcd.print("HitTime=");
        lcd.println(hitTime);
        lcd.print("Dist=");
        lcd.print(hitTime);
        lcd.print(",");
        lcd.print(hitTime / 74.75);
        lcd.println("\"");
    }
    
    delay(1500); // Delay 1500ms (1.5s)
}
