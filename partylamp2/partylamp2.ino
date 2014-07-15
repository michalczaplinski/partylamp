int currentValue;
int maxValue;
int minValue;

int led1 = 13;
int led2 = 06;

int left;
int right;

unsigned long timer;
int sampleSpan = 1000; // Amount in milliseconds to sample data
int volume;            // this roughly goes from 0 to 70
int threshold = 15;     //single digit numbers

void setup() {
    pinMode(led1, OUTPUT); 
    pinMode(led2, OUTPUT);    
    Serial.begin(9600); 
        resetValues();
}

void loop() {
    currentValue = analogRead(A0);
    int pin4state = analogRead(A4);
    int pin5state = analogRead(A5);
    int state = checkstate();
    
    if (currentValue < minValue) {
        minValue = currentValue;
    } 
    if (currentValue > maxValue) {
        maxValue = currentValue;
    }

    if (millis() - timer >= sampleSpan) {
        volume = maxValue - minValue;

        Serial.println(volume);
        resetValues();
    }
      
    if (state == 1) {
        if(volume > threshold) { 
            red();
        }
        else {
            green();
        }
    }
          
    else if (state == 2) {
        if(volume > threshold) {
          green();
        }
        else {
          red();
        }
    }
    else {
        none();
    }
}


////////////////////////////////////////////////////
////////////////// MY FUNCTIONS ////////////////////

// check the state of the switch
int checkstate() {
  int pin4state = analogRead(A4);
  int pin5state = analogRead(A5);
  
  // off
  if (pin4state > 0 && pin5state > 0) {
    return 0; 
  }
  // party mode
  else if (pin4state == 0) {
    return 1;
  }
  // chill mode
  else if (pin5state == 0) {
    return 2;
  }
}
    
// 
void red() {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
//  Serial.println("RED"); // for debugging
}

void green() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
//  Serial.println("GREEN"); // for debugging
}

// the lamp is "off"
void none() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
//  Serial.println("NONE"); // for debugging
}


void resetValues() {
    maxValue = 0;
    minValue = 1024;
    timer = millis();
}


