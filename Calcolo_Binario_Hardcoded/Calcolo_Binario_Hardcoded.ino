#define OFF 0
#define ON 1

/*
PINS START FROM 2 (first digit)
*/
int button = 0;
int old_button = 0;
int state = OFF;
int pinButton = 12;
int counter = 0;
int old_counter = 0;
/*
Array which cointains the LEDs that have to be powered on
*/
int powerOn[8];

void setup() {  
  pinMode(pinButton, INPUT);
  Serial.begin(9600);
}

void ledOn(int porta) {
  pinMode(porta, OUTPUT);
  digitalWrite(porta, HIGH);  
}

void parseButton(){
  button = digitalRead(pinButton);
  old_counter = counter;
  if (button == HIGH && old_button == LOW) {
    state = 1 - state;
    delay(150);
    counter++;
    if (counter > 255)
      counter = 0;
  }
  old_button = button;
}

void turnEverythingOff() {
  for (int i = 0; i < 16; i++) {
    digitalWrite(i, LOW);
  }
}

void parseLEDs() {
  int tmp = counter, bits = 0, index, sub;
  while (tmp > 0) {
      sub = 1;
      index = 1;
      while (sub <= tmp && sub*2 <= tmp) {
        sub *= 2;
        index++;
      }
      append(index);
      tmp -= sub;
  }
  if (tmp == 1) {
    append(1);
  }
}

void eraseArray(){
  for (int i = 0; i < 8; i++)
    powerOn[i] = NULL; 
}

void append(int num) {
  int i;
  for (i = 0; powerOn[i] != NULL; i++);
  powerOn[i] = num;
}

void lightLEDs(){
  for (int i = 0; powerOn[i] != NULL; i++){
    Serial.print("POWERING ON: ");
    Serial.println(2 + powerOn[i]);
    ledOn(2 + powerOn[i]); 
  }
}

void loop() {
  parseButton();
  if (old_counter != counter) {
    Serial.print("COUNTER: ");
    Serial.println(counter); 
    turnEverythingOff();
    eraseArray();
    parseLEDs();
    lightLEDs();
  }
}

