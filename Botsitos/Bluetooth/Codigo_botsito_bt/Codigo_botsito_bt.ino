#include <SoftwareSerial.h>
#define TX 2
#define RX 3
#define EN1 6
#define MA1 7
#define MA2 8
#define MB1 9
#define MB2 10
#define EN2 11

#define  VELOCIDAD 255

SoftwareSerial BT(RX,TX); // RX, TX recordar que se cruzan
void setup() {
	
    pinMode(TX, OUTPUT);
	pinMode(RX, INPUT);
	pinMode(EN1, OUTPUT);
	pinMode(MA1, OUTPUT);
	pinMode(MA2, OUTPUT);
	pinMode(MB1, OUTPUT);
	pinMode(MB2, OUTPUT);
	pinMode(EN2, OUTPUT);
	Serial.begin(9600);
	BT.begin(9600);
}

void loop() {
  if(BT.available()){
	char state=BT.read();
	if (state == 'q') { //Giro Izquierda
		analogWrite(EN1,VELOCIDAD);
		digitalWrite(MA1, 1);
		digitalWrite(MA2, 0);
		digitalWrite(MB1, 1);
		digitalWrite(MB2, 0);
		analogWrite(EN2,VELOCIDAD);
   }
	  else if (state == 'e') { //Giro Derecha
		analogWrite(EN1,VELOCIDAD);
		digitalWrite(MA1, 0);
		digitalWrite(MA2, 1);
		digitalWrite(MB1, 0);
		digitalWrite(MB2, 1);
		analogWrite(EN2,VELOCIDAD);
   }
	  else if (state == 'a') { //Izquierda Arriba
		analogWrite(EN1,VELOCIDAD);
		digitalWrite(MA1, 0);
		digitalWrite(MA2, 1);
		digitalWrite(MB1, 0);
		digitalWrite(MB2, 0);
		analogWrite(EN2,0);
   }
	  else if (state == 'z') { //Izquierda Abajo
		analogWrite(EN1,VELOCIDAD);
		digitalWrite(MA1, 1);
		digitalWrite(MA2, 0);		
		digitalWrite(MB1, 0);
		digitalWrite(MB2, 0);
		analogWrite(EN2,0);
   }
	  else if (state == 'd') { //Derecha Arriba
		analogWrite(EN1,0);
		digitalWrite(MA1, 0);
		digitalWrite(MA2, 0);	
		digitalWrite(MB1, 1);
		digitalWrite(MB2, 0);
		analogWrite(EN2,VELOCIDAD);
   }
	  else if (state == 'c') { //Derecha Abajo
		analogWrite(EN1,0);
		digitalWrite(MA1, 0);
		digitalWrite(MA2, 0);
		digitalWrite(MB1, 0);
		digitalWrite(MB2, 1);
		analogWrite(EN2,VELOCIDAD);
  }
	  else if (state == 'w') { //Avanzar
		analogWrite(EN1,VELOCIDAD);
		digitalWrite(MA1, 0);
		digitalWrite(MA2, 1);
		digitalWrite(MB1, 1);
		digitalWrite(MB2, 0);
		analogWrite(EN2,VELOCIDAD);
   }
	   else if (state == 's') { //Retroceder
		analogWrite(EN1,VELOCIDAD);
		digitalWrite(MA1, 1);
		digitalWrite(MA2, 0);
		digitalWrite(MB1, 0);
		digitalWrite(MB2, 1);
		analogWrite(EN2,VELOCIDAD);
	 }
		else if (state == 'p') { //Detener
		analogWrite(EN1,0);
		digitalWrite(MA1, 0); 
		digitalWrite(MA2, 0);
		digitalWrite(MB1, 0);
		digitalWrite(MB2, 0);
		analogWrite(EN2,0);
	 }
  } 
}