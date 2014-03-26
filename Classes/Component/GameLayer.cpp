#include "GameLayer.h"
#include "Dot.h"
#include "../Core/Random.h"

USING_NS_CC;

bool GameLayer::init() {
    if ( !Layer::init() )
    {
        return false;
    }

    resetDots();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    scoreTxt = LabelBMFont::create("Score: 0", "font/font.fnt");
    scoreTxt->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
    scoreTxt->setPosition(origin + Point(10, visibleSize.height - 10));
    addChild(scoreTxt);
    
    gameOverTxt = LabelBMFont::create("GAME OVER", "font/font.fnt");
    gameOverTxt->setPosition(origin + Point(visibleSize.width / 2, visibleSize.height / 2));
    gameOverTxt->setScale(2);
    gameOverTxt->setVisible(false);
    addChild(gameOverTxt);
    
    tutorialTxt = LabelBMFont::create("Choose the right dot\nand remember the sequence.", "font/font.fnt");
    tutorialTxt->setAlignment(TextHAlignment::CENTER);
    tutorialTxt->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    tutorialTxt->setPosition(origin + Point(visibleSize.width / 2, 10));
    tutorialTxt->setScale(0.5);
    addChild(tutorialTxt);
    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void GameLayer::resetDots() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    if (!dots) {
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

        dots = new Dot*[3];
        for (int i = 0; i < 3; i++) {
            auto dot = Dot::create(origin + Point(visibleSize.width / 2 + (Dot::RADIUS * 2 + 10) * (i - 1), visibleSize.height / 2), colors[i]);
            addChild(dot);
            _eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), dot);
            dots[i] = dot;
        }
    }
    
    Color4F currentColors[3];
    for (int i = 0; i < 3; i++) {
        currentColors[i] = colors[i];
        int j = floor(Random::get() * (i + 1));
        
        if (i != j) {
            Color4F temp = colors[i];
            colors[i] = colors[j];
            colors[j] = temp;
        }
    }
    for (int i = 0; i < 3; i++) {
        dots[i]->runAction(Sequence::create(
                                            CallFuncN::create(std::bind(&GameLayer::setDotEnabled, this, std::placeholders::_1, false)),
                                            DelayTime::create(0.15 * i),
                                            MoveBy::create(0.2, Point(0, 30)),
                                            CallFuncN::create(std::bind(&GameLayer::changeDotStatus, this, std::placeholders::_1, currentColors[i], colors[i])),
                                            MoveBy::create(0.2, Point(0, -30)),
                                            CallFuncN::create(std::bind(&GameLayer::setDotEnabled, this, std::placeholders::_1, true)),
                                            NULL)
                           );
    }
}

void GameLayer::setDotEnabled(Node* dot, bool value) {
    ((Dot*)dot)->setEnabled(value);
}

void GameLayer::changeDotStatus(Node* dot, Color4F color, Color4F nextColor) {
    ((Dot*)dot)->setColor(color);
    ((Dot*)dot)->setRight(nextColor == Color4F::GREEN);
}

void GameLayer::gameOver() {
    log("GAME OVER");
    
    gameOverTxt->setVisible(true);
    tutorialTxt->setVisible(true);
    tutorialTxt->setString("Tap to retry.");
    for (int i = 0; i < 3; ++i) {
        dots[i]->setVisible(false);
    }
    
    isOver = true;
}

void GameLayer::resetGame() {
    unsigned int seeds[] = {123456789, 362436069, 521288629, 88675123};
    Random::setSeeds(seeds);

    colors[0] = Color4F::RED;
    colors[1] = Color4F::GREEN;
    colors[2] = Color4F::BLUE;
    
    gameOverTxt->setVisible(false);
    for (int i = 0; i < 3; ++i) {
        dots[i]->setVisible(true);
    }

    resetDots();
    
    score = 0;
    scoreTxt->setString("Score: 0");

    tutorialTxt->setVisible(true);
    tutorialTxt->setString("Choose the right dot\nand remember the sequence.");
    
    isOver = false;
}

void GameLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    log("onKeyReleased %d %d", keyCode, EventKeyboard::KeyCode::KEY_BACKSPACE);
    if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE) {
        Director::getInstance()->end();
    }
}

bool GameLayer::onTouchBegan(Touch* touch, Event* event) {
    log("onTouchBegan");

    isMoved = false;

    if (isOver) {
        return true;
    }
    
    auto target = static_cast<Dot*>(event->getCurrentTarget());
    Point locationInNode = target->convertToNodeSpace(touch->getLocation());
    if (target->isOver(locationInNode))
    {
        log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
        target->setScale(0.9);
        return true;
    }
    return false;
}

void GameLayer::onTouchMoved(Touch* touch, Event* event) {
    log("onTouchMoved");

    auto target = static_cast<Dot*>(event->getCurrentTarget());
    Point locationInNode = target->convertToNodeSpace(touch->getLocation());
    if (target->isOver(locationInNode)) {
        target->setScale(0.9);
    }
    else {
        target->setScale(1);
    }

    isMoved = true;
}

void GameLayer::onTouchEnded(Touch* touch, Event* event) {
    log("onTouchEnded");

    if (isOver) {
        resetGame();
        return;
    }

    auto target = static_cast<Dot*>(event->getCurrentTarget());
    target->setScale(1);
    Point locationInNode = target->convertToNodeSpace(touch->getLocation());
    if (target->isOver(locationInNode)) {
        if (target->isRight()) {
            scoreTxt->setString(StringUtils::format("Score: %d", ++score));
            tutorialTxt->setVisible(false);

            resetDots();
        }
        else {
            gameOver();
        }
    }
}
