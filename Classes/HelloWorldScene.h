#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <vector>

#include "CSetAlgorithm.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
public:
    Layer* boardLayer;
    Size winSize;
    
    std::vector<cocos2d::Sprite*> mGrid;
    cocos2d::EventDispatcher* eventDispatcher;
    CSetGame* pSetGame;
    int* pBoardArray;
    int answerCount;
    int answerSheet[3];
    
    
public:
    void drawGrid(int* array);
    void addTileButtonEventListener();
    
};

#endif // __HELLOWORLD_SCENE_H__