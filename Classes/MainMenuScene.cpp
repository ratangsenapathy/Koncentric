#include "MainMenuScene.h"
#include "LevelSelectScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto gameTitle = Label::createWithTTF("Koncentric", "fonts/Marker Felt.ttf", 100);
    gameTitle->setPosition(Point(visibleSize.width/2+origin.x,visibleSize.height*3/4+origin.y));
    gameTitle->setColor(Color3B(100,25, 200));
    
    auto playItem = MenuItemFont::create("Play",CC_CALLBACK_1(MainMenuScene::goToGameScene,this));
    playItem->setColor(cocos2d::Color3B::BLUE);
    playItem->setScale(2);
    playItem->setPosition(Point(visibleSize.width/2+origin.x, visibleSize.height/2+origin.y));
    
    auto menu = Menu::create(playItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(gameTitle);
    this->addChild(menu);
    
    
    
    return true;
}

void MainMenuScene::goToGameScene(cocos2d::Ref *sender){
    this->removeAllChildrenWithCleanup(true);
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    _eventDispatcher->removeAllEventListeners();
    this->unscheduleUpdate();
    auto scene = LevelSelectScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

}
