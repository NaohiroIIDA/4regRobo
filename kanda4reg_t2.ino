#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>


//#define DEBUG
//#define DEMO




#define PIN 10
#define LED_NUM 36

#define leg_up 9500
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
int motor_mode;

int now_move;

int led_tick;
int led_mode;
int led_pos;





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

  led_tick  = 0;
  led_mode  = 0;
  led_pos   = 0;


  strip.begin();

  mySerial.begin(9600);
  delay(100);
  mp3_reset();
  mp3_sdset();
  mp3_vol(10);


  mp3_play(1,2);

  delay(2000);

  pos_init();

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
  
  
}

void loop() {


//demo_move();

led_tick++;
if(led_tick > 10){

  eye(250,250,250,led_pos);
  led_pos++;
  led_tick = 0;
}

motor_tick++;
pos_motor_set();

if(motor_tick > 2){
   loop_motor();
  motor_tick = 0;
}


motor_count++;

#ifdef DEBUG
    Serial.print(leg[0]);
    Serial.print("\t");
    Serial.println(tgt[0]);
#endif

  //if(motor_count > 1000){
  if(leg[now_move] == tgt[now_move]){

    switch(motor_mode){
      case 0:
        tgt[0] = leg_down;    spd[0] = 10;
        tgt[2] = leg_center;  spd[0] = 10;
        tgt[4] = leg_down;    spd[0] = 10;
        tgt[6] = leg_center;   spd[0] = 10;


        tgt[1] = leg_fw13;  spd[0] = 2;
        tgt[3] = leg_bw13;  spd[0] = 2;
        tgt[5] = leg_fw57;  spd[0] = 2;
        tgt[7] = leg_bw57;  spd[0] = 2;

        now_move = 2;

      break;

      case 1:
        tgt[0] = leg_down;    spd[0] = 10;
        tgt[2] = leg_center;  spd[0] = 10;
        tgt[4] = leg_down;    spd[0] = 10;
        tgt[6] = leg_center;    spd[0] = 10;


        tgt[1] = leg_bw13;  spd[0] = 1;
        tgt[3] = leg_fw13;  spd[0] = 20;
        tgt[5] = leg_bw57;  spd[0] = 1;
        tgt[7] = leg_fw57;  spd[0] = 20;

        now_move = 3;
        
      break;

      case 2:
        tgt[0] = leg_down;    spd[0] = 10;
        tgt[2] = leg_down;    spd[0] = 10;
        tgt[4] = leg_down;    spd[0] = 10;
        tgt[6] = leg_down;    spd[0] = 10;


        tgt[1] = leg_bw13;  spd[0] = 1;
        tgt[3] = leg_fw13;  spd[0] = 20;
        tgt[5] = leg_bw57;  spd[0] = 1;
        tgt[7] = leg_fw57;  spd[0] = 20;


        now_move = 2;
        
      break;

      case 3:
        tgt[0] = leg_center;    spd[0] = 10;
        tgt[2] = leg_down;  spd[0] = 10;
        tgt[4] = leg_center;    spd[0] = 10;
        tgt[6] = leg_down;   spd[0] = 10;


        tgt[1] = leg_bw13;  spd[0] = 1;
        tgt[3] = leg_fw13;  spd[0] = 20;
        tgt[5] = leg_bw57;  spd[0] = 1;
        tgt[7] = leg_fw57;  spd[0] = 20;

        now_move = 0;

      break;

      case 4:
        tgt[0] = leg_center;    spd[0] = 10;
        tgt[2] = leg_down;  spd[0] = 10;
        tgt[4] = leg_center;    spd[0] = 10;
        tgt[6] = leg_down;   spd[0] = 10;


        tgt[1] = leg_fw13;  spd[0] = 1;
        tgt[3] = leg_bw13;  spd[0] = 20;
        tgt[5] = leg_fw57;  spd[0] = 1;
        tgt[7] = leg_bw57;  spd[0] = 20;

        now_move = 1;
        
      break;

      case 5:
        tgt[0] = leg_down;    spd[0] = 10;
        tgt[2] = leg_down;    spd[0] = 10;
        tgt[4] = leg_down;    spd[0] = 10;
        tgt[6] = leg_down;    spd[0] = 10;


        tgt[1] = leg_fw13;  spd[0] = 1;
        tgt[3] = leg_bw13;  spd[0] = 20;
        tgt[5] = leg_fw57;  spd[0] = 1;
        tgt[7] = leg_bw57;  spd[0] = 20;


        now_move = 0;
        
      break;

    

      

      

    }
    motor_mode++;
    if(motor_mode == 6) motor_mode = 0;

    motor_count = 0;

  }
  
}
