const int buttonPin = 2;  // pushbutton pin
const int RledPin   = 3;  // LED R
const int GledPin   = 5;  // LED G
const int BledPin   = 4;  // LED B

//Variable
int buttonState = 0;      // pushbutton status
int ledcolor = 0;
bool ButtonPressed = false;
String currentcolor = "LED";

//Double click variables
unsigned long double_click = 350;     // max time between 2 clics
unsigned long last_click_time = 0; 
bool led_on = true;

void setup() {

  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);

  pinMode(buttonPin, INPUT); 
  Serial.begin(9600);

  //initial state
  digitalWrite(RledPin, HIGH);
  digitalWrite(GledPin, HIGH);
  digitalWrite(BledPin, HIGH);
}

void loop() {

  //Reading command from serial monitor
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.toUpperCase();   //not case sensitive

    if (cmd == "RED")
    { 
      ledcolor = 1; led_on = true; 
    }
    else if (cmd == "GREEN")
    {
      ledcolor = 2; led_on = true;
    }
    else if (cmd == "BLUE")
    { 
      ledcolor = 3; led_on = true;
    }
    else if (cmd == "YELLOW")
    {
      ledcolor = 4; led_on = true;
    }
    else if (cmd == "PURPLE")
    { 
      ledcolor = 5; led_on = true;
    }
    else if (cmd == "CYAN")  
    {
      ledcolor = 6; led_on = true;
    }
    else if (cmd == "WHITE") 
    { 
      ledcolor = 7; led_on = true;
    }
    else if (cmd == "OFF") 
    { 
      led_on = false; 
    }
    else if (cmd == "ON")
    { 
      led_on = true;
    }
  }

  //button logic
  buttonState = digitalRead(buttonPin);

  //Logic for double clic or simple clic made at each loop
  if (buttonState == HIGH && !ButtonPressed)
  {
    ButtonPressed = true;

    unsigned long currentTime = millis();

    //Check time between 2 click
    if (currentTime - last_click_time < double_click)
    {
      // Double clic ON/OFF
      led_on = !led_on;
      last_click_time = 0;       
    } 
    else
    {
      last_click_time = currentTime;
    }
  }

  if (buttonState == LOW && ButtonPressed) {
    ButtonPressed = false;
  }

  if (last_click_time != 0 && millis() - last_click_time >= double_click && led_on) {
    ledcolor++;
    if (ledcolor > 7) ledcolor = 0;
    last_click_time = 0;  
  }

  //Led color logic
  if (!led_on) {
    currentcolor = "LED OFF";
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledcolor == 0) {
    currentcolor = "LED OFF";
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledcolor == 1) {
    currentcolor = "RED";
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledcolor == 2) {
    currentcolor = "GREEN";
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledcolor == 3) {
    currentcolor = "BLUE";
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);
  }
  else if (ledcolor == 4) {
    currentcolor = "YELLOW";
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledcolor == 5) {
    currentcolor = "PURPLE";
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);
  }
  else if (ledcolor == 6) {
    currentcolor = "CYAN";
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);
  }
  else if (ledcolor == 7) {
    currentcolor = "WHITE";
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);
  }

  //actual color print
  Serial.print("Current Color: ");
  Serial.println(currentcolor);
}
