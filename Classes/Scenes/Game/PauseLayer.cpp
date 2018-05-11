//
// Created by igor on 03.04.18.
//

#include <Global/Variables.h>
#include <cocos/ui/UIButton.h>
#include <Global/Localization/LocalizedStrings.h>
#include <Scenes/Menu/Settings.h>
#include <Scenes/Menu/MainScene.h>
#include "PauseLayer.h"
#include "GameScene.h"

USING_NS_CC;

enum {
    BACKGROUND_LEVEL = 1,
    WIDGETS_LEVEL = 2,

    kTagBackground = 101,
    kTagResumeButton = 102,
    kTagSettingsButton = 103,
    kTagMenuButton = 104
};

bool PauseLayer::init() {
    if (!ParentLayer::init()) {
        return false;
    }

    auto black = LayerColor::create(Color4B(0, 0, 0, 0), _visibleSize.width, _visibleSize.height);
    this->addChild(black, BACKGROUND_LEVEL, kTagBackground);

    _color = Color4B(79, 127, 204, 255);

    this->runAction(Sequence::create(
            CallFunc::create([&]{
                _addContent();
            }),
            DelayTime::create(ADD_REMOVE_SPEED),
            CallFunc::create([&, black]{
                black->runAction(FadeTo::create(.3f, 180));
            }),
            NULL
    ));

    return true;
}

void PauseLayer::_backButtonHandler() {
    _removeAllWidgets();
    onQuit();
}

void PauseLayer::onQuit() {
    this->runAction(Sequence::create(
            CallFunc::create([&]{
                ParentLayer::onQuit();
                this->getChildByTag(kTagBackground)->runAction(FadeOut::create(.3f));
            }),
            DelayTime::create(ADD_REMOVE_SPEED * 2),
            CallFunc::create([&]{
                dynamic_cast<GameScene*>(this->getParent())->unPause();
            }),
            NULL
    ));
}

void PauseLayer::_addContent() {
    _fillArea(5, 11, 1, Variables::FACTOR - 1, WIDGETS_LEVEL);

    auto resumeButton = cocos2d::ui::Button::create();
    resumeButton->setTitleText(LocalizedStrings::getInstance()->getString("RESUME"));
    resumeButton->setTitleFontName(Variables::FONT_NAME);
    resumeButton->setTitleFontSize(_blockSize.height * .8f);
    resumeButton->addTouchEventListener([&](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) {
            case cocos2d::ui::Widget::TouchEventType::ENDED: {
                _backButtonHandler();
                break;
            }
            default:
                break;
        }
    });

    resumeButton->setPosition(Vec2(_visibleSize.width / 2,  _blockSize.height * 5 - _blockSize.height / 2));
    resumeButton->setTag(kTagResumeButton);

    auto settingsButton = cocos2d::ui::Button::create();
    settingsButton->setTitleText(LocalizedStrings::getInstance()->getString("SETTINGS"));
    settingsButton->setTitleFontName(Variables::FONT_NAME);
    settingsButton->setTitleFontSize(_blockSize.height * .5f);
    settingsButton->addTouchEventListener([&](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) {
            case cocos2d::ui::Widget::TouchEventType::ENDED: {
                this->runAction(Sequence::create(
                        CallFunc::create([&](){
                            _removeAllWidgets();
                            ParentLayer::onQuit();
                        }),
                        DelayTime::create(ADD_REMOVE_SPEED * 2),
                        CallFunc::create([&]() {
                            this->getParent()->addChild(Settings::create(), 4);
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

    auto menuButton = cocos2d::ui::Button::create();
    menuButton->setTitleText(LocalizedStrings::getInstance()->getString("MENU"));
    menuButton->setTitleFontName(Variables::FONT_NAME);
    menuButton->setTitleFontSize(_blockSize.height * .8f);
    menuButton->addTouchEventListener([&](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) {
            case cocos2d::ui::Widget::TouchEventType::ENDED: {
                this->runAction(Sequence::create(
                        CallFunc::create([&](){
                            _backButtonHandler();
                        }),
                        DelayTime::create(ADD_REMOVE_SPEED * 2),
                        CallFunc::create([&]() {
                            Director::getInstance()->popToRootScene();

                            auto scene = MainScene::create();

                            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
                        }),
                        NULL)
                );
                break;
            }
            default:
                break;
        }
    });
    menuButton->setPosition(Vec2(_visibleSize.width / 2, _blockSize.height * 7 - _blockSize.height / 2));
    menuButton->setTag(kTagMenuButton);

    auto delay = 1.f;

    _addWidget(resumeButton, delay);
    _addWidget(settingsButton, delay);
    _addWidget(menuButton, delay);
}
