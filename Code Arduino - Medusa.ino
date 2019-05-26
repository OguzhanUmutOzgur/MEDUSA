

#define interupteur 7
#define moteur 10
#include <TinyGPS++.h>  //library GPS
#include <Servo.h>      //library servo
#include <Wire.h>       //library i2c

/*GPS*/
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;

/*servo*/
Servo monServo1;
Servo monServo2;
int po = 0;
String message = "gneugneu";    //message= chaine de caractère de base qui est envoyé
String texte;                   //texte= chaine de caractère envoyé
String posistiongps;            //positiongps= chaine de caractèrede la position gps

/*ultrasons*/
const byte TRIGGER_PIN = 2; // Broche TRIGGER
const byte ECHO_PIN = 3;    // Broche ECHO
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s Constantes pour le timeou
const float SOUND_SPEED = 340.0 / 1000; //Vitesse du son dans l'air en mm/us

long randNumber;  //direction random

/*servomoteurs*/
void servo1left()   //fonction qui dirige le servo1 à gauche
{
  for (po = 1; po < 90; po++)
  {
    monServo1.write(po);
  }
}
void servo1down()   //fonction qui dirige le servo1 en bas
{
  for (po = 90; po < 180; po++)
  {
    monServo1.write(po);
  }
}
void servo2right()    //fonction qui dirige le servo2 à droite
{
  for (po = 1; po < 90; po++)
  {
    monServo2.write(po);
  }
}
void servo2up()     //fonction qui dirige le servo2 à droite
{
  for (po = 90; po < 180; po++)
  {
    monServo2.write(po);
  }
}


/*wifi*/
void AT(String mes)
{
  Serial1.print(mes);
  Serial1.write(13);
  Serial1.write(10);
}

void envMessage()   //fonction qui envoie le message
{
  int nbCar = message.length();
  AT("AT+CIPSEND=" + String(nbCar));
  AttendConnect("OK");
  Serial1.print(message);
  //Serial1.write(13);
  //Serial1.write(10);
  Serial.println();
}


void recMessage()   //fonction qui recoit le contenue du site
{
  texte = "";
  do
    if (Serial1.available() > 0)
    {
      char car = Serial1.read();
      if (car == '+')
        do
        {
          if (Serial1.available() > 0) car = Serial1.read();
        }
        while (car != ':');
      else if (car > 32)    // enleve les caractes ascii invisibles
        texte += car;
    }
  while (texte.indexOf("CLOSE") == -1);
  while (Serial1.available() > 0) Serial1.read();
  Serial.print(texte.substring(texte.indexOf("direction"), (texte.indexOf("</div>"))));
  Serial.print("   ");
  Serial.print(texte.substring(texte.indexOf("mode"), (texte.indexOf("Fin"))));       // permet de garder seulement une partie du texte du serveur
  Serial.print("   ");
}

void AttendConnect(String mot)
{
  texte = "";
  do
    if (Serial1.available() > 0)
    {
      char car = Serial1.read();
      texte += car;
      //Serial.print(car);
    }

  while (texte.indexOf(mot) == -1);
  while (Serial1.available() > 0) Serial1.read();
  //Serial.println();
  //Serial.println("......................");
  //Serial.println();
}


/*GPS*/
void displayInfo()
{
  Serial.print("Location: ");
  if (gps.location.isValid())
  {
    posistiongps = gps.location.lat(), gps.location.lng() ;
    Serial.print(posistiongps);
  }
  /*
    Serial.print(gps.location.lat(), 6);
    Serial.print(",");
    Serial.print(gps.location.lng(), 6);
    }*/
  else
  {
    posistiongps = "INVALID";
    Serial.print(posistiongps);
  }
  Serial.println();
  delay(200);
}



