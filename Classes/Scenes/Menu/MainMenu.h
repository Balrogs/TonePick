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
    CREATE_FUNC(MainMenu);

    bool init();

    void onPushScene(int id);

protected:
    virtual void  _backButtonHandler() override ;

private:
    void _menuButtons();
    void _exitButtons();
    void _onExit();

};


#endif //TONEPICK_MAINMENU_H
