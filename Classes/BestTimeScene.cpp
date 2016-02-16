#include "BestTimeScene.h"
#include "Definitions.h"



USING_NS_CC;

using namespace cocos2d::ui;

Scene* BestTimeScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = BestTimeScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool BestTimeScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    currentPackNumber=1;
    
    loadScene();
    
    //this->addChild((scrollView));
        return true;
}

void BestTimeScene::loadScene()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(BestTimeScene::onTouchBegan,this);
    listener->onTouchEnded = CC_CALLBACK_2(BestTimeScene::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    numberOfPacks =ceil(LEVEL_COUNT/LEVEL_PACK_LENGTH);
    displayBestTimeOn=false;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /*
     
     Size scrollFrameSize = Size(visibleSize.width, visibleSize.height);
     auto scrollView = cocos2d::ui::ScrollView::create();
     scrollView->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
     scrollView->setBackGroundColor(Color3B(0, 0, 0));
     scrollView->setSize(scrollFrameSize);
     scrollView->setPosition(Point(origin.x,visibleSize.height*0.05));
     scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
     auto containerSize = Size(scrollFrameSize.width, scrollFrameSize.height*NO_OF_SCROLL_PANES_BEST_TIME);
     scrollView->setInnerContainerSize(containerSize);
     */
    
    auto bestTimeTitle = Label::createWithTTF("Best Times", "fonts/Marker Felt.ttf", 80);
    bestTimeTitle->setPosition(Point(visibleSize.width/2+origin.x,visibleSize.height*0.90+origin.y));
    bestTimeTitle->setColor(Color3B(100,25, 200));
    
    
    auto backItem = MenuItemFont::create("Back",CC_CALLBACK_1(BestTimeScene::goToMainMenuScene,this));
    //backItem->setColor(cocos2d::Color3B::BLUE);
    backItem->setScale(1);
    backItem->setPosition(Point(visibleSize.width+origin.x-backItem->getContentSize().width/2, visibleSize.height+origin.y-backItem->getContentSize().height/2));
    backItem->setTag(0);
    
    
    
    auto menu = Menu::create(backItem,NULL);
    menu->setPosition(Point::ZERO);
    /*
     auto levelSubTitle = Label::createWithTTF("Level", "fonts/Marker Felt.ttf", 50);
     levelSubTitle->setPosition(Point(containerSize.width*0.15,containerSize.height*0.8));
     levelSubTitle->setColor(Color3B(0,0, 255));
     
     auto timeSubTitle = Label::createWithTTF("Time", "fonts/Marker Felt.ttf", 50);
     timeSubTitle->setPosition(Point(containerSize.width*0.85,containerSize.height*0.8));
     timeSubTitle->setColor(Color3B(0,0, 255));
     
     for(int i=0;i<LEVEL_COUNT;i++)
     {
     char levelNo[4];
     sprintf(levelNo,"%d",i+1);
     auto levelNoLabel = Label::createWithTTF(levelNo, "fonts/Marker Felt.ttf", 50);
     levelNoLabel->setPosition(Point(containerSize.width*0.15,containerSize.height*0.8-levelSubTitle->getContentSize().height*2*(i+1)));
     levelNoLabel->setColor(Color3B(200,200, 200));
     scrollView->addChild(levelNoLabel);
     
     char minKey[15],secKey[15];
     char bestTimeText[15];
     sprintf(minKey, "BestMinKey%d",i);
     sprintf(secKey, "BestSecKey%d",i);
     int bestMin = UserDefault::getInstance()->getIntegerForKey(minKey,-1);
     int bestSec = UserDefault::getInstance()->getIntegerForKey(secKey,-1);
     if(bestMin==-1 || bestSec==-1)
     {
     sprintf(bestTimeText, "NA");
     }
     else
     {
     sprintf(bestTimeText, "%s",getTimeText(bestMin, bestSec).c_str());
     }
     auto bestTimeLabel = Label::createWithTTF(bestTimeText,"fonts/Marker Felt.ttf",50);
     bestTimeLabel->setPosition(Point(containerSize.width*0.85,containerSize.height*0.8-timeSubTitle->getContentSize().height*2*(i+1)));
     bestTimeLabel->setColor(Color3B(200,200, 200));
     scrollView->addChild(bestTimeLabel);
     
     }
     
     scrollView->addChild(bestTimeTitle);
     scrollView->addChild(levelSubTitle);
     scrollView->addChild(timeSubTitle);
     
     */
    
    
    
    currentLayout = generateLevelPackLayer(currentPackNumber,0);
    this->addChild(bestTimeTitle);
    this->addChild(currentLayout);
    this->addChild(menu,2);
}

void BestTimeScene::goToMainMenuScene(cocos2d::Ref *sender){
    
    if(displayBestTimeOn)
    {
       //` _eventDispatcher->removeAllEventListeners();
        currentLayout->removeAllChildrenWithCleanup(true);
        this->removeAllChildrenWithCleanup(true);
        loadScene();
    }
    else
    {
        displayBestTimeOn=false;
        this->removeAllChildrenWithCleanup(true);
//        _eventDispatcher->removeAllEventListeners();

    Director::getInstance()->getTextureCache()->removeUnusedTextures();
   

    Director::getInstance()->popScene();
    }
}


