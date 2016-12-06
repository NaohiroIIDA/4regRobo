#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 12); // RX, TX


#define PIN 10
#define LED_NUM 36

#define leg_up 9500
#define leg_down 5500

#define leg_fw24  8500
#define leg_bw24  6500
#define leg_fw68  6500
#define leg_bw68  8500

#define leg_center 7500


Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_NUM, PIN, NEO_GRB + NEO_KHZ800);



int led_r[LED_NUM];
int led_g[LED_NUM];
int led_b[LED_NUM];




int pos;
int AD_IN[5];

int pos_leg[8];



void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200, SERIAL_8E1);
  while (!Serial1) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Serial.begin(9600);
  // while (!Serial) {
  //   ; // wait for serial port to connect. Needed for native USB port only
  // }

  pos = 7500;
  strip.begin();

  mySerial.begin(9600);
  delay(100);
  mp3_reset();
  mp3_sdset();
  mp3_vol(10);


  mp3_play(1,2);

  delay(2000);

  pos_init();

  for(int i = 0;i<8;i++){
    ics_pos_write(i, pos_leg[i]);
    delay(1000);
  }

  
  
  
  for (pos = leg_center; pos > leg_down; pos -= 2) {
    ics_pos_write(0, pos);
    ics_pos_write(2, pos);
    ics_pos_write(4, pos);
    ics_pos_write(6, pos);
  }
  for (pos = leg_down; pos < leg_up; pos += 2) {
    ics_pos_write(0, pos);
    ics_pos_write(2, pos);
    ics_pos_write(4, pos);
    ics_pos_write(6, pos);
  }
  for (pos = leg_up; pos > leg_center; pos -= 2) {
    ics_pos_write(0, pos);
    ics_pos_write(2, pos);
    ics_pos_write(4, pos);
    ics_pos_write(6, pos);
  }

  delay(1000);

  for (pos = leg_center; pos < leg_fw24; pos += 2) {
    ics_pos_write(1, pos);
    ics_pos_write(3, pos);
    ics_pos_write(5, pos);
    ics_pos_write(7, pos);
  }
   for (pos = leg_fw24; pos > leg_bw24; pos -= 2) {
    ics_pos_write(1, pos);
    ics_pos_write(3, pos);
    ics_pos_write(5, pos);
    ics_pos_write(7, pos);
  }
  for (pos = leg_bw24; pos < leg_center; pos += 2) {
    ics_pos_write(1, pos);
    ics_pos_write(3, pos);
    ics_pos_write(5, pos);
    ics_pos_write(7, pos);
  }
  



 
  
  
}

void loop() {


demo_move();
  
}
