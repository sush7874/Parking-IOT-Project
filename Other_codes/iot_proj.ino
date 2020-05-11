#include <WiFi.h>
#include <Servo.h>
//#include <LiquidCrystal_I2C.h>
#include <Wire.h>
//#include <FirebaseArduino.h>

//#define FIREBASE_HOST "https://iot-proj-bcf82.firebaseio.com/"                 // the project name address from firebase id
//#define FIREBASE_AUTH "u0jiw1MSJ0vjSnRyWhnduW5s4tcxf6LGrpPiYyW8"            // the secret key generated from firebase

#define WIFI_SSID "Pixel_7667"                                             // input your home or public wifi name 
#define WIFI_PASSWORD "iotproj1"                                    //password for Wifi
String Available = "";                                                  //availability string
String fireAvailable = "";

//LiquidCrystal_I2C lcd(0x27, 16, 2);         //i2c display address 27 and 16x2 lcd display
Servo myservo;                          //servo as gate at entry
Servo myservos;                               //servo as gate at exit 
int Empty;                            //available space integer
int allSpace = 90;
int countYes = 0;
int carEnter = 39;                      // entry sensor 
int carExited = 36;                   //exi sensor
int TRIG = 23;                  //ultrasonic trig  pin
int ECHO = 34;                // ultrasonic echo pin
int led = 5;                 // spot occupancy signal
int pos;
int pos1;

long duration, distance;     

void setup() {
  delay(1000);
  Serial.begin (9600);     // serial debugging
  //Wire.begin(D2, D1);       // i2c start
  myservo.attach(21);      // servo pin to D6 entry servo
  myservos.attach(19);       // servo pin to D5 exit servo
  pinMode(TRIG, OUTPUT);      // trig pin as output 
  pinMode(ECHO, INPUT);         // echo pin as input
  pinMode(led, OUTPUT);         // spot indication
  pinMode(carExited, INPUT);    // ir as input
  pinMode(carEnter, INPUT);     // ir as input

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);                          // display ssid
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");                          // if not connected print this
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  //Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);        // begin firebase authentication

  //lcd.begin();                           //begin lcd
  //lcd.home();                            
  //lcd.setCursor(0, 0);                      // 0th row and 0thh column
  //lcd.print("Smart Parking");    
}

void loop() {

  digitalWrite(TRIG, LOW);         // make trig pin low
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);        // make trig pin high
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH); // measures the width of the pulse. 
  distance = (duration / 2) / 29.1;      // take distance in cm

    Serial.print("Centimeter: ");
    Serial.println(distance);

  int carEntry = digitalRead(carEnter);      // read ir input
  if (carEntry == HIGH) {                     // if high then count and send data
    countYes++;                             //increment number of cars entered. 
    Serial.print("Car Entered = " ); Serial.println(countYes );
    //lcd.setCursor(0, 1);
    //lcd.print("Car Entered");
    for (pos = 140; pos >= 45; pos -= 1) {        // change servo position
      myservo.write(pos);                       
      delay(5);
    }
    delay(2000);

    for (pos = 45; pos <= 140; pos += 1) {       // change servo position
      // in steps of 1 degree
      myservo.write(pos);
      delay(5);
    }
    Serial.print("No of cars present :");
    Serial.println(countYes);
    //Firebase.pushString("/Parking Status/", fireAvailable );    // send string to firebase
    //lcd.clear();
  }
  int carExit = digitalRead(carExited);              //read exit ir sensor
  if (carExit == HIGH) {                            //if high then count and send
    countYes--;                                    //decrement count
    Serial.print("Car Exited = " ); Serial.println(countYes);
//    lcd.setCursor(0, 1);
  //  lcd.print("Car Exited");
    for (pos1 = 140; pos1 >= 45; pos1 -= 1) {         // change servo position
      myservos.write(pos1);
      delay(5);
    }
    delay(2000);

    for (pos1 = 45; pos1 <= 140; pos1 += 1) {            // change servo position
      // in steps of 1 degree
      myservos.write(pos1);
      delay(5);
    }
    //Firebase.pushString("/Parking Status/", fireAvailable );  // send string to firebase
    //lcd.clear();
  }
  if (distance < 6) {                      //if distance is less than 6cm then on led 
        Serial.println("Occupied ");
    digitalWrite(led, HIGH);
  }

  if (distance > 6) {                        //if distance is greater than 6cm then off led 
        Serial.println("Available ");
    digitalWrite(led, LOW);
  }

  Empty = allSpace - countYes;         //calculate available data
 
  Available = String("Available= ") + String(Empty) + String("/") + String(allSpace);       // convert the int to string
  fireAvailable = String("Available=") + String(Empty) + String("/") + String(allSpace);

  //lcd.setCursor(0, 0);
  //lcd.print(Available);                 //print available data to lcd

}
