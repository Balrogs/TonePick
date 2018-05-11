//
// Created by igor on 15.03.18.
//

#ifndef TONEPICK_PANEL_H
#define TONEPICK_PANEL_H

#include "cocos2d.h"
#include "GameBlock.h"

USING_NS_CC;

class Panel: public Node {
public:
    static const int DEFAULT_LEVEL;
    static const int FOCUSED_BLOCK_LEVEL;
    static const float ACTION_TIME_INTERVAL;

    static Panel* create(Size blockSize, int blocksCount, Color4F colorStart, Color4F colorEnd, int id);
    bool init(Size blockSize, int blocksCount, Color4F colorStart, Color4F colorEnd, int id);

    void appear();

    int countEquality();

    int getId();

    GameBlock* checkTouch(Vec2 pos);

    void move(GameBlock* block, float delta);

    void setBlockPosition(GameBlock* block, float x);
    void setBlockPosition(GameBlock* block);

private:
    int _id;

    Size _blockSize;
    Rect _boundingBox;
    std::vector<GameBlock*> _blocks;

    GameBlock* _createById(int id, bool isStatic, Color4F colorStart, Vec3 diff);
};


#endif //TONEPICK_PANEL_H
