#include <arduino.h>
#include "led_matrix.h"

/*
  - 16 15 14 13 12 11 10 9 -
  [ 5  6  7  8  9  10 11 12 ]
  [ x  x  x  x  x  x  x  x  ]
  - 1  2  3  4  5  6  7  8 -
 
  H 13  3  4 10  6 11 15 16
  L  9 14  8 12  1  7  2  5
*/
unsigned char led_high[8] = {13,3,4,10,6,11,15,16}; //点阵屏正极引脚
unsigned char led_gnds[8] = {9,14,8,12,1,7,2,5};    //点阵屏负极引脚
unsigned char led_9_16[8] = {LED_PIN_9,LED_PIN_10,LED_PIN_11,LED_PIN_12,
LED_PIN_13,LED_PIN_14,LED_PIN_15,LED_PIN_16};  //9-16引脚对应的IO口

void write_led_pin(unsigned char d[16]){
  byte v = 0;
  for(int i=0;i<8;i++){
    v = v << 1;
    v += d[i];
  }
  
  // 1-8 pin
  digitalWrite(STCP_PIN, LOW);
  shiftOut(DS_PIN, SHCP_PIN, LSBFIRST, v);
  digitalWrite(STCP_PIN, HIGH);
  
  // 9-16 pin
  for(int i=8;i<16;i++){
    digitalWrite(led_9_16[i-8], d[i]);
  }
}

void clear_led(){
  unsigned char d[16] = {1,1,0,0,1,0,1,1,1,0,0,1,0,1,0,0}; //点阵屏熄灭状态
  write_led_pin(d);
}

void plot_led_dot(char raw, char col){
  unsigned char d[16] = {1,1,0,0,1,0,1,1,1,0,0,1,0,1,0,0};
  d[led_high[col]-1] = 1;
  d[led_gnds[raw]-1] = 0;

  write_led_pin(d);
}

void test_led_matrix(){
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      plot_led_dot(i,j);
      delay(30);
    }
  }
}

void display_arr(unsigned char dat[8][8]){
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      if(dat[i][j]==1){
        plot_led_dot(i,j);
        clear_led();
      }
    }
  }
}
