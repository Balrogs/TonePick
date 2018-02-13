//
// Created by igor on 24.01.18.
//

#ifndef TONEPICK_MAINMENU_H
#define TONEPICK_MAINMENU_H

#include "cocos2d.h"
#include "Objects/MenuBlock.h"
#include "ParentLayer.h"

class MainMenu : public ParentLayer {
public:
    static MainMenu *create();

    bool init();

    void onEnter() override;
    void onQuit() override;

    void onPushScene(int id);

    void showPopUp(cocos2d::Node* popUp);

protected:
    std::vector<std::vector<BasicBlock*>> _blocks;
    int _touch;
    BasicBlock* _focused;

    bool _touchHandlerBegin(const cocos2d::Touch *touch, cocos2d::Event *event);
    bool _touchHandlerMoved(const cocos2d::Touch *touch, cocos2d::Event *event);
    bool _touchHandlerEnd(const cocos2d::Touch *touch, cocos2d::Event *event);

    void _enterFrameHandler(float passedTime) override ;

    cocos2d::Size _visibleSize;

    void _fillArea();

    void _updateColor();

    Color4B _color;
private:

    void _addWidget(cocos2d::Node* node, float delay);
};


#endif //TONEPICK_MAINMENU_H
