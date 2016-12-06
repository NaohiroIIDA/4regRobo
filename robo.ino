


void pos_init(){

	for (int i = 0; i < 9; ++i)
	{
		pos_leg[i] = leg_center;
		pos_tgt[i] = leg_center;

	}
}




byte ics_pos_h(unsigned int data) {

  int exem = (data >> 7) & 0x7F;
  byte exem_b = (byte)exem;
  return exem_b;

}

byte ics_pos_l(unsigned int data) {

  int exem = data & 0x7F;
  byte exem_b = (byte)exem;
  return exem_b;
}

void ics_pos_write(unsigned int id, unsigned int data) {
  Serial1.write(0x80 + id);
  Serial1.write(ics_pos_h(pos));
  Serial1.write(ics_pos_l(pos));
  delay(2);
}

void loop_servo(){
	int i;

	for (int i = 1; i < 9; ++i)
	{
		if(pos_leg[i] > pos_tgt[i]){

			pos_leg[i] -= speed[i];
			if(pos_leg[i] < pos_tgt[i]) pos_leg[i] = pos_tgt[i];

		}else{

			pos_leg[i] += speed[i];
			if(pos_leg[i] > pos_tgt[i]) pos_leg[i] = pos_tgt[i];

		}
	}

}

void set_pos(){
	ics_pos_write(1, pos_leg[1]);
	ics_pos_write(2, pos_leg[2]);
	ics_pos_write(3, pos_leg[3]);
	ics_pos_write(4, pos_leg[4]);
	ics_pos_write(5, pos_leg[5]);
	ics_pos_write(6, pos_leg[6]);
	ics_pos_write(7, pos_leg[7]);
	ics_pos_write(8, pos_leg[8]);
	
}


void demo_work(){
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

void demo_pos_set(unsigned int pos){

	pos_leg[1] = pos;
  	pos_leg[2] = pos;
  	pos_leg[3] = pos;
  	pos_leg[4] = pos;
  	pos_leg[5] = pos;
  	pos_leg[6] = pos;
  	pos_leg[7] = pos;
  	pos_leg[8] = pos;
}







void demo_move(){

	unsigned int pos;

  for (pos = 7500; pos < 9500; pos += 2) {

  	demo_pos_set(pos);
	set_pos();
  }

  for (pos = 9500; pos > 7500; pos -= 2) {

  	demo_pos_set(pos);
	 set_pos();
  }

  for (pos = 7500; pos > 5500; pos -= 2) {
  	demo_pos_set(pos);
	 set_pos();
  }

  for (pos = 5500; pos < 7500; pos += 2) {
  	demo_pos_set(pos);
	 set_pos();
  }


}