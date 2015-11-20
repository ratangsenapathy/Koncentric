

struct block
{
  int ring;
  float theta1;
  float theta2;

};

struct level
{
      int count;
      struct block blocks[100];
};


