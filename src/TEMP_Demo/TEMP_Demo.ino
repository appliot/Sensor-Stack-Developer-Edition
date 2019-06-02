#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// 'temp_icon', 34x23px    http://javl.github.io/image2cpp/
const unsigned char temp_icon [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc7, 0x00, 0x00, 0x07,
  0xc6, 0x65, 0xb8, 0x00, 0x01, 0xcc, 0x27, 0x70, 0x00, 0x00, 0x84, 0x20, 0xc0, 0x00, 0x00, 0xc4,
  0x20, 0xc0, 0x00, 0x07, 0xc5, 0xa0, 0x78, 0x00, 0x00, 0xc5, 0xa0, 0x00, 0x00, 0x00, 0xc5, 0xa0,
  0x00, 0x00, 0x01, 0xcd, 0xa0, 0x00, 0x00, 0x07, 0xc5, 0xa0, 0x00, 0x00, 0x01, 0x8d, 0xa0, 0x00,
  0x00, 0x00, 0x05, 0xa0, 0x00, 0x00, 0x00, 0x0d, 0xb0, 0x00, 0x00, 0x00, 0x19, 0x98, 0x00, 0x00,
  0x00, 0x33, 0xc8, 0x00, 0x00, 0x00, 0x36, 0x68, 0x00, 0x00, 0x00, 0x13, 0xc8, 0x00, 0x00, 0x00,
  0x0c, 0x30, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00
};

#define OLED_ADDR   0x3C
//Adafruit_SSD1306 display(-1);
#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
//Adafruit_SSD1306 display(-1);

//#if (SSD1306_LCDHEIGHT != 64)
////#error("Height incorrect, please fix Adafruit_SSD1306.h!");
//#endif

int Thermistor_Pin = 4;
int Vo;
float R2 = 10000;
float logR1, R1, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {
  Serial.begin(115200);
  pinMode(Thermistor_Pin, INPUT);


  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
}

void loop() {
  Vo = analogRead(Thermistor_Pin);
  R1 = R2 * (4095.0 / (float)Vo - 1.0);
  logR1 = log(R1);
  T = (1.0 / (c1 + c2 * logR1 + c3 * logR1 * logR1 * logR1));
  Tc = T - 273.15;
  Tf = (Tc * 9.0) / 5.0 + 32.0;
  Serial.print(" %\t Temperature: ");
  Serial.print(Tc);
  Serial.println(" *C ");
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(42, 0);
  display.print("TEMP");
  display.setCursor(30, 15);
  display.print(Tc);
  display.display();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  // drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.drawBitmap(90, 10,  temp_icon , 34, 23, WHITE);
  display.display();
  delay(1000);
  display.clearDisplay();

  // put your main code here, to run repeatedly:

}
