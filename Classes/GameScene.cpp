#include "GameScene.h"
#include "MainMenuScene.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"

//#include "Levels.h"


#define COCOS2D_DEBUG 1

USING_NS_CC;
using namespace rapidjson;



GameScene::~GameScene()
{
   
    delete []obstacles;
    delete []ringSpin;
    
    this->unschedule(schedule_selector(GameScene::changeObstacleDirection));
    rotationPoint->removeAllChildrenWithCleanup(true);
    clockwiseObstacleRotationPoint->removeAllChildrenWithCleanup(true);
    antiClockwiseObstacleRotationPoint->removeAllChildrenWithCleanup(true);
    this->removeAllChildrenWithCleanup(true);
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    //_eventDispatcher->removeAllEventListeners();
       this->unscheduleUpdate();
   // this->removeAllComponents();
}

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
   
    
    // 'layer' is an autorelease object

    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance

bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
   
    std::string fullPath = "res/Levels.json";
    std::string jsonFile = FileUtils::getInstance()->getStringFromFile(fullPath.c_str());
    levelNo = UserDefault::getInstance()->getIntegerForKey("LevelNo");
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    rIncrement=visibleSize.width/20;
    generateJSON(jsonFile);
    
    
    loadScene();
    
    return true;
}

void GameScene::loadScene()
{
    
    
    //obstacleSpeed =10;
    timerRunning=true;
    secondCount=0; minuteCount=0;
    theta=0;
    controlable=0;
    distance=rMax;
    r=0;
    
  
    
    
    
#if COMPILE_FOR_MOBILE == 1
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
#endif
    
    ParticleSystemQuad* m_emitter = new ParticleSystemQuad();
    m_emitter = ParticleSnow::create();
    m_emitter->setEmissionRate(25);
    m_emitter->setSpeed(180);
    //m_emitter->setLifeVar(0);
    CCLOG("%f",m_emitter->getDuration());
    // m_emitter->setColor(Color3B(50, 100, 200));
    m_emitter->setStartColor(Color4F(0, 0, 255, 255));
    m_emitter->setPosition(Vec2(origin.x+visibleSize.width/2,visibleSize.height+origin.y));
    //  m_emitter->setGravity(Vec2(0,0));
    this->addChild(m_emitter);

    ParticleSystemQuad* m_emitter2 = new ParticleSystemQuad();
    m_emitter2 = ParticleGalaxy::create();
       m_emitter2->setEmissionRate(200);
   
    m_emitter2->setStartSize(1.5*5*M_PI);
    m_emitter2->setStartSizeVar(0);
    m_emitter2->setEndSize(1.5*5*M_PI);
    m_emitter2->setEndSizeVar(0);
    m_emitter2->setLife(1);
    m_emitter2->setLife(0);
    m_emitter2->setStartColor(goalColor);
    m_emitter2->setPosition(Vec2(origin.x+visibleSize.width/2,visibleSize.height/2+origin.y));
    //  m_emitter->setGravity(Vec2(0,0));
    this->addChild(m_emitter2);
    /*
    goal = DrawNode::create();
    goal->drawDot(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y), 5, goalColor);
    this->addChild(goal,1);          // drawing the goal
    */
    
    rotationPoint = Node::create();
    rotationPoint->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
    this->addChild(rotationPoint, 2);
    
    
    //Setting the exit button
    auto exitLabel = Label::createWithTTF("Exit","fonts/Marker Felt.ttf",32);
    exitButtonWidth=exitLabel->getContentSize().width;
    exitButtonHeight=exitLabel->getContentSize().height;
    exitLabel->setPosition(Point(visibleSize.width-exitButtonWidth+origin.x,visibleSize.height-exitButtonHeight+origin.y));
    this->addChild(exitLabel);
    
    
    //setting the clock
    timer = Label::createWithTTF("00:00","fonts/Marker Felt.ttf",32);
    timer->setPosition(Point(timer->getContentSize().width+origin.x,visibleSize.height-timer->getContentSize().height+origin.y));
    this->schedule(schedule_selector(GameScene::updateClock),1.0f);  //scedule to call upDateClock function every 1.0 sec
    this->addChild(timer);
    
    if(spinSwitchTime!=0)
        this->schedule(schedule_selector(GameScene::changeObstacleDirection),spinSwitchTime);
    
    char minKey[15],secKey[15];
    char bestTimeText[15];
    sprintf(minKey, "BestMinKey%d",levelNo);
    sprintf(secKey, "BestSecKey%d",levelNo);
    int bestMin = UserDefault::getInstance()->getIntegerForKey(minKey,-1);
    int bestSec = UserDefault::getInstance()->getIntegerForKey(secKey,-1);
    if(bestMin==-1 || bestSec==-1)
    {
        sprintf(bestTimeText, "Best Time=NA");
    }
    else
    {
        sprintf(bestTimeText, "Best Time=%s",getTimeText(bestMin, bestSec).c_str());
    }
    auto bestTimeLabel = Label::createWithTTF(bestTimeText,"fonts/Marker Felt.ttf",32);
    float bestTimeWidth=bestTimeLabel->getContentSize().width;
    float bestTimeHeight=bestTimeLabel->getContentSize().height;
    bestTimeLabel->setPosition(Point(bestTimeWidth/2+origin.x,visibleSize.height-bestTimeHeight-timer->getContentSize().height-3+origin.y));

    this->addChild(bestTimeLabel);
    
    clockwiseObstacleRotationPoint = Node::create();
    clockwiseObstacleRotationPoint->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
    this->addChild(clockwiseObstacleRotationPoint, 3);
    
    antiClockwiseObstacleRotationPoint = Node::create();
    antiClockwiseObstacleRotationPoint->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
    this->addChild(antiClockwiseObstacleRotationPoint, 3);
    //float theta=0;
    /*
    ball = DrawNode::create();
    ball->drawDot(Vec2(0,0),ballRadius,ballColor);
    */
    ball = new ParticleSystemQuad();
    ball = ParticleMeteor::create();
    ball->setEmissionRate(100);
    ball->setSpeedVar(0);
    
    ball->setSpeed(50);
    ball->setStartColor(ballColor);
    ball->setStartSize(1.3*M_PI*ballRadius);
    ball->setStartSizeVar(0);
    ball->setPosition(Vec2(0,0));
    
    //theta+=2*M_PI/rIncrement0;
    //this->addChild(snake[0],2);
    
    rotationPoint->addChild(ball);
    // fixedPoint->addChild(snake[0]);
    
    
    //loop to draw the concentric circles
    
    for(r=rIncrement;r<=rMax;r+=rIncrement)
    {
        for(theta=0;theta<=2*M_PI;theta+=2*M_PI/r){
            pathNode = DrawNode::create();
            pathNode->drawDot(Vec2(r*cos(theta)+origin.x+visibleSize.width/2,r*sin(theta)+origin.y+visibleSize.height/2),1,ringColor);
            //pathNode->autorelease();
            this->addChild(pathNode,1);
            //this->removeChild(pathNode);
        }
    }
    
    
    for(int i=0;i<obstacleCount;i++)
    {
        
        int index=0;
        int base=obstacles[i].ringNum*rIncrement;
        int vertexUpperCount= (int)ceil((obstacles[i].theta2*M_PI/180-obstacles[i].theta1*M_PI/180)/(2*M_PI/(base+rIncrement)));
        
        int vertexLowerCount= (int)ceil((obstacles[i].theta2*M_PI/180-obstacles[i].theta1*M_PI/180)/(2*M_PI/(base!=0?base:rIncrement)));
        
        Point *vertices = new Point[vertexLowerCount+vertexUpperCount+1];
        
        //Loops to draw obstacles
        float lower=obstacles[i].theta1*M_PI/180;
        float upper=obstacles[i].theta2*M_PI/180;
        
        for(theta=upper;theta>=lower;theta-=2*M_PI/(base+rIncrement)){
            
            vertices[index++]=Vec2((base+rIncrement)*cos(theta),(base+rIncrement)*sin(theta));
            
        }
        for(theta=lower;theta<=upper;theta+=2*M_PI/(base!=0?base:rIncrement)){
            
            vertices[index++]=Vec2(base*cos(theta),base*sin(theta));
            
        }
        
        Color4F obstacleColor = convertHexToRBG(obstacles[i].color);
        DrawNode* polygon = DrawNode::create();
        
        polygon->drawPolygon(vertices,index, obstacleColor, 1, obstacleColor);
        if(ringSpin[obstacles[i].ringNum] == 1)
        antiClockwiseObstacleRotationPoint->addChild(polygon);
        else
        clockwiseObstacleRotationPoint->addChild(polygon);
        lower =upper;
        
        delete []vertices;
        vertices=NULL;
        
        
    }
    
    
    ball->runAction(Sequence::create(Place::create(Vec2(ball->getPosition().x+rMax,ball->getPosition().y)),CallFunc::create(CC_CALLBACK_0(GameScene::actionComplete,this)),NULL)); // set ball position
    
    distance=rMax;
    // auto rotateBy = RotateBy::create(0.25f,360/distance);
    // rotationPoint->runAction(RepeatForever::create(rotateBy));
    
    auto obstacleRotate = RotateBy::create(0.5f,obstacleSpeed*-1);
    auto clockwiseAction = RepeatForever::create(obstacleRotate->reverse());
    auto antiClockwiseAction = RepeatForever::create(obstacleRotate);

    antiClockwiseAction->setTag(0);
    clockwiseAction->setTag(0);
        antiClockwiseObstacleRotationPoint->runAction(antiClockwiseAction);
    clockwiseObstacleRotationPoint->runAction(clockwiseAction);
    
    controlable=0;
    this->scheduleUpdate();
}

