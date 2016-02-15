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
 
    currentPackNumber=1;
    loadScene();
    
    return true;
}


void LevelSelectScene::loadScene()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(LevelSelectScene::onTouchBegan,this);
    listener->onTouchEnded = CC_CALLBACK_2(LevelSelectScene::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    numberOfPacks =ceil(LEVEL_COUNT/LEVEL_PACK_LENGTH);
    displayLevelsOn=false;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
 
    
    
    auto backItem = MenuItemFont::create("Back",CC_CALLBACK_1(LevelSelectScene::goBack,this));
    //backItem->setColor(cocos2d::Color3B::BLUE);
    backItem->setScale(1);
    backItem->setPosition(Point(visibleSize.width+origin.x-backItem->getContentSize().width/2, visibleSize.height+origin.y-backItem->getContentSize().height/2));
    backItem->setTag(0);
    
    
    
    auto menu = Menu::create(backItem,NULL);
    menu->setPosition(Point::ZERO);
   
    
    
    
    currentLayout = generateLevelPackLayer(currentPackNumber,0);
    this->addChild(currentLayout);
    this->addChild(menu,2);
    
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


void LevelSelectScene::displayPackLevels()
{
    displayLevelsOn=true;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
   
    
    //Scroll View for level select
    /*Size scrollFrameSize = Size(visibleSize.width, visibleSize.height*0.8);
    auto scrollView = cocos2d::ui::ScrollView::create();
    scrollView->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    scrollView->setBackGroundColor(Color3B(0, 0, 0));
    scrollView->setSize(scrollFrameSize);
    scrollView->setPosition(Point(origin.x,visibleSize.height*0.05));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
    auto containerSize = Size(scrollFrameSize.width, scrollFrameSize.height*NO_OF_SCROLL_PANES);
    scrollView->setInnerContainerSize(containerSize);*/
    //sroll view definition
    //Level select label
    auto levelSelectLabel = Label::createWithTTF("Select a Level","fonts/Marker Felt.ttf",60);
    levelSelectLabel->setPosition(Point(visibleSize.width/2+origin.x,visibleSize.height*15/16));
    
    
    auto backItem = MenuItemFont::create("Back",CC_CALLBACK_1(LevelSelectScene::goBack,this));
    //backItem->setColor(cocos2d::Color3B::BLUE);
    backItem->setScale(1);
    backItem->setPosition(Point(visibleSize.width+origin.x-backItem->getContentSize().width/2, visibleSize.height+origin.y- backItem->getContentSize().height/2));
    
    
    
    levelSelectLabel->setColor(cocos2d::Color3B::BLUE);
    auto *menu = Menu::create();  //menu creation
    auto *menu2= Menu::create(backItem,NULL);
    int width_factor = 1;
    
    int rangeBegin=(currentPackNumber-1)*(int)LEVEL_PACK_LENGTH ;
    int rangeEnd = rangeBegin+(int)LEVEL_PACK_LENGTH>LEVEL_COUNT?LEVEL_COUNT:rangeBegin+(int)LEVEL_PACK_LENGTH;
    for(int i=rangeBegin;i<rangeEnd;i++)  // loop to position menu items depending on scroll view container size and various macros
    {
        std::stringstream stream;
        stream << i+1;
        
        std::string levNo = stream.str();
        auto menu_item =MenuItemFont::create(levNo,CC_CALLBACK_1(LevelSelectScene::Play,this));
        menu_item->setTag(i+1);
        menu_item->setScale(2);
        menu_item->setPosition(Point((visibleSize.width/6)* width_factor+origin.x, visibleSize.height*0.80 +origin.y));
        menu->addChild(menu_item);
        width_factor++;
      //  if (i%5==0){width_factor=1;}
        
    }
    menu->setPosition(Point::ZERO);          //position menu
    menu2->setPosition(Point::ZERO);
    this->addChild(levelSelectLabel);     //add items to parents
    this->addChild(menu);
    this->addChild(menu2);
  //  this->addChild(scrollView);

}

void LevelSelectScene::goBack(cocos2d::Ref *pSender)
{
    
    if(displayLevelsOn)
    {
        //` _eventDispatcher->removeAllEventListeners();
        currentLayout->removeAllChildrenWithCleanup(true);
        this->removeAllChildrenWithCleanup(true);
        loadScene();
    }
    else
    {
        displayLevelsOn=false;
        this->removeAllChildrenWithCleanup(true);
        Director::getInstance()->getTextureCache()->removeUnusedTextures();
        _eventDispatcher->removeAllEventListeners();
        auto scene=MainMenuScene::createScene();
        Director::getInstance()->replaceScene(scene);    }

    
}

void LevelSelectScene::goToGameScene(cocos2d::Ref *sender){
 //   auto scene = GameScene::createScene(0);
 //   Director::getInstance()->replaceScene(scene);

}

cocos2d::ui::Layout* LevelSelectScene::generateLevelPackLayer(int packNo,int type)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto layout = cocos2d::ui::Layout::create();
    layout->setLayoutType(ui::Layout::Type::HORIZONTAL);
    // layout->setContentSize(Size(visibleSize.width*0.8,visibleSize.height/3));
    layout->setContentSize(Size(visibleSize.width*0.6,visibleSize.width*0.6));
    layout->setRotation(-45);
    layout->setPosition(Vec2(origin.x + visibleSize.width*0.5+type*visibleSize.width, origin.y + visibleSize.height*0.45-layout->getContentSize().height/2));
    layout->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
    layout->setOpacity(100);
    layout->setBackGroundColor(Color3B(50, 50, 50));
    
    
    currentPackNumber=packNo;
    char packNum[4];
    sprintf(packNum,"Pack %d",packNo);
    auto packItem = MenuItemFont::create(packNum,CC_CALLBACK_1(LevelSelectScene::generatePackLevels,this));
    packItem->setScale(3);
    packItem->setTag(packNo);
    packItem->setColor(Color3B::BLUE);
    packItem->setPosition(layout->getContentSize().width/2,layout->getContentSize().height/2);
    auto menu = Menu::create(packItem,NULL);
    menu->setPosition(Point::ZERO);
    packItem->setRotation(45);
    layout->addChild(menu);
    
    return layout;
    
    
}

