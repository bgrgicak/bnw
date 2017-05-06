#include <SoftwareServo.h> 

//Staticke dekalracije
#define pinServo A1
#define ledCrvena 2
#define ledZelena 3
#define vlagaPin 0


//Globalne vrijednosti
int vlaga = 0;
int brojac = 0;
boolean pauza = false;

//Servo
SoftwareServo myservo;
boolean refresh = false; 

void setup() {
  //Otvori serijski port 9600
  Serial.begin(9600);
  //Ispiši poruku na serijski port
  Serial.println("Hello world"); 

  //Led init
  pinMode(ledCrvena, OUTPUT);
  pinMode(ledZelena, OUTPUT);


  //Servo init
  
  myservo.attach(pinServo);
  myservo.write(90);  
  
}

void loop() {
  //Ispis stanja vlage
  Serial.println(vlaga);
  //Pročitaj vlagu s senzora
  vlaga = analogRead(vlagaPin);
  if(pauza){
    if(brojac > 1000 && brojac < 3000){
      myservo.write(90); 
    }else if(brojac > 3000){
      pauza = false;
    }
    brojac++;
  }
  Serial.println(brojac);
  //Test vlažnosti
  if(vlaga < 600){
    digitalWrite(ledZelena, HIGH);
    digitalWrite(ledCrvena, LOW);
    myservo.write(90); 
    pauza = false;
  }
  else if(!pauza){
    digitalWrite(ledZelena, LOW);
    digitalWrite(ledCrvena, HIGH);
    myservo.write(0); 
    brojac = 0;
    pauza = true;
  }

  int angle = myservo.read();
  

  // set refresh one time / 2
  refresh = refresh ? false : true;
  if (refresh) SoftwareServo::refresh();

  
  
  //Pričekaj 1 milisekundu
  //delay(1);
}
