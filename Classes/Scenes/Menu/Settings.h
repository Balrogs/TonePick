//
// Created by igor on 24.01.18.
//

#ifndef TONEPICK_SETTINGS_H
#define TONEPICK_SETTINGS_H

#include <ui/UIScrollView.h>
#include <cocos/ui/UIButton.h>
#include "cocos2d.h"
#include "ParentLayer.h"

class Settings : public ParentLayer {
public:
    CREATE_FUNC(Settings);

    bool init();

protected:
    std::string _language;
    bool _effectsState;

    virtual void  _backButtonHandler() override;
    void onQuit() override;

    void _showLanguages();
    void _showCurrentLanguage();
    void _showLanguageTitle();
    void _showTitle();
    void _defaultButtons();
};



#endif //TONEPICK_SETTINGS_H
