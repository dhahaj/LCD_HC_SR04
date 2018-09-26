#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ST_HW_HC_SR04.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
ST_HW_HC_SR04 ultrasonicSensor(5, 6); // ST_HW_HC_SR04(TRIG, ECHO)

void setup()
{
    lcd.init(); // initialize the lcd
    lcd.backlight();
    lcd.clear();
    lcd.home();
    lcd.print(F("Sketch Starting!"));
    delay(2000);
}

// * hitTime / 29.10 = distance [centimeters]
// * hitTime / 74.75 = distance [inches]
void loop()
{
    float hitTime = ultrasonicSensor.getHitTime(); // In microseconds

    if( !hitTime && (ultrasonicSensor.getTimeout() == 5000) )
    {
        lcd.clear();
        lcd.home();
        lcd.print(F("Timeout!"));
        delay(1500);
    }
    else
    {
        float in = hitTime / 74.75,
              mm = hitTime / 29.10;
        lcd.home();
        lcd.print(F("Echo Time="));
        lcd.print((uint8_t)hitTime);
        lcd.print(F("us "));
        lcd.setCursor(0, 1);
        lcd.print(F("Dis="));
        lcd.print(mm);
        lcd.print(F("mm"));
        lcd.print(F(","));
        lcd.print(in);
        lcd.println(F("\""));
        delay(500);
    }
}
