#ifndef __BEST_TIME_SCENE_H__
#define __BEST_TIME_SCENE_H__
#include "ui/CocosGUI.h"
#include "cocos2d.h"
//#include <ui/UICheckBox.h>

class BestTimeScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    int currentPackNumber;
    cocos2d::ui::Layout* currentLayout;
    cocos2d::ui::Layout* newLayout;
    float touchBeganX;
    float touchBeganY;
    float touchEndedX;
    float touchEndedY;
    int numberOfPacks;
    int currentPackNo;
    bool displayBestTimeOn;
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(BestTimeScene);
    
private:
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event* event);
    void goToMainMenuScene(cocos2d::Ref *sender);
    //void checkBoxSelectEvent(Ref* pSender,cocos2d::ui::CheckBox::EventType type);
    std::string getTimeText(int minCount,int secCount);
    cocos2d::ui::Layout* generateLevelPackLayer(int packNo,int type);
    void generatePackLevels(Ref *pSender);
    void displayBestTime();
    void swipeFinished();
    
};

#endif // __BEST_TIME_SCENE_H__
