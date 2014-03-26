//
//  Dot.cpp
//  ThreeDots
//
//  Created by Khanh Hoang Bui on 3/18/14.
//
//

#include "Dot.h"

USING_NS_CC;

const float Dot::RADIUS = 50.0;

Dot* Dot::create(Point pos, Color4F color) {
    auto ret = new Dot();
    ret->color = color;
    ret->setAnchorPoint(Point::ANCHOR_MIDDLE);
    ret->setPosition(pos);
    
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        ret = NULL;
        return NULL;
    }
}

bool Dot::init() {
    if (!DrawNode::init()) {
        return false;
    }
    
    setColor(color);
    
    return true;
}

void Dot::setColor(Color4F color) {
    drawDot(Point::ZERO, RADIUS, color);
}

bool Dot::isOver(Point touchPos) const {
    return enabled && sqrt(pow(touchPos.x, 2) + pow(touchPos.y, 2)) <= RADIUS;
}

void Dot::setRight(bool value) {
    right = value;
    if (right && false) {
        clear();
        this->setColor(Color4F::ORANGE);
    }
}

bool Dot::isRight() {
    return right;
}

void Dot::setEnabled(bool value) {
    enabled = value;
}
