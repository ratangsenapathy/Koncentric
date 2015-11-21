#include "GameScene.h"

#include "MainMenuScene.h"
#include "Levels.cpp"
#define COCOS2D_DEBUG 1

USING_NS_CC;

float theta=0;
int r=0;
int levelNo=0;
int controlable=1;
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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
   
    goal = DrawNode::create();
    goal->drawDot(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y), 5, Color4F(100,0,0,1));
    this->addChild(goal,1);
   
    
    rotationPoint = Node::create();
    rotationPoint->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
    this->addChild(rotationPoint, 2);
    
    
  

    fixedPoint = Node::create();
    fixedPoint->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
    this->addChild(fixedPoint, 3);    

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
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
        snake[i]->drawDot(Vec2(90*cos(theta),90*sin(theta)),2,Color4F(100,0,0,1));
        theta+=2*M_PI/150;
      //  this->addChild(snake[i],2);
        rotationPoint->addChild(snake[i]);
    }
    */
    
   for(r=15;r<=90;r+=15)
    {
      for(theta=0;theta<=2*M_PI;theta+=2*M_PI/r){
          pathNode = DrawNode::create();
          pathNode->drawDot(Vec2(r*cos(theta)+origin.x+visibleSize.width/2,r*sin(theta)+origin.y+visibleSize.height/2),1,Color4F(0,0,10,1));
           this->addChild(pathNode,1);
        }
    }

    
         
         for(int i=0;i<levels[levelNo].count;i++)
	{   CCPoint vertices[720]; int index=0;
                 int base=levels[levelNo].blocks[i].ring*15;

   
    for(theta=levels[levelNo].blocks[i].theta2;theta>=levels[levelNo].blocks[i].theta1;theta-=2*M_PI/(base+15)){
          
           vertices[index++]=ccp((base+15)*cos(theta),(base+15)*sin(theta));
          
        }
  for(theta=levels[levelNo].blocks[i].theta1;theta<=levels[levelNo].blocks[i].theta2;theta+=2*M_PI/(base!=0?base:15)){
          
           vertices[index++]=ccp(base*cos(theta),base*sin(theta));
          
        }
   
            CCLOG("Index=%d",index);
       CCDrawNode* polygon = CCDrawNode::create();

	polygon->drawPolygon(vertices,index, ccc4f(1, 1, 0, 1), 1, ccc4f(1, 1, 0, 1));
	fixedPoint->addChild(polygon);
	}
        
     snake[0]->runAction(CCSequence::create(MoveTo::create(0.5,Vec2(snake[0]->getPosition().x+90,snake[0]->getPosition().y)),
       CCCallFunc::create(this,callfunc_selector(GameScene::actionComplete)),NULL));

    distance=90;
    auto rotateBy = RotateBy::create(0.25f,360/distance);
    rotationPoint->runAction(RepeatForever::create(rotateBy));
    
    this->scheduleUpdate();
    return true;
}


void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event){
   
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event){
     if (keyCode == EventKeyboard::KeyCode::KEY_SPACE && controlable==1) {
          //rotationPoint->removeChild(snake[0]);
         // snake[0]->drawDot(Vec2(90*cos(theta),90*sin(theta)),3,Color4F(100,0,0,1));
         // fixedPoint->addChild(snake[0]);
         //r-=15; 
	controlable=0;
	distance-=15;
  auto rotateBy = RotateBy::create(0.25f,0);
    rotationPoint->runAction(RepeatForever::create(rotateBy));

          // CCLOG("Cor=%f,%f",snake[0]->getPosition().x,snake[0]->getPosition().y);
       snake[0]->runAction(CCSequence::create(MoveTo::create(0.5,Vec2(snake[0]->getPosition().x-15,snake[0]->getPosition().y)),
       CCCallFunc::create(this,callfunc_selector(GameScene::actionComplete)),NULL));


        
    }
}


void GameScene::actionComplete()
{
         auto rotateBy = RotateBy::create(0.25f,360/distance);
    rotationPoint->runAction(RepeatForever::create(rotateBy));
controlable=1;
}

void GameScene::update(float dt){
 Point snakePosition1 = rotationPoint->convertToWorldSpace(snake[0]->getPosition());
//CCLOG("Position=%f,%f",snakePosition1.x,snakePosition1.y);
if(controlable==1){
  for(int i=0;i<levels[levelNo].count;i++)
   {              // CCLOG("Distance=%f",distance);
         if(levels[levelNo].blocks[i].ring*15==distance || levels[levelNo].blocks[i].ring*15+15==distance)
           {
                      Point snakePosition = rotationPoint->convertToWorldSpace(snake[0]->getPosition());

 		Size visibleSize = Director::getInstance()->getVisibleSize();
                Vec2 origin = Director::getInstance()->getVisibleOrigin();
                int originX=visibleSize.width/2+origin.x;
                int originY=visibleSize.height/2+origin.y;
                int snakeX=snakePosition.x;
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
                         int diff=90-distance;
                             distance=90;
  auto rotateBy = RotateBy::create(0.25f,0);
    rotationPoint->runAction(RepeatForever::create(rotateBy));

           //CCLOG("Cor=%f,%f",snake[0]->getPosition().x,snake[0]->getPosition().y);
       snake[0]->runAction(CCSequence::create(MoveTo::create(0.5,Vec2(snake[0]->getPosition().x+diff,snake[0]->getPosition().y)),
       CCCallFunc::create(this,callfunc_selector(GameScene::actionComplete)),NULL));
                           break;
                 }
           }
   }

  }
    
}
