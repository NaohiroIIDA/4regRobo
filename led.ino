int ledpos(int pos)
{
  int ret = pos;

  if (pos < 0 ) ret = LED_NUM + pos +1;
  if (pos > LED_NUM ) ret = pos % LED_NUM ;
  
  return ret;
}


void eye(byte R, byte G, byte B, long i) {

  int pos;

    led_r[ledpos(i-3)]  = char(R * 0.0);  led_g[ledpos(i-3)]  = char(G * 0.0);  led_b[ledpos(i-3)]  = char(B * 0.0);
    led_r[ledpos(i-2)]  = char(R * 0.1);  led_g[ledpos(i-2)]  = char(G * 0.1);  led_b[ledpos(i-2)]  = char(B * 0.1);
    led_r[ledpos(i-1)]  = char(R * 0.2);  led_g[ledpos(i-1)]  = char(G * 0.2);  led_b[ledpos(i-1)]  = char(B * 0.2);
    led_r[ledpos(i-0)]  = char(R * 1.0);  led_g[ledpos(i-0)]  = char(G * 1.0);  led_b[ledpos(i-0)]  = char(B * 1.0);
    led_r[ledpos(i+1)]  = char(R * 0.2);  led_g[ledpos(i+1)]  = char(G * 0.2);  led_b[ledpos(i+1)]  = char(B * 0.2);
    led_r[ledpos(i+2)]  = char(R * 0.1);  led_g[ledpos(i+2)]  = char(G * 0.1);  led_b[ledpos(i+2)]  = char(B * 0.1);
    led_r[ledpos(i+3)]  = char(R * 0.0);  led_g[ledpos(i+3)]  = char(G * 0.0);  led_b[ledpos(i+3)]  = char(B * 0.0);
  

  write_vmem();
}


void all_clear()
{
  for (long i = 0; i < LED_NUM; i++) {
    led_r[i] = 0;led_g[i] = 0; led_b[i] = 0;
    strip.setPixelColor(i, strip.Color(led_r[i], led_g[i], led_b[i]));
  }
  strip.show();
  delay(10);
}

void all_up()
{
  for (long i = 0; i < LED_NUM; i++) {
    led_r[i] += 1;led_g[i] +=1; led_b[i] += 1;

    if(led_r[i] >255) led_r[i] = 255;
    if(led_g[i] >255) led_g[i] = 255;
    if(led_b[i] >255) led_b[i] = 255;

    strip.setPixelColor(i, strip.Color(led_r[i], led_g[i], led_b[i]));
  }
  strip.show();
  delay(10);
}

void all_down()
{
  for (long i = 0; i < LED_NUM; i++) {
    led_r[i] -= 1;led_g[i] -=1; led_b[i] -= 1;

    if(led_r[i] <0) led_r[i] = 0;
    if(led_g[i] <0) led_g[i] = 0;
    if(led_b[i] <0) led_b[i] = 0;

    strip.setPixelColor(i, strip.Color(led_r[i], led_g[i], led_b[i]));
  }
  strip.show();
  delay(10);
}



void all_up_green()
{
  for (long i = 0; i < LED_NUM; i++) {
    led_r[i] -= 1;led_g[i] +=1; led_b[i] -= 1;

    if(led_r[i] >255) led_r[i] = 255;
    if(led_g[i] >255) led_g[i] = 255;
    if(led_b[i] >255) led_b[i] = 255;
    if(led_r[i] <0) led_r[i] = 0;
    if(led_g[i] <0) led_g[i] = 0;
    if(led_b[i] <0) led_b[i] = 0;

    strip.setPixelColor(i, strip.Color(led_r[i], led_g[i], led_b[i]));
  }
  strip.show();
  delay(10);
}

void all_up_red()
{
  for (long i = 0; i < LED_NUM; i++) {
    led_r[i] += 1;led_g[i] -= 1; led_b[i] -= 1 ;

    if(led_r[i] >255) led_r[i] = 255;
    if(led_g[i] >255) led_g[i] = 255;
    if(led_b[i] >255) led_b[i] = 255;
    if(led_r[i] <0) led_r[i] = 0;
    if(led_g[i] <0) led_g[i] = 0;
    if(led_b[i] <0) led_b[i] = 0;

    strip.setPixelColor(i, strip.Color(led_r[i], led_g[i], led_b[i]));
  }
  strip.show();
  delay(10);
}

void all_up_blue()
{
  for (long i = 0; i < LED_NUM; i++) {
    led_r[i] -= 1;led_g[i] -= 1; led_b[i] += 1;

    if(led_r[i] >255) led_r[i] = 255;
    if(led_g[i] >255) led_g[i] = 255;
    if(led_b[i] >255) led_b[i] = 255;
    if(led_r[i] <0) led_r[i] = 0;
    if(led_g[i] <0) led_g[i] = 0;
    if(led_b[i] <0) led_b[i] = 0;

    strip.setPixelColor(i, strip.Color(led_r[i], led_g[i], led_b[i]));
  }
  strip.show();
  delay(10);
}



void write_vmem() {
  for (long i = 0; i < LED_NUM; i++) {
    strip.setPixelColor(i, strip.Color(led_r[i], led_g[i], led_b[i]));
  }
  strip.show();
  delay(10);
}
