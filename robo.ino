

void pos_init() {

  for (int i = 0; i < 8; ++i)
  {
    leg[i] = leg_center;
    tgt[i] = leg_center;
    spd[i] = 10;
  }
}


byte ics_pos_h(int data) {

  int exem = (data >> 7) & 0x7F;
  byte exem_b = (byte)exem;
  return exem_b;

}

byte ics_pos_l(int data) {

  int exem = data & 0x7F;
  byte exem_b = (byte)exem;
  return exem_b;
}

void ics_pos_write(int id, int data) {
  Serial1.write(0x80 + (id + 1));
  Serial1.write(ics_pos_h(data));
  Serial1.write(ics_pos_l(data));
  // delay(10);
}


void loop_motor() {
  for (int i = 0; i < 8; ++i)
  {
    if (leg[i] != tgt[i]) {


      if (leg[i] > tgt[i]) {
        leg[i] -= spd[i];
        if (leg[i] < tgt[i]) leg[i] = tgt[i];
      } else {
        leg[i] += spd[i];
        if (leg[i] > tgt[i]) leg[i] = tgt[i];
      }
    }
  }

}

void pos_motor_set() {

  for (int i = 0; i < 8; ++i)
  {
    ics_pos_write(i, leg[i]);
  }
}

void demo_set(int data)
{

  for (int i = 0; i < 8; ++i)
  {
    leg[i] = data;
  }
}


void demo_move() {

  for (pos = 7500; pos < 9500; pos += 2) {

    demo_set(pos);
    pos_motor_set();

  }

  for (pos = 9500; pos > 7500; pos -= 2) {

    demo_set(pos);
    pos_motor_set();

  }

  for (pos = 7500; pos > 5500; pos -= 2) {

    demo_set(pos);
    pos_motor_set();

  }

  for (pos = 5500; pos < 7500; pos += 2) {

    demo_set(pos);
    pos_motor_set();

  }

}


void master_motor_loop() {
  if (walk_mode == 0) {

    motor_count++;
    //if(motor_count > 1000){
    if (leg[now_move] == tgt[now_move]) {

      switch (motor_mode) {
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
      if (motor_mode == 6) motor_mode = 0;

      motor_count = 0;
    }
  }

  if (walk_mode == 1) {

    if (leg[now_move] == tgt[now_move]) {

      switch (motor_mode) {
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
      if (motor_mode == 12) motor_mode = 0;

      motor_count = 0;
    }
  }

  if (walk_mode == 2) {

    if (leg[now_move] == tgt[now_move]) {

      switch (motor_mode) {
        case 0:
          tgt[0] = leg_up;  spd[0] = 20;
          now_move = 0;
          break;

        case 1:
          tgt[1] = leg_bw13;  spd[1] = 10;
          tgt[3] = leg_fw13;  spd[3] = 2;
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
          tgt[5] = leg_bw57;  spd[5] = 2;
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
          tgt[7] = leg_bw57;  spd[7] = 2;

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
          tgt[1] = leg_fw13;  spd[1] = 2;
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
      if (motor_mode == 12) motor_mode = 0;

      motor_count = 0;
    }
  }

  if (walk_mode == 3) {

    //motor_count++;
    //if(motor_count > 500){
    if (leg[now_move] == tgt[now_move]) {


      switch (motor_mode) {
        case 0:
          tgt[0] = leg_center;  spd[0] = 10;
          tgt[1] = leg_center;  spd[1] = 10;
          tgt[2] = leg_center;  spd[2] = 10;
          tgt[3] = leg_center;  spd[3] = 10;
          tgt[4] = leg_center;  spd[4] = 10;
          tgt[5] = leg_center;  spd[5] = 10;
          tgt[6] = leg_center;  spd[6] = 10;
          tgt[7] = leg_center;  spd[7] = 10;

          motor_mode = 1;
          now_move = 0;
          break;

          case 1:
          tgt[0] = leg_hold_a;  spd[0] = 10;
          tgt[1] = leg_hold_a;  spd[1] = 10;
          tgt[2] = leg_hold_a;  spd[2] = 10;
          tgt[3] = leg_hold_a;  spd[3] = 10;
          tgt[4] = leg_hold_a;  spd[4] = 10;
          tgt[5] = leg_hold_a;  spd[5] = 10;
          tgt[6] = leg_hold_a;  spd[6] = 10;
          tgt[7] = leg_hold_a;  spd[7] = 10;

          motor_mode = 2;
          now_move = 0;
          break;

          case 2:
          tgt[0] = leg_hold_b;  spd[0] = 10;
          tgt[1] = leg_hold_b;  spd[1] = 10;
          tgt[2] = leg_hold_b;  spd[2] = 10;
          tgt[3] = leg_hold_b;  spd[3] = 10;
          tgt[4] = leg_hold_b;  spd[4] = 10;
          tgt[5] = leg_hold_b;  spd[5] = 10;
          tgt[6] = leg_hold_b;  spd[6] = 10;
          tgt[7] = leg_hold_b;  spd[7] = 10;

          motor_mode = 3;
          now_move = 0;

          break;

          case 3:
          led_mode = 2;
          led_light = 0;
          
          motor_mode = 4;
          break;


      }
      motor_count = 0;
    }
  }

  if (walk_mode == 4) {

    motor_count++;
    if(motor_count > 1000){

      switch (motor_mode) {
        case 0:

          tgt[0] = leg_center;  spd[0] = 10;
          tgt[1] = leg_center;  spd[1] = 10;
          tgt[2] = leg_center;  spd[2] = 10;
          tgt[3] = leg_center;  spd[3] = 10;
          tgt[4] = leg_center;  spd[4] = 10;
          tgt[5] = leg_center;  spd[5] = 10;
          tgt[6] = leg_center;  spd[6] = 10;
          tgt[7] = leg_center;  spd[7] = 10;

          motor_mode = 1;
          motor_count = 0;

          led_mode = 4;
          led_light = 0;

          break;

          case 1:
          led_mode = 5;
          led_light = 0;

          motor_mode = 2;
          break;



      }
      motor_count = 0;
    }
  }
}
