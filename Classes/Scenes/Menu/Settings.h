//
// Created by igor on 24.01.18.
//

#ifndef TONEPICK_SETTINGS_H
#define TONEPICK_SETTINGS_H

#include <ui/UIScrollView.h>
#include <cocos/ui/UIButton.h>
#include "cocos2d.h"

class Settings : public cocos2d::Layer {
public:
    CREATE_FUNC(Settings);

    bool init();

protected:
    void _reloadButtons();

    cocos2d::ui::Button *_musicButton;
    cocos2d::ui::Button *_effectsButton;
    cocos2d::ui::Button *_languageBox;
    cocos2d::ui::ScrollView *_scrollView;
    std::string _language;

    bool _musicState;

    bool _effectsState;

    void onEnter() override;

    void onQuit();

    void _showScrollView();

    cocos2d::Size _visibleSize;
};



#endif //TONEPICK_SETTINGS_H
