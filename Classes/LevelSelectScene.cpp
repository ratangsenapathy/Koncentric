#include "LevelSelectScene.h"
#include "GameScene.h"
#include "Definitions.h"


USING_NS_CC;

Scene* LevelSelectScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = LevelSelectScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LevelSelectScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /*
    
    auto menu_item_1 = MenuItemFont::create("1",CC_CALLBACK_1(LevelSelectScene::Play,this));
    auto menu_item_2 = MenuItemFont::create("2", CC_CALLBACK_1(LevelSelectScene::Play,this));
    auto menu_item_3= MenuItemFont::create("3", CC_CALLBACK_1(LevelSelectScene::Play,this));
    
    menu_item_1->setTag(1);
    menu_item_2->setTag(2);
    menu_item_3->setTag(3);
    
    menu_item_1->setPosition(Point(visibleSize.width/2,(visibleSize.height/5)*4));
    menu_item_2->setPosition(Point(visibleSize.width/2,(visibleSize.height/5)*3));
    menu_item_3->setPosition(Point(visibleSize.width/2,(visibleSize.height/5)*2));
    
    
    auto *menu = Menu::create(menu_item_1,menu_item_2,menu_item_3,NULL);
    menu->setPosition(Point(0,0));
    // menu->alignItemsVertically();
    this->addChild(menu);
    
    */
    auto label = Label::createWithTTF("Select a Level","fonts/Marker Felt.ttf",45);
    label->setPosition(Point(visibleSize.width/2,visibleSize.height*15/16));
    
    label->setColor(cocos2d::Color3B::BLUE);
    this -> addChild(label);
    auto *menu = Menu::create();
    int height_factor = 1;
    int width_factor = 1;
    for(int i=1;i<=LEVEL_COUNT;i++)
    {
        std::string levNo = std::to_string(i);
        auto menu_item =MenuItemFont::create(levNo,CC_CALLBACK_1(LevelSelectScene::Play,this));
        menu_item->setTag(i);
        
        menu_item->setPosition(Point((visibleSize.width/6)* width_factor, visibleSize.height - height_factor/6.0 * visibleSize.height));
        menu->addChild(menu_item);
        width_factor++;
        if (i%5==0){height_factor++; width_factor=1;}
        
    }
    menu->setPosition(Point(0,0));
    this->addChild(menu);
    
    
    return true;
}

void LevelSelectScene::Play(cocos2d::Ref *pSender){
    MenuItem* item = (MenuItem*) pSender;
    int levelNo =  (int)item->getTag();
    auto scene = GameScene::createScene(levelNo-1);
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
  
}

void LevelSelectScene::goToGameScene(cocos2d::Ref *sender){
 //   auto scene = GameScene::createScene(0);
 //   Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

}
