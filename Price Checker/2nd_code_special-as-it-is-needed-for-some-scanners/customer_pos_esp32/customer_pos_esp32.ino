

#define RXD2 16
#define TXD2 17





#include <Wire.h>
#include <LiquidCrystal_I2C.h>


#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>



const char* ssid = "test";
const char* password = "test12345678";
String serverName = "http://192.168.77.223:8080/test";

long unsigned int lastUpdate = millis();
bool mode = 0;
unsigned long int x = 0;
unsigned long int y = 0;
  StaticJsonDocument<200> doc;




uint8_t bell[8]  = {0x4, 0xe, 0xe, 0xe, 0x1f, 0x0, 0x4};
uint8_t note[8]  = {0x2, 0x3, 0x2, 0xe, 0x1e, 0xc, 0x0};
uint8_t clockx[8] = {0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0};
uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};
uint8_t duck[8]  = {0x0, 0xc, 0x1d, 0xf, 0xf, 0x6, 0x0};
uint8_t check[8] = {0x0, 0x1 ,0x3, 0x16, 0x1c, 0x8, 0x0};
uint8_t cross[8] = {0x0, 0x1b, 0xe, 0x4, 0xe, 0x1b, 0x0};
uint8_t retarrow[8] = {	0x1, 0x1, 0x5, 0x9, 0x1f, 0x8, 0x4};

uint8_t arabicChars[30][8] = {
 { 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06 },
 { 0x00, 0x00, 0x00, 0x02, 0x02, 0x1E, 0x00, 0x02 },
 { 0x03, 0x00, 0x01, 0x01, 0x1F, 0x00, 0x00, 0x00 },
 { 0x02, 0x06, 0x00, 0x02, 0x02, 0x1E, 0x00, 0x00 },
 { 0x00, 0x00, 0x06, 0x09, 0x11, 0x1F, 0x00, 0x04 },
 { 0x00, 0x00, 0x06, 0x09, 0x11, 0x1F, 0x00, 0x00 },
 { 0x02, 0x00, 0x06, 0x09, 0x11, 0x1F, 0x00, 0x00 },
 { 0x00, 0x00, 0x00, 0x01, 0x01, 0x0F, 0x00, 0x00 },
{ 0x00, 0x01, 0x00, 0x01, 0x01, 0x0F, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x0C },
{ 0x00, 0x01, 0x00, 0x01, 0x01, 0x02, 0x02, 0x0C },

   
};

int text[12]={ 1,2,3,4,5,6,7,8,9,10};

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);

long unsigned int scannerOffEnd = 0;

void setup() {
  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial.begin(115200);
  //Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Serial Txd is on pin: "+String(TX));
  Serial.println("Serial Rxd is on pin: "+String(RX));

pinMode(2,INPUT);
  pinMode(15,OUTPUT);
    digitalWrite(15 , LOW);


	lcd.begin();
	lcd.backlight();

lcd.setCursor(0, 1);
	lcd.print("Connecting to WiFi...");
	


 WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());











  


	lcd.createChar(0, bell);
	lcd.createChar(1, note);
	lcd.createChar(2, clockx);
	lcd.createChar(3, heart);
	lcd.createChar(4, duck);
	lcd.createChar(5, check);
	lcd.createChar(6, cross);
	lcd.createChar(7, retarrow);
	lcd.home();

  lcd.clear();

	lcd.print("Hello World!");
	lcd.setCursor(0, 1);
	lcd.print("Tormos ");
//	lcd.write(3);
	lcd.print("Market");
  	lcd.setCursor(4, 2);
	lcd.print("Proway ");
//	lcd.write(3);
	lcd.print("Solutions");


  lcd.setCursor(0, 3);
  lcd.write(1);
  lcd.write(2);
  lcd.write(3);
  lcd.write(5);
  lcd.write(4);
    lcd.write(5);
  lcd.write(6);
  lcd.write(7);
  lcd.write(0);

	delay(5000);
//  displayKeyCodes();




}




// display all keycodes
void displayKeyCodes(void) {
	uint8_t i = 0;

	while (1) {
		lcd.clear();
		lcd.print("Codes 0x");
		lcd.print(i, HEX);
		lcd.print("-0x");
		lcd.print(i + 16, HEX);
		lcd.setCursor(0, 1);

		for (int j = 0; j < 16; j++) {
			lcd.write(i + j);
		}
		i += 16;

		delay(4000);
	}
}







void loop() { 

  if ( digitalRead(2) && ( millis() > scannerOffEnd)){

    digitalWrite(15 , HIGH);
  }else{
    digitalWrite(15 , LOW);
  }

  
  if(millis() - lastUpdate > 15000){

    mode = 1;

  }

  if(mode){

  x = millis() / 4000;

  if (x > y){
    y=x;

 

    if(x%2 == 0 ){
      	lcd.begin();
	lcd.backlight();
       lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Price Checker v1.0");
  delay(40);
	lcd.setCursor(0, 2);
	lcd.print("by Dawoud Tormos ");
    }else{
      	lcd.begin();
	lcd.backlight();
      lcd.clear();
      lcd.setCursor(0, 0);
	lcd.print("Tormos Market ");
  
        lcd.setCursor(0, 2);
          delay(10);
	lcd.print("Proway Solutions ");

    }

  }
  /*lcd.setCursor(0, 3);
	lcd.print("Proway Solutions");*/

  }






  if (Serial2.available()) {
    String bar = Serial2.readStringUntil('\n');
    mode = 0 ;
    //int barInt = bar.toInt();
    Serial.print(bar);


    	lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(bar);

       lcd.setCursor(0, 2);

       
getPrice(bar);
lastUpdate = millis();


  }








   if (Serial.available()) {
    String bar = Serial.readStringUntil('\n');
    mode = 0 ;
    //int barInt = bar.toInt();
    Serial.println(bar);


    	lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(bar);

       lcd.setCursor(0, 2);



getPrice(bar);
lastUpdate = millis();


/*
     
      for (int i=0; i<8; i++) {
        delay(30);
        	lcd.createChar(i, arabicChars[text[i]]);
          delay(10);
          lcd.home();
          delay(10);
          lcd.setCursor(i, 1);
          delay(10);
         lcd.write(i);
         delay(10);
         Serial.println(text[i]);
         Serial.println("");
         delay(10);

      }
*/

  }






}