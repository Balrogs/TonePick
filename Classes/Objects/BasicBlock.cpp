//
// Created by igor on 24.01.18.
//

#include "BasicBlock.h"

enum {
    kTagStencilNode = 100,
    kTagClipperNode = 101,
    kTagShapeNode = 102,
    kTagStencilTop = 103,
    kTagStencilLeft = 104,
    kTagStencilBottom = 105,
    kTagStencilRight = 106,
};

BasicBlock *BasicBlock::create(Size size, Color4F color) {
    BasicBlock *ret = new(std::nothrow) BasicBlock();
    if (ret && ret->init(size, color)) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool BasicBlock::init(Size size, Color4F color) {
    if(!Node::init()){
        return false;
    }
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

Node *BasicBlock::_stencil() {
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
    bottom->setVisible(false);

    auto left = DrawNode::create();
    left->setTag(kTagStencilLeft);
    triangle[0] = Vec2(margin / 4, margin / 2);
    triangle[1] = Vec2(_size.width / 2 - margin / 4, _size.height / 2);
    triangle[2] = Vec2(margin / 4, _size.height - margin / 2);

    left->drawPolygon(triangle, 3, green, 0, green);
    stencil->addChild(left);
    left->setVisible(false);

    auto top = DrawNode::create();
    top->setTag(kTagStencilTop);
    triangle[0] = Vec2(margin / 2, _size.height - margin / 4);
    triangle[1] = Vec2(_size.width / 2, _size.height / 2 + margin / 4);
    triangle[2] = Vec2(_size.width  - margin / 2, _size.height - margin / 4);

    top->drawPolygon(triangle, 3, green, 0, green);
    stencil->addChild(top);
    top->setVisible(false);

    auto right = DrawNode::create();
    right->setTag(kTagStencilRight);
    triangle[0] = Vec2(_size.width - margin / 4, margin / 2);
    triangle[1] = Vec2(_size.width / 2 + margin / 4, _size.height / 2);
    triangle[2] = Vec2(_size.width - margin / 4, _size.height - margin / 2);

    right->drawPolygon(triangle, 3, green, 0, green);
    stencil->addChild(right);
    right->setVisible(false);

    return stencil;
}

Node *BasicBlock::_shape() {
    DrawNode* dn = DrawNode::create();
    dn->drawSolidRect(Vec2::ZERO, Vec2(_size.width, _size.height), _color);
    return dn;
}

ClippingNode *BasicBlock::_clipper() {
    return ClippingNode::create();
}

void BasicBlock::paint(Color4F color) {
    auto drawNode = dynamic_cast<DrawNode *> (this->getChildByTag(kTagClipperNode)->getChildByTag(kTagShapeNode));
    drawNode->clear();
    drawNode->drawSolidRect(Vec2::ZERO, Vec2(_size.width, _size.height), color);
}

void BasicBlock::appear() {
    _show(true);
}

void BasicBlock::_show(bool isVisible) {
    auto stencil = dynamic_cast<ClippingNode *> (this->getChildByTag(kTagClipperNode))->getStencil();
    auto delay = DelayTime::create(0.05f);
    this->runAction(Sequence::create(
            CallFunc::create([&, stencil, isVisible]{
                stencil->getChildByTag(kTagStencilLeft)->setVisible(isVisible);
            }),
            delay,
            CallFunc::create([&, stencil, isVisible]{
                stencil->getChildByTag(kTagStencilBottom)->setVisible(isVisible);
            }),
            delay,
            CallFunc::create([&, stencil, isVisible]{
                stencil->getChildByTag(kTagStencilTop)->setVisible(isVisible);
            }),
            delay,
            CallFunc::create([&, stencil, isVisible]{
                stencil->getChildByTag(kTagStencilRight)->setVisible(isVisible);
            }),
            NULL
    ));
}
