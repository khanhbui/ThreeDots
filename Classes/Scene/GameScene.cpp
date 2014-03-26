#include "GameScene.h"
#include "../Component/GameLayer.h"

USING_NS_CC;

bool GameScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    
    auto layer = GameLayer::create();
    this->addChild(layer);
    
    return true;
}
