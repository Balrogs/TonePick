#ifndef TONEPICK_GAMESCENE_H
#define TONEPICK_GAMESCENE_H

#include "cocos2d.h"
#include <Objects/GameBlock.h>
#include <Global/Utils.h>
#include <Objects/Panel.h>

USING_NS_CC;

class GameScene: public cocos2d::Scene {
public:
    static GameScene *createScene(int type);

    static GameScene* getInstance();

    bool isPaused();

    void pauseScene();

    void unPause();

    void onQuit();

protected:

    std::vector<Panel*> _panels;
    GameBlock* _focused;

    Size _visibleSize;
    bool _isPaused;
    static GameScene *_instance;
    //disable multitouch variable
    int _touch;

    bool init(int type);

    bool _touchHandlerBegin(const Touch *touch, Event *event);

    bool _touchHandlerMove(const Touch *touch, Event *event);

    bool _touchHandlerEnd(const Touch *touch, Event *event);

    bool _touchEnd();

    void _pause(bool pause);

    void _pauseRecursive(Node *_node, bool _pause);
};


#endif //TONEPICK_GAMESCENE_H
