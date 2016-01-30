#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "Definitions.h"

#include "cocos2d.h"
//#include "CCVector.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(int level);
    virtual bool init();
    cocos2d::Size visibleSize;
    cocos2d::DrawNode* goal;
    cocos2d::DrawNode* pathNode;
    cocos2d::DrawNode* snake[SNAKE_LENGTH];
    cocos2d::Node* rotationPoint;
    cocos2d::Node* obstacleRotationPoint;
    cocos2d::DrawNode* blocks;
    float distance;
    int exitButtonWidth;
    int exitButtonHeight;
//    cocos2d::Size visibleSize;
//    cocos2d::Vec2 origin;
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
   #if COMPILE_FOR_MOBILE == 1
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event* event);
  // #else
   // void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
   #endif
 
    void update(float dt);
    void actionComplete();
    void updateClock(float dt);
    
    
};

#endif // __HELLOWORLD_SCENE_H__
