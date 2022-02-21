// Car Garage Stoplight Sensor

#include <FastLED.h>

#define LED_PIN     6
#define NUM_LEDS    64
#define BRIGHTNESS  32
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

// Define the array of leds
CRGB leds[NUM_LEDS];

#define echoPin 9 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 8 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement


long TempDistance = 0; // A variable to store the temporary distance
int counter = 0; // Counter value to check if the object has stopped moving

void setup() {
  delay(3000); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
    
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(115200); // // Serial Communication is starting with 9600 of baudrate speed
  
}

void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  //distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  distance = (duration / 2) / 74; // Distance in inches

if (counter < 30) {
  
  if (distance > 55) {
    FastLED.clear();
    fill_solid( leds, 64, CRGB::Green);
    FastLED.show();
  }
  if (distance < 55 && distance > 24) {
    FastLED.clear();
    fill_solid( leds, 64, CRGB::Yellow);
    FastLED.show();
  }
  if (distance < 24) {
    FastLED.clear();
    fill_solid( leds, 64, CRGB::Red);
    FastLED.show();
  }
  /*if (distance > 225) {
    FastLED.clear(true);
  }*/
}  
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" inches");

  if ((distance == TempDistance) || ((distance+1) == TempDistance) || ((distance-1) == TempDistance)) {

    if(counter >= 30) { // Turn off the lights if the object hasn't moved for 20 cycles (no change in distance)
      Serial.println("No movement detected, turning off the lights");
      FastLED.clear(true);
    } else {
      counter++;
    }
  } else {
    counter = 0; // Reset counter if there is a movement
  }

  TempDistance = distance;
  delay(250);
  
}
