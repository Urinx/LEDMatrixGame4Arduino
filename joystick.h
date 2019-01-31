#define STICK_X A1
#define STICK_Y A0

struct Direction{
  int dx=0;
  int dy=0;
};

struct Direction get_direction();
