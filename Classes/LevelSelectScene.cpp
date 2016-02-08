#include "LevelSelectScene.h"
#include "GameScene.h"
#include "Definitions.h"
#include "MainMenuScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

// Scene to select levels
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
    
    //Scroll View for level select
    Size scrollFrameSize = Size(visibleSize.width, visibleSize.height*0.8);
    auto scrollView = cocos2d::ui::ScrollView::create();
    scrollView->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    scrollView->setBackGroundColor(Color3B(0, 0, 0));
    scrollView->setSize(scrollFrameSize);
    scrollView->setPosition(Point(origin.x,visibleSize.height*0.05));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
    auto containerSize = Size(scrollFrameSize.width, scrollFrameSize.height*NO_OF_SCROLL_PANES);
    scrollView->setInnerContainerSize(containerSize);
    //sroll view definition
    
    //Level select label
    auto levelSelectLabel = Label::createWithTTF("Select a Level","fonts/Marker Felt.ttf",36);
    levelSelectLabel->setPosition(Point(visibleSize.width/2+origin.x,visibleSize.height*15/16));
    
    
    auto backItem = MenuItemFont::create("Back",CC_CALLBACK_1(LevelSelectScene::goBack,this));
    //backItem->setColor(cocos2d::Color3B::BLUE);
    backItem->setScale(1);
    backItem->setPosition(Point(visibleSize.width+origin.x-backItem->getContentSize().width/2, visibleSize.height+origin.y- backItem->getContentSize().height/2));
    

    
    levelSelectLabel->setColor(cocos2d::Color3B::BLUE);
    auto *menu = Menu::create();  //menu creation
    auto *menu2= Menu::create(backItem,NULL);
    float height_factor = 0.5;
    int width_factor = 1;
    for(int i=1;i<=LEVEL_COUNT;i++)  // loop to position menu items depending on scroll view container size and various macros
    {
        std::stringstream stream;
        stream << i;
        
        std::string levNo = stream.str();
        auto menu_item =MenuItemFont::create(levNo,CC_CALLBACK_1(LevelSelectScene::Play,this));
        menu_item->setTag(i);
        menu_item->setScale(2);
        menu_item->setPosition(Point((containerSize.width/6)* width_factor, containerSize.height - height_factor/HEIGHT_DIVISION_FACTOR * containerSize.height));
        menu->addChild(menu_item);
        width_factor++;
        if (i%5==0){height_factor++; width_factor=1;}
        
    }
    menu->setPosition(Point::ZERO);          //position menu
    menu2->setPosition(Point::ZERO);
    this->addChild(levelSelectLabel);     //add items to parents
    scrollView->addChild(menu);
    this->addChild(menu2);
    this->addChild(scrollView);
    
    
    return true;
}

void LevelSelectScene::Play(cocos2d::Ref *pSender){   //what happens when a level is selected 
    MenuItem* item = (MenuItem*) pSender;
    int levelNo =  (int)item->getTag();
    UserDefault::getInstance()->setIntegerForKey("LevelNo",levelNo-1);
   // auto scene = GameScene::createScene(levelNo-1);
    
    this->removeAllChildrenWithCleanup(true);
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    _eventDispatcher->removeAllEventListeners();
    this->unscheduleUpdate();
    auto scene = GameScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
  
}
void LevelSelectScene::goBack(cocos2d::Ref *pSender)
{
    this->removeAllChildrenWithCleanup(true);
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    _eventDispatcher->removeAllEventListeners();
    auto scene=MainMenuScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void LevelSelectScene::goToGameScene(cocos2d::Ref *sender){
 //   auto scene = GameScene::createScene(0);
 //   Director::getInstance()->replaceScene(scene);

}
