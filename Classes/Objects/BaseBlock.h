#ifndef TONEPICK_BASEBLOCK_H
#define TONEPICK_BASEBLOCK_H

#include "cocos2d.h"

USING_NS_CC;

class BaseBlock: public Node {
public:
    virtual bool init(Size size, Color4F color);

    void appear();
    void hide();

    Rect getBoundingBox() const override;

protected:
    Size _size;
    Color4F _color;
    virtual Node* _stencil() = 0;
    virtual Node* _shape();
    virtual ClippingNode* _clipper();

    virtual void _show(bool isVisible) = 0;
};


#endif //TONEPICK_BASEBLOCK_H
