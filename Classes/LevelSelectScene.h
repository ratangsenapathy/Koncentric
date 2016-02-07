#ifndef __LEVEL_SELECT_SCENE_H__
#define __LEVEL_SELECT_SCENE_H__
#include "cocos2d.h"

class LevelSelectScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    
    
    CREATE_FUNC(LevelSelectScene);
    void Play(Ref *pSender);
    void goBack(Ref *pSender);
    
private:
    void goToGameScene(cocos2d::Ref *sender);
};

#endif // __LEVEL_SELECT_SCENE_H__
