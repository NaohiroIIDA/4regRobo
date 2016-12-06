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

#define DEBUG

#define MOTOR



byte led_r[LED_NUM];
byte led_g[LED_NUM];
byte led_b[LED_NUM];


unsigned int pos;
unsigned int AD_IN[5];

unsigned int pos_leg[10];
unsigned int pos_tgt[10];
unsigned int speed[10];

unsigned int work_loop;
unsigned int work_mode;





void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200, SERIAL_8E1);
  while (!Serial1) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  #ifdef DEBUG

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  #endif

  pos = 7500;
  strip.begin();

  mySerial.begin(9600);
  delay(100);

  led_all_clear();

  mp3_reset();
  mp3_sdset();
  mp3_vol(10);


  mp3_play(1,2);


 #ifdef MOTOR

  delay(2000);

  pos_init();

  #ifdef DEBUG
      Serial.println("init");
  #endif

  ics_pos_write(2, pos_leg[2]);
  delay(200);
  ics_pos_write(6, pos_leg[6]);
  delay(200);
  ics_pos_write(4, pos_leg[4]);
  delay(200);
  ics_pos_write(8, pos_leg[8]);
  delay(500);

  ics_pos_write(1, pos_leg[1]);
  delay(200);
  ics_pos_write(5, pos_leg[5]);
  delay(200);
  ics_pos_write(3, pos_leg[3]);
  delay(200);
  ics_pos_write(7, pos_leg[7]);
  delay(200);

#ifdef DEBUG
      Serial.println("demo");
      Serial.println(pos_leg[1]);
  #endif

  //demo_move();

  #endif

  work_loop = 0;
  work_mode = 0;



}




void loop() {
  // put your main code here, to run repeatedly:

  int dir, power;
  int i,t;
  




  #ifdef DEBUG
      Serial.println("up");
  #endif
  pos_leg[1] = leg_up;
  ics_pos_write(5, 7000);
  delay(1500);

  #ifdef DEBUG
      Serial.println("down");
  #endif

  pos_leg[1] = leg_down;
  ics_pos_write(5, 6500);
  delay(1500);


 // loop_servo();
  

  //ics_pos_write(1, pos_leg[1]);


  // work_loop++;

  // if(work_loop > 100){

  //   #ifdef DEBUG
  //     Serial.println(work_mode);
  //   #endif



  //   if (work_mode == 0){
  //     pos_leg[1] = leg_up;
  //     pos_leg[3] = leg_up;
  //     pos_leg[5] = leg_up;
  //     pos_leg[7] = leg_up;
      
  //   }
  //   if (work_mode == 1){
  //     pos_leg[1] = leg_down;
  //     pos_leg[3] = leg_down;
  //     pos_leg[5] = leg_down;
  //     pos_leg[7] = leg_down;
      
  //   }

  //   #ifdef DEBUG
  //     Serial.println(pos_leg[1]);
  //   #endif

  //   ics_pos_write(1, pos_leg[1]);


  //   work_mode++;
  //   if(work_mode == 2) work_mode = 0;

  //   work_loop = 0;
  // }

  // delay(10);
 
//     for (i = 0; i < LED_NUM * 5 ;i++) {
//       eye(255, 255, 255, i);
//       delay(10);
//     }
  

//   led_all_clear();
//   delay(500);


// for (i = 0; i < 255 ;i++) {
//       all_up();
//       delay(10);
//     }

//   delay(500);

//   for (i = 0; i < 255 ;i++) {
//       all_down();
//       delay(10);
//     }

// for (i = 0; i < 255 ;i++) {
//       all_up_red();
//       delay(2);
//     }

//   delay(500);


// for (i = 0; i < 255 ;i++) {
//       all_up_green();
//       delay(2);
//     }

//   delay(500);
//   for (i = 0; i < 255 ;i++) {
//       all_up_blue();
//       delay(2);
//     }

//   delay(500);

//    for (i = 0; i < 255 ;i++) {
//       all_down();
//       delay(10);
//     }

  





  get_light();
  dir = get_light_dir();
  power = get_light_power();

//   Serial.print(AD_IN[0]);
//   Serial.print("\t");
// Serial.print(AD_IN[1]);
//   Serial.print("\t");
// Serial.print(AD_IN[2]);
//   Serial.print("\t");
// Serial.print(AD_IN[3]);
//   Serial.print("\t");
// Serial.print(AD_IN[4]);
//   Serial.println("\t");

  

  // Serial.print(dir);
  // Serial.print("/");
  // Serial.println(power);

 // mp3_play(1,2);





}
