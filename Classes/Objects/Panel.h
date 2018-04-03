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
    static Panel* create(Size blockSize, int blocksCount, Color4F colorStart, Color4F end);
    bool init(Size blockSize, int blocksCount, Color4F colorStart, Color4F end);

private:
    std::vector<GameBlock*> _blocks;
};


#endif //TONEPICK_PANEL_H