void LevelSelectScene::generatePackLevels(cocos2d::Ref *pSender)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto resizeAction = ScaleTo::create(0.5, visibleSize.width*1.5, visibleSize.height*1.5);
    auto moveAction = MoveBy::create(0.5,Vec2(0,-visibleSize.height/2));
    auto spawnAction = Spawn::create(resizeAction,moveAction, NULL);
    currentLayout->runAction(Sequence::create(spawnAction,CallFunc::create(CC_CALLBACK_0(LevelSelectScene::displayPackLevels,this)) ,NULL));
    
    
}

void LevelSelectScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event* event)
{
    if(displayLevelsOn)return;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    touchEndedX=touch->getLocation().x;
    touchEndedY=touch->getLocation().y;
    float touchDifference=touchEndedX-touchBeganX;
    //swipe right
    if (touchDifference > 50) {
        if(currentPackNumber==1)return;
        newLayout = generateLevelPackLayer(--currentPackNumber, -1);
        this->addChild(newLayout);
        auto curLayerMovement = MoveBy::create(0.5f, Vec2(visibleSize.width,0));
        auto newLayerMovement = MoveBy::create(0.5f, Vec2(visibleSize.width,0));
        
        //  auto parallelMovements = Spawn::create(curLayerMovement,newLayerMovement, NULL);
        
        currentLayout->runAction(Sequence::create(curLayerMovement,CallFunc::create(CC_CALLBACK_0(LevelSelectScene::swipeFinished,this)), NULL));
        newLayout->runAction(newLayerMovement);
    }
    //swipe left
    if (touchDifference < -50) {
        if(currentPackNumber==numberOfPacks)return;
        newLayout = generateLevelPackLayer(++currentPackNumber, 1);
        this->addChild(newLayout);
        auto curLayerMovement = MoveBy::create(0.5f, Vec2(-visibleSize.width,0));
        auto newLayerMovement = MoveBy::create(0.5f, Vec2(-visibleSize.width,0));
        
        //  auto parallelMovements = Spawn::create(curLayerMovement,newLayerMovement, NULL);
        
        currentLayout->runAction(Sequence::create(curLayerMovement,CallFunc::create(CC_CALLBACK_0(LevelSelectScene::swipeFinished,this)), NULL));
        newLayout->runAction(newLayerMovement);
        
        
        
    }
    /*//swipe up
     if (touch->getDelta().y > 10) {
     //swiped up
     }
     //swipe down
     if (touch->getDelta().y < 10) {
     //swiped down
     }
     */
}

void LevelSelectScene::swipeFinished()
{
    this->removeChild(currentLayout);
    currentLayout=newLayout;
    //this->addChild(currentLayout);
    newLayout=NULL;
    
}
bool LevelSelectScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event* event)
{
    touchBeganX=touch->getLocation().x;
    touchBeganY=touch->getLocation().y;
    return true;
}

