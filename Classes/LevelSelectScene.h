#ifndef __LEVEL_SELECT_SCENE_H__
#define __LEVEL_SELECT_SCENE_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class LevelSelectScene : public cocos2d::Layer
{
public:
    int currentPackNumber;
    cocos2d::ui::Layout* currentLayout;
    cocos2d::ui::Layout* newLayout;
    float touchBeganX;
    float touchBeganY;
    float touchEndedX;
    float touchEndedY;
    int numberOfPacks;
   
    bool displayLevelsOn;
    
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
    void loadScene();
    void generatePackLevels(Ref *pSender);
    void displayPackLevels();
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event* event);
    cocos2d::ui::Layout* generateLevelPackLayer(int packNo,int type);
    void swipeFinished();
};

#endif // __LEVEL_SELECT_SCENE_H__
