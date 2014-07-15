int currentValue;
int maxValue;
int minValue;
unsigned long timer;
int sampleSpan = 300; // Amount in milliseconds to sample data
int volume; // this roughly goes from 0 to 700

int led1 = 13;
int led2 = 06;
int threshold = 100; //Change This

void setup() 
{
  pinMode(led1, OUTPUT); 
  pinMode(led2, OUTPUT);    
  Serial.begin(9600); 
    resetValues();
}

void loop() 
{
    currentValue = analogRead(A0);

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
    
     if(volume>threshold){
    digitalWrite(led1, HIGH); //Turn ON Led
    digitalWrite(led2, LOW);
  }  
  else{
    digitalWrite(led1, LOW); // Turn OFF Led
    digitalWrite(led2, HIGH); 
  }
}

void resetValues()
{
    maxValue = 0;
    minValue = 1024;
    timer = millis(); 
}



