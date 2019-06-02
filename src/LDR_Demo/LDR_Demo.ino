#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// 'arrow - Copy', 37x37px

#define OLED_ADDR   0x3C
//Adafruit_SSD1306 display(-1);
#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
//Adafruit_SSD1306 display(-1);
//
// 'bulb_icon', 41x21px    http://javl.github.io/image2cpp/
const unsigned char bulb_icon [] PROGMEM = {
  0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1c, 0x0c, 0x00, 0x00, 0x00, 0x0c, 0x08, 0x18,
  0x00, 0x00, 0x00, 0x06, 0x7f, 0x30, 0x00, 0x00, 0x06, 0x03, 0xff, 0xe0, 0x30, 0x00, 0x07, 0xce,
  0x00, 0x39, 0xf0, 0x00, 0x00, 0x38, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x30, 0x00, 0x06, 0x00, 0x00,
  0x00, 0x60, 0x00, 0x03, 0x00, 0x00, 0x3f, 0x60, 0xff, 0x83, 0x7e, 0x00, 0x00, 0x70, 0xff, 0x83,
  0x00, 0x00, 0x00, 0x30, 0x3e, 0x06, 0x00, 0x00, 0x01, 0xdc, 0x1c, 0x1d, 0xc0, 0x00, 0x07, 0x0e,
  0x1c, 0x38, 0xf0, 0x00, 0x00, 0x03, 0x9c, 0xe0, 0x00, 0x00, 0x00, 0x01, 0x9c, 0xc0, 0x00, 0x00,
  0x00, 0x00, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0xc1, 0x80, 0x00, 0x00, 0x00, 0x00, 0xc1, 0x80,
  0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00
};

//#if (SSD1306_LCDHEIGHT != 64)
////#error("Height incorrect, please fix Adafruit_SSD1306.h!");
//#endif

int ldr_pin = 15;
int LDR_VALUE;

void setup() {
  Serial.begin(115200);

  pinMode(ldr_pin, INPUT);

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();

}

void loop() {

  LDR_VALUE = analogRead(ldr_pin);

  Serial.print("LDR_VALUE:- ");
  Serial.println(LDR_VALUE);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(50, 0);
  display.print("LDR");
  display.setCursor(35, 16);
  display.print(LDR_VALUE);
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  // drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.drawBitmap(85, 10,  bulb_icon , 41, 21, WHITE);
  display.display();
  delay(5000);
  display.clearDisplay();

  // put your main code here, to run repeatedly:

}
