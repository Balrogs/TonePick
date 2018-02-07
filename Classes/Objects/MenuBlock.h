//
// Created by igor on 24.01.18.
//

#ifndef TONEPICK_BASICBLOCK_H
#define TONEPICK_BASICBLOCK_H

#include "cocos2d.h"

USING_NS_CC;

class BasicBlock: public Node {
public:
    static BasicBlock* create(Size size, Color4F color);
    static BasicBlock* create(Size size, Color4F color, bool isBreakable);
    bool init(Size size, Color4F color);
    bool init(Size size, Color4F color, bool isBreakable);

    void paint(Color4F color);
    void appear();
    void hide();

    Rect getBoundingBox() const override;

protected:
    bool _isBreakable;
    Size _size;
    Color4F _color;
    virtual Node* _stencil();
    virtual Node* _shape();
    virtual ClippingNode* _clipper();

    void _show(bool isVisible);
};


#endif //TONEPICK_BASICBLOCK_H