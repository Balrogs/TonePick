//
// Created by igor on 24.01.18.
//

#ifndef TONEPICK_MAINSCENE_H
#define TONEPICK_MAINSCENE_H

#include "cocos2d.h"
#include "ParentLayer.h"

class MainScene : public cocos2d::Scene{
public:
    static MainScene* getInstance();

    static MainScene *create();

    bool init();

    void replaceMain(ParentLayer* layer);

    void pushMain(ParentLayer* layer);

    void popMain();

    void popAndReplace();

    ParentLayer *getMain();

private:

    static MainScene *_instance;

    ParentLayer *_main;

    std::stack<ParentLayer *> _mainStack;
};


#endif //TONEPICK_MAINSCENE_H