void GameScene::generateJSON(std::string jsonFile)
{
    
    document.Parse<0>(jsonFile.c_str());
    parseJSON();
}

void GameScene::parseJSON()
{
    
    if(document.HasMember("levels"))
    {
        
        const rapidjson::Value& jsonLevels = document["levels"];
        noOfLevels=jsonLevels.Size();
        rMax = jsonLevels[(SizeType)levelNo]["numOfRings"].GetInt()*rIncrement;
        ballTime = 1.0/jsonLevels[(SizeType)levelNo]["ball"]["speed"].GetDouble();
        ballRadius = jsonLevels[(SizeType)levelNo]["ball"]["radius"].GetDouble();
        ringColor = convertHexToRBG(jsonLevels[(SizeType)levelNo]["ringColor"].GetString());
        std::string hexString = jsonLevels[(SizeType)levelNo]["ball"]["color"].GetString();
        goalColor = convertHexToRBG(jsonLevels[(SizeType)levelNo]["goalColor"].GetString());
        const rapidjson::Value& ringSpinsJSON = jsonLevels[(SizeType)levelNo]["ringSpin"];
        ringSpin = new int[ringSpinsJSON.Size()];
        spinSwitchTime = jsonLevels[(SizeType)levelNo]["spinSwitchTime"].GetDouble();
        
        
        for(int i=0;i<ringSpinsJSON.Size();i++)
        {
            ringSpin[i]=ringSpinsJSON[i].GetInt();
        }
        
        ballColor = convertHexToRBG(hexString);
        ballDirection = jsonLevels[(SizeType)levelNo]["ball"]["direction"].GetInt();
        ballInitTheta = jsonLevels[(SizeType)levelNo]["ball"]["initTheta"].GetDouble();
        
        obstacleSpeed=jsonLevels[(SizeType)levelNo]["obstacleSpeed"].GetDouble();
        //CCLOG("Test=%d",test);
        const rapidjson::Value& jsonObstacles = jsonLevels[(SizeType)levelNo]["obstacles"];
        obstacleCount=jsonObstacles.Size();
        obstacles = new struct obstacle[obstacleCount];
        
        for (SizeType i = 0; i < obstacleCount; i++)
        {
            //obstacles[i].speed = jsonObstacles[i]["speed"].GetDouble();
            obstacles[i].theta1 = jsonObstacles[i]["theta1"].GetDouble();
            obstacles[i].theta2 = jsonObstacles[i]["theta2"].GetDouble();
            obstacles[i].ringNum= jsonObstacles[i]["ringNum"].GetInt();
            obstacles[i].color = (char*)jsonObstacles[i]["color"].GetString();
            
        }
        
        
    }
    
}

