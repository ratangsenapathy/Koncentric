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
      float obstacleSpeed;
      struct block blocks[100];
};


struct level levels[LEVEL_COUNT]={
    
    {6,4,8,10,
        {
            {2,90,135},
            {4,0,45},
            {3,180,225},
            {3,270,315}
        }
    }
    
    ,
    
    {6,5,8,10,
        {
            {2,90,135},
            {3,270,315},
            {1,60,105},
            {3,270,315},
            {2,324,369}
        }
    }
    
    ,
    
    {7,7,10,10,
        {
            {3,270,315},
            {2,324,369},
            {3,180,225},
            {4,0,45},
            {3,270,315},
            {5,270,315},
            {5,306,351}
        }
        
    }
    
    ,
    
    {6,7,10,10,
        {
            {2,90,135},
            {4,0,45},
            {1,60,105},
            {1,195,240},
            {3,270,315},
            {2,324,369},
            {3,180,225}
        }
    }
    
    ,
    
    {7,11,12,10,
        {
            
            {2,324,369},
            
            {4,0,45},
            {3,180,225},
            {3,270,315},
            {5,90,135},
            {5,126,171},
            {2,90,135},
            {1,60,105},
            {1,195,240},
            {5,270,315},
            {1,126,171}
        }
        
    }
    
    ,
    
    {7,8,12,10,
        {
            {4,300,330},
            {5,216, 270},
            {3,180,225},
            {4,0,90},
            {5,108,153},
            {1,60,105},
            {1,195,240},
            {2,315,360}
        }
        
    }
    
};

#endif


