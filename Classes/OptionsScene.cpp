#include "OptionsScene.h"
#include "Definitions.h"
#include <UICheckBox.h>
USING_NS_CC;

using namespace cocos2d::ui;

Scene* OptionsScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = OptionsScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool OptionsScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto optionsTitle = Label::createWithTTF("Options", "fonts/Marker Felt.ttf", 80);
    optionsTitle->setPosition(Point(visibleSize.width/2+origin.x,visibleSize.height*0.8+origin.y));
    optionsTitle->setColor(Color3B(100,25, 200));
    //this->setKeypadEnabled(true);
    
    auto backItem = MenuItemFont::create("Back",CC_CALLBACK_1(OptionsScene::goToMainMenuScene,this));
    //backItem->setColor(cocos2d::Color3B::BLUE);
    backItem->setScale(1);
    backItem->setPosition(Point(visibleSize.width+origin.x-backItem->getContentSize().width/2, visibleSize.height+origin.y-backItem->getContentSize().height/2));
    
    backItem->setTag(0);
    
    auto music = CheckBox::create("check_box_normal.png",
                                     "check_box_normal_press.png",
                                     "check_box_active.png",
                                     "check_box_normal_disable.png",
                                     "check_box_active_disable.png");
 
    music->setPosition(Vec2(music->getContentSize().width/2+origin.x,visibleSize.height*0.8-optionsTitle->getContentSize().height*1.5+origin.y));
    
    auto menu = Menu::create(backItem,NULL);
    menu->setPosition(Point::ZERO);
    
    
    this->addChild(optionsTitle,1);
    this->addChild(menu,1);
    this->addChild(music,2);
    return true;
}

void OptionsScene::goToMainMenuScene(cocos2d::Ref *sender){
    
    this->removeAllChildrenWithCleanup(true);
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
   

    Director::getInstance()->popScene();
}

