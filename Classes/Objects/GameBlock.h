#ifndef TONEPICK_GAMEBLOCK_H
#define TONEPICK_GAMEBLOCK_H

#include "cocos2d.h"
#include "BaseBlock.h"

USING_NS_CC;

class GameBlock: public BaseBlock {
public:
    static GameBlock* create(Size size, Color4F color, int id, int panelId);
    static GameBlock* create(Size size, Color4F color, int id, int panelId, bool isStatic);
    bool init(Size size, Color4F color, int id, int panelId);
    bool init(Size size, Color4F color, int id, int panelId, bool isStatic);

    bool isStatic();

    bool isMoving();
    void setMoving(bool moving);

    Color4F getColor();

    int getId();
    int getPanelId();

protected:
    bool _isStatic;
    bool _isMoving;

    int _id;
    int _panelId;

    virtual Node* _stencil();

    void _show(bool isVisible);
};



#endif //TONEPICK_GAMEBLOCK_H
