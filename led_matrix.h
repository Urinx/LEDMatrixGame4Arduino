#define SHCP_PIN    4
#define STCP_PIN    3
#define DS_PIN      2
#define LED_PIN_9   13
#define LED_PIN_10  12
#define LED_PIN_11  10
#define LED_PIN_12  9
#define LED_PIN_13  8
#define LED_PIN_14  7
#define LED_PIN_15  6
#define LED_PIN_16  5

/*
  - 16 15 14 13 12 11 10 9 -
  [ 5  6  7  8  9  10 11 12 ]
  [ x  x  x  x  x  x  x  x  ]
  - 1  2  3  4  5  6  7  8 -
*/

void test_led_matrix();
void clear_led();
void plot_led_dot(char raw, char col);
void display_arr(unsigned char dat[8][8]);
