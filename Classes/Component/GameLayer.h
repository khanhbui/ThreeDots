#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "Dot.h"

USING_NS_CC;

class GameLayer: public cocos2d::Layer
{
    Dot** dots;
    Color4F colors[3] = {Color4F::RED, Color4F::GREEN, Color4F::BLUE};
    LabelBMFont* scoreTxt;
    LabelBMFont* gameOverTxt;
    
    int score = 0;
    bool isOver = false;
    bool isMoved = false;
    
    bool isFirstTime = true;
    LabelBMFont* tutorialTxt;
    
    void resetDots();
    void gameOver();
    void resetGame();
    void setRight(Node* dot);
    
    void changeDotStatus(Node* dot,  Color4F color, Color4F nextColor);
    void setDotEnabled(Node* dot, bool value);
public:
    virtual bool init();

    virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);

	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(GameLayer);
};

#endif // __GAME_LAYER_H__