std::string BestTimeScene::getTimeText(int minCount, int secCount)
{
    char secondText[3];  char minuteText[3];
    char timeText[6];
    if(secCount<10)
    {
        sprintf(secondText,"0%d",secCount);
    }
    else
        sprintf(secondText,"%d",secCount);
    
    if(minCount<10)
    {
        sprintf(minuteText,"0%d",minCount);
    }
    else
        sprintf(minuteText,"%d",minCount);
    sprintf(timeText,"%s:%s",minuteText,secondText);
    return timeText;
    
}

void BestTimeScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event* event)
{
    if(displayBestTimeOn)return;
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
        
        currentLayout->runAction(Sequence::create(curLayerMovement,CallFunc::create(CC_CALLBACK_0(BestTimeScene::swipeFinished,this)), NULL));
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
        
        currentLayout->runAction(Sequence::create(curLayerMovement,CallFunc::create(CC_CALLBACK_0(BestTimeScene::swipeFinished,this)), NULL));
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

void BestTimeScene::swipeFinished()
{
    this->removeChild(currentLayout);
    currentLayout=newLayout;
    //this->addChild(currentLayout);
    newLayout=NULL;

}
bool BestTimeScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event* event)
{
    touchBeganX=touch->getLocation().x;
    touchBeganY=touch->getLocation().y;
    return true;
}



cocos2d::ui::Layout* BestTimeScene::generateLevelPackLayer(int packNo,int type)
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
    char packNum[10];
    sprintf(packNum,"Pack %d",packNo);
    auto packItem = MenuItemFont::create(packNum,CC_CALLBACK_1(BestTimeScene::generatePackLevels,this));
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

void BestTimeScene::generatePackLevels(cocos2d::Ref *pSender)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto resizeAction = ScaleTo::create(0.5, visibleSize.width*1.5, visibleSize.height*1.5);
    auto moveAction = MoveBy::create(0.5,Vec2(0,-visibleSize.height/2));
    auto spawnAction = Spawn::create(resizeAction,moveAction, NULL);
    currentLayout->runAction(Sequence::create(spawnAction,CallFunc::create(CC_CALLBACK_0(BestTimeScene::displayBestTime,this)) ,NULL));
    
    
   
}

void BestTimeScene::displayBestTime()
{   this->removeChild(currentLayout);
    displayBestTimeOn=true;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto levelSubTitle = Label::createWithTTF("Level", "fonts/Marker Felt.ttf", 50);
    levelSubTitle->setPosition(Point(visibleSize.width*0.15+origin.x,visibleSize.height*0.8+origin.y));
    levelSubTitle->setColor(Color3B(0,0, 255));
    
    auto timeSubTitle = Label::createWithTTF("Time", "fonts/Marker Felt.ttf", 50);
    timeSubTitle->setPosition(Point(visibleSize.width*0.85+origin.x,visibleSize.height*0.8+origin.y));
    timeSubTitle->setColor(Color3B(0,0, 255));
    int k=0;
    int rangeBegin=(currentPackNumber-1)*(int)LEVEL_PACK_LENGTH;
    int rangeEnd = rangeBegin+(int)LEVEL_PACK_LENGTH>LEVEL_COUNT?LEVEL_COUNT:rangeBegin+(int)LEVEL_PACK_LENGTH;
    for(int i=rangeBegin;i<rangeEnd;i++)
    {
        char levelNo[4];
        sprintf(levelNo,"%d",i+1);
        auto levelNoLabel = Label::createWithTTF(levelNo, "fonts/Marker Felt.ttf", 50);
        levelNoLabel->setPosition(Point(visibleSize.width*0.15+origin.x,visibleSize.height*0.8+origin.y-levelSubTitle->getContentSize().height*2*(++k)));
        levelNoLabel->setColor(Color3B(200,200, 200));
        this->addChild(levelNoLabel);
        
        char minKey[15],secKey[15];
        char bestTimeText[15];
        sprintf(minKey, "BestMinKey%d",i);
        sprintf(secKey, "BestSecKey%d",i);
        int bestMin = UserDefault::getInstance()->getIntegerForKey(minKey,-1);
        int bestSec = UserDefault::getInstance()->getIntegerForKey(secKey,-1);
        if(bestMin==-1 || bestSec==-1)
        {
            sprintf(bestTimeText, "NA");
        }
        else
        {
            sprintf(bestTimeText, "%s",getTimeText(bestMin, bestSec).c_str());
        }
        auto bestTimeLabel = Label::createWithTTF(bestTimeText,"fonts/Marker Felt.ttf",50);
        bestTimeLabel->setPosition(Point(visibleSize.width*0.85+origin.x,visibleSize.height*0.8+origin.y-timeSubTitle->getContentSize().height*2*k));
        bestTimeLabel->setColor(Color3B(200,200, 200));
        this->addChild(bestTimeLabel);
        
    }
    
    this->addChild(levelSubTitle);
    this->addChild(timeSubTitle);
    auto fadeAwayAction =FadeTo::create(1.0, 0);
    currentLayout->runAction(fadeAwayAction);
}