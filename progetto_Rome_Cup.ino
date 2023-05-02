// sensore di colore, temp e umid, umid terreno, fotoresistenza, bluetooth

#include <SoftwareSerial.h>
#define rxPin 2
#define txPin 3
SoftwareSerial hc06(rxPin, txPin);
#define baudrate 9600


#include <DHT.h>
#define DHTPIN 9 
#define DHTTYPE    DHT11 
#define S0 12
#define S1 13
#define S2 6
#define S3 5
#define sensorOut 7
#define FOTOPIN A1
#define UMIDPIN A3


DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(baudrate);
  hc06.begin(baudrate);
  dht.begin();
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
}

unsigned long r, g, b;

void loop() {
  if(hc06.available()) {
  char l = hc06.read();
    if(l = "info") {
       dht11();
       lux();
       terreno();
       colore();
      } 
     }
   }
  

void dht11() {
  int temp = dht.readTemperature();
  int umid = dht.readHumidity();
  Serial.println("Temperatura ed umidità:");
  Serial.print(temp);
  Serial.print("°C");
  Serial.print("  ");
  Serial.print(umid);
  Serial.println("%");
  hc06.println("Temperatura ed umidità:");
  hc06.print(temp);
  hc06.print("°C");
  hc06.print("  ");
  hc06.print(umid);
  hc06.println("%");
}

void lux() {
  int luce = analogRead(FOTOPIN);
  int perc_lum = map(luce, 200, 800, 0, 100);
  Serial.println("Luminosità");
  Serial.print(luce);
  Serial.print(" ");
  Serial.print(perc_lum);
  Serial.println("%");
  hc06.println("Luminosità");
  hc06.print(perc_lum);
  hc06.println("%");
  
}

void terreno() {
  int umid_terreno = analogRead(UMIDPIN);
  int perc_umid_terreno = map(umid_terreno, 1020, 284, 0, 100);
  Serial.println("Umidità del terreno");
  Serial.print(perc_umid_terreno);
  Serial.println("%");
  hc06.println("Umidità del terreno");
  hc06.print(perc_umid_terreno);
  hc06.println("%");
}

void colore() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  r = pulseIn(sensorOut, LOW);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  g = pulseIn(sensorOut, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  b = pulseIn(sensorOut, LOW);
  Serial.println("Sensore colore:");
  Serial.print("R=");
  Serial.print(r);
  Serial.print("\tG=");
  Serial.print(g);
  Serial.print("\tB=");
  Serial.println(b);
  hc06.println("Sensore colore:");
  hc06.print("R=");
  hc06.print(r);
  hc06.print("\tG=");
  hc06.print(g);
  hc06.print("\tB=");
  hc06.println(b);
}
