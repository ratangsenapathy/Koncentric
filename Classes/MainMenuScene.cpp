#include "MainMenuScene.h"
#include "LevelSelectScene.h"
#include "OptionsScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"

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
    bool musicOn = UserDefault::getInstance()->getBoolForKey("MusicOn",true);
    
    if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/Fantasy Armies.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    if(musicOn)
    {
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/Fantasy Armies.mp3",true);
    }
    }
    auto gameTitle = Label::createWithTTF("Koncentric", "fonts/Marker Felt.ttf", 100);
    gameTitle->setPosition(Point(visibleSize.width/2+origin.x,visibleSize.height*0.9+origin.y));
    gameTitle->setColor(Color3B(100,25, 200));
    
    auto playItem = MenuItemFont::create("Play",CC_CALLBACK_1(MainMenuScene::goToGameScene,this));
    playItem->setColor(cocos2d::Color3B::BLUE);
    playItem->setScale(2);
    playItem->setPosition(Point(visibleSize.width/2+origin.x, visibleSize.height*0.6+origin.y));
    auto optionItem = MenuItemFont::create("Options",CC_CALLBACK_1(MainMenuScene::goToGameScene,this));
    playItem->setTag(0);
    
    optionItem->setColor(cocos2d::Color3B::BLUE);
    optionItem->setScale(2);
    optionItem->setPosition(Point(visibleSize.width/2+origin.x, visibleSize.height*0.6-playItem->getContentSize().height*2+origin.y));
    optionItem->setTag(1);
    
    ParticleSystemQuad* m_emitter = new ParticleSystemQuad();
    m_emitter = ParticleFlower::create();
   // m_emitter->setEmitterMode(cocos2d::ParticleSystem::Mode::RADIUS);
    m_emitter->setEmissionRate(20);
    m_emitter->setSpeed(150);
   // m_emitter->setColor(Color3B(50, 100, 200));
    m_emitter->setStartColor(Color4F(0, 180, 200, 255));
    m_emitter->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height*0.55+origin.y));
//    m_emitter->setStartRadius(10);
//    m_emitter->setEndRadius(50);
    //m_emitter->setGravity(Vec2(0,-90));
    // = kCCParticleModeGravity
    //m_emitter->modeA.gravity = ccp(0,-90);
    
    auto menu = Menu::create(playItem,optionItem,NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(m_emitter);
    this->addChild(gameTitle);
    this->addChild(menu);
    
    
    
    return true;
}

void MainMenuScene::goToGameScene(cocos2d::Ref *sender){
    MenuItem* item = (MenuItem*) sender;
    if(item->getTag()==0)
    {
        this->removeAllChildrenWithCleanup(true);
        Director::getInstance()->getTextureCache()->removeUnusedTextures();
        _eventDispatcher->removeAllEventListeners();
        this->unscheduleUpdate();
        auto scene = LevelSelectScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
    else
    {
       // this->removeAllChildrenWithCleanup(true);
       // Director::getInstance()->getTextureCache()->removeUnusedTextures();
       // _eventDispatcher->removeAllEventListeners();
       // this->unscheduleUpdate();
        auto scene = OptionsScene::createScene();
        Director::getInstance()->pushScene(TransitionFade::create(TRANSITION_TIME, scene));
        
    }
    

}
