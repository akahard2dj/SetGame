#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    winSize = Director::getInstance()->getWinSize();
    
    eventDispatcher = _eventDispatcher;
    answerCount = 0;
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    // add a label shows "Hello World"
    // create and initialize a label
    
    boardLayer = Layer::create();
    boardLayer->setContentSize(Size(winSize.width, winSize.width));
    boardLayer->setPosition(Point(0, 200));
    
    this->addChild(boardLayer, 1);
    
    pSetGame = CSetGame::createSetGame(3, 3);
    pBoardArray = pSetGame->getBoard();
    
    while (!(pSetGame->isBoardSolution())) {
        pSetGame->shuffleBoard();
    }
    
    drawGrid(pBoardArray);
    
    
    return true;
}

void HelloWorld::drawGrid(int* array)
{
    Sprite* grid;
    int idx;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            idx = i * 3 + j;
            switch (array[idx]) {
                case 0:
                    grid = Sprite::create("00.png");
                    break;
                case 1:
                    grid = Sprite::create("01.png");
                    break;
                case 2:
                    grid = Sprite::create("02.png");
                    break;
                case 3:
                    grid = Sprite::create("03.png");
                    break;
                case 4:
                    grid = Sprite::create("04.png");
                    break;
                case 5:
                    grid = Sprite::create("05.png");
                    break;
                case 6:
                    grid = Sprite::create("06.png");
                    break;
                case 7:
                    grid = Sprite::create("07.png");
                    break;
                case 8:
                    grid = Sprite::create("08.png");
                    break;
                case 9:
                    grid = Sprite::create("09.png");
                    break;
                case 10:
                    grid = Sprite::create("10.png");
                    break;
                case 11:
                    grid = Sprite::create("11.png");
                    break;
                case 12:
                    grid = Sprite::create("12.png");
                    break;
                case 13:
                    grid = Sprite::create("13.png");
                    break;
                case 14:
                    grid = Sprite::create("14.png");
                    break;
                case 15:
                    grid = Sprite::create("15.png");
                    break;
                case 16:
                    grid = Sprite::create("16.png");
                    break;
                case 17:
                    grid = Sprite::create("17.png");
                    break;
                case 18:
                    grid = Sprite::create("18.png");
                    break;
                case 19:
                    grid = Sprite::create("19.png");
                    break;
                case 20:
                    grid = Sprite::create("20.png");
                    break;
                case 21:
                    grid = Sprite::create("21.png");
                    break;
                case 22:
                    grid = Sprite::create("22.png");
                    break;
                case 23:
                    grid = Sprite::create("23.png");
                    break;
                case 24:
                    grid = Sprite::create("24.png");
                    break;
                case 25:
                    grid = Sprite::create("25.png");
                    break;
                case 26:
                    grid = Sprite::create("26.png");
                    break;
                default:
                    break;
            }
            grid->setPosition(winSize.width / (3 + 1)*(j + 1), winSize.width / (3 + 1)*(i + 1));
            grid->setTag(array[idx]);
            boardLayer->addChild(grid, 2);
            mGrid.push_back(grid);
            
        }
        addTileButtonEventListener();
    }
}

void HelloWorld::addTileButtonEventListener()
{
    auto tileListener = EventListenerTouchOneByOne::create();
    tileListener->setSwallowTouches(true);
    
    tileListener->onTouchBegan = [=](Touch* touch, Event* event) {
        auto target = event->getCurrentTarget();
        int tagNum = target->getTag();
        
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        
        if (rect.containsPoint(locationInNode)) {			
            
            return true;
        }
        return false;
    };
    
    tileListener->onTouchEnded = [=](Touch* touch, Event* event) {
        auto target = event->getCurrentTarget();
        int tagNum = target->getTag();
        
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        
        if (rect.containsPoint(locationInNode)) {
            printf("selected tile : %d, answerCount : %d\n", tagNum, answerCount);
            answerSheet[answerCount] = tagNum;
            if (answerCount % 3 == 2 && answerCount != 0) {
                printf(">> %d %d %d\n", answerSheet[0], answerSheet[1], answerSheet[2]);
                bool isSet = pSetGame->isSet(answerSheet);
                if (isSet)
                    printf("Set!");
                else
                    printf("Failed");
            }
            
            answerCount = (answerCount + 1) % 3;
        }
        return;
    };
    
    for (int i = 0; i < mGrid.size(); i++) {
        eventDispatcher->addEventListenerWithSceneGraphPriority(tileListener->clone(), mGrid.at(i));
    }
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}