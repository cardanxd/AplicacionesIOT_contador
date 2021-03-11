int people = 0;
enum{
	_SALIDA = 0,
  	_ENTRADA = 1
};


class Radar
{
  public:
  int trig;
  int echo;
  int dist;
  int buzzer;
  bool type;
  bool on_of;
  
  Radar(int trig, int echo, int dist, int buzzer,bool type){
    this->trig = trig;
    this->echo = echo;
  	this->dist = dist;
  	this->buzzer = buzzer;
    this->type = type;
    this->on_of = false;
    pinMode(buzzer, OUTPUT);
  }
  
	long readUltrasonicDistance(int triggerPin, int echoPin);
  	void action();
};

long Radar::readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void Radar::action(){
	dist = 0.01723 * readUltrasonicDistance(trig, echo);
  	//Serial.println(dist);
  	Serial.println("Personas dentro: ");
  	Serial.println(people);
      
	delay(300); // Wait for 300 millisecond(s)
  
  	if (dist > 0 and dist < 253 and !on_of) {
     	tone(buzzer,500);
    	delay(30);
    	noTone(buzzer);               
    	delay(30);
      	this->on_of = true;
      	type == _ENTRADA? people++ : people--;
  	}
  	
  
  if(on_of and dist < 0 or dist >=253)
      this->on_of = false;
  
}

Radar* r2;
Radar* radar;


void setup()
{
  Serial.begin(9600);
  r2 = new Radar(8,9,0,6, _ENTRADA);
  radar = new Radar(3,4,0,5, _SALIDA);
}

void loop()
{
  r2->action();
  radar->action();
}
