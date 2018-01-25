//
// Created by igor on 24.01.18.
//

#ifndef TONEPICK_MAINMENU_H
#define TONEPICK_MAINMENU_H

#include "cocos2d.h"


class MainMenu : public cocos2d::LayerColor {
public:
    static MainMenu *create();

    bool init();

    void onEnter() override;

    void onPushScene(int id);

    void showPopUp(cocos2d::Node* popUp);

private:

    bool _touchHandlerBegin(const cocos2d::Touch *touch, cocos2d::Event *event);

    void _enterFrameHandler(float passedTime);

    cocos2d::Size _visibleSize;

    void _fillArea();
};


#endif //TONEPICK_MAINMENU_H
