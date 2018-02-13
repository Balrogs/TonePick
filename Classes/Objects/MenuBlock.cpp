//
// Created by igor on 24.01.18.
//

#include "MenuBlock.h"

enum {
    kTagStencilNode = 100,
    kTagClipperNode = 101,
    kTagShapeNode = 102,
    kTagStencilTop = 103,
    kTagStencilLeft = 104,
    kTagStencilBottom = 105,
    kTagStencilRight = 106,
};

MenuBlock *MenuBlock::create(Size size, Color4F color) {
    return create(size, color, true);
}

bool MenuBlock::init(Size size, Color4F color) {
    return init(size, color, true);
}


MenuBlock *MenuBlock::create(Size size, Color4F color, bool isBreakable) {
    MenuBlock *ret = new(std::nothrow) MenuBlock();
    if (ret && ret->init(size, color, isBreakable)) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool MenuBlock::init(Size size, Color4F color, bool isBreakable) {
    if(!Node::init()){
        return false;
    }
    _isBreakable = isBreakable;
    _size = size;
    _color = color;


    auto stencil = this->_stencil();
    stencil->setTag( kTagStencilNode );

    auto clipper = this->_clipper();
    clipper->setTag( kTagClipperNode );
    clipper->setStencil(stencil);
    this->addChild(clipper);

    auto shape = this->_shape();
    shape->setTag( kTagShapeNode );
    clipper->addChild(shape);

    return true;
}


Node *MenuBlock::_stencil() {
    auto stencil = Node::create();
    static Color4F green(0, 1, 0, 1);

    auto margin = _size.width * .1f;

    auto bottom = DrawNode::create();
    bottom->setTag(kTagStencilBottom);
    static Vec2 triangle[3];
    triangle[0] = Vec2(margin / 2, margin / 4);
    triangle[1] = Vec2(_size.width / 2, _size.height / 2 - margin / 4);
    triangle[2] = Vec2(_size.width - margin / 2, margin / 4);

    bottom->drawPolygon(triangle, 3, green, 0, green);
    stencil->addChild(bottom);
    bottom->setScale(0);

    auto left = DrawNode::create();
    left->setTag(kTagStencilLeft);
    triangle[0] = Vec2(margin / 4, margin / 2);
    triangle[1] = Vec2(_size.width / 2 - margin / 4, _size.height / 2);
    triangle[2] = Vec2(margin / 4, _size.height - margin / 2);

    left->drawPolygon(triangle, 3, green, 0, green);
    stencil->addChild(left);
    left->setScale(0);

    auto top = DrawNode::create();
    top->setTag(kTagStencilTop);
    triangle[0] = Vec2(margin / 2, _size.height - margin / 4);
    triangle[1] = Vec2(_size.width / 2, _size.height / 2 + margin / 4);
    triangle[2] = Vec2(_size.width  - margin / 2, _size.height - margin / 4);

    top->drawPolygon(triangle, 3, green, 0, green);
    stencil->addChild(top);
    top->setScale(0);

    auto right = DrawNode::create();
    right->setTag(kTagStencilRight);
    triangle[0] = Vec2(_size.width - margin / 4, margin / 2);
    triangle[1] = Vec2(_size.width / 2 + margin / 4, _size.height / 2);
    triangle[2] = Vec2(_size.width - margin / 4, _size.height - margin / 2);

    right->drawPolygon(triangle, 3, green, 0, green);
    stencil->addChild(right);
    right->setScale(0);

    return stencil;
}

Node *MenuBlock::_shape() {
    DrawNode* dn = DrawNode::create();
    dn->drawSolidRect(Vec2::ZERO, Vec2(_size.width, _size.height), _color);
    return dn;
}

ClippingNode *MenuBlock::_clipper() {
    return ClippingNode::create();
}

void MenuBlock::paint(Color4F color) {
    auto drawNode = dynamic_cast<DrawNode *> (this->getChildByTag(kTagClipperNode)->getChildByTag(kTagShapeNode));
    drawNode->clear();
    drawNode->drawSolidRect(Vec2::ZERO, Vec2(_size.width, _size.height), color);
}

void MenuBlock::appear() {
    _show(true);
}

void MenuBlock::hide() {
    if(_isBreakable)
        _show(false);
}


void MenuBlock::_show(bool isVisible) {
    float scale = 1.f;

    if(!isVisible){
        scale = 0.f;
    }
    float timeDelay = .4f;

    auto stencil = dynamic_cast<ClippingNode *> (this->getChildByTag(kTagClipperNode))->getStencil();
    auto delay = DelayTime::create(0.05f);

    this->runAction(Sequence::create(
            CallFunc::create([&, stencil, scale, timeDelay]{
                stencil->getChildByTag(kTagStencilLeft)->runAction(ScaleTo::create(timeDelay, scale));
            }),
            delay,
            CallFunc::create([&, stencil, scale, timeDelay]{
                stencil->getChildByTag(kTagStencilBottom)->runAction(ScaleTo::create(timeDelay, scale) );
            }),
            delay,
            CallFunc::create([&, stencil, scale, timeDelay]{
                stencil->getChildByTag(kTagStencilTop)->runAction(ScaleTo::create(timeDelay, scale));
            }),
            delay,
            CallFunc::create([&, stencil, scale, timeDelay]{
                stencil->getChildByTag(kTagStencilRight)->runAction(ScaleTo::create(timeDelay, scale));
            }),
            NULL
    ));
}

Rect MenuBlock::getBoundingBox() const {
    Rect rect(this->getPosition().x, this->getPosition().y, _size.width, _size.height);
    return rect;
}
