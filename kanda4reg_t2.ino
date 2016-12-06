#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>


//#define DEBUG
//#define DEMO




#define PIN 10
#define LED_NUM 30

#define leg_up 8000
#define leg_down 5500

#define leg_fw13  8000
#define leg_bw13  6000
#define leg_fw57  6000
#define leg_bw57  8000

#define leg_center 7500


Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_NUM, PIN, NEO_GRB + NEO_KHZ800);
SoftwareSerial mySerial(11, 12); // RX, TX



int led_r[LED_NUM];
int led_g[LED_NUM];
int led_b[LED_NUM];


int pos;
int AD_IN[5];

int leg[8];
int tgt[8];

int spd[8];

int motor_count;
int motor_tick;

int walk_mode;

int motor_mode;
int now_move;

int led_tick;
int led_mode;
int led_pos;
int led_light;





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

  motor_tick = 0;
  motor_count = 0;
  motor_mode = 0;
  now_move = 0;

  walk_mode = 2;


  led_tick  = 0;
  led_mode  = 1;
  led_pos   = 0;


  strip.begin();
  all_clear();

  mySerial.begin(9600);
  delay(100);
  mp3_reset();
  mp3_sdset();
  mp3_vol(10);


  mp3_play(1,2);

  delay(2000);

  pos_init();


  for(int i = 0;i<8;i++){
    ics_pos_write(i, leg[i]);
    delay(500);
  }


  #ifdef DEMO

  for(int i = 0;i<8;i++){
    ics_pos_write(i, leg[i]);
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
  for (pos = leg_up; pos > leg_down; pos -= 2) {
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

#endif

  delay (2000);

  
  
}

void loop() {


//demo_move();

led_tick++;
if(led_tick > 10){

  if(led_mode == 0){
     eye(250,250,250,led_pos);
    led_pos++;
    if(led_pos > LED_NUM){
      led_pos = 0;
    }
  }

  if(led_mode == 1){
     eye(250,250,250,led_pos);
    led_pos--;
    if(led_pos < 0){
      led_pos = LED_NUM;
    }
  }

  if(led_mode == 2){
     led_loop_set(255,70,0,led_light);
    led_light++;
    if (led_light > 100){
      led_light =100;
      led_mode = 2;
    }

  }
  if(led_mode == 3){
     led_loop_set(255,70,0,led_light);
    led_light--;
    if (led_light < 0){
      led_light = 0;
      led_mode = 1;
    }

  }
 
  led_tick = 0;
}

motor_tick++;
pos_motor_set();

if(motor_tick > 2){
   loop_motor();
  motor_tick = 0;
}

if(walk_mode == 0){

  motor_count++;
    //if(motor_count > 1000){
    if(leg[now_move] == tgt[now_move]){

      switch(motor_mode){
        case 0:
          tgt[2] = leg_center;  spd[2] = 10;
          tgt[6] = leg_center;   spd[6] = 10;
          now_move = 2;
        break;

        case 1:
          tgt[1] = leg_bw13;  spd[1] = 10;
          tgt[3] = leg_fw13;  spd[3] = 10;
          tgt[5] = leg_bw57;  spd[5] = 10;
          tgt[7] = leg_fw57;  spd[7] = 10;
          now_move = 1;
        break;

        case 2:
          tgt[2] = leg_down;  spd[2] = 10;
          tgt[6] = leg_down;   spd[4] = 10;
          now_move = 2;
        break;

        case 3:
          tgt[0] = leg_center;    spd[0] = 10;
          tgt[4] = leg_center;    spd[4] = 10;
          now_move = 0;
        break;

        case 4:
          tgt[1] = leg_fw13;  spd[1] = 10;
          tgt[3] = leg_bw13;  spd[3] = 10;
          tgt[5] = leg_fw57;  spd[5] = 10;
          tgt[7] = leg_bw57;  spd[7] = 10;
          now_move = 3;
        break;

        case 5:
          tgt[0] = leg_down;    spd[0] = 10;
          tgt[4] = leg_down;    spd[4] = 10;
          now_move = 0;
        break;
      }
      motor_mode++;
      if(motor_mode == 6) motor_mode = 0;

      motor_count = 0;
    }
  }

  if(walk_mode == 1){

    if(leg[now_move] == tgt[now_move]){

      switch(motor_mode){
        case 0:
          tgt[0] = leg_up;  spd[0] = 20;
          now_move = 0;
        break;

        case 1:
          tgt[1] = leg_fw13;  spd[1] = 10;
          tgt[3] = leg_bw13;  spd[3] = 1;
          tgt[5] = leg_fw57;  spd[5] = 1;
          tgt[7] = leg_fw57;  spd[7] = 1;

          now_move = 1;
        break;

        case 2:
          tgt[0] = leg_down;  spd[0] = 20;
          now_move = 0;
        break;

        case 3:
          tgt[2] = leg_up;  spd[2] = 20;
          now_move = 2;
        break;

        case 4:
          tgt[1] = leg_bw13;  spd[1] = 1;
          tgt[3] = leg_fw13;  spd[3] = 10;
          tgt[5] = leg_fw57;  spd[5] = 1;
          tgt[7] = leg_fw57;  spd[7] = 1;

          now_move = 3;
        break;

        case 5:
          tgt[2] = leg_down;  spd[2] = 20;
          now_move = 2;
        break;

        case 6:
          tgt[4] = leg_up;  spd[4] = 20;
          now_move = 4;
        break;

        case 7:
          tgt[1] = leg_bw13;  spd[1] = 1;
          tgt[3] = leg_bw13;  spd[3] = 1;
          tgt[5] = leg_bw57;  spd[5] = 10;
          tgt[7] = leg_fw57;  spd[7] = 1;

          now_move = 5;
        break;

        case 8:
          tgt[4] = leg_down;  spd[4] = 20;
          now_move = 4;
        break;

        case 9:
          tgt[6] = leg_up;  spd[6] = 20;
          now_move = 6;
        break;

        case 10:
          tgt[1] = leg_bw13;  spd[1] = 1;
          tgt[3] = leg_bw13;  spd[3] = 1;
          tgt[5] = leg_fw57;  spd[5] = 1;
          tgt[7] = leg_bw57;  spd[7] = 10;

          now_move = 7;
        break;

        case 11:
          tgt[6] = leg_down;  spd[6] = 20;
          now_move = 6;
        break;


        


      }
      motor_mode++;
      if(motor_mode == 12) motor_mode = 0;

      motor_count = 0;
    }
  }

  if(walk_mode == 2){

    if(leg[now_move] == tgt[now_move]){

      switch(motor_mode){
        case 0:
          tgt[0] = leg_up;  spd[0] = 20;
          now_move = 0;
        break;

        case 1:
          tgt[1] = leg_bw13;  spd[1] = 10;
          tgt[3] = leg_fw13;  spd[3] = 1;
          tgt[5] = leg_bw57;  spd[5] = 1;
          tgt[7] = leg_bw57;  spd[7] = 1;

          now_move = 1;
        break;

        case 2:
          tgt[0] = leg_down;  spd[0] = 20;
          now_move = 0;
        break;

        case 3:
          tgt[2] = leg_up;  spd[2] = 20;
          now_move = 2;
        break;

        case 4:
          tgt[1] = leg_fw13;  spd[1] = 1;
          tgt[3] = leg_bw13;  spd[3] = 10;
          tgt[5] = leg_bw57;  spd[5] = 1;
          tgt[7] = leg_bw57;  spd[7] = 1;

          now_move = 3;
        break;

        case 5:
          tgt[2] = leg_down;  spd[2] = 20;
          now_move = 2;
        break;

        case 6:
          tgt[4] = leg_up;  spd[4] = 20;
          now_move = 4;
        break;

        case 7:
          tgt[1] = leg_fw13;  spd[1] = 1;
          tgt[3] = leg_fw13;  spd[3] = 1;
          tgt[5] = leg_fw57;  spd[5] = 10;
          tgt[7] = leg_bw57;  spd[7] = 1;

          now_move = 5;
        break;

        case 8:
          tgt[4] = leg_down;  spd[4] = 20;
          now_move = 4;
        break;

        case 9:
          tgt[6] = leg_up;  spd[6] = 20;
          now_move = 6;
        break;

        case 10:
          tgt[1] = leg_fw13;  spd[1] = 1;
          tgt[3] = leg_fw13;  spd[3] = 1;
          tgt[5] = leg_bw57;  spd[5] = 1;
          tgt[7] = leg_fw57;  spd[7] = 10;

          now_move = 7;
        break;

        case 11:
          tgt[6] = leg_down;  spd[6] = 20;
          now_move = 6;
        break;


        


      }
      motor_mode++;
      if(motor_mode == 12) motor_mode = 0;

      motor_count = 0;
    }
  }
  
}
