//
// Created by igor on 24.01.18.
//

#ifndef TONEPICK_MAINSCENE_H
#define TONEPICK_MAINSCENE_H

#include "cocos2d.h"

class MainScene : public cocos2d::Scene{
public:
    static MainScene* getInstance();

    static MainScene *create();

    bool init();

    void replaceMain(cocos2d::Layer* layer);

    void pushMain(cocos2d::Layer* layer);

    void popMain();

    void popAndReplace();

    cocos2d::Layer *getMain();

private:

    static MainScene *_instance;

    cocos2d::Layer *_main;

    std::stack<cocos2d::Layer *> _mainStack;
};


#endif //TONEPICK_MAINSCENE_H
