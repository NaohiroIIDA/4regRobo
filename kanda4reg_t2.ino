#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

#define leg_up 5500
#define leg_down 9500

#define leg_fw24  8500
#define leg_bw24  6500
#define leg_fw68  6500
#define leg_bw68  8500

#define leg_center 7500


SoftwareSerial mySerial(11, 12); // RX, TX


#define PIN 10
#define LED_NUM 36


Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_NUM, PIN, NEO_GRB + NEO_KHZ800);


#define MOTOR


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
  mp3_vol();


  mp3_play(1,2);


  //#ifdef MOTOR

  delay(2000);

  pos_init();


#ifdef MOTOR
  

  ics_pos_write(2, pos_leg[2]);
  delay(1000);
  ics_pos_write(6, pos_leg[6]);
  delay(1000);
  ics_pos_write(4, pos_leg[4]);
  delay(1000);
  ics_pos_write(8, pos_leg[8]);
  delay(2000);

  ics_pos_write(1, pos_leg[1]);
  delay(1000);
  ics_pos_write(5, pos_leg[5]);
  delay(1000);
  ics_pos_write(3, pos_leg[3]);
  delay(1000);
  ics_pos_write(7, pos_leg[7]);
  delay(1000);

  #endif

}




void loop() {
  // put your main code here, to run repeatedly:

  int dir, power;
  int i,t;


#ifdef MOTOR
  demo_move();
#endif

 
    for (i = 0; i < LED_NUM * 5 ;i++) {
      eye(255, 255, 255, i);
      delay(10);
    }
  

  all_clear();
  delay(500);


for (i = 0; i < 255 ;i++) {
      all_up();
      delay(10);
    }

  delay(500);

  for (i = 0; i < 255 ;i++) {
      all_down();
      delay(10);
    }

for (i = 0; i < 255 ;i++) {
      all_up_red();
      delay(2);
    }

  delay(500);


for (i = 0; i < 255 ;i++) {
      all_up_green();
      delay(2);
    }

  delay(500);
  for (i = 0; i < 255 ;i++) {
      all_up_blue();
      delay(2);
    }

  delay(500);

   for (i = 0; i < 255 ;i++) {
      all_down();
      delay(10);
    }

  





  get_light();
  dir = get_light_dir();
  power = get_light_power();

  

  // Serial.print(dir);
  // Serial.print("/");
  // Serial.println(power);

 // mp3_play(1,2);





}
