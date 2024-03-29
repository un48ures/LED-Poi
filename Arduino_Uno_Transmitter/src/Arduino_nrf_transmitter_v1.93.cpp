/*
  Teensy 4.0 - Poi Project
         //Transmitter Signal Strength Test

  by Felix Geisler
  16.03.2022
*/


#include <variables.h>
#include <get_signal_strength.h>

RF24 radio(7, 8); // CE, CSN



void setup()
{
  //Configuration I/O
  pinMode(LED_green, OUTPUT); 
  pinMode(LED_red, OUTPUT);
  pinMode(taster, INPUT); // Pin 3 button Input

  //Serial configuration
  Serial.begin(115200);
  
  //Radio configuration
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_1MBPS);
  radio.setRetries(0, 0);
  radio.stopListening();
  radio.openWritingPipe(pipe_address);
  
  //Set LEDs
  digitalWrite(LED_green, HIGH);
  digitalWrite(LED_red, HIGH);
  delay(500);
  digitalWrite(LED_green, LOW);
  digitalWrite(LED_red, LOW);
  digitalWrite(LED_green, HIGH);
}

void loop()
{
  print_signal_strength(&radio, CHs, int(sizeof(CHs)));
}

// //Channel, Bildnr, roteLED an
// void send_data (int ch, byte content) {
//   digitalWrite(LED_red, 1);
//   radio.setChannel(ch);
//   radio.openWritingPipe(pipe_address);
//   array_manual_ctrl[1] = content;
//   array_manual_ctrl[3] = brightness;
//   radio.write(&array_manual_ctrl, sizeof(array_manual_ctrl));
//   digitalWrite(LED_red, LOW);
// }

// //Main Loop---------------------------------------------------------------------------------
// void loop() {
//   //Poti Eingangswert lesen
//   sensorwert = analogRead(eingang);
//   brightness = map(sensorwert, 0, 1023, 0, 50);

//   //Tastereingang einlesen
//   tasterstatus = digitalRead(taster);

//   //Modus über Taster hochzählen
//     if (tasterstatus_old == LOW and tasterstatus == HIGH) {
//       taster_z++;
//       tasterstatus_old = HIGH;
//     }
//     if (tasterstatus_old == HIGH and tasterstatus == LOW) {
//       tasterstatus_old = LOW;
//     }

//   //Nur Senden wenn es eine Veränderung bei Taster oder Poti gibt
//   if (brightness_old != brightness || taster_z_old != taster_z || taster_z > 11) {
//     brightness_old = brightness;
//     taster_z_old = taster_z;

//     if (taster_z > 13) {
//       taster_z = 0;
//     }

//     //Taster-Auswertung und Taster/Poti Daten senden
//     if (taster_z > 0 and taster_z < 12) {
//       send_data(CH_P1, taster_z);
//       send_data(CH_P2, taster_z);
//       send_data(CH_P3, taster_z);
//       send_data(CH_P4, taster_z);
//       send_data(CH_P5, taster_z);
//       send_data(CH_P6, taster_z);
//     }

//     //Standby wenn Taster-Modus = 0
//     if (taster_z == 0) {
//       //99 = standby - red led blinking
//       send_data(CH_P1, 0); //black picture
//       send_data(CH_P1, 99);   //Standby 1st LED blinking RED
//       send_data(CH_P2, 0); //black
//       send_data(CH_P2, 99);   //Standby 1st LED blinking RED
//       send_data(CH_P3, 0); //black
//       send_data(CH_P3, 99);   //Standby 1st LED blinking RED
//       send_data(CH_P4, 0); //black
//       send_data(CH_P4, 99);   //Standby 1st LED blinking RED
//       send_data(CH_P5, 0); //black
//       send_data(CH_P5, 99);   //Standby 1st LED blinking RED
//       send_data(CH_P6, 0); //black
//       send_data(CH_P6, 99);   //Standby 1st LED blinking RED
//     }

//     //Lauflicht 1-6 links nach rechts
//     if (taster_z == 12) {
//       for (int i = 1; i < 7; i++) {
//         send_data(i + 19, 1);
//         delay(25);
//         send_data(i + 19, 0);
//       }
//     }

