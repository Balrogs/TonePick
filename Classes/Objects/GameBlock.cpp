#include "GameBlock.h"

enum {
    kTagStencilNode = 100,
    kTagClipperNode = 101,
    kTagShapeNode = 102
};

GameBlock *GameBlock::create(Size size, Color4F color) {
    return create(size, color, false);
}

GameBlock *GameBlock::create(Size size, Color4F color, bool isStatic) {
    GameBlock *ret = new(std::nothrow) GameBlock();
    if (ret && ret->init(size, color, isStatic)) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool GameBlock::init(Size size, Color4F color) {
    return GameBlock::init(size, color, false);
}

bool GameBlock::init(Size size, Color4F color, bool isStatic) {
    if(!BaseBlock::init(size, color)){
        return false;
    }
    _isStatic = isStatic;

    return true;
}

Node *GameBlock::_stencil() {
    auto stencil = DrawNode::create();
    static Color4F green(0, 1, 0, 1);

    auto margin = _size.width * .1f;
    Vec2 origin = Vec2(margin / 2, margin / 4);
    Vec2 dest = Vec2(_size.width  - margin / 2, _size.height - margin / 4);

    stencil->drawSolidRect(origin, dest, green);
    stencil->setScale(0);

    return stencil;
}

void GameBlock::_show(bool isVisible) {
    float scale = 1.f;

    if(!isVisible){
        scale = 0.f;
    }

    auto stencil = dynamic_cast<ClippingNode *> (this->getChildByTag(kTagClipperNode))->getStencil();

    stencil->runAction(ScaleTo::create(.4f, scale));
}
