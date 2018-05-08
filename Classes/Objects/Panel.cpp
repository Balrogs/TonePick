//
// Created by igor on 15.03.18.
//

#include "Panel.h"

const int THRESHOLD = 51;

Panel *Panel::create(Size blockSize, int blocksCount, Color4F colorStart, Color4F colorEnd, int id) {
    Panel *ret = new(std::nothrow) Panel();
    if (ret && ret->init(blockSize, blocksCount, colorStart, colorEnd, id)) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool Panel::init(Size blockSize, int blocksCount, Color4F colorStart, Color4F colorEnd, int id) {
    if(!Node::init()){
        return false;
    }

    _id = id;
    _blockSize = blockSize;

    auto diff = Vec3(
            (colorEnd.r - colorStart.r) / blocksCount,
            (colorEnd.g - colorStart.g) / blocksCount,
            (colorEnd.b - colorStart.b) / blocksCount
    );

    for(int i = 1; i < blocksCount - 1; i++) {
        auto block = _createById(i, false, colorStart, diff);

        this->addChild(block);
        _blocks.push_back(block);
    }

    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(_blocks), std::end(_blocks), rng);

    auto first = _createById(0, true, colorStart, diff);

    this->addChild(first);

    auto last = _createById(blocksCount - 1, true, colorStart, diff);

    this->addChild(last);

    _blocks.insert(_blocks.begin(), first);
    _blocks.insert(_blocks.end(), last);


    for(int i = 0; i < blocksCount; i ++){
        auto color = Color4F(
                (float) colorStart.r + diff.x * i,
                (float) colorStart.g + diff.y * i,
                (float) colorStart.b + diff.z * i,
                1.f
        );
        _expected.push_back(color);
    }

    _boundingBox = Rect(Vec2::ZERO, Size(_blockSize.width * blocksCount, _blockSize.height));

    return true;
}

void Panel::appear() {
    for(auto block: _blocks){
        block->appear();
    }
}

int Panel::countEquality() {
    int blocksCount = (int) _blocks.size();
    double counter = 0;
    for(int i = 1; i < blocksCount - 1; i++){
        if(_blocks[i] != nullptr && _blocks[i]->getColor().equals(_expected[i])){
            counter++;
        }
    }
    return (int) (counter / (blocksCount - 2) * 100);
}

int Panel::getId() {
    return _id;
}

GameBlock *Panel::checkTouch(Vec2 pos) {
    for(auto child : this->getChildren()){
        auto block = dynamic_cast<GameBlock*>(child);
        if(block == nullptr){
            continue;
        }
        auto point = new Vec3(pos.x, pos.y, 0);
        this->getWorldToNodeTransform().transformPoint(point);

        if(block->getBoundingBox().containsPoint(Vec2(point->x, point->y))){
            return block;
        }
    }
    return nullptr;
}

GameBlock *Panel::_createById(int id, bool isStatic, Color4F colorStart, Vec3 diff) {
    auto color = Color4F(
            (float) colorStart.r + diff.x * id,
            (float) colorStart.g + diff.y * id,
            (float) colorStart.b + diff.z * id,
            1.f
    );

    auto block = GameBlock::create(_blockSize, color, id, _id, isStatic);

    auto pos = Vec2(id * _blockSize.width, 0);
    block->setPosition(pos);

    return block;
}


void Panel::move(GameBlock *block, float delta) {
    if(block->getPositionX() + delta < _blockSize.width || block->getPositionX() + delta > (_blocks.size() - 2) * _blockSize.width){
        return;
    }

    block->setPositionX(block->getPositionX() + delta);

    for(auto b : _blocks) {
        if(b == block || b->isMoving()) continue;

        auto diff = b->getPositionX() - block->getPositionX();
        if(fabs(diff) > _blockSize.width) continue;
        auto fact = fabs(diff) / _blockSize.width * 100;
        CCLOG("FACT %f", fact);
        if(fact < THRESHOLD){
            CCLOG("INTERSECTION");
            auto offset = _blockSize.width;
            if(diff > 0){
                offset = -offset;
            }

            setBlockPosition(b, b->getPositionX() + offset);
            break;
        }
    }
}

void Panel::setBlockPosition(GameBlock *block, float x) {
    CCLOG("SET POS %f", x);

    block->setMoving(true);

    block->runAction(Sequence::create(
                        Spawn::create(
                        //  ScaleTo::create(.2f, 1.f),
                            MoveTo::create(.2f, Vec2(x, 0)),
                            NULL),
                        CallFunc::create([&, block]{
                            block->setMoving(false);
                        }),
                        NULL
    ));
}

void Panel::setBlockPosition(GameBlock *block) {
    auto pos = block->getPositionX();

    pos = roundf(pos / _blockSize.width) * _blockSize.width;

    setBlockPosition(block, pos);
}



