#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "Definitions.h"

#include "cocos2d.h"
//#include "CCVector.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(int level);
    struct obstacle
    {
        float speed;
        float theta1;
        float theta2;
        int ringNum;
        char *color;
        cocos2d::Node* rotationPoint;
    };
    
    struct uniqueSpeedEntry
    {
        cocos2d::Node* rotPoint;
        float speed;
    };
    
    virtual bool init();
    
    cocos2d::Size visibleSize;
    cocos2d::DrawNode* goal;
    cocos2d::DrawNode* pathNode;
    cocos2d::DrawNode* snake[SNAKE_LENGTH];
    cocos2d::Node* rotationPoint;
    cocos2d::Node* obstacleRotationPoint;
  //  std::set<uniqueSpeedEntry> obstacleRotationPoints;
    cocos2d::DrawNode* blocks;
    cocos2d::Color4F ballColor;
    float distance;
    float ballRadius;
    float ballInitTheta;
    int exitButtonWidth;
    int exitButtonHeight;
    int secondCount;
    int minuteCount;
    int ballDirection;
    int obstacleCount;
   // unsigned int uniqueObstacleSpeedCount;
    struct obstacle *obstacles;
   // std::set<float> uniqueObstacleSpeeds;
    
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
    void parseJSON(std::string json);
    void setInitThetaForBall();
    cocos2d::Color4F convertHexToRBG(std::string hexString);
    
    
};

#endif // __HELLOWORLD_SCENE_H__