Color4F GameScene::convertHexToRBG(std::string hexString)
{
    int hexValue;
    std::stringstream ss;
    ss << std::hex << hexString.substr(1);
    ss >> hexValue;
    float red = ((hexValue >> 16) & 0xFF) /255.0;  // Extract the RR byte
    float green = ((hexValue >> 8) & 0xFF)/255.0;   // Extract the GG byte
    float blue = ((hexValue) & 0xFF)/255.0;
    return Color4F(red,green,blue,1);
}

#if COMPILE_FOR_MOBILE == 1
bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{   // check if exit button region was clicked
    //_eventDispatcher->removeAllEventListeners();
    //auto scene = GameScene::createScene(levelNo);
   // auto scene = GameScene::createScene();
   // Director::getInstance()->replaceScene(scene);
   // return true;

    if((touch->getLocation().x>=(visibleSize.width-2*exitButtonWidth)) && (touch->getLocation().y>=(visibleSize.height-1.5*exitButtonHeight)))
    {           auto scene = MainMenuScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
        //removeResources();

        return true;
    }
    if(controlable==1)  //  otherwise move ball inwards if controllable
    {
        controlable=0; // while moving inwards ball should not be controllable
        distance-=rIncrement;
        auto rotateBy = RotateBy::create(ballTime,0);
        rotationPoint->runAction(RepeatForever::create(rotateBy));
        bool soundsOn = UserDefault::getInstance()->getBoolForKey("SoundsOn",true);
        if(soundsOn)
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/moveInwards.mp3");
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/moveInwards.mp3");
        }
            
        // CCLOG("Cor=%f,%f",snake[0]->getPosition().x,snake[0]->getPosition().y);
        ball->runAction(Sequence::create(MoveTo::create(ballTime*2,Vec2(ball->getPosition().x-rIncrement,ball->getPosition().y)),CallFunc::create(CC_CALLBACK_0(GameScene::actionComplete,this)),NULL));
        
    }
    
    return true;
}
//#else
/*
void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    if((touch->getLocation().x>=(visibleSize.width-2*exitButtonWidth)) && (touch->getLocation().y>=(visibleSize.height-1.5*exitButtonHeight)))
    {
        auto scene = MainMenuScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
        return true;
    }
    if(controlable==1)
    {
        controlable=0;
        distance-=rIncrement;
        auto rotateBy = RotateBy::create(objectTime,0);
        rotationPoint->runAction(RepeatForever::create(rotateBy));
        
        // CCLOG("Cor=%f,%f",snake[0]->getPosition().x,snake[0]->getPosition().y);
        snake[0]->runAction(Sequence::create(MoveTo::create(objectTime*2,Vec2(snake[0]->getPosition().x-rIncrement,snake[0]->getPosition().y)),
                                             CallFunc::create(CC_CALLBACK_0(GameScene::actionComplete,this)),NULL));
        
        
    }
    
}
*/
#endif

