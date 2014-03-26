#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene: public Scene
{
public:
    CREATE_FUNC(GameScene);

    virtual bool init();
};

#endif // __GAME_SCENE_H__
