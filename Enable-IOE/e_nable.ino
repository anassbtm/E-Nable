// utilise les ports 4 7 10 11 et 12
#include <WiFi.h>
#include <SPI.h>
#include <string.h>
#include <IRremote.h>

#include <Servo.h>

#define SERVO1 5
#define IRREMOTE 6

//--- Servo-Moteurs
Servo monservo1;
boolean etatServo1, etatServo2, etatServo3, etatServo4;

//--- Parametre IRremote
long int res_val;
int remt_value;

IRrecv irrecv(IRREMOTE);// Déclation d'un objet IRrecv
decode_results results;

//--- Wifi Shield
int status = WL_IDLE_STATUS; // Statut du shield
char ssid[] = "FREEBOX_MOHAMMED_X3";
char pass[] = "F4CAE55AF478";
char server[] = "88.170.244.38";
WiFiClient client ;

unsigned long lastConnectionTime = 0;            // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 3000L; //10L * 1000L; // delay between updates, in milliseconds

void setup() {
  Serial.begin(9600);
  // Test Wifi Shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield non connecte");
    while (true); // Ne pas continuer
  }
  else {
    Serial.println("WiFi shield connecte");
  }

  // Initialisation moteurs
  monservo1.attach(SERVO1);
  monservo1.write(0); // servo a 0°
  etatServo1 = false ;
  etatServo2 = false ;
  etatServo3 = false ;
  etatServo4 = false ;

  irrecv.enableIRIn();   // Activation d'entrée du signal reçu

  // Initialisation Wifi
  status = WiFi.begin(ssid, pass);
  while (status != WL_CONNECTED) {
    Serial.print("Tentative de connexion au reseau: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid);
    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connecte au wifi");
  printWifiStatus();
  Serial.print("Firmware version: ");
  Serial.println(WiFi.firmwareVersion());
  /*
    Serial.print("connection serveur..");
    while (!client.connect(server, 80)) {
    Serial.print(".");
    }
    Serial.println("reussi !");*/
  //sendRequest(etatServo1, etatServo2, etatServo3, etatServo4);
}


void loop() {
  /*while (client.available()) {
    Serial.println("hey");
    }*/
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  if (irrecv.decode(&results)) { // reception d'un signal IR ?
    res_val = results.value;         // Lecture d'un code
    remt_value = translateIR(res_val); // Conversion d'une touche de la télécommande
    irrecv.resume();                 // Réception de la nouvelle valeur

    Serial.println(remt_value);

    if ( remt_value == 12 ) { // Touche "1" de la télécommande
      if (etatServo1)  {
        monservo1.write(0);
      }
      else            {
        monservo1.write(180);
      }

      etatServo1 = !etatServo1 ;

      //sendRequest(etatServo1, etatServo2, etatServo3, etatServo4);
     
    }

    //while(client.available()) client.flush();
    //client.stop();

  }
  
  if (millis() - lastConnectionTime > postingInterval) {
     Serial.print("connected ?? "); Serial.println(client.connected());

     sendRequest(etatServo1, etatServo2, etatServo3, etatServo4);
  } 
  //sendRequest(etatServo1, etatServo2, etatServo3, etatServo4);
 
}

void sendRequest(boolean etatServo1, boolean etatServo2, boolean etatServo3, boolean etatServo4)
{
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 80)) {
    char req[20] ;
    req[0] = 0;
    strcat(req, "PUT /set/");
    strcat(req, boolstring(etatServo1));
    strcat(req, "/");
    strcat(req, boolstring(etatServo2));
    strcat(req, "/");
    strcat(req, boolstring(etatServo3));
    strcat(req, "/");
    strcat(req, boolstring(etatServo4));
    strcat(req, " HTTP/1.1");

    
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.println(req);
    client.println("Host: 88.170.244.38");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
    } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}

/*
  void sendRequest(boolean etatServo1, boolean etatServo2, boolean etatServo3, boolean etatServo4)
  {
  if (client.connect(server, 80)) {  //starts client connection, checks for connection
    char req[20] ;
    req[0] = 0;
    strcat(req, "PUT /set/");
    strcat(req, boolstring(etatServo1));
    strcat(req, "/");
    strcat(req, boolstring(etatServo2));
    strcat(req, "/");
    strcat(req, boolstring(etatServo3));
    strcat(req, "/");
    strcat(req, boolstring(etatServo4));
    strcat(req, " HTTP/1.1");

    Serial.println("connected");
    Serial.println(req);

    client.println(req);
    client.println("Host: 88.170.244.38");
    client.println("Connection: close");
    //client.println("Connection: keep-alive");

  //----------------------------
    String content = "Hey, just testing a post request.";
    client.println("POST /try HTTP/1.1");
    client.println("Host: 88.170.244.38");
*///client.println("Accept: */*");
/*
  client.println("Content-Length: " + content.length());
  client.println("Content-Type: application/x-www-form-urlencoded");
  client.println();
  client.println(content);
  }
  else {
  Serial.println("connection failed"); //error message if no client connect
  }

  delay(2000);
  //delay(1);

  Serial.println("disconnecting.");
  Serial.println("==================");

  //client.flush();
  client.stop(); //stop client

  }
*/
int translateIR(long int res_val) {
  int out_val;

  switch (res_val) {
    case 0xFFA25D:
      Serial.println(" CH-            ");
      out_val = 0;
      break;

    case 0xFF629D:
      Serial.println(" CH             ");
      out_val = 1;
      break;

    case 0xFFE21D:
      Serial.println(" CH+            ");
      out_val = 2;
      break;

    case 0xFF22DD:
      Serial.println(" PREV           ");
      out_val = 3;
      break;

    case 0xFF02FD:
      Serial.println(" NEXT           ");
      out_val = 4;
      break;

    case 0xFFC23D:
      Serial.println(" PLAY/PAUSE     ");
      out_val = 5;
      break;

    case 0xFFE01F:
      Serial.println(" VOL-           ");
      out_val = 6 ;
      break;

    case 0xFFA857:
      Serial.println(" VOL+           ");
      out_val = 7;
      break;

    case 0xFF906F:
      Serial.println(" EQ             ");
      out_val = 8;
      break;

    case 0xFF6897:
      Serial.println(" 0              ");
      out_val = 9;
      break;

    case 0xFF9867:
      Serial.println(" 100+           ");
      out_val = 10;
      break;

    case 0xFFB04F:
      Serial.println(" 200+           ");
      out_val = 11;
      break;

    case 0xFF30CF:
      Serial.println(" 1              ");
      out_val = 12;
      break;

    case 0xFF18E7:
      Serial.println(" 2              ");
      out_val = 13;
      break;

    case 0xFF7A85:
      Serial.println(" 3              ");
      out_val = 14;
      break;

    case 0xFF10EF:
      Serial.println(" 4              ");
      out_val = 15;
      break;

    case 0xFF38C7:
      Serial.println(" 5              ");
      out_val = 16;
      break;

    case 0xFF5AA5:
      Serial.println(" 6              ");
      out_val = 17;
      break;

    case 0xFF42BD:
      Serial.println(" 7              ");
      out_val = 18;
      break;

    case 0xFF4AB5:
      Serial.println(" 8              ");
      out_val = 19;
      break;

    case 0xFF52AD:
      Serial.println(" 9              ");
      out_val = 20;
      break;

    default:
      Serial.println(" other button   ");
      out_val = -1;
  }
  return out_val;
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

const char *boolstring( _Bool b ) {
  return b ? "true" : "false";
}