//     //Lauflicht 1-6 hin und her
//     if (taster_z == 13) {
//       for (int i = 1; i < 7; i++) {
//         send_data(i + CH_P1-1, 1);
//         delay(25);
//         send_data(i + CH_P1-1, 0);
//       }
//       for (int i = 6; i > 0; i--) {
//         send_data(i + CH_P1-1, 1);
//         delay(25);
//         send_data(i + CH_P1-1, 0);
//       }
//     }
//   }

//   //HAUPTFUNKTION:
//   //Das Musik-Programm sendet Töne und deren Pitch-Bend über MIDI/Seriell an den Arduino
//   //144+Kanal = Note-on Befehl gefolgt von einem Byte für die Tonhöhe -> hier: Instrument 1(Kanal 1) für Poi 1, Tonhöhe 60 für Bild 1
//   //224+Kanal = Pitch Bend -> hier: Signal für Helligkeit
//   //Serielle Schnittstelle nach neuen Paketen abfragen
//   if (Serial.available() > 1) {
//     digitalWrite(LED_green, HIGH);
//     data0 = Serial.read();

//     //Instrument_1-----------------------------------------------------
//     if (data0 == 144) {
//       array1[0] = 144;
//       array1[1] = Serial.read();
//       //Ch10
//       digitalWrite(LED_red, HIGH);
//       radio.setChannel(CH_P1);
//       radio.openWritingPipe(pipe_address);
//       radio.write(&array1, sizeof(array1));
//       delay(25);
//       digitalWrite(LED_red, LOW);
//     }

//     if (data0 == 224) {
//       array1[2] = 224;
//       array1[3] = Serial.read();
//       array1[4] = Serial.read();
//     }

//     //Instrument_2-----------------------------------------------------
//     if (data0 == 145) {
//       array2[0] = 145;
//       array2[1] = Serial.read();
//       digitalWrite(LED_red, HIGH);
//       radio.setChannel(CH_P2);
//       radio.openWritingPipe(pipe_address);
//       radio.write(&array2, sizeof(array2));
//       delay(25);
//       digitalWrite(LED_red, LOW);
//     }

//     if (data0 == 225) {
//       array2[2] = 225;
//       array2[3] = Serial.read();
//       array2[4] = Serial.read();
//     }

//     //Instrument_3-----------------------------------------------------
//     if (data0 == 146) {
//       array3[0] = 146;
//       array3[1] = Serial.read();
//       digitalWrite(LED_red, HIGH);
//       radio.setChannel(CH_P3);
//       radio.openWritingPipe(pipe_address);
//       radio.write(&array3, sizeof(array3));
//       delay(25);
//       digitalWrite(LED_red, LOW);
//     }

//     if (data0 == 226) {
//       array3[2] = 226;
//       array3[3] = Serial.read();
//       array3[4] = Serial.read();
//     }

//     //Instrument_4-----------------------------------------------------
//     if (data0 == 147) {
//       array4[0] = 147;
//       array4[1] = Serial.read();
//       digitalWrite(LED_red, HIGH);
//       radio.setChannel(CH_P4);
//       radio.openWritingPipe(pipe_address);
//       radio.write(&array4, sizeof(array4));
//       delay(25);
//       digitalWrite(LED_red, LOW);
//     }

//     if (data0 == 227) {
//       array4[2] = 227;
//       array4[3] = Serial.read();
//       array4[4] = Serial.read();
//     }

//     //Instrument_5-----------------------------------------------------
//     if (data0 == 148) {
//       array5[0] = 148;
//       array5[1] = Serial.read();
//       digitalWrite(LED_red, HIGH);
//       radio.setChannel(CH_P5);
//       radio.openWritingPipe(pipe_address);
//       radio.write(&array5, sizeof(array5));
//       delay(25);
//       digitalWrite(LED_red, LOW);
//     }

//     if (data0 == 228) {
//       array5[2] = 228;
//       array5[3] = Serial.read();
//       array5[4] = Serial.read();
//     }

//     //Instrument_6-----------------------------------------------------
//     if (data0 == 149) {
//       array6[0] = 149;
//       array6[1] = Serial.read();
//       digitalWrite(LED_red, HIGH);
//       radio.setChannel(CH_P6);
//       radio.openWritingPipe(pipe_address);
//       radio.write(&array6, sizeof(array6));
//       delay(25);
//       digitalWrite(LED_red, LOW);
//     }

//     if (data0 == 229) {
//       array6[2] = 229;
//       array6[3] = Serial.read();
//       array6[4] = Serial.read();
//     }
//   }
// }