//function to update the clock
void GameScene::updateClock(float dt)
{
    if(timerRunning)
    {
    secondCount++;
    if(secondCount == 60) {secondCount=0; minuteCount++;}
   // std::stringstream stream;
   // stream << secondCount;
 /*  char secondText[3];  char minuteText[3];
    char timeText[6];
    if(secondCount<10)
    {
        sprintf(secondText,"0%d",secondCount);
    }
    else
        sprintf(secondText,"%d",secondCount);
    
    if(minuteCount<10)
    {
        sprintf(minuteText,"0%d",minuteCount);
    }
    else
        sprintf(minuteText,"%d",minuteCount);

    sprintf(timeText,"%s:%s",minuteText,secondText);*/
    std::string timeText=getTimeText(minuteCount, secondCount);
    timer->setString(timeText);
    }
}

//after a move into the next path or outside after collision the ball should be made controllab;e againa and speed adjusted

void GameScene::actionComplete()
{
    if(distance==0)
    {
       
        saveScores();
        if(levelNo+1==noOfLevels)
        {   //removeResources();
            auto scene = GameOverScene::createScene();
            Director::getInstance()->replaceScene(scene);
            return;
        }
        else
        {
            
            
            //auto scene = GameScene::createScene(levelNo);
            //auto scene = GameScene::createScene();
            //Director::getInstance()->replaceScene(scene);
            displayLevelCompleteLayer();
           
            return;
            }
    }
    auto rotateBy = RotateBy::create(ballTime,360/distance);
    rotationPoint->runAction(RepeatForever::create(rotateBy));
controlable=1;
}

