#ifndef  _LEVELS_H_
#define  _LEVELS_H_
#define LEVEL_COUNT 3
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


struct level levels[LEVEL_COUNT]={
    {4,
        {
            {2,M_PI/2,M_PI/2+M_PI/4},
            {4,0,M_PI/4},
            {3,M_PI,M_PI+M_PI/4},
            {3,3*M_PI/2,3*M_PI/2+M_PI/4}
        }
    }
    ,
    {5,
        {
            {2,M_PI/2,M_PI/2+M_PI/4},
            {3,3*M_PI/2,3*M_PI/2+M_PI/4},
            {1,M_PI/3,M_PI/3+M_PI/4},
            {3,1.5*M_PI,1.5*M_PI+M_PI/4},
            {2,1.8*M_PI,1.8*M_PI+M_PI/4}
        }
    }
    ,
    {7,
        {
            {2,M_PI/2,M_PI/2+M_PI/4},
            {4,0,M_PI/4},
            {1,M_PI/3,M_PI/3+M_PI/4},
            {1,M_PI/3+M_PI*3/4,M_PI/3+M_PI*3/4+M_PI/4},
            {3,1.5*M_PI,1.5*M_PI+M_PI/4},
            {2,1.8*M_PI,1.8*M_PI+M_PI/4},
            {3,M_PI,M_PI+M_PI/4}
        }
    }
};


#endif