void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(GPSBaud); //GPS
  Wire.begin();           // join i2c bus (address optional for master)

  pinMode(interupteur, INPUT_PULLUP);   //interupteur défini
  pinMode(moteur, OUTPUT);    //moteur (direction) définie

  Serial.println("Demarrage...");
  Serial.println("Connection au wifi...");
  AT("AT+CWJAP=\"Wifiprojet\",\"projet123\"");  //connexion au Wifi
  AttendConnect("OK");
  Serial.println("Wifi connecté");

  /*ultason*/
  pinMode(TRIGGER_PIN, OUTPUT);   //Initialise les broches capt ultason
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN, INPUT);       //Initialise les broches capt ultason

  /*servomoteurs*/
  monServo1.attach(A4);
  monServo2.attach(A2);
  monServo1.write(po);
  monServo2.write(po);

  randomSeed(analogRead(0));    //direction random

  Serial.println("...........fin du void setup...........");
}



void loop()
{
  AT("AT+CIPSTART=\"TCP\",\"172.16.13.4\",80"); //connexion au serveur
  AttendConnect("OK");
  envMessage();  // Envoie de la requete au serveur
  recMessage();  // reception de la reponse du serveur
  AT("");
  delay(300);

  /*MODE MANUEL*/
  if (texte.substring(texte.indexOf("mode"), (texte.indexOf("Fin")))  == "mode6")
    //if (digitalRead(interupteur) == 0)
  {
    Serial.println("Mode manuel (interupteur à 0)");
    digitalWrite(moteur, HIGH);
    if (texte.substring(texte.indexOf("direction"), (texte.indexOf("</div>")))  == "direction2")
    {
      servo1left();
      Serial.println("servo1left()");

    }
    if (texte.substring(texte.indexOf("direction"), (texte.indexOf("</div>")))  == "direction4")
    {
      servo1down();
      Serial.println("servo1down()");

    }
    if (texte.substring(texte.indexOf("direction"), (texte.indexOf("</div>")))  == "direction1")
    {
      servo2up();
      Serial.println("servo2up()");
    }
    if (texte.substring(texte.indexOf("direction"), (texte.indexOf("</div>")))  == "direction3")
    {
      servo2right();
      Serial.println("servo2right()");

    }
    if (texte.substring(texte.indexOf("direction"), (texte.indexOf("</div>")))  == "direction0")
    {
      digitalWrite(moteur, LOW);
    }
  }


  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);       //Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe)
  float distance_mm = measure / 2.0 * SOUND_SPEED;    //Calcul la distance à partir du temps mesuré

  /*MODE AUTAMATIQUE*/
  if (texte.substring(texte.indexOf("mode"), (texte.indexOf("Fin")))  == "mode5")
    //if (digitalRead(interupteur) == 1)
  {
    Serial.println("Mode automatique (interupteur à 1)");
    digitalWrite(moteur, HIGH);
    if (distance_mm > 1)
    {
      Serial.println(distance_mm);      //distance en mm s'écris dans le moniteur
    }
    delay(100); //Délai d'attente pour éviter d'afficher trop de résultats à la seconde

    if (distance_mm < 200 && distance_mm > 1)
    {
      randNumber = random(1, 4);
      if (randNumber == 1)
      {
        servo2up();
        Serial.println("servo2up()");
      }
      if (randNumber == 2)
      {
        servo1left();
        Serial.println("servo1left()");
      }
      if (randNumber == 3)
      {
        servo2right();
        Serial.println("servo2right()");
      }
      if (randNumber == 4)
      {
        servo1down();
        Serial.println("servo1down()");
      }

    }
  }

  /*GPS*/
  if (Serial2.available() > 0)
  {
    displayInfo();
    message = posistiongps;
  }
  //Serial.println(message);


  /*I2C*/
  Wire.requestFrom(8, 20);    // request 6 bytes from slave device #8
  while (Wire.available())
  {
    //  Serial.println("rrrrrrrrrrrrrrrrrrrrrr");
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
    Serial.println();
  }

  delay(500);

}
