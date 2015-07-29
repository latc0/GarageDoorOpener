#define BIT_HIGH 350
#define BIT_LOW 1150
#define LONG_HIGH 1000
#define SHORT_LOW 500
#define PATTERN_GAP 11500

#define TX_PIN 32
#define BUTTON_PULL_UP 30
#define HIGH 1

/*Transmitter
*
*  ________________
*  |    |    |    |
* GND Data  Vcc  ANT
*
*/

//Number of times for each pattern
//Starts with normal and alternates with odd
//e.g. 5*normal, then 1*odd, then 1*normal etc.
int times[] = {5, 1, 1, 3, 1, 1, 3, 1, 6, 2, 1};

void setup() {
  pinMode(TX_PIN, OUTPUT);
  pinMode(BUTTON_PULL_UP, INPUT);
}
void odd() {
  digitalWrite(TX_PIN, HIGH);
  delayMicroseconds(LONG_HIGH);
  digitalWrite(TX_PIN, LOW);
  delayMicroseconds(SHORT_LOW);
}
void normal() {
  digitalWrite(TX_PIN, HIGH);
  delayMicroseconds(BIT_HIGH);
  digitalWrite(TX_PIN, LOW);
  delayMicroseconds(BIT_LOW);
}
void loop() {
  if (digitalRead(BUTTON_PULL_UP) == HIGH) {
    for (int i = 0; i < 80; i++)
      openCloseGarage(); //Same signal for opening and closing door
  }
}

void openCloseGarage() {
  for (int i = 0; i < 11; i++) {
    int val = times[i];
    for (int j = 0; j < val; j++) {
      if (i % 2 == 0 || i == 0) {
        normal();
      }
      else
        odd();
    }
  }
  digitalWrite(TX_PIN, LOW);
  delayMicroseconds(PATTERN_GAP);
}

