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
    Vec2 _focusedStartPos;

    Size _visibleSize;
    bool _isPaused;
    static GameScene *_instance;
    //disable multitouch variable
    int _touch;

    bool init(int type);

    void _keyBoardPressedHandler(EventKeyboard::KeyCode keyCode, Event *event);

    void _keyBoardReleasedHandler(EventKeyboard::KeyCode keyCode, Event *event);

    bool _touchHandlerBegin(const Touch *touch, Event *event);

    bool _touchHandlerMove(const Touch *touch, Event *event);

    bool _touchHandlerEnd(const Touch *touch, Event *event);

    bool _isGameOver();

    bool _checkIntersection();

    void _pause(bool pause);
};


#endif //TONEPICK_GAMESCENE_H
