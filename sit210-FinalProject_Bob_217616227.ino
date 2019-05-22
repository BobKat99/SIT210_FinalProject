int S1 = D1;
int S2 = D2;
int S3 = D3;
int S4 = D4;

int LED = D7;

bool entering()
{
    bool result;
    
    if (digitalRead(S3) == LOW)
    {
      result = true;
      delay(1000);
      
    }
    else if (digitalRead(S4)== LOW)
    {
      result = false;
      delay(1000);
    }
    
    return result;
}

bool children()
{
    bool result;
    
    if ((digitalRead(S3)== LOW || digitalRead(S4)== LOW) && digitalRead(S1) == HIGH && digitalRead(S2) == HIGH)
    {
        result = true;
    }
    else if ((digitalRead(S1)==LOW && digitalRead(S3)== LOW) || (digitalRead(S2)== LOW && digitalRead(S4)==LOW)) 
    {
        result = false;
    }
    
    return result;
}

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(S1, INPUT);
    pinMode(S2, INPUT);
    pinMode(S3, INPUT);
    pinMode(S4, INPUT);
}

void loop() {
    
    digitalWrite(LED, LOW);
    
    
    if (children()&&entering())
    {
        digitalWrite(LED, LOW);
        Particle.publish("check", "children entering");
    }
    else if(!children()&&entering())
    {
        digitalWrite(LED, LOW);
        Particle.publish("check", "adult entering");
    }
    else if(children()&&!entering())
    {
        digitalWrite(LED, HIGH);
        Particle.publish("check", "children exiting");
    }
    else if(!children()&&!entering())
    {
        digitalWrite(LED, LOW);
        Particle.publish("check", "adult exiting");
    }
    else
    {
        digitalWrite(LED, LOW);
        Particle.publish("check", "nothing");
    }
    
    delay (30000);
}