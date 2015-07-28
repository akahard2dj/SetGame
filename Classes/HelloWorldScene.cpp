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
										   CC_CALLBACK_1(HelloWorld::gameRefreshCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + visibleSize.height - closeItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto refreshItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",CC_CALLBACK_1(HelloWorld::gameRefreshCallback, this));

	refreshItem->setPosition(Vec2(origin.x + visibleSize.width - refreshItem->getContentSize().width / 2,
								  origin.y - visibleSize.height - refreshItem->getContentSize().height / 2));

	auto refMenu = Menu::create(refreshItem, NULL);
	refMenu->setPosition(Vec2::ZERO);
	this->addChild(refMenu, 1);
    

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
				grid = Sprite::create("black.png");
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
				if (isSet) {
					arrangeBoard(answerSheet);
					printf("Set!\n");
				}
				else {
					printf("Failed\n");
				}
			}

			answerCount = (answerCount + 1) % 3;
		}
		return;
	};

	for (int i = 0; i < mGrid.size(); i++) {
		eventDispatcher->addEventListenerWithSceneGraphPriority(tileListener->clone(), mGrid.at(i));
	}
}

void HelloWorld::arrangeBoard(int answerSheet[])
{
	std::vector<int> vStackValue1;
	std::vector<int> vStackValue2;
	std::vector<int> vStackValue3;

	std::vector<int> vStacknewValue1;
	std::vector<int> vStacknewValue2;
	std::vector<int> vStacknewValue3;

	int selectedIndex[3];

	for (int i = 0; i < 3; i++) {
		vStackValue1.push_back(pBoardArray[i * 3]);
		vStackValue2.push_back(pBoardArray[i * 3 + 1]);
		vStackValue3.push_back(pBoardArray[i * 3 + 2]);
	}

	for (int i = 0; i < 3; i++) {
		int value = answerSheet[i];
		for (int j = 0; j < mGrid.size(); j++) {
			if (mGrid.at(j)->getTag() == value) {
				selectedIndex[i] = j;
				break;
			}
		}
		mGrid.at(selectedIndex[i])->setTexture("black.png");
	}
	
	for (int i = 0; i < 3; i++) {
		int remainder = selectedIndex[i] % 3;
		switch (remainder) {
		case 0:
			vStackValue1[selectedIndex[i] / 3] = -1;
			break;
		case 1:
			vStackValue2[selectedIndex[i] / 3] = -1;
			break;
		case 2:
			vStackValue3[selectedIndex[i] / 3] = -1;
			break;
		default:
			break;
		}
	}

	printf(">> ArrangeBoard : \n");
	for (int i = 0; i < 3; i++) {

		printf(" %d %d %d\n", vStackValue1[i], vStackValue2[i], vStackValue3[i]);
	}

	vStackValue1.erase(std::remove(vStackValue1.begin(), vStackValue1.end(), -1), vStackValue1.end());
	vStackValue2.erase(std::remove(vStackValue2.begin(), vStackValue2.end(), -1), vStackValue2.end());
	vStackValue3.erase(std::remove(vStackValue3.begin(), vStackValue3.end(), -1), vStackValue3.end());

	for (int i = 0; i < 3; i++) {
		vStacknewValue1.push_back(-1);
		vStacknewValue2.push_back(-1);
		vStacknewValue3.push_back(-1);
	}

	for (int i = 0; i < vStackValue1.size(); i++) {
		vStacknewValue1[i] = vStackValue1[i];
	}

	for (int i = 0; i < vStackValue2.size(); i++) {
		vStacknewValue2[i] = vStackValue2[i];
	}

	for (int i = 0; i < vStackValue3.size(); i++) {
		vStacknewValue3[i] = vStackValue3[i];
	}

	printf(">> ArrangeBoard : \n");
	for (int i = 0; i < 3; i++) {
		
		printf(" %d %d %d\n", vStacknewValue1[i], vStacknewValue2[i], vStacknewValue3[i]);
	}

	for (int i = 0; i < vStacknewValue1.size(); i++) {
		pBoardArray[i * 3] = vStacknewValue1[i];
	}

	for (int i = 0; i < vStacknewValue2.size(); i++) {
		pBoardArray[i * 3 + 1] = vStacknewValue2[i];
	}

	for (int i = 0; i < vStacknewValue3.size(); i++) {
		pBoardArray[i * 3 + 2] = vStacknewValue3[i];
	}

	pSetGame->setBoard(pBoardArray);
	pSetGame->redesignBoard();
	

	bool check = pSetGame->isBoardSolution();
	
	

	//while (!(pSetGame->isBoardSolution())) {
	//	pSetGame->shuffleBoard();
	//}

	refreshGrid(pBoardArray);
}

void HelloWorld::refreshGrid(int* array)
{
	//mGrid.at(idx)->setTexture("black.png");
	int idx;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			idx = i * 3 + j;
			switch (array[idx]) {
			case 0:
				mGrid.at(idx)->setTexture("00.png");				
				break;
			case 1:
				mGrid.at(idx)->setTexture("01.png");
				break;
			case 2:
				mGrid.at(idx)->setTexture("02.png");
				break;
			case 3:
				mGrid.at(idx)->setTexture("03.png");
				break;
			case 4:
				mGrid.at(idx)->setTexture("04.png");
				break;
			case 5:
				mGrid.at(idx)->setTexture("05.png");
				break;
			case 6:
				mGrid.at(idx)->setTexture("06.png");
				break;
			case 7:
				mGrid.at(idx)->setTexture("07.png");
				break;
			case 8:
				mGrid.at(idx)->setTexture("08.png");
				break;
			case 9:
				mGrid.at(idx)->setTexture("09.png");
				break;
			case 10:
				mGrid.at(idx)->setTexture("10.png");
				break;
			case 11:
				mGrid.at(idx)->setTexture("11.png");
				break;
			case 12:
				mGrid.at(idx)->setTexture("12.png");
				break;
			case 13:
				mGrid.at(idx)->setTexture("13.png");
				break;
			case 14:
				mGrid.at(idx)->setTexture("14.png");
				break;
			case 15:
				mGrid.at(idx)->setTexture("15.png");
				break;
			case 16:
				mGrid.at(idx)->setTexture("16.png");
				break;
			case 17:
				mGrid.at(idx)->setTexture("17.png");
				break;
			case 18:
				mGrid.at(idx)->setTexture("18.png");
				break;
			case 19:
				mGrid.at(idx)->setTexture("19.png");
				break;
			case 20:
				mGrid.at(idx)->setTexture("20.png");
				break;
			case 21:
				mGrid.at(idx)->setTexture("21.png");
				break;
			case 22:
				mGrid.at(idx)->setTexture("22.png");
				break;
			case 23:
				mGrid.at(idx)->setTexture("23.png");
				break;
			case 24:
				mGrid.at(idx)->setTexture("24.png");
				break;
			case 25:
				mGrid.at(idx)->setTexture("25.png");
				break;
			case 26:
				mGrid.at(idx)->setTexture("26.png");
				break;
			default:
				mGrid.at(idx)->setTexture("black.png");
				break;
			}
			mGrid.at(idx)->setTag(array[idx]);
		}
	}
}

void HelloWorld::gameRefreshCallback(Ref* pSender)
{
	pSetGame->shuffleBoard();	

	while (!(pSetGame->isBoardSolution())) {
		pSetGame->shuffleBoard();
	}

	pBoardArray = pSetGame->getBoard();

	refreshGrid(pBoardArray);
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
