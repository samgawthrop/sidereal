/*
 * Hydro Decoder 
 * Jan 21 2017
 * Sam Reese
 * for Siderial, small bot
 * 
 * 
 * Inputs:
 *  PWM signal from futaba FASST 1500uS pulses
 *  single PWM input, zero deadband, with up or down triggering the 
 *      output SSR's.
 *  single pwm input, high/low input, for hydro enable, perhaps 
 *      expand to be pump speed through pull-down transistor to 
 *      emulate a 5k pot for alltrax throttle
 * 
 * Output:
 *  LED indicators (3)
 *  SSR output to hydro pump contactor
 *  SSR output to up solenoid
 *  SSR output to down solenoid
 * 
 */
//input pins
const int UPDOWN_PIN = 6;
const int ENABLE_PIN = 10;

// output pins
const int UP_PIN = 7;
const int DOWN_PIN = 8;
const int LED_PIN = 13;

//values for pwm
const int BOTTOM = 11500;
const int CENTER = 12320; // ms
const int DEADBAND = 200; // ms
const int TOP = 12900;


void setup() {
  pinMode(UPDOWN_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
  Serial.println("Setup: initialized");

  pinMode(UP_PIN, OUTPUT);
  pinMode(DOWN_PIN, OUTPUT);
  digitalWrite(UP_PIN, HIGH);
  digitalWrite(DOWN_PIN, HIGH);

}

void loop() {
  int updown;
  Serial.print("reading pwm 6: ");
  updown = pulseIn(UPDOWN_PIN, LOW, 25000);
  Serial.println( updown);
  if (updown > CENTER - DEADBAND && updown < CENTER + DEADBAND || updown == 0){
    // in center: all off
    digitalWrite(UP_PIN, HIGH);
    digitalWrite(DOWN_PIN, HIGH);
    Serial.println("ALL OFF");
  }
  else {
    if (updown > BOTTOM && updown < CENTER - DEADBAND){
        digitalWrite(LED_PIN, HIGH);
        Serial.println("GOING UP");
        digitalWrite(DOWN_PIN, HIGH);
        delay(10);
        digitalWrite(UP_PIN, LOW);
    }
    if (updown < TOP && updown > CENTER + DEADBAND){
        digitalWrite(LED_PIN, HIGH);
        Serial.println("Going Down");
        digitalWrite(UP_PIN, HIGH);
        delay(10);
        digitalWrite(DOWN_PIN, LOW);
    }
  }
  
}
