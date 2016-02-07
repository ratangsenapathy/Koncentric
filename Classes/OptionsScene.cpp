#include "OptionsScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"

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
    optionsTitle->setPosition(Point(visibleSize.width/2+origin.x,visibleSize.height*0.9+origin.y));
    optionsTitle->setColor(Color3B(100,25, 200));
    //this->setKeypadEnabled(true);
    
    auto backItem = MenuItemFont::create("Back",CC_CALLBACK_1(OptionsScene::goToMainMenuScene,this));
    //backItem->setColor(cocos2d::Color3B::BLUE);
    backItem->setScale(1);
    backItem->setPosition(Point(visibleSize.width+origin.x-backItem->getContentSize().width/2, visibleSize.height+origin.y-backItem->getContentSize().height/2));
    
    backItem->setTag(0);
    
    auto musicCheck = CheckBox::create("check_box_normal.png",
                                     "check_box_normal_press.png",
                                     "check_box_active.png",
                                     "check_box_normal_disable.png",
                                     "check_box_active_disable.png");
 
    musicCheck->setPosition(Vec2(visibleSize.width/6+musicCheck->getContentSize().width/2+origin.x,
                            visibleSize.height*0.9-optionsTitle->getContentSize().height*1.5+origin.y));
    musicCheck->addEventListener(CC_CALLBACK_2(OptionsScene::checkBoxSelectEvent,this));
    musicCheck->setTag(0);
    
    auto musicLabel = Label::createWithTTF(" Music", "fonts/Marker Felt.ttf",musicCheck->getContentSize().height);
    musicLabel->setPosition(Vec2(visibleSize.width/6+musicCheck->getContentSize().width+musicLabel->getContentSize().width/2+origin.x,
                                 visibleSize.height*0.9-optionsTitle->getContentSize().height*1.5+origin.y));
    
    
    auto soundsCheck = CheckBox::create("check_box_normal.png",
                                       "check_box_normal_press.png",
                                       "check_box_active.png",
                                       "check_box_normal_disable.png",
                                       "check_box_active_disable.png");
    
    soundsCheck->setPosition(Vec2(visibleSize.width/6+soundsCheck->getContentSize().width/2+origin.x,
                                 visibleSize.height*0.9-optionsTitle->getContentSize().height*1.5-musicCheck->getContentSize().height*2+origin.y));
    
    auto soundsLabel = Label::createWithTTF(" Sounds", "fonts/Marker Felt.ttf",soundsCheck->getContentSize().height);
    soundsLabel->setPosition(Vec2(visibleSize.width/6+soundsCheck->getContentSize().width+soundsLabel->getContentSize().width/2+origin.x,
                                 visibleSize.height*0.9-optionsTitle->getContentSize().height*1.5-musicCheck->getContentSize().height*2+origin.y));
    
    soundsCheck->setTag(1);
    
    auto menu = Menu::create(backItem,NULL);
    menu->setPosition(Point::ZERO);
    
    
    bool musicOn = UserDefault::getInstance()->getBoolForKey("MusicOn",true);
    bool soundsOn = UserDefault::getInstance()->getBoolForKey("SoundsOn", true);
    
        //musicCheck->setSelectedState(musicOn);
    soundsCheck->addEventListener(CC_CALLBACK_2(OptionsScene::checkBoxSelectEvent,this));
    musicCheck->setSelected(musicOn);
    soundsCheck->setSelectedState(soundsOn);
    
    this->addChild(optionsTitle,1);
    this->addChild(menu,1);
    this->addChild(musicCheck,2);
    this->addChild(musicLabel,2);
    this->addChild(soundsCheck,2);
    this->addChild(soundsLabel,2);
    return true;
}

void OptionsScene::goToMainMenuScene(cocos2d::Ref *sender){
    
    this->removeAllChildrenWithCleanup(true);
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
   

    Director::getInstance()->popScene();
}

void OptionsScene::checkBoxSelectEvent(Ref *pSender, cocos2d::ui::CheckBox::EventType type)
{
    auto selectedCheckBox = (CheckBox*)pSender;
    int tag=selectedCheckBox->getTag();
    switch (type)
    {
        case CheckBox::EventType::SELECTED:
            if(tag==0)
            {
                UserDefault::getInstance()->setBoolForKey("MusicOn", true);
                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/Fantasy Armies.mp3");
            }
            else
            {
                 UserDefault::getInstance()->setBoolForKey("SoundsOn", true);
            }
            break;
            
        case CheckBox::EventType::UNSELECTED:
            if(tag==0)
            {
                UserDefault::getInstance()->setBoolForKey("MusicOn", false);
                CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            }
            else
            {
                UserDefault::getInstance()->setBoolForKey("SoundsOn", false);
            }
            break;
            
        default:
            break;
    }
}