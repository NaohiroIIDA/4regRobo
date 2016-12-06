void get_light()
{
  AD_IN[0] = analogRead(A0);
  AD_IN[1] = analogRead(A1);
  AD_IN[2] = analogRead(A8);
  AD_IN[3] = analogRead(A9);
  AD_IN[4] = analogRead(A7);

}

int get_light_dir()
{
  int dir = 0;
  if (( AD_IN[0] > AD_IN[1]) && ( AD_IN[0] > AD_IN[2]) && ( AD_IN[0] > AD_IN[3])) dir = 1;
  if (( AD_IN[1] > AD_IN[0]) && ( AD_IN[1] > AD_IN[2]) && ( AD_IN[1] > AD_IN[3])) dir = 2;
  if (( AD_IN[2] > AD_IN[0]) && ( AD_IN[2] > AD_IN[1]) && ( AD_IN[2] > AD_IN[3])) dir = 3;
  if (( AD_IN[3] > AD_IN[0]) && ( AD_IN[3] > AD_IN[1]) && ( AD_IN[3] > AD_IN[2])) dir = 4;

  return dir;

}

int get_light_power()
{
  int power = 0;
  if (( AD_IN[0] > AD_IN[1]) && ( AD_IN[0] > AD_IN[2]) && ( AD_IN[0] > AD_IN[3])) power = AD_IN[0];
  if (( AD_IN[1] > AD_IN[0]) && ( AD_IN[1] > AD_IN[2]) && ( AD_IN[1] > AD_IN[3])) power = AD_IN[1];
  if (( AD_IN[2] > AD_IN[0]) && ( AD_IN[2] > AD_IN[1]) && ( AD_IN[2] > AD_IN[3])) power = AD_IN[2];
  if (( AD_IN[3] > AD_IN[0]) && ( AD_IN[3] > AD_IN[1]) && ( AD_IN[3] > AD_IN[2])) power = AD_IN[3];

  return power;

}

int get_light_power_upside()
{
  int power = AD_IN[4];
  
  return power;

}


void debug_sensor(){
  Serial.print(AD_IN[0]);
  Serial.print("\t" );
  Serial.print(AD_IN[1]);
  Serial.print("\t" );
  Serial.print(AD_IN[2]);
  Serial.print("\t" );
  Serial.print(AD_IN[3]);
  Serial.print("\t" );
  Serial.print(AD_IN[4]);
  Serial.println("\t" );
}
