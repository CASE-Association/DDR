#include <Arduino.h>
#include <FastLED.h>

#include <Keyboard.h>
#define ENTER_PIN 2
#define ESC_PIN 3
#define LED_PIN 4

bool lastEnter = HIGH;
bool lastEsc = HIGH;


#define ledcount 300


CRGB leds[ledcount];

void setup() {
  pinMode(ENTER_PIN, INPUT_PULLUP);
  pinMode(ESC_PIN, INPUT_PULLUP);
  Keyboard.begin();


  Serial.begin(115200);
  FastLED.addLeds<WS2811, LED_PIN, BRG>(leds, ledcount);
  leds[0]=CRGB::Red;
  FastLED.show();
  delay(1000);
}

int i = 0;

void loop() {
  if(i >= ledcount*3){
    i = 0;
  }
  
  bool enter = digitalRead(ENTER_PIN);
  bool esc = digitalRead(ESC_PIN);
  
  if (enter != lastEnter) {
    lastEnter = enter;
    if (enter == LOW) {
      Keyboard.press(KEY_RETURN);
      delay(50);
    }else{
      Keyboard.release(KEY_RETURN);
      delay(50);
    }
  }
  if (esc != lastEsc) {
    lastEsc = esc;
    if (esc == LOW) {
      Keyboard.press(KEY_ESC);
      delay(50);
    }else{
      Keyboard.release(KEY_ESC);
      delay(50);
    }
  }

  if(Serial.available() == 0){
    return;
  }
  byte val = Serial.read();
  if(val == 255){
    FastLED.show();
    i = 0;
  }else{
    leds[i/3][i%3]=val;
    i++;
  }
}