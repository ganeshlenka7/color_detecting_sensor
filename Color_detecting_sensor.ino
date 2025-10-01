#include <Wire.h> // Include the Wire library for I2C communication
#include <LiquidCrystal_I2C.h> // Include the LiquidCrystal_I2C library

LiquidCrystal_I2C lcd(0x27, 16, 2); // Define LCD address and dimensions

// TCS230 pins connected to Arduino
const int s0 = 8;
const int s1 = 9;
const int s2 = 11;
const int s3 = 12;
const int out = 10;

// Variables
int red = 0;
int green = 0;
int blue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);

  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);

  lcd.init(); // Initialize the LCD
  lcd.backlight(); // Turn on the backlight
  lcd.setCursor(3, 0);
  lcd.print("Arduino RGB");
  lcd.setCursor(0, 1);
  lcd.print("Color Detector");
  delay(2000);
  lcd.clear();

  Serial.println("==================================");
  Serial.println("   Arduino Color Detection Start  ");
  Serial.println("==================================");
}

void loop() {
  color();

  // Print RGB values clearly
  Serial.print("Red: ");
  Serial.print(red);
  Serial.print(" | Green: ");
  Serial.print(green);
  Serial.print(" | Blue: ");
  Serial.print(blue);

  // Add nice spacing
  Serial.print("  --> ");

  if (red < blue && red < green && red < 25) {
    if (green - blue >= 10 && green - blue <= 25 && green - (2 * red) >= 8) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Detected Color:");
      lcd.setCursor(0, 1);
      lcd.print("RED");
      Serial.println("Red Color Detected");
    } else if (green - red <= 10 && green - red >= -3 && blue >= green) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Detected Color:");
      lcd.setCursor(0, 1);
      lcd.print("YELLOW");
      Serial.println("Yellow Color Detected");
    } else if (blue - red >= 3 && blue - red <= 10 && green - (2 * red) <= 5) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Detected Color:");
      lcd.setCursor(0, 1);
      lcd.print("PINK");
      Serial.println("Pink Color Detected");
    } else if (green - blue >= -5 && green - blue <= 5 && green - (2 * red) <= 5) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Detected Color:");
      lcd.setCursor(0, 1);
      lcd.print("ORANGE");
      Serial.println("Orange Color Detected");
    }
  } else if (green < red && green < blue && green < 25) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Detected Color:");
    lcd.setCursor(0, 1);
    lcd.print("GREEN");
    Serial.println("Green Color Detected");
  } else if ((red > green && blue < green) && blue < 25 && red > 40) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Detected Color:");
    lcd.setCursor(0, 1);
    lcd.print("BLUE");
    Serial.println("Blue Color Detected");
  } else if (red - (2 * blue) >= -2 && red - (2 * blue) <= 5 && green - red < 10) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Detected Color:");
    lcd.setCursor(0, 1);
    lcd.print("PURPLE");
    Serial.println("Purple Color Detected");
  } else if (blue < red && blue < green && (blue && red && green) < 25) {
    if (red - green <= 5 && red - green >= 0 && ((green - blue) || (red - blue)) < 5 && blue < 50) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Detected Color:");
      lcd.setCursor(0, 1);
      lcd.print("WHITE");
      Serial.println("White Color Detected");
    }
  } else {
    Serial.println("No Clear Match");
  }

  delay(300);
}

void color() {
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  digitalWrite(s3, HIGH);
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  digitalWrite(s2, HIGH);
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
}
