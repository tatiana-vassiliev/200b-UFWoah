
#include <FastLED.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#define NUM_LEDS 110
#define DATA_PIN 2
#define CLOCK_PIN 13
// constants won't change. They're used here to set pin numbers:
int sensorPin = A0;
const int buttonPin1 = 3;
const int buttonPin2 = 4;
const int buttonPin3 = 5;
const int buttonPin4 = 6;
const int buttonPin5 = 7;
const int buttonPin6 = 8;
const int buttonPin7 = 9;
const int ledPin = 2;    // the number of the LED pin
CRGB leds[NUM_LEDS];
SoftwareSerial mySoftwareSerial(11, 10);                    // Recieve Pin (RX), Transmit Pin (TX)
DFRobotDFPlayerMini myDFPlayer;                           // Create myDFPlayer of the DFPlayer Class
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int buttonState5 = 0;
int buttonState6 = 0;
bool twisting = false;
int button_one = 0;
int button_two = 0;
int button_one_past = 0;
int button_two_past = 0;
int score = 0;
int safe = 0;
int game_state = 1;
float reference_Value=0;
int sensorValue = 0;
float current_time = 0;
float past_time = 0;




void clearLed(int ledId) 
{
	leds[ledId] = CRGB(0, 0, 0);
  FastLED.show();
}

void light(int button) 
{
  // turn LED on:
  int middle = 0;
  int R = 0;
  int G = 0;
  int B = 0;
  if (button ==1)
  {
    R = 193;
    G = 228;
    middle = 4;
  }
  else if (button == 2)
  {
    R = 80;
    G = 185;
    middle = 22;
  }
  else if (button == 3)
  {
    R = 12;
    G = 145;
    middle = 41;
  }
  else if (button == 4)
  {
    R = 2;
    G = 255;
    B = 85;
    middle = 59;
  }
  else if (button == 5)
  {
    R = 2;
    G = 126;
    B = 188;
    middle = 77;
  }
  else if (button == 6)
  {
    B = 255;
    middle = 95;
  }
  if ((button >1) && (button <7) && !(button==3))
  {
    for (int i = middle-6; i < middle+7; i++) 
    {                           // Turn the LEDs off before starting
      clearLed(i);
    }
    FastLED.show();
    leds[middle] = CRGB(R,G,B);
    leds[middle+1] = CRGB(R,G,B);
    leds[middle-1] = CRGB(R,G,B);
    FastLED.show();
    delay(100);
    leds[middle+2] = CRGB(R,G,B);
    leds[middle-2] = CRGB(R,G,B);
    leds[middle+3] = CRGB(R,G,B);
    leds[middle-3] = CRGB(R,G,B);
    FastLED.show();
    delay(100);
    leds[middle+4] = CRGB(R,G,B);
    leds[middle-4] = CRGB(R,G,B);
    leds[middle+5] = CRGB(R,G,B);
    leds[middle-5] = CRGB(R,G,B);
    FastLED.show();
    delay(100);
    leds[middle+6] = CRGB(R,G,B);
    leds[middle-6] = CRGB(R,G,B);
    FastLED.show();
  }
  else if (button == 1)
  {
    for (int i = middle-4; i < middle+7; i++) 
    {                           // Turn the LEDs off before starting
      clearLed(i);
    }
    clearLed(108);
    FastLED.show();
    leds[middle] = CRGB(R,G,B);
    leds[middle+1] = CRGB(R,G,B);
    leds[middle-1] = CRGB(R,G,B);
    FastLED.show();
    delay(100);
    leds[middle+2] = CRGB(R,G,B);
    leds[middle-2] = CRGB(R,G,B);
    leds[middle+3] = CRGB(R,G,B);
    leds[middle-3] = CRGB(R,G,B);
    FastLED.show();
    delay(100);
    leds[middle+4] = CRGB(R,G,B);
    leds[middle-4] = CRGB(R,G,B);
    leds[middle+5] = CRGB(R,G,B);
    leds[108] = CRGB(R,G,B);
    delay(100);
    leds[middle+6] = CRGB(R,G,B);
    FastLED.show();
  }
  else if (button == 3)
  {
    for (int i = middle-7; i < middle+7; i++) 
    {                           // Turn the LEDs off before starting
      clearLed(i);
    }
    FastLED.show();
    leds[middle] = CRGB(R,G,B);
    leds[middle+1] = CRGB(R,G,B);
    leds[middle-1] = CRGB(R,G,B);
    FastLED.show();
    delay(100);
    leds[middle+2] = CRGB(R,G,B);
    leds[middle-2] = CRGB(R,G,B);
    leds[middle+3] = CRGB(R,G,B);
    leds[middle-3] = CRGB(R,G,B);
    FastLED.show();
    delay(100);
    leds[middle+4] = CRGB(R,G,B);
    leds[middle-4] = CRGB(R,G,B);
    leds[middle+5] = CRGB(R,G,B);
    leds[middle-5] = CRGB(R,G,B);
    FastLED.show();
    delay(100);
    leds[middle+6] = CRGB(R,G,B);
    leds[middle-6] = CRGB(R,G,B);
    leds[middle-7] = CRGB(R,G,B);
    FastLED.show();
  }
  else if (button == 7)
  {
    clearLed(108);
    for (int i = 0; i < 108; i++) 
    {                           // Turn the LEDs off before starting
      clearLed(i);
    }
    for (int i = 0; i < 109; i=i+2) 
    {                           // Turn the LEDs off before starting
      leds[i] = CRGB(100,0,100);
      FastLED.show();
    }
  }
}

