

#ifndef TONEPICK_PARENTLAYER_H
#define TONEPICK_PARENTLAYER_H


#include <cocos/2d/CCLayer.h>

class ParentLayer : public cocos2d::Layer {
public:
    virtual void onQuit() = 0;

protected:

    virtual void _enterFrameHandler(float passedTime) = 0;

    cocos2d::Size _visibleSize;
};

#endif //TONEPICK_PARENTLAYER_H
