


void mp3_reset(){

  mySerial.write((byte)0x7E);   // start
  mySerial.write((byte)0xFF);   // 
  mySerial.write((byte)0x06);   // num
  mySerial.write((byte)0x0C);   // command
  mySerial.write((byte)0x00);   // res
  mySerial.write((byte)0x00);   // param 1
  mySerial.write((byte)0x00);   // param 2
  mySerial.write((byte)0xEF);   // end

  delay(1000);
}

void mp3_sdset(){

  mySerial.write((byte)0x7E);   // start
  mySerial.write((byte)0xFF);   // ver
  mySerial.write((byte)0x06);   // num
  mySerial.write((byte)0x09);   // command
  mySerial.write((byte)0x00);   // res
  mySerial.write((byte)0x00);   // param 1
  mySerial.write((byte)0x02);   // param 2
  mySerial.write((byte)0xEF);   // end

  delay(100);
}

void mp3_vol(byte vol){

  mySerial.write((byte)0x7E);   // start
  mySerial.write((byte)0xFF);   // ver
  mySerial.write((byte)0x06);   // num
  mySerial.write((byte)0x06);   // command
  mySerial.write((byte)0x00);   // res
  mySerial.write((byte)0x00);   // param 1
  mySerial.write((byte)vol);   // param 2
  mySerial.write((byte)0xEF);   // end

  delay(100);
}

void mp3_play(byte folder,byte track){

  mySerial.write((byte)0x7E);   // start
  mySerial.write((byte)0xFF);   // ver
  mySerial.write((byte)0x06);   // num
  mySerial.write((byte)0x0F);   // command
  mySerial.write((byte)0x00);   // res
  mySerial.write((byte)folder);   // param 1
  mySerial.write((byte)track);   // param 2
  mySerial.write((byte)0xEF);   // end

  delay(100);
}

void mp3_stop(){

  mySerial.write((byte)0x7E);   // start
  mySerial.write((byte)0xFF);   // ver
  mySerial.write((byte)0x06);   // num
  mySerial.write((byte)0x16);   // command
  mySerial.write((byte)0x00);   // res
  mySerial.write((byte)0x00);   // param 1
  mySerial.write((byte)0x00);   // param 2
  mySerial.write((byte)0xEF);   // end

  delay(100);
}







