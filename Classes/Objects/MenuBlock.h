#ifndef TONEPICK_BASICBLOCK_H
#define TONEPICK_BASICBLOCK_H

#include "cocos2d.h"
#include "BaseBlock.h"

USING_NS_CC;

class MenuBlock: public BaseBlock {
public:
    static MenuBlock* create(Size size, Color4F color);
    static MenuBlock* create(Size size, Color4F color, bool isBreakable);
    bool init(Size size, Color4F color);
    bool init(Size size, Color4F color, bool isBreakable);

    void paint(Color4F color);

protected:
    bool _isBreakable;
    virtual Node* _stencil();

    void _show(bool isVisible);
};


#endif //TONEPICK_BASICBLOCK_H
