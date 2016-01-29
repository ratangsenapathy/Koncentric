#ifndef  __LEVELS_H__
#define  __LEVELS_H__
//#define LEVEL_COUNT 3


struct block
{
  int ring;
  float theta1;
  float theta2;

};

struct level
{
      int ringCount;
      int obstacleCount;
      float speed;
      struct block blocks[100];
};


struct level levels[LEVEL_COUNT]={
    
    {6,4,4,
        {
            {2,M_PI/2,M_PI/2+M_PI/4},
            {4,0,M_PI/4},
            {3,M_PI,M_PI+M_PI/4},
            {3,3*M_PI/2,3*M_PI/2+M_PI/4}
        }
    }
    
    ,
    
    {6,5,4,
        {
            {2,M_PI/2,M_PI/2+M_PI/4},
            {3,3*M_PI/2,3*M_PI/2+M_PI/4},
            {1,M_PI/3,M_PI/3+M_PI/4},
            {3,1.5*M_PI,1.5*M_PI+M_PI/4},
            {2,1.8*M_PI,1.8*M_PI+M_PI/4}
        }
    }
    
    ,
    
    {7,8,4,
        {
            {3,1.5*M_PI,1.5*M_PI+M_PI/4},
            {2,1.8*M_PI,1.8*M_PI+M_PI/4},
            {3,M_PI,M_PI+M_PI/4},
            {4,0,M_PI/4},
            {3,M_PI,M_PI+M_PI/4},
            {3,3*M_PI/2,3*M_PI/2+M_PI/4},
            {5,3*M_PI/2,3*M_PI/2+M_PI/4},
            {5,3*M_PI/2+M_PI/5,3*M_PI/2+M_PI/5+M_PI/4}
        }
        
    }
    
    ,
    
    {6,7,4,
        {
            {2,M_PI/2,M_PI/2+M_PI/4},
            {4,0,M_PI/4},//
            {1,M_PI/3,M_PI/3+M_PI/4},
            {1,M_PI/3+M_PI*3/4,M_PI/3+M_PI*3/4+M_PI/4},
            {3,1.5*M_PI,1.5*M_PI+M_PI/4},//
            {2,1.8*M_PI,1.8*M_PI+M_PI/4},//
            {3,M_PI,M_PI+M_PI/4}//
        }
    }
    
    ,
    
    {7,12,4,
        {
            {3,1.5*M_PI,1.5*M_PI+M_PI/4},
            {2,1.8*M_PI,1.8*M_PI+M_PI/4},
            
            {4,0,M_PI/4},
            {3,M_PI,M_PI+M_PI/4},
            {3,3*M_PI/2,3*M_PI/2+M_PI/4},
            {5,M_PI/2,M_PI/2+M_PI/4},
            {5,M_PI/2+M_PI/5,M_PI/2+M_PI/5+M_PI/4},
            {2,M_PI/2,M_PI/2+M_PI/4},
            {1,M_PI/3,M_PI/3+M_PI/4},
            {1,M_PI/3+M_PI*3/4,M_PI/3+M_PI*3/4+M_PI/4},
            {5,3*M_PI/2,3*M_PI/2+M_PI/4},
            {1,M_PI/2+M_PI/5,M_PI/2+M_PI/5+M_PI/4}
        }
        
    }
    
    ,
    
    {7,8,6,
        {
            {4,3*M_PI/2 + M_PI/9,2*M_PI-M_PI/6},
            {5,M_PI+M_PI/5, M_PI + M_PI/2},
            {3,M_PI,M_PI+M_PI/4},
            {4,0,M_PI/4},
            {5,M_PI/2+M_PI/10,M_PI/2+M_PI/4+M_PI/10},
            {1,M_PI/3,M_PI/3+M_PI/4},
            {1,M_PI/3+M_PI*3/4,M_PI/3+M_PI*3/4+M_PI/4},
            {2,3*M_PI/2+M_PI/4,2*M_PI}
        }
        
    }
    
};

#endif


