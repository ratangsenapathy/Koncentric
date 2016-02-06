#include "GameOverScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* GameOverScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto label = Label::createWithTTF("Congrats! You completed\nall the levels","fonts/Marker Felt.ttf",45,Size::ZERO,TextHAlignment::CENTER,TextVAlignment::TOP);
    label->setPosition(Point(visibleSize.width/2+origin.x,visibleSize.height*3/4+origin.y));
    
    label->setColor(cocos2d::Color3B::GREEN);
    auto goToMainMenu = MenuItemFont::create("Go to Main Menu",CC_CALLBACK_1(GameOverScene::GoToMainMenu,this));
    this->addChild(label);
    
    goToMainMenu->setPosition(Point(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
    
    auto *menu = Menu::create(goToMainMenu,NULL);
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu);

    
    
    return true;
}


void GameOverScene::GoToMainMenu(cocos2d::Ref *pSender)
{
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(scene);
}