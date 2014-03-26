//
//  Dot.h
//  ThreeDots
//
//  Created by Khanh Hoang Bui on 3/18/14.
//
//

#ifndef __DOT_H__
#define __DOT_H__

#include "cocos2d.h"

USING_NS_CC;

class Dot: public DrawNode {
    Color4F color = Color4F::WHITE;
    bool right = false;
    bool enabled = true;

public:
    CREATE_FUNC(Dot);
    
    static const float RADIUS;
    static Dot* create(Point pos, Color4F color);
    virtual bool init();
    bool isOver(Point touchPos) const;
    void setRight(bool value);
    bool isRight();
    void setColor(Color4F color);
    void setEnabled(bool value);
};

#endif
