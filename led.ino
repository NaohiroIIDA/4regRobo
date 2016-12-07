int ledpos(int pos)
{
  int ret = pos;

  if (pos < 0 ) ret = LED_NUM + pos + 1;
  if (pos > LED_NUM ) ret = pos % LED_NUM ;

  return ret;
}


void eye(byte R, byte G, byte B, long i) {

  int pos;

  led_r[ledpos(i - 3)]  = char(R * 0.0);  led_g[ledpos(i - 3)]  = char(G * 0.0);  led_b[ledpos(i - 3)]  = char(B * 0.0);
  led_r[ledpos(i - 2)]  = char(R * 0.1);  led_g[ledpos(i - 2)]  = char(G * 0.1);  led_b[ledpos(i - 2)]  = char(B * 0.1);
  led_r[ledpos(i - 1)]  = char(R * 0.2);  led_g[ledpos(i - 1)]  = char(G * 0.2);  led_b[ledpos(i - 1)]  = char(B * 0.2);
  led_r[ledpos(i - 0)]  = char(R * 1.0);  led_g[ledpos(i - 0)]  = char(G * 1.0);  led_b[ledpos(i - 0)]  = char(B * 1.0);
  led_r[ledpos(i + 1)]  = char(R * 0.2);  led_g[ledpos(i + 1)]  = char(G * 0.2);  led_b[ledpos(i + 1)]  = char(B * 0.2);
  led_r[ledpos(i + 2)]  = char(R * 0.1);  led_g[ledpos(i + 2)]  = char(G * 0.1);  led_b[ledpos(i + 2)]  = char(B * 0.1);
  led_r[ledpos(i + 3)]  = char(R * 0.0);  led_g[ledpos(i + 3)]  = char(G * 0.0);  led_b[ledpos(i + 3)]  = char(B * 0.0);


  write_vmem();
}


void all_clear()
{
  for (long i = 0; i < LED_NUM; i++) {
    led_r[i] = 0; led_g[i] = 0; led_b[i] = 0;
    strip.setPixelColor(i, strip.Color(led_r[i], led_g[i], led_b[i]));
  }
  strip.show();
  delay(10);
}

int led_blight(int goal, int par) {

  int ret = goal * par / 256;
  return ret;
}


void led_loop_set(byte R, byte G, byte B, int par)
{
  for (long i = 0; i < LED_NUM; i++) {

    led_r[i] = led_blight(R, par);
    led_g[i] = led_blight(G, par);
    led_b[i] = led_blight(B, par);

    if (led_r[i] > 255) led_r[i] = 255;
    if (led_g[i] > 255) led_g[i] = 255;
    if (led_b[i] > 255) led_b[i] = 255;
    if (led_r[i] < 0) led_r[i] = 0;
    if (led_g[i] < 0) led_g[i] = 0;
    if (led_b[i] < 0) led_b[i] = 0;

    strip.setPixelColor(i, strip.Color(led_r[i], led_g[i], led_b[i]));
  }
  strip.show();
}



void write_vmem() {
  for (long i = 0; i < LED_NUM; i++) {
    strip.setPixelColor(i, strip.Color(led_r[i], led_g[i], led_b[i]));
  }
  strip.show();
  delay(10);
}


void master_led_loop() {

  if (led_mode == 0) {                            // led looping (right)
    eye(250, 250, 250, led_pos);
    led_pos++;
    if (led_pos > LED_NUM) {
      led_pos = 0;
    }
  }

  if (led_mode == 1) {                            // led looping (left)                        
    eye(250, 250, 250, led_pos);
    led_pos--;
    if (led_pos < 0) {
      led_pos = LED_NUM;
    }
  }

  if (led_mode == 2) {                            // Yellow led (up)
    led_loop_set(255, 70, 0, led_light);
    led_light++;
    if (led_light > 100) {
      led_light = 100;
      led_mode = 3;
    }

  }
  if (led_mode == 3) {                            // Yellow led (down)
    led_loop_set(255, 70, 0, led_light);
    led_light--;
    if (led_light < 0) {
      led_light = 0;
      led_mode = 2;
    }
  }

    if (led_mode == 4) {                            // blue led (up)
    led_loop_set(0, 0, 255, led_light);
    led_light++;
    if (led_light > 100) {
      led_light = 100;
    }

  }

    if (led_mode == 5) {                            // white led (up)
    led_loop_set(255, 255, 255, led_light);
    led_light+=5;
    if (led_light > 100) {
      led_light = 100;
      led_mode = 6;
    }

  }
  if (led_mode == 6) {                            // white led (down)
    led_loop_set(255, 255, 255, led_light);
    led_light-=5;
    if (led_light < 0) {
      led_light = 0;
      led_mode = 5;
    }
  }
}
