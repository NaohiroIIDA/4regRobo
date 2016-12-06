

void pos_init(){

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


void loop_motor(){
  for (int i = 0; i < 8; ++i)
  {
    if(leg[i] != tgt[i]){


      if(leg[i] > tgt[i]){
        leg[i] -= spd[i];
        if(leg[i] < tgt[i]) leg[i] = tgt[i];
      }else{
        leg[i] += spd[i];
        if(leg[i] > tgt[i]) leg[i] = tgt[i];
      }
    }
  }

}

void pos_motor_set(){

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


void demo_move(){
	
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


// for (pos = 7500; pos > 6500; pos -= 2) {
//     ics_pos_write(1, pos);
//   }
//   delay(3000);
// for (pos = 7500; pos > 6500; pos -= 2) {
//     ics_pos_write(2, pos);
//   }

//   delay(3000);

// for (pos = 6500; pos < 7500; pos += 2) {
//     ics_pos_write(1, pos);
//   delay(3000);
//   }
// for (pos = 6500; pos < 8500; pos += 2) {
//     ics_pos_write(2, pos);
//   delay(3000);
//   }



}
