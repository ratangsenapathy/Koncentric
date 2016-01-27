#include "GameScene.h"
#include "MainMenuScene.h"
#include "GameOverScene.h"
#include "Levels.h"
#define COCOS2D_DEBUG 1

USING_NS_CC;

float theta=0;
int r=0;
int levelNo=0;
int controlable=0;
int rMax=0;
Scene* GameScene::createScene(int level)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    controlable=0;
    r=0;
    theta=0;
    // 'layer' is an autorelease object
    levelNo=level;
    rMax=levels[levelNo].ringCount * 15;
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
    controlable=0;
    distance=rMax;
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
   
    goal = DrawNode::create();
    goal->drawDot(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y), 5, Color4F(100,0,0,1));
    this->addChild(goal,1);
   
    
    rotationPoint = Node::create();
    rotationPoint->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
    this->addChild(rotationPoint, 2);
    
    auto label = Label::createWithTTF("Exit","fonts/Marker Felt.ttf",10);
    exitButtonWidth=label->getContentSize().width;
    exitButtonHeight=label->getContentSize().height;
    label->setPosition(Point(visibleSize.width-exitButtonWidth,visibleSize.height-exitButtonHeight));
    this->addChild(label);
    

    fixedPoint = Node::create();
    fixedPoint->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
    this->addChild(fixedPoint, 3);    

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
       
    float theta=0;

    snake[0] = DrawNode::create();
    snake[0]->drawDot(Vec2(0,0),3,Color4F(100,0,0,1));
    theta+=2*M_PI/150;
    //this->addChild(snake[0],2);
    
    rotationPoint->addChild(snake[0]);
      // fixedPoint->addChild(snake[0]);
/*
    for(int i=1;i<21;i++)
    {   
       
        snake[i] = DrawNode::create();
        snake[i]->drawDot(Vec2(rMax*cos(theta),rMax*sin(theta)),2,Color4F(100,0,0,1));
        theta+=2*M_PI/150;
      //  this->addChild(snake[i],2);
        rotationPoint->addChild(snake[i]);
    }
    */
   
   for(r=15;r<=rMax;r+=15)
    {
      for(theta=0;theta<=2*M_PI;theta+=2*M_PI/r){
          pathNode = DrawNode::create();
          pathNode->drawDot(Vec2(r*cos(theta)+origin.x+visibleSize.width/2,r*sin(theta)+origin.y+visibleSize.height/2),1,Color4F(0,0,10,1));
           this->addChild(pathNode,1);
        }
    }

    
         
         for(int i=0;i<levels[levelNo].obstacleCount;i++)
	{   Point vertices[720]; int index=0;
                 int base=levels[levelNo].blocks[i].ring*15;

   
    for(theta=levels[levelNo].blocks[i].theta2;theta>=levels[levelNo].blocks[i].theta1;theta-=2*M_PI/(base+15)){
          
           vertices[index++]=ccp((base+15)*cos(theta),(base+15)*sin(theta));
          
        }
  for(theta=levels[levelNo].blocks[i].theta1;theta<=levels[levelNo].blocks[i].theta2;theta+=2*M_PI/(base!=0?base:15)){
          
           vertices[index++]=ccp(base*cos(theta),base*sin(theta));
          
        }
   
        
       DrawNode* polygon = DrawNode::create();

	polygon->drawPolygon(vertices,index, ccc4f(1, 1, 0, 1), 1, ccc4f(1, 1, 0, 1));
	fixedPoint->addChild(polygon);
	}
        
    snake[0]->runAction(Sequence::create(Place::create(Vec2(snake[0]->getPosition().x+rMax,snake[0]->getPosition().y)),CallFunc::create(CC_CALLBACK_0(GameScene::actionComplete,this)),NULL));

    distance=rMax;
   // auto rotateBy = RotateBy::create(0.25f,360/distance);
   // rotationPoint->runAction(RepeatForever::create(rotateBy));
    controlable=0;
    this->scheduleUpdate();
    return true;
}


bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
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
        distance-=15;
        auto rotateBy = RotateBy::create(0.25f,0);
        rotationPoint->runAction(RepeatForever::create(rotateBy));
        
        // CCLOG("Cor=%f,%f",snake[0]->getPosition().x,snake[0]->getPosition().y);
        snake[0]->runAction(Sequence::create(MoveTo::create(0.5,Vec2(snake[0]->getPosition().x-15,snake[0]->getPosition().y)),
                                             CallFunc::create(CC_CALLBACK_0(GameScene::actionComplete,this)),NULL));
        
        
    }
    return true;
}


void GameScene::actionComplete()
{
    if(distance==0)
    {   if(levelNo+1==LEVEL_COUNT)
    {   _eventDispatcher->removeAllEventListeners();
        auto scene = GameOverScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }else{
        _eventDispatcher->removeAllEventListeners();
        auto scene = GameScene::createScene(++levelNo);
        Director::getInstance()->replaceScene(scene);}
    }
         auto rotateBy = RotateBy::create(0.25f,360/distance);
    rotationPoint->runAction(RepeatForever::create(rotateBy));
controlable=1;
}

void GameScene::update(float dt){
 Point snakePosition1 = rotationPoint->convertToWorldSpace(snake[0]->getPosition());
//CCLOG("Position=%f,%f",snakePosition1.x,snakePosition1.y);
if(controlable==1){
  for(int i=0;i<levels[levelNo].obstacleCount;i++)
   {              // CCLOG("Distance=%f",distance);
         if(levels[levelNo].blocks[i].ring*15==distance || levels[levelNo].blocks[i].ring*15+15==distance)
           {
                      Point snakePosition = rotationPoint->convertToWorldSpace(snake[0]->getPosition());

 		Size visibleSize = Director::getInstance()->getVisibleSize();
                Vec2 origin = Director::getInstance()->getVisibleOrigin();
                int originY=visibleSize.height/2+origin.y;
                int snakeY=snakePosition.y;
                 float curTheta = acos((float)(snakePosition.x-rotationPoint->getPosition().x)/(float)distance);

                  if(snakeY<originY)
                           curTheta=2*M_PI-curTheta;
                    //  CCLOG("Distance=%f, Theta=%f",distance,curTheta*180/M_PI);
                     // float thetaone=levels[levelNo].blocks[i].theta1*180/M_PI;
		     // float thetatwo=levels[levelNo].blocks[i].theta2*180/M_PI;
		     // CCLOG("Bottom,Top: %f, %f",thetaone,thetatwo);
		 if(curTheta>=levels[levelNo].blocks[i].theta1 && curTheta<=levels[levelNo].blocks[i].theta2)
                 {
                             controlable=0;
                         int diff=rMax-distance;
                             distance=rMax;
  auto rotateBy = RotateBy::create(0.25f,0);
    rotationPoint->runAction(RepeatForever::create(rotateBy));

           //CCLOG("Cor=%f,%f",snake[0]->getPosition().x,snake[0]->getPosition().y);
                     snake[0]->runAction(Sequence::create(MoveTo::create(0.5,Vec2(snake[0]->getPosition().x+diff,snake[0]->getPosition().y)),CallFunc::create(CC_CALLBACK_0(GameScene::actionComplete,this)),NULL));
                           break;
                 }
           }
   }

  }
    
}