void GameScene::displayLevelCompleteLayer()
{  timerRunning=false;
    layout = ui::Layout::create();
    layout->setLayoutType(ui::Layout::Type::HORIZONTAL);
    layout->setContentSize(Size(visibleSize.width*0.8,visibleSize.height/3));
    layout->setPosition(Vec2(origin.x + visibleSize.width/2-layout->getContentSize().width/2, origin.y + visibleSize.height/2-layout->getContentSize().height/2));
    layout->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
    layout->setOpacity(100);
    layout->setBackGroundColor(Color3B(50, 50, 50));
     this->addChild(layout,4);
    
    auto congratsLabel = Label::createWithTTF("You cleared the level", "fonts/Marker Felt.ttf", 50);
    congratsLabel->setColor(Color3B::GREEN);
    congratsLabel->setPosition(Vec2(layout->getContentSize().width/2,layout->getContentSize().height*0.8));
    
    auto goToNextLevelItem = MenuItemFont::create("Next", CC_CALLBACK_1(GameScene::goToNextLevel,this));
    goToNextLevelItem->setColor(Color3B(0, 0, 255));
    goToNextLevelItem->setPosition(Vec2(layout->getContentSize().width/2,layout->getContentSize().height/2));
    auto menu = Menu::create(goToNextLevelItem,NULL);
    menu->setPosition(Point::ZERO);
    layout->addChild(congratsLabel);
    layout->addChild(menu);
}

void GameScene::goToNextLevel(cocos2d::Ref *pSender)
{
    removeResources();
    
    UserDefault::getInstance()->setIntegerForKey("LevelNo", ++levelNo);
    parseJSON();
    loadScene();
}

void GameScene::removeResources()
{
    layout->removeAllChildrenWithCleanup(true);
    timer->unschedule(schedule_selector(GameScene::updateClock));
    this->unschedule(schedule_selector(GameScene::changeObstacleDirection));
    delete []obstacles;
    delete []ringSpin;
    rotationPoint->removeAllChildrenWithCleanup(true);
    clockwiseObstacleRotationPoint->removeAllChildrenWithCleanup(true);
    antiClockwiseObstacleRotationPoint->removeAllChildrenWithCleanup(true);
    
    this->removeAllChildrenWithCleanup(true);
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    //_eventDispatcher->removeAllEventListeners();
    _eventDispatcher->removeAllEventListeners();
    this->unscheduleUpdate();
}

