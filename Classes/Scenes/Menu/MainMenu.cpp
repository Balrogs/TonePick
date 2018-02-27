//
// Created by igor on 24.01.18.
//

#include <cocos/ui/UIButton.h>
#include <Global/Localization/LocalizedStrings.h>
#include <Global/Variables.h>
#include <Global/Utils.h>
#include "MainMenu.h"
#include "MainScene.h"
#include "Settings.h"

USING_NS_CC;

enum {
    menuTag = 10,
    exitTag = 11,
    kTagStartButton = 100,
    kTagSettingsButton = 101,
    kTagExitYesButton = 102,
    kTagExitNoButton = 103,
    kTagExitLabel = 104
};

bool MainMenu::init() {
    if (!ParentLayer::init()) {
        return false;
    }

    _color = Color4B(79, 127, 204, 255);
    _fillArea(4, 12, 1, Variables::FACTOR - 1);
    _menuButtons();

    return true;
}

void MainMenu::onPushScene(int id) {

//    auto scene = BattleParent::createScene(id);
//    Director::getInstance()->pushScene(scene);
}



void MainMenu::_menuButtons() {
    if(_viewTag == menuTag){
        return;
    }
    _viewTag = menuTag;

    auto delay = 1.f;

    auto startButton = cocos2d::ui::Button::create();
    startButton->setTitleText(LocalizedStrings::getInstance()->getString("START"));
    startButton->setTitleFontName(Variables::FONT_NAME);
    startButton->setTitleFontSize(_blockSize.height * .8f);
    startButton->addTouchEventListener([&](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) {
            case cocos2d::ui::Widget::TouchEventType::ENDED: {
                this->runAction(Sequence::create(
                        CallFunc::create([&](){
                            onQuit();
                            _removeWidgetByTag(kTagStartButton, .7f);
                            _removeWidgetByTag(kTagSettingsButton, .5f);
                        }),
                        DelayTime::create(1.1f),
                        CallFunc::create([&]() {
                            onPushScene(1);
                        }),
                        NULL)
                );
                break;
            }
            default:
                break;
        }
    });

    startButton->setPosition(Vec2(_visibleSize.width / 2,  _blockSize.height * 6 - _blockSize.height / 2));
    startButton->setTag(kTagStartButton);

    auto settingsButton = cocos2d::ui::Button::create();
    settingsButton->setTitleText(LocalizedStrings::getInstance()->getString("SETTINGS"));
    settingsButton->setTitleFontName(Variables::FONT_NAME);
    settingsButton->setTitleFontSize(_blockSize.height * .5f);
    settingsButton->addTouchEventListener([&](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) {
            case cocos2d::ui::Widget::TouchEventType::ENDED: {
                this->runAction(Sequence::create(
                        CallFunc::create([&](){
                            onQuit();
                            _removeWidgetByTag(kTagSettingsButton, .7f);
                            _removeWidgetByTag(kTagStartButton, .5f);
                        }),
                        DelayTime::create(1.2f),
                        CallFunc::create([&]() {
                            MainScene::getInstance()->replaceMain(Settings::create());
                        }),
                        NULL)
                );
                break;
            }
            default:
                break;
        }
    });
    settingsButton->setPosition(Vec2(_visibleSize.width / 2, _blockSize.height * 3 - _blockSize.height / 2));
    settingsButton->setTag(kTagSettingsButton);
    _addWidget(startButton, delay);
    _addWidget(settingsButton, delay);
}

void MainMenu::_exitButtons() {
    if(_viewTag == exitTag){
        return;
    }
    _viewTag = exitTag;
    auto delay = 1.f;

    auto exitLabel = Label::createWithTTF(LocalizedStrings::getInstance()->getString("EXIT?"), Variables::FONT_NAME, Variables::H_FONT_SIZE());
    exitLabel->setTag(kTagExitLabel);
    exitLabel->setPosition(Vec2(_visibleSize.width / 2,  _blockSize.height * 8 - _blockSize.height / 2));

    auto yesButton = cocos2d::ui::Button::create();
    yesButton->setTitleText(LocalizedStrings::getInstance()->getString("YES"));
    yesButton->setTitleFontName(Variables::FONT_NAME);
    yesButton->setTitleFontSize(_blockSize.height * .8f);
    yesButton->addTouchEventListener([&](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) {
            case cocos2d::ui::Widget::TouchEventType::ENDED: {
                _removeWidgetByTag(kTagExitYesButton, .7f);
                _removeWidgetByTag(kTagExitNoButton, .5f);
                _removeWidgetByTag(kTagExitLabel, .3f);
                onQuit();
                this->runAction(Sequence::create(
                        DelayTime::create(1.2f),
                        CallFunc::create([&](){
                            _onExit();
                        }),
                        NULL)
                );
                break;
            }
            default:
                break;
        }
    });

    yesButton->setPosition(Vec2(_visibleSize.width / 2 - _blockSize.width * 1.5f,  _blockSize.height * 5 - _blockSize.height / 2));
    yesButton->setTag(kTagExitYesButton);

    auto noButton = cocos2d::ui::Button::create();
    noButton->setTitleText(LocalizedStrings::getInstance()->getString("NO"));
    noButton->setTitleFontName(Variables::FONT_NAME);
    noButton->setTitleFontSize(_blockSize.height * .8f);
    noButton->addTouchEventListener([&](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) {
            case cocos2d::ui::Widget::TouchEventType::ENDED: {
                _removeWidgetByTag(kTagExitNoButton, .7f);
                _removeWidgetByTag(kTagExitYesButton, .5f);
                _removeWidgetByTag(kTagExitLabel, .3f);
                _menuButtons();
                _refill();
                break;
            }
            default:
                break;
        }
    });
    noButton->setPosition(Vec2(_visibleSize.width / 2 + _blockSize.width * 1.5f, _blockSize.height * 5 - _blockSize.height / 2));
    noButton->setTag(kTagExitNoButton);

    _addWidget(exitLabel, delay);
    _addWidget(yesButton, delay + 0.2f);
    _addWidget(noButton, delay + 0.2f);
}

void MainMenu::_onExit() {
    this->removeFromParent();
    Director::getInstance()->end();
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
    #endif
}

void MainMenu::_backButtonHandler() {
    if(_viewTag != exitTag){
        _removeAllWidgets();
        _exitButtons();
        _refill();
    } else {
        _removeAllWidgets();
        _menuButtons();
        _refill();
    }
}

