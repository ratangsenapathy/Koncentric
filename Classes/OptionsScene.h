#ifndef __OPTIONS_SCENE_H__
#define __OPTIONS_SCENE_H__

#include "cocos2d.h"
#include <ui/UICheckBox.h>

class OptionsScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(OptionsScene);
    
private:
    void goToMainMenuScene(cocos2d::Ref *sender);
    void checkBoxSelectEvent(Ref* pSender,cocos2d::ui::CheckBox::EventType type);
};

#endif // __OPTIONS_SCENE_H__
