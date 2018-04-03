#ifndef TONEPICK_GAMEBLOCK_H
#define TONEPICK_GAMEBLOCK_H

#include "cocos2d.h"
#include "BaseBlock.h"

USING_NS_CC;

class GameBlock: public BaseBlock {
public:
    static GameBlock* create(Size size, Color4F color);
    static GameBlock* create(Size size, Color4F color, bool isStatic);
    bool init(Size size, Color4F color);
    bool init(Size size, Color4F color, bool isStatic);

protected:
    bool _isStatic;
    virtual Node* _stencil();

    void _show(bool isVisible);
};



#endif //TONEPICK_GAMEBLOCK_H
