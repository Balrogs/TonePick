#include "BaseBlock.h"

enum {
    kTagStencilNode = 100,
    kTagClipperNode = 101,
    kTagShapeNode = 102
};

bool BaseBlock::init(Size size, Color4F color) {
    if(!Node::init()){
        return false;
    }
    _size = size;
    _color = color;

    auto stencil = this->_stencil();
    stencil->setTag(kTagStencilNode);

    auto clipper = this->_clipper();
    clipper->setTag(kTagClipperNode);
    clipper->setStencil(stencil);
    this->addChild(clipper);

    auto shape = this->_shape();
    shape->setTag(kTagShapeNode);
    clipper->addChild(shape);

    return true;
}

Node *BaseBlock::_shape() {
    DrawNode* dn = DrawNode::create();
    dn->drawSolidRect(Vec2::ZERO, Vec2(_size.width, _size.height), _color);
    return dn;
}

ClippingNode *BaseBlock::_clipper() {
    return ClippingNode::create();
}

void BaseBlock::appear() {
    _show(true);
}

void BaseBlock::hide() {
    _show(false);
}



Rect BaseBlock::getBoundingBox() const {
    Rect rect(this->getPosition().x, this->getPosition().y, _size.width, _size.height);
    return rect;
}

const Size &BaseBlock::getContentSize() const {
    return _size;
}