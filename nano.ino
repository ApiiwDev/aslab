#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);


//ultrasonic 1 Kiri
int echoPin1 = 8;
int trigPin1 = 9;
int distance1 = 0;

//ultrasonic 2 Tengah
int echoPin2 = 6;
int trigPin2 = 7;
int distance2 = 0;

// Utrasonic 3 kanan
int echoPin3 = 4;
int trigPin3 = 5;
int distance3 = 0;

// Ultrasonic 4 bawah
int echoPin4 = 2;
int trigPin4 = 3;
int distance4 = 0;

void setup() {
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  // Definisi Ultrasonic 1
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  // Definisi Ultrasonic 2
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  // Definisi Ultrasonic 3
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  // Definisi Ultrasonic 4
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);

  //Memulai MP3 Player
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  
  //----Set volume----
  myDFPlayer.volume(20);  //Set volume value (0~30).
  myDFPlayer.volumeUp(); //Volume Up
  myDFPlayer.volumeDown(); //Volume Down
  
  //----Set different EQ----
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

}

void loop() {
  // Baca Ultrasonic 1
  distance1 = getDistance(trigPin1, echoPin1);
  delay(50);
  // Baca Ultrasonic 2
  distance2 = getDistance(trigPin2, echoPin2);
  delay(50);
  // Baca Ultrasonic 3
  distance3 = getDistance(trigPin3, echoPin3);
  delay(50);
  // Baca Ultrasonic 4
  distance4 = getDistance(trigPin4, echoPin4);

  //Memunculkan data ultrasonic di serial Monitor
  Serial.print("Ultrasonic 1=");  Serial.println(distance1);
  Serial.print("Ultrasonic 2=");  Serial.println(distance2);
  Serial.print("Ultrasonic 3="); Serial.println(distance3);
  Serial.print("Ultrasonic 4="); Serial.println(distance4);

  // Kondisi Ultrasonic 1(Kiri) ketika jarak kurang dari 30cm, maka akan memutar SD:002.mp3 (Awas Kiri)  
  if(distance1<30){
    myDFPlayer.loop(2);  //play specific mp3 in SD:/15/002.mp3; Folder Name(1~99); File Name(1~255)
    delay(2000);
  }
  // Kondisi Ultrasonic 2(Depan) ketika jarak kurang dari 30cm, maka akan memutar SD:001.mp3 (Awas depan)
  if(distance2<30){
    myDFPlayer.loop(1);  //play specific mp3 in SD:/15/001.mp3; Folder Name(1~99); File Name(1~255)
    delay(2000);
  }
  // Kondisi Ultrasonic 3(Kanan) ketika jarak kurang dari 30cm, maka akan memutar SD:003.mp3 (Awas Kanan)
  if(distance3<30){
    myDFPlayer.loop(3);  //play specific mp3 in SD:/15/003.mp3; Folder Name(1~99); File Name(1~255)
    delay(2000);
  }
  // Kondisi Ultrasonic 4(Bawah) ketika jarak kurang dari 30cm, maka akan memutar SD:003.mp3 (Awas Bawah)
  if(distance4<30){
    myDFPlayer.loop(4);  //play specific mp3 in SD:/15/004.mp3;(blum ada) Folder Name(1~99); File Name(1~255)
    delay(2000);
  }

  
}

//Baca Ultrasonic
int getDistance (int trigPin, int echoPin){

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 unsigned long pulseTime = pulseIn(echoPin, HIGH);
 int distance = pulseTime/58;
 return distance;

}
