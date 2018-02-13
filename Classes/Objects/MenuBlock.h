//
// Created by igor on 24.01.18.
//

#ifndef TONEPICK_BASICBLOCK_H
#define TONEPICK_BASICBLOCK_H

#include "cocos2d.h"

USING_NS_CC;

class MenuBlock: public Node {
public:
    static MenuBlock* create(Size size, Color4F color);
    static MenuBlock* create(Size size, Color4F color, bool isBreakable);
    bool init(Size size, Color4F color);
    bool init(Size size, Color4F color, bool isBreakable);

    void paint(Color4F color);
    void appear();
    void hide();
    bool isHidden();

    Rect getBoundingBox() const override;

protected:
    bool _isBreakable;
    bool _isHidden;
    Size _size;
    Color4F _color;
    virtual Node* _stencil();
    virtual Node* _shape();
    virtual ClippingNode* _clipper();

    void _show(bool isVisible);
};


#endif //TONEPICK_BASICBLOCK_H
