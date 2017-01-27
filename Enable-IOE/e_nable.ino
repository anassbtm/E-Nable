#include <IRremoteInt.h>
#include <IRremote.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <boarddefs.h>

#include <Servo.h>

int pinBouton1;
Servo monservo1;
boolean etatServo1;


long int res_val;
int remt_value;

// Déclation d'un objet IRrecv
IRrecv irrecv(10);
decode_results results;


void setup() {
  Serial.begin(9600);
  
  monservo1.attach(7);
  monservo1.write(0); // servo a 0°
  
  irrecv.enableIRIn();   // Activation d'entrée du signal reçu

  etatServo1 = false ;
}



void loop()
{
  if (irrecv.decode(&results)) // reception d'un signal IR ?
  {
    res_val = results.value;         // Lecture d'un code
    remt_value=translateIR(res_val); // Conversion d'une touche de la télécommande
    irrecv.resume();                 // Réception de la nouvelle valeur

    //Serial.println(remt_value);

    if ( remt_value == 12 ) // Touche "1" de la télécommande 
    {      
      if(etatServo1)
      {
        monservo1.write(0);
      }
      else
      {
        monservo1.write(180); 
      }
     
      etatServo1 = !etatServo1 ;
    }
    
    delay(100);
  }
}

int translateIR(long int res_val)
{
  int out_val;
  
  switch(res_val)
  {
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
