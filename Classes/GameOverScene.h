#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
   
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);
    
    void GoToMainMenu(Ref *pSender);

   
};

#endif // __GAME_OVER_SCENE_H__
