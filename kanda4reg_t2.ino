#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>


//#define DEBUG
//#define DEMO

#define PIN 10
#define LED_NUM 34

#define leg_up 8000
#define leg_down 5500

#define leg_hold_a  5500
#define leg_hold_b  9500


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

int sensor_tick;






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

  walk_mode = 0;


  led_tick  = 0;
  led_mode  = 1;
  led_pos   = 0;

  sensor_tick = 0;

  strip.begin();
  all_clear();

  mySerial.begin(9600);
  delay(100);
  mp3_reset();
  mp3_sdset();
  mp3_vol(10);


  mp3_play(1, 2);

  delay(2000);

  pos_init();


  for (int i = 0; i < 8; i++) {
    ics_pos_write(i, leg[i]);
    delay(500);
  }


#ifdef DEMO

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

  delay (5000);

}

void loop() {

  int dir, power, power2;

  //demo_move();

  sensor_tick++;
  if (sensor_tick > 2000) {

    sensor_tick = 0;
    get_light();
    dir = get_light_dir();
    power = get_light_power();
    power2 = get_light_power_upside();

#ifdef DEBUG
    Serial.print(dir);
    Serial.print("\t");
    Serial.print(power);

    Serial.print("\t");
    Serial.println(power2);
#endif

    if(power2 > 500){
      if(walk_mode != 3){
        walk_mode = 3;
        motor_mode = 0;
      }
    }else{
      if(walk_mode == 3 && motor_mode == 4){
        walk_mode = 4;
        motor_mode = 0;
      }
      
      if(walk_mode == 4 && motor_mode == 2){
        walk_mode = 0;
        motor_mode = 0;
      }

      if(walk_mode == 0 || walk_mode == 1 || walk_mode == 2 ){

        switch(dir){
          case 1:
            if(walk_mode != 0){
              walk_mode = 0;
              motor_mode = 0;
            }
          break;

          case 2:
            if(walk_mode != 2){
              walk_mode = 2;
              motor_mode = 0;
            }
          break;

           case 3:
            if(walk_mode != 2){
              walk_mode = 2;
              motor_mode = 0;
            }
          break;

          case 4:
            if(walk_mode != 1){
              walk_mode = 1;
              motor_mode = 0;
            }
          break;


        }

      }
    }
  }

  

  led_tick++;
  if (led_tick > 20) {
    master_led_loop();
    led_tick = 0;
  }

  motor_tick++;
  pos_motor_set();

  if (motor_tick > 2) {
    loop_motor();
    motor_tick = 0;
  }
  master_motor_loop();

}
