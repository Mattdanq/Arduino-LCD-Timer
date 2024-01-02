/*
  Matthew Danque mdanq2@uic.edu 653044344
  Lab 6 - Serial Monitor
  Kaz 8 am Tuesday
  The code is supposed to take inputs for TIME and DATE, and sets up a clock in which displays such and changes in real time.
  It will prompt you on each portion for TIME and DATE, but for date it will ask for year before the day as it will require the year to check for leap years.
  What I never expected is Serial.available() to be strange in which the serial monitor requires No Line Ending to avoid multiple inputs.
  Also you can't forget that seconds and minutes are RESET TO 0... fun fun
  References:
  https://forum.arduino.cc/t/serial-read-and-serial-available-are-working-not-as-expected-in-the-code/925823
  https://forum.arduino.cc/t/serial-available-doesnt-seem-to-work/635690/8
*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

bool prompt = true;
int month;
int day;
int year;
int hour;
int minute;
int second;

bool leap = false;
String datebuf;
String timebuf;

void setup() {
  // set up the LCD's number of columns and rows:
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  lcd.setCursor(0, 0);

  //checks if input(s) were made
  if (prompt == true) {
      prompt = false;

      bool day_set = false;
      bool month_set = false;
      bool year_set = false;
      bool hour_set = false;
      bool min_set = false;
      bool sec_set = false;

      //setting the month
      while (month_set == false) {
        lcd.setCursor(0,0);
        lcd.print("insert date");
        lcd.setCursor(0,1);
        lcd.print("set month");
        while (Serial.available() == 0) {}
        month = Serial.parseInt();
        //checks in month input is good
        if (month < 1 || month > 12) {
          lcd.clear();
          lcd.print("Incorrect month input");
          delay(3000);
        } else {
          month_set = true;
        }
        lcd.clear();
      }
      lcd.clear();

      //setting the year
      while (year_set == false) {
        lcd.setCursor(0,0);
        lcd.print("insert date");
        lcd.setCursor(0,1);
        lcd.print("set year");
        while (Serial.available() == 0) {}
        year = Serial.parseInt();

        //checks if the year is correct
        if (year < 1) {
          lcd.clear();
          lcd.print("Incorrect year");
          delay(3000);
        } else {
          if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
            leap = true;
          }
          year_set = true;
        }
        lcd.clear();
      }
      lcd.clear();

      //sets the day properly
      while (day_set == false) {
        lcd.setCursor(0,0);
        lcd.print("insert date");
        lcd.setCursor(0,1);
        lcd.print("set day");
        while (Serial.available() == 0) {}
        day = Serial.parseInt();
        lcd.setCursor(0,0);
        //checks the day input
        if (month == 2) {
          if (leap == true && (day > 0 && day < 30)) {
            day_set = true;
          } else if (leap == false && (day > 0 && day < 30)) {
            day_set = true;
          } else {
            lcd.clear();
            lcd.print("insert date");
            lcd.setCursor(0,1);
            lcd.print("Incorrect Day");
            delay(3000);
          }
        } else if (month % 2 == 0 && month < 7) {
          if (day > 0 && day < 31) {
            day_set = true;
          } else {
            lcd.clear();
            lcd.print("insert date");
            lcd.setCursor(0,1);
            lcd.print("Incorrect Day");
            delay(3000);
          }
        } else if (month % 2 == 0 && month > 7) {
          if (day > 0 && day < 32) {
            day_set = true;
          } else {
            lcd.clear();
            lcd.print("insert date");
            lcd.setCursor(0,1);
            lcd.print("Incorrect Day");
            delay(3000);
          }
        } else if (month % 2 == 1 && month < 8) {
          if (day > 0 && day < 32) {
            day_set = true;
          } else {
            lcd.clear();
            lcd.print("insert date");
            lcd.setCursor(0,1);
            lcd.print("Incorrect Day");
            delay(3000);
          }
        } else if (month % 2 == 1 && month > 7) {
          if (day > 0 && day < 31) {
            day_set = true;
          } else {
            lcd.clear();
            lcd.print("insert date");
            lcd.setCursor(0,1);
            lcd.print("Incorrect Day");
            delay(3000);
          }
        }
        lcd.clear();
      }
      lcd.clear();
      //sets hours properly
      while (hour_set == false) {
        lcd.setCursor(0,0);
        lcd.print("insert time");
        lcd.setCursor(0,1);
        lcd.print("set hour");
        while (Serial.available() == 0) {}
        hour = Serial.parseInt();
        lcd.setCursor(0,0);
        if (hour > 24 || hour < 1) {
          lcd.clear();
          lcd.print("insert time");
          lcd.setCursor(0,1);
          lcd.print("Incorrect hour");
          delay(3000);
        } else {
          hour_set = true;
        }
        lcd.clear();
      }
      lcd.clear();
      //sets minutes properly
      while (min_set == false) {
        lcd.setCursor(0,0);
        lcd.print("insert time");
        lcd.setCursor(0,1);
        lcd.print("set minute");
        while (Serial.available() == 0) {}
        minute = Serial.parseInt();
        lcd.setCursor(0,0);
        if (minute > 59 || minute < 0) {
          lcd.clear();
          lcd.print("insert time");
          lcd.setCursor(0,1);
          lcd.print("Incorrect min");
          delay(3000);
        } else {
          min_set = true;
        }
        lcd.clear();
      }
      lcd.clear();
      //sets seconds properly
      while (sec_set == false) {
        lcd.setCursor(0,0);
        lcd.print("insert time");
        lcd.setCursor(0,1);
        lcd.print("set seconds");
        while (Serial.available() == 0) {}
        second = Serial.parseInt();
        lcd.setCursor(0,0);
        if (second > 59 || second < 0) {
          lcd.clear();
          lcd.print("insert time");
          lcd.setCursor(0,1);
          lcd.print("Incorrect secs");
          delay(3000);
        } else {
          sec_set = true;
        }
        lcd.clear();
      }
      lcd.clear();
    prompt = false;
  } else {
    lcd.clear();
    //just in case there is confusion with the year being less than a thousand/s
    String trueYear;
    if (year < 10) {
      trueYear = "000" + String(year);
    } else if (year < 100) {
      trueYear = "00" + String(year);
    } else if (year < 1000) {
      trueYear = "0" + String(year);
    } else {
      trueYear = String(year);
    }
    datebuf = "date: " + String(month) + "/" + String(day) + "/" + trueYear;
    String trueHour;
    String trueMin;
    String trueSec;
    //makes the timer more professional in some sense
    if (hour < 10) {
      trueHour = "0" + String(hour);
    } else {
      trueHour = String(hour);
    }
    if (minute < 10) {
      trueMin = "0" + String(minute);
    } else {
      trueMin = String(minute);
    }
    if (second < 10) {
      trueSec = "0" + String(second);
    } else {
      trueSec = String(second);
    }
    timebuf = "time: " + trueHour + ":" + trueMin + ":" + trueSec;
    lcd.setCursor(0,0);
    lcd.print(datebuf);
    lcd.setCursor(0,1);
    lcd.print(timebuf);
    delay(1000);
    second++;
    //makes sure everything updates in proper order
    if (second == 60) {second = 0; minute++;}
    if (minute == 60) {minute = 0; hour++;}
    if (hour == 24) {hour = 1; day++;}

    if (leap == true && month == 2 && day == 30) {
      day = 1;
      month++;
    } else if (leap == false && month == 2 && day == 29) {
      month++;
      day = 1;
    } else if (month % 2 == 0 && day == 31 && month < 7) {
      day = 1;
      month++;
    } else if (month % 2 == 0 && day == 32 && month > 6) {
      day = 1;
      month++;
    } else if (month % 2 == 1 && day == 32 && month < 8) {
      day = 1;
      month++;
    } else if (month % 2 == 1 && day == 31 && month > 7) {
      day = 1;
      month++;
    }
    if (month == 13) {
      month = 1;
      year++;
      if (year % 4 == 0 && year % 100 != 0 && year % 400 == 0) {
        leap = true;
      } else {
        leap = false;
      }
    }
  }
}