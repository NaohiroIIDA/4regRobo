


void pos_init(){

	for (int i = 0; i < 8; ++i)
	{
		pos_leg[i] = leg_center;
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
  Serial1.write(0x80 + id);
  Serial1.write(ics_pos_h(pos));
  Serial1.write(ics_pos_l(pos));
  // delay(10);
}

void pos_speed_set(int id,int target,int speed){

	long pos;

	if(pos_leg[id] > target){

		while(pos_leg[id] > target)
		{
			pos_leg[id] -= speed;
			ics_pos_write(id, pos_leg[id]);
		}

	}else{
		while(pos_leg[id] < target)
		{
			pos_leg[id] += speed;
			ics_pos_write(id, pos_leg[id]);
		}
	}

}

void 

void before_work(){
	long pos;

	for (pos = 7500; pos > 5500; pos -= 2) 
	{
    ics_pos_write(1, pos);
    ics_pos_write(3, pos);
    ics_pos_write(5, pos);
    ics_pos_write(7, pos);
  }
  delay (1500);



  for (pos = 7500; pos > leg_bw24; pos -=1) 
	{
    ics_pos_write(2, pos);
    ics_pos_write(4, pos);
  }

  for (pos = 7500; pos > leg_bw24; pos -=1) 
	{
    ics_pos_write(2, pos);
    ics_pos_write(4, pos);
  }



}

void demo_move(){

	int pos;
	
  for (pos = 7500; pos < 9500; pos += 2) {

    ics_pos_write(1, pos);
    ics_pos_write(2, pos);
    ics_pos_write(3, pos);
    ics_pos_write(4, pos);
    ics_pos_write(5, pos);
    ics_pos_write(6, pos);
    ics_pos_write(7, pos);
    ics_pos_write(8, pos);
  }

  for (pos = 9500; pos > 7500; pos -= 2) {

    ics_pos_write(1, pos);
    ics_pos_write(2, pos);
    ics_pos_write(3, pos);
    ics_pos_write(4, pos);
    ics_pos_write(5, pos);
    ics_pos_write(6, pos);
    ics_pos_write(7, pos);
    ics_pos_write(8, pos);
  }





  for (pos = 7500; pos > 5500; pos -= 2) {

    ics_pos_write(1, pos);
    ics_pos_write(2, pos);
    ics_pos_write(4, pos);
    ics_pos_write(3, pos);
    ics_pos_write(5, pos);
    ics_pos_write(6, pos);
    ics_pos_write(7, pos);
    ics_pos_write(8, pos);

  }

  


  for (pos = 5500; pos < 7500; pos += 2) {

    ics_pos_write(1, pos);
    ics_pos_write(2, pos);
    ics_pos_write(3, pos);
    ics_pos_write(4, pos);
    ics_pos_write(5, pos);
    ics_pos_write(6, pos);
    ics_pos_write(7, pos);
    ics_pos_write(8, pos);
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