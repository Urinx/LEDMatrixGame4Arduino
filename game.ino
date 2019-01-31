#include "led_matrix.h"
#include "joystick.h"
#include "pitches.h"
#define RANDOM_PIN A5
#define BUZZER 11

unsigned char cur_map[8][8] = {
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
};

struct Position{
  char x;
  char y;
} pos = {0, 0};
struct Position garbage;
bool isclean = true;
int CanonD_melody[] = {N_A6, N_FS6, N_G6, N_A6, N_FS6, N_G6, N_A6, N_A5, N_B5, N_CS6, N_D6, N_E6, N_FS6, N_G6, N_FS6, N_D6, N_E6, N_FS6, N_FS5, N_G5, N_A5, N_B5, N_A5, N_G5, N_A5, N_FS5, N_G5, N_A5, N_G5, N_B5, N_A5, N_G5, N_FS5, N_E5, N_FS5, N_E5, N_D5, N_E5, N_FS5, N_G5, N_A5, N_B5, N_G5, N_B5, N_A5, N_B5, N_CS6, N_D6, N_A5, N_B5, N_CS6, N_D6, N_E6, N_FS6, N_G6, N_A6};
int CanonD_duration[] = {8, 16, 16, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 16, 16, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 16, 16, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 16, 16, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16};
int count = 0;
int gar_num = 0;

void play_melody(){
  for(int i=0;i<56;i++){
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 2500 / CanonD_duration[i];
    tone(BUZZER, CanonD_melody[i], noteDuration);
  
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
  }
}

void play_bgm0(){
  count++;
  if(count%5==0){
    tone(BUZZER, N_B5, 20);
    count = 0;
  }
}

void play_bgm1(){
  for(int i=0;i<10;i++){
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 2500 / CanonD_duration[i];
    tone(BUZZER, CanonD_melody[i], noteDuration);
  
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
  }
}

void setup() {
  pinMode(SHCP_PIN, OUTPUT); // clock 
  pinMode(STCP_PIN, OUTPUT); // lock
  pinMode(DS_PIN, OUTPUT);

  pinMode(LED_PIN_9, OUTPUT);
  pinMode(LED_PIN_10, OUTPUT);
  pinMode(LED_PIN_11, OUTPUT);
  pinMode(LED_PIN_12, OUTPUT);
  pinMode(LED_PIN_13, OUTPUT);
  pinMode(LED_PIN_14, OUTPUT);
  pinMode(LED_PIN_15, OUTPUT);
  pinMode(LED_PIN_16, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);
  randomSeed(analogRead(RANDOM_PIN));
  
  clear_led();
}

void loop() {
  if(isclean){
    char x= random(0,8);
    char y= random(0,8);
    while(pos.x == x || pos.y == y){
      x = random(0,8);
      y = random(0,8);
    }
    garbage = {x, y};
    isclean = false;
  }

  if(gar_num == 5){
    test_led_matrix();
    for(;gar_num>0;gar_num--){
      play_melody();
    }
  }
  
  cur_map[pos.x][pos.y] = 1;
  cur_map[garbage.x][garbage.y] = 1;
  for(int i=0;i<120;i++){
    display_arr(cur_map);
  }

  if(pos.x == garbage.x && pos.y == garbage.y){
    isclean = true;
    gar_num++;

    for(int i=0;i<5;i++){
      display_arr(cur_map);
      
      tone(BUZZER, N_B5, 100);
      delay(80);
    }
    
  }
  cur_map[pos.x][pos.y] = 0;
  struct Direction dir = get_direction();

  pos.x -= dir.dx;
  pos.y += dir.dy;
  if(pos.x < 0){pos.x = 0;}
  else if(pos.x > 7){pos.x = 7;}
  if(pos.y < 0){pos.y = 0;}
  else if(pos.y > 7){pos.y = 7;}

  play_bgm0();
}
