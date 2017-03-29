#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 8 //set DS18B20 DQ pin
#define RELAY_CONTROL_PIN 9 //set REPLY's interupt control pin
int  R_Int = RELAY_CONTROL_PIN;
#define Sous_Temp 59 //set temperature here
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
unsigned long timerbase;
void setup() {

  Serial.begin(9600);
  //delay(500);
  
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);
  display.clearDisplay();
  timerbase = millis();
  Serial.println("Temperature Sensor Start");
  pinMode(R_Int,OUTPUT); //set reply control pin to GPIO output
  sensors.begin();
}

void loop() {
  float CurrentTemp = 0;

  sensors.requestTemperatures();
  CurrentTemp = sensors.getTempCByIndex(0);
  Serial.println(CurrentTemp);
  if (CurrentTemp < Sous_Temp)
  {
    digitalWrite(R_Int,HIGH); //turn on power, common pin to NC
  } else{
    digitalWrite(R_Int,LOW);  //turn off power, common pin to NO
  }
  
  display.clearDisplay();

  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Hello, hihi!");
  display.print("Current Temperature: ");
  display.println(CurrentTemp);
  display.print("Timer: ");
  //display.println(millis() - timerbase);
  TimerConvert();
  display.display();

  delay(500);
}

void TimerConvert(){
  unsigned long timer2;
  unsigned int seconds, minutes, hours;
  timer2 = millis() - timerbase;
  timer2 = timer2 / 1000; //seconds
  seconds = timer2 % 60;
  minutes = (timer2 / 60) % 60;
  hours = (timer2 / 60 / 60) % 60;
  display.print(hours);
  display.print("h:");  
  display.print(minutes);
  display.print("m:");
  display.print(seconds);
  display.println("s");
}