void playAudio(int s) 
{
  myDFPlayer.play(s);
}

int generate(int change, int buttonOne, int buttonTwo)
{
  if (change == 1)
  {
    buttonOne= random(1,8);
    while (buttonOne==buttonTwo or buttonOne == button_one_past)
    {
      buttonOne= random(1,8);
    }
    Serial.print(buttonOne);
    Serial.print(button_one_past);
    Serial.println("");
    return buttonOne;
  }
  else if (change == 2)
  {
    buttonTwo= random(1,8);
    while (buttonOne==buttonTwo or buttonTwo == button_two_past)
    {
      buttonTwo= random(1,8);
    }
    Serial.print(buttonTwo);
    Serial.print(button_two_past);
    Serial.println("");
    return buttonTwo;
  }
}

void check(int button)
{
  if (button == safe)
  {
  }
  else if (button == button_one)
  {
    past_time =millis();
    playAudio(3);
    score +=1;
    if (button == 1)
    {
      clearLed(108);
      for (int i = 0; i < 11; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
      for (int i = 0; i < 11; i++) 
      {                           // Turn the LEDs off before starting
      leds[i] = CRGB(255,255,255);
      }
      leds[108]=CRGB(255,255,255);
      FastLED.show();
      delay(100);
      clearLed(108);
      for (int i = 0; i < 11; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
    }
    else if (button == 2)
    {
      for (int i = 16; i < 29; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
      for (int i = 16; i < 29; i++) 
      {                           // Turn the LEDs off before starting
      leds[i] = CRGB(255,255,255);
      }
      FastLED.show();
      delay(100);
      for (int i = 16; i < 29; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
    }
    else if (button == 3)
    {
      for (int i = 34; i < 48; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
      for (int i = 34; i < 48; i++) 
      {                           // Turn the LEDs off before starting
      leds[i] = CRGB(255,255,255);
      }
      FastLED.show();
      delay(100);
      for (int i = 34; i < 48; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
    }
    else if (button == 4)
    {
      for (int i = 53; i < 66; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
      for (int i = 53; i < 66; i++) 
      {                           // Turn the LEDs off before starting
      leds[i] = CRGB(255,255,255);
      }
      FastLED.show();
      delay(100);
      for (int i = 53; i < 66; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
    }
    else if (button == 5)
    {
      for (int i = 71; i < 84; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
      for (int i = 71; i < 84; i++) 
      {                           // Turn the LEDs off before starting
      leds[i] = CRGB(255,255,255);
      }
      FastLED.show();
      delay(100);
      for (int i = 71; i < 84; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
    }
    else if (button == 6)
    {
      for (int i = 89; i < 102; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
      for (int i = 89; i < 102; i++) 
      {                           // Turn the LEDs off before starting
      leds[i] = CRGB(255,255,255);
      }
      FastLED.show();
      delay(100);
      for (int i = 89; i < 102; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
    }
    safe = button_one;
    button_one_past = button_one;
    button_one = 0;
  }
  else if (button == button_two)
  {
    past_time=millis();
    playAudio(3);
    score +=1;
    if (button == 1)
    {
      clearLed(108);
      for (int i = 0; i < 11; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
      for (int i = 0; i < 11; i++) 
      {                           // Turn the LEDs off before starting
      leds[i] = CRGB(255,255,255);
      }
      leds[108]=CRGB(255,255,255);
      FastLED.show();
      delay(100);
      clearLed(108);
      for (int i = 0; i < 11; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
    }
    else if (button == 2)
    {
      for (int i = 16; i < 29; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
      for (int i = 16; i < 29; i++) 
      {                           // Turn the LEDs off before starting
      leds[i] = CRGB(255,255,255);
      }
      FastLED.show();
      delay(100);
      for (int i = 16; i < 29; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
    }
    else if (button == 3)
    {
      for (int i = 34; i < 48; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
      for (int i = 34; i < 48; i++) 
      {                           // Turn the LEDs off before starting
      leds[i] = CRGB(255,255,255);
      }
      FastLED.show();
      delay(100);
      for (int i = 34; i < 48; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
    }
    else if (button == 4)
    {
      for (int i = 53; i < 66; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
      for (int i = 53; i < 66; i++) 
      {                           // Turn the LEDs off before starting
      leds[i] = CRGB(255,255,255);
      }
      FastLED.show();
      delay(100);
      for (int i = 53; i < 66; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
    }
    else if (button == 5)
    {
      for (int i = 71; i < 84; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
      for (int i = 71; i < 84; i++) 
      {                           // Turn the LEDs off before starting
      leds[i] = CRGB(255,255,255);
      }
      FastLED.show();
      delay(100);
      for (int i = 71; i < 84; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
    }
    else if (button == 6)
    {
      for (int i = 89; i < 102; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
      for (int i = 89; i < 102; i++) 
      {                           // Turn the LEDs off before starting
      leds[i] = CRGB(255,255,255);
      }
      FastLED.show();
      delay(100);
      for (int i = 89; i < 102; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
    }
    safe = button_two;
    button_two_past = button_two;
    button_two = 0;
  }
  else
  {
    if (button == 1)
    {
      clearLed(108);
      for (int i = 0; i < 11; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
      for (int i = 0; i < 11; i++) 
      {                           // Turn the LEDs off before starting
      leds[i] = CRGB(255,0,0);
      }
      leds[108]=CRGB(255,0,0);
      FastLED.show();
      delay(100);
      clearLed(108);
      for (int i = 0; i < 11; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
    }
    else if (button == 2)
    {
      for (int i = 16; i < 29; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
      for (int i = 16; i < 29; i++) 
      {                           // Turn the LEDs off before starting
      leds[i] = CRGB(255,0,0);
      }
      FastLED.show();
      delay(100);
      for (int i = 16; i < 29; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
    }
    else if (button == 3)
    {
      for (int i = 34; i < 48; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
      for (int i = 34; i < 48; i++) 
      {                           // Turn the LEDs off before starting
      leds[i] = CRGB(255,0,0);
      }
      FastLED.show();
      delay(100);
      for (int i = 34; i < 48; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
    }
    else if (button == 4)
    {
      for (int i = 53; i < 66; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
      for (int i = 53; i < 66; i++) 
      {                           // Turn the LEDs off before starting
      leds[i] = CRGB(255,0,0);
      }
      FastLED.show();
      delay(100);
      for (int i = 53; i < 66; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
    }
    else if (button == 5)
    {
      for (int i = 71; i < 84; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
      for (int i = 71; i < 84; i++) 
      {                           // Turn the LEDs off before starting
      leds[i] = CRGB(255,0,0);
      }
      FastLED.show();
      delay(100);
      for (int i = 71; i < 84; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
    }
    else if (button == 6)
    {
      for (int i = 89; i < 102; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
      for (int i = 89; i < 102; i++) 
      {                           // Turn the LEDs off before starting
      leds[i] = CRGB(255,0,0);
      }
      FastLED.show();
      delay(100);
      for (int i = 89; i < 102; i++) 
      {                           // Turn the LEDs off before starting
      clearLed(i);
      }
    }
    clearLed(108);
    for (int i = 0; i < 108; i++) 
    {                           // Turn the LEDs off before starting
    clearLed(i);
    }
    for (int i = 0; i < 109; i++) 
    {                           // Turn the LEDs off before starting
      leds[i] = CRGB(255,0,0);
      FastLED.show();
    }
    game_state = 3;
  }
}

void playScoreSound(int s) 
{
  if (s < 20) 
  {
    playAudio(s + 11);
    delay(1500);
  } 
  else if (s < 100) 
  {
    int tens = (s) / 10;
    int ones = (s) % 10;
    playAudio(tens + 29);
    delay(800);
    if (ones != 0) 
    {
      playAudio(ones + 11);
      delay(1500);
    }
  } 
}

void setup() {
  int i;
  float sum=0;
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
  Serial.println("Please do not rotate it before calibrate!");
  Serial.println("Get the reference value:");
  for(i=0;i<1000;i++)
  {
      // read the value from the sensor:
       sensorValue = analogRead(sensorPin);
       sum += sensorValue;
       delay(5);
  }
  reference_Value = sum/1000.0;
  Serial.println(reference_Value);
  Serial.println("Now you can begin your test!");

  FastLED.addLeds<WS2812B,DATA_PIN,GRB>(leds,NUM_LEDS);
	FastLED.setBrightness(84);
  randomSeed(analogRead(0));
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);
  pinMode(buttonPin6, INPUT_PULLUP);
  for (int i = 0; i < 110; i++) 
  {                           // Turn the LEDs off before starting
    clearLed(i);
  }
  mySoftwareSerial.begin(9600);                           // Initiate communication with the DFPlayer
  Serial.begin(115200);                                   // Mostly used for debugging
  delay(1000);
  if (!myDFPlayer.begin(mySoftwareSerial, true, false)) {              // Use softwareSerial to communicate with mp3. If we have trouble,
    Serial.println(F("Unable to begin:"));                // print to the serial monitor so we can see.
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
  } else {
    Serial.println(F("DFPlayer Mini online."));          
  }
  myDFPlayer.volume(30);                                   // Set volume value. From 0 to 30
  //playAudio(1);       
  //playAudio(2);
  //playAudio(3); 
  playAudio(42);                                    // Play the first mp3! Exciting stuff                                         // This delay and digital write is timed to turn each light on and off                                        // We're all set with this state. Let's set the state to 1 to start the sequence playing
  light(1);
  light(2);
  light(3);
  light(4);
  light(5);
  light(6);
}

void loop() 
{
  // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  buttonState5 = digitalRead(buttonPin5);
  buttonState6 = digitalRead(buttonPin6);
  if (game_state ==1)
  {
    score = 0;
    button_one = 0;
    button_two = 0;
    button_one = 0;
    button_one_past = 0;
    button_two_past = 0;
    score = 0;
    safe = 0;
    if (buttonState1 == LOW)
    {
      game_state = 2;
      safe = 1;
    }
    if (buttonState2 == LOW)
    {
      game_state = 2;
      safe = 2;
    }
    if (buttonState3 == LOW)
    {
      game_state = 2;
      safe = 3;
    }
    if (buttonState4 == LOW)
    {
      game_state = 2;
      safe = 4;
    }
    if (buttonState5 == LOW)
    {
      game_state = 2;
      safe = 5;
    }
    if (buttonState6 == LOW)
    {
      game_state = 2;
      safe = 6;
    }
    if (game_state == 2)
    {
      clearLed(108);
      for (int i = 0; i < 108; i++) 
      {                           // Turn the LEDs off before starting
        clearLed(i);
      }
      past_time=millis();
    }
  }
  else if (game_state == 2)
  {
    current_time = millis();
    if (button_one ==7 || button_two == 7)
    {
      game_state = 4;
      playAudio(43);
    }
    else
    {      
      if (safe ==1 && buttonState1 == HIGH)
      {
        safe = 0;
      }
      if (safe ==2 && buttonState2 == HIGH)
      {
        safe = 0;
      }
      if (safe ==3 && buttonState3 == HIGH)
      {
        safe = 0;
      }
      if (safe ==4 && buttonState4 == HIGH)
      {
        safe = 0;
      }
      if (safe ==5 && buttonState5 == HIGH)
      {
        safe = 0;
      }
      if (safe ==6 && buttonState6 == HIGH)
      {
        safe = 0;
      }
      if (button_one == 0)
      {
        button_one = generate(1,button_one,button_two);
        light(button_one);
      }
      if (button_two == 0)
      {
        button_two = generate(2,button_one,button_two);
        light(button_two);
      }
      if (buttonState1 == LOW)
      {
        check(1);
      }
      if (buttonState2 == LOW)
      {
        check(2);
      }
      if (buttonState3 == LOW)
      {
        check(3);
      }
      if (buttonState4 == LOW)
      {
        check(4);
      }
      if (buttonState5 == LOW)
      {
        check(5);
      }
      if (buttonState6 == LOW)
      {
        check(6);
      }
    }
  }
  else if (game_state == 3)
  {
    playAudio(10);
    delay(3500);
    playScoreSound(score);
    game_state = 1;
    for (int i = 0; i < 110; i++) 
    {                           // Turn the LEDs off before starting
    clearLed(i);
    }
    playAudio(42);
    light(1);
    light(2);
    light(3);
    light(4);
    light(5);
    light(6);
  }
  else if (game_state == 4)
  {
    double angularVelocity;
    sensorValue = analogRead(sensorPin);
    angularVelocity =((double)(sensorValue-reference_Value)*4930.0)/1023.0/0.67; //get the angular velocity
    Serial.println(angularVelocity);
    if (((abs(angularVelocity)) > 400) && ((abs(angularVelocity)) < 1000))
    {
      Serial.println("TWISTING");
      twisting = true;
      score +=1;
      playAudio(3);
      for (int i = 0; i < 109; i=i+2) 
      {                           // Turn the LEDs off before starting
        leds[i] = CRGB(0,255,0);
        FastLED.show();
      }
      for (int i = 0; i < 109; i++) 
      {                           // Turn the LEDs off before starting
        clearLed(i);
      }
      if (button_one == 7)
      {
        button_one_past = button_one;
        button_one = 0;
        light(button_two);
      }
      else if (button_two ==7)
      {
        button_two_past = button_two;
        button_two = 0;
        light(button_one);
      }
      game_state = 2;
    } 
    else 
    {
      Serial.println("NOT TWISTING");
      twisting = false;
    }
  }
}
