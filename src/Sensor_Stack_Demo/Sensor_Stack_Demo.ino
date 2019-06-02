#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define OLED_ADDR   0x3C
//Adafruit_SSD1306 display(-1);
#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
//Adafruit_SSD1306 display(-1);
//
//#if (SSD1306_LCDHEIGHT != 64)
////#error("Height incorrect, please fix Adafruit_SSD1306.h!");
//#endif
#define DEMO_CASE 1
#define BLINK_CASE 2
#define RGB_CASE 3
#define LDR_CASE 4
#define TEMP_CASE 5
#define BUZZER_CASE 6
#define TILT_CASE 7

static int case_value = 1;
int wait_time  = 5000;

int Blink_Pin = 2;
static boolean led_blink = true;

#define NUMPIXELS      1
#define RGB_Pin 33
int RGB_Power_Pin = 32;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, RGB_Pin, NEO_GRB + NEO_KHZ800);

int Buzzer_Pin = 14;


int ldr_pin = 15;
int LDR_VALUE;

int Thermistor_Pin = 4;
int Vo;
float R2 = 10000;
float logR1, R1, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

int Tilt_Pin = 13;
int Tilt_data;
String Tilt_String;
char linebuf[80];
int charcount = 0;

int blink_delay = 500;
int rgb_delay = 500;
int buzzer_delay = 500;


void setup() {
  Serial.begin(115200);

  pinMode(Blink_Pin, OUTPUT);
  pinMode(RGB_Pin, OUTPUT);
  pinMode(RGB_Power_Pin, OUTPUT);
  pinMode(Buzzer_Pin, OUTPUT);
  pinMode(ldr_pin, INPUT);
  pinMode(Thermistor_Pin, INPUT);
  pinMode(Tilt_Pin, INPUT);

#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin();

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.setCursor(32, 0);
  display.print("SENSOR");
  display.display();
  display.setCursor(37, 16);
  display.print("STACK");
  display.display();
  Serial.println("SENSOR STACK");
  delay(2000);
  display.clearDisplay();
  //  display.setTextSize(2);
  //  display.setTextColor(WHITE);
}

void loop() {


  switch (case_value)
  {
    case DEMO_CASE:// oled demo
      Serial.println("STARTING DEMO");
      display.setCursor(20, 0);
      display.print("STARTING");
      display.display();
      display.setCursor(43, 16);
      display.print("DEMO");
      display.display();
      case_value = BLINK_CASE;
      delay(2000);
      break;
    case BLINK_CASE: // blink demo

      Serial.println("BLINK TEST");
      display.clearDisplay();
      display.setCursor(37, 0);
      display.print("BLINK");
      display.display();
      display.setCursor(42, 16);
      display.print("TEST");
      display.display();

      for (int i = 0; i <= wait_time; i++)
      {
        digitalWrite(Blink_Pin, led_blink);
        led_blink = !led_blink;
        i += 500;
        delay(blink_delay);
      }
      case_value = RGB_CASE;
      break;
    case RGB_CASE:  // RGB demo
      Serial.println("RGB TEST");
      display.clearDisplay();
      display.setCursor(50, 0);
      display.print("RGB");
      display.display();
      display.setCursor(42, 16);
      display.print("TEST");
      display.display();
      digitalWrite(RGB_Power_Pin, HIGH);
      for (int i = 0; i <= wait_time; i++)
      {
        pixels.setPixelColor(0, pixels.Color(150, 0, 0)); // Moderately bright green color.

        pixels.show(); // This sends the updated pixel color to the hardware.

        delay(rgb_delay);
        pixels.setPixelColor(0, pixels.Color(0, 150, 0)); // Moderately bright green color.

        pixels.show(); // This sends the updated pixel color to the hardware.
        delay(rgb_delay);
        pixels.setPixelColor(0, pixels.Color(0, 0, 150)); // Moderately bright green color.

        pixels.show(); // This sends the updated pixel color to the hardware.
        i += 1000;
        delay(rgb_delay);
      }
      digitalWrite(RGB_Power_Pin, LOW);
      case_value = LDR_CASE;
      break;
    case LDR_CASE:  //  LDR demo
      display.clearDisplay();
      for (int i = 0; i <= wait_time; i++)
      {
        display.clearDisplay();
        int LDR_VALUE = analogRead(ldr_pin);
        display.setCursor(50, 0);
        display.print("LDR");
        display.display();
        display.setCursor(42, 16);
        display.print(LDR_VALUE);
        display.display();
        i += 500;
        Serial.print("LDR:- ");
        Serial.println(LDR_VALUE);
        delay(1000);
      }
      case_value = TEMP_CASE;
      break;
    case TEMP_CASE:  //  TEMP_CASE demo
      display.clearDisplay();
      Vo = analogRead(Thermistor_Pin);
      R1 = R2 * (4095.0 / (float)Vo - 1.0);
      logR1 = log(R1);
      T = (1.0 / (c1 + c2 * logR1 + c3 * logR1 * logR1 * logR1));
      Tc = T - 273.15;
      Tf = (Tc * 9.0) / 5.0 + 32.0;
      //      display.setCursor(0, 0);
      //      display.print("TEMPERATURE");
      display.setCursor(42, 0);
      display.print("TEMP");
      display.display();
      display.setCursor(25, 16);
      display.print(Tc);
      display.setCursor(90, 16);
      display.print("\176C");
      display.display();
      Serial.print("TEMP:- ");
      Serial.print(Tc);
      Serial.println(" *c");
      delay(wait_time);
      case_value = TILT_CASE;
      break;
    case TILT_CASE:  //  BUZZER_CASE demo
      display.clearDisplay();

      for (int i = 0; i <= wait_time; i++)
      {
        display.clearDisplay();
        Tilt_data = digitalRead(Tilt_Pin);
        if (Tilt_data == 1)
        {
          Tilt_String = "ON";
        }
        else
        {
          Tilt_String = "OFF";
        }
        display.setCursor(42, 0);
        display.print("TILT  ");
        display.display();
        display.setCursor(12, 16);
        display.print("SWITCH ");
        display.setCursor(90, 16);
        display.print(Tilt_String);
        display.display();
        Serial.print("TILT SWITCH:- ");
        Serial.println(Tilt_String);
        i += 500;
        delay(500);
      }
      case_value = BUZZER_CASE;
      break;
    case BUZZER_CASE:  //  BUZZER_CASE demo
      Serial.println("BUZZER TEST");
      display.clearDisplay();
      display.setCursor(30, 0);
      display.print("BUZZER ");
      display.display();
      display.setCursor(42, 16);
      display.print("TEST");
      display.display();
      for (int i = 0; i <= wait_time; i++)
      {
        digitalWrite(Buzzer_Pin, led_blink);
        led_blink = !led_blink;
        i += 500;
        delay(buzzer_delay);
      }
      case_value = DEMO_CASE;
      display.clearDisplay();
      break;
    default:
      break;

  }
  // delay(wait_time);
}