//function updates every frame
void GameScene::update(float dt){
 Point snakePosition1 = rotationPoint->convertToWorldSpace(ball->getPosition());
    int clockwiseRotationValue = (360-(int)(clockwiseObstacleRotationPoint->getRotation()) % 360);
    int antiClockwiseRotationValue = (360-(int)(antiClockwiseObstacleRotationPoint->getRotation()) % 360);
    clockwiseRotationValue=clockwiseRotationValue==360?0:clockwiseRotationValue;
    antiClockwiseRotationValue=antiClockwiseRotationValue==360?0:antiClockwiseRotationValue;
    int rotationValue=0;
  //  CCLOG("%d",360-(int)(clockwiseObstacleRotationPoint->getRotation()) % 360);
//CCLOG("Position=%f,%f",snakePosition1.x,snakePosition1.y);
if(controlable==1){
  for(int i=0;i<obstacleCount;i++)
   {              // CCLOG("Distance=%f",distance);
         if(obstacles[i].ringNum*rIncrement==distance || obstacles[i].ringNum*rIncrement+rIncrement==distance)
           {
                      Point snakePosition = rotationPoint->convertToWorldSpace(ball->getPosition());
               if(ringSpin[obstacles[i].ringNum] == 1)
                   rotationValue=antiClockwiseRotationValue;
               else
                   rotationValue=clockwiseRotationValue;
 		        //Size visibleSize = Director::getInstance()->getVisibleSize();
               // Vec2 origin = Director::getInstance()->getVisibleOrigin();
                int originY=visibleSize.height/2+origin.y;
                int snakeY=snakePosition.y;
                int curTheta = (int)((acos((float)(snakePosition.x-rotationPoint->getPosition().x)/(float)distance))*180/M_PI);

                  if(snakeY<originY)
                           curTheta=360-curTheta;
                    //  CCLOG("Distance=%f, Theta=%f",distance,curTheta*180/M_PI);
                     // float thetaone=levels[levelNo].blocks[i].theta1*180/M_PI;
		     // float thetatwo=levels[levelNo].blocks[i].theta2*180/M_PI;
		     // CCLOG("Bottom,Top: %f, %f",thetaone,thetatwo);
               int lower =((int)((obstacles[i].theta1)+rotationValue)) % 360;
               int upper =((int)((obstacles[i].theta2)+rotationValue)) % 360;
		 if((lower < upper && curTheta>=lower && curTheta<=upper) || (lower>=upper && ((curTheta>=lower && curTheta<=360) || curTheta<=upper)))       // check is collision occurs
                 {
                             controlable=0;
                         int diff= rMax - distance;
                             distance=rMax;
      auto rotateBy = RotateBy::create(0.25f,0);
      rotationPoint->runAction(RepeatForever::create(rotateBy));

           //CCLOG("Cor=%f,%f",snake[0]->getPosition().x,snake[0]->getPosition().y);
                     
                     bool soundsOn = UserDefault::getInstance()->getBoolForKey("SoundsOn",true);
                     if(soundsOn)
                     {

                         CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/collision.mp3");
                         CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/collision.mp3");
                     }
                     ball->runAction(Sequence::create(MoveTo::create(ballTime*2,Vec2(ball->getPosition().x+diff,ball->getPosition().y)),CallFunc::create(CC_CALLBACK_0(GameScene::actionComplete,this)),NULL));
                           break;
                 }
           }
   }

  }
    
}


std::string GameScene::getTimeText(int minCount, int secCount)
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

void GameScene::changeObstacleDirection(float dt)
{
    auto antiClockwiseAction = antiClockwiseObstacleRotationPoint->getActionByTag(0)->clone();
    antiClockwiseAction->setTag(0);
    auto clockwiseAction = clockwiseObstacleRotationPoint->getActionByTag(0)->clone();
    clockwiseAction->setTag(0);
    clockwiseObstacleRotationPoint->stopAllActions();
    antiClockwiseObstacleRotationPoint->stopAllActions();
    clockwiseObstacleRotationPoint->runAction(antiClockwiseAction);
    antiClockwiseObstacleRotationPoint->runAction(clockwiseAction);
}

void GameScene::saveScores()
{
    char minKey[15],secKey[15];
    sprintf(minKey, "BestMinKey%d",levelNo);
    sprintf(secKey, "BestSecKey%d",levelNo);
    int bestMin = UserDefault::getInstance()->getIntegerForKey(minKey,-1);
    
    int bestSec = UserDefault::getInstance()->getIntegerForKey(secKey,-1);
    
    if(bestMin==-1 || bestSec==-1)
    {
        UserDefault::getInstance()->setIntegerForKey(minKey, minuteCount);
        UserDefault::getInstance()->setIntegerForKey(secKey, secondCount);
    }
    else
        if(minuteCount<bestMin)
        {
            UserDefault::getInstance()->setIntegerForKey(minKey, minuteCount);
            UserDefault::getInstance()->setIntegerForKey(secKey, secondCount);
        }
        else
            if(minuteCount==bestMin && secondCount<bestSec)
            {
                UserDefault::getInstance()->setIntegerForKey(minKey, minuteCount);
                UserDefault::getInstance()->setIntegerForKey(secKey, secondCount);
            }
    
    

}
