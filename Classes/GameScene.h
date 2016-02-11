#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "Definitions.h"
#include "rapidjson/document.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
//#include "CCVector.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    struct obstacle
    {
        float speed;
        float theta1;
        float theta2;
        int ringNum;
        char *color;
    };
    
    virtual bool init();
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    cocos2d::DrawNode* goal;
    cocos2d::DrawNode* pathNode;
    //cocos2d::DrawNode* ball;
    cocos2d::ParticleSystemQuad* ball;
    cocos2d::Node* rotationPoint;
    cocos2d::Node* clockwiseObstacleRotationPoint;
    cocos2d::Node* antiClockwiseObstacleRotationPoint;
    cocos2d::DrawNode* blocks;
    cocos2d::ui::Layout* layout;
    struct obstacle *obstacles;
    int noOfLevels;
    int r=0;
    int levelNo=0;
    int controlable=0;      // flag to check if user can controll the ball or not
    int rMax=0;             // max radius of circle
    int *ringSpin;
    int secondCount=0;    // second han value in the timer
    int minuteCount=0;   //minute hand clock in the timer
    float obstacleSpeed=0;
    cocos2d::Label *timer;
    bool timerRunning;
    int rIncrement;
    float distance;
    float theta=0;
    float ballTime;
    float ballRadius;
    float ballInitTheta;
    float spinSwitchTime;
    int exitButtonWidth;
    int exitButtonHeight;
    int ballDirection;
    int obstacleCount;
    int levelMinUserDefault;
    int levelSecUserDefault;
    cocos2d::Color4F ballColor;
    cocos2d::Color4F ringColor;
    cocos2d::Color4F goalColor;
    rapidjson::Document document;
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
    void loadScene();
    void removeResources();
    cocos2d::Color4F convertHexToRBG(std::string hexString);
    void generateJSON(std::string jsonFile);
    void parseJSON();
    void saveScores();
    void changeObstacleDirection(float dt);
    std::string getTimeText(int minCount,int secCount);
    void displayLevelCompleteLayer();
    void goToNextLevel(cocos2d::Ref *pSender);
    ~GameScene();
    
    
};

#endif // __HELLOWORLD_SCENE_H__
