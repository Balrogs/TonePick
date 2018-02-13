//
// Created by igor on 24.01.18.
//

#include <Global/Localization/LocalizedStrings.h>
#include <Global/Variables.h>
#include "Settings.h"
#include "MainScene.h"
#include "MainMenu.h"

USING_NS_CC;

bool Settings::init() {
    if (!Layer::init()) {
        return false;
    }

    _visibleSize = Director::getInstance()->getVisibleSize();

//    auto backButton = cocos2d::ui::Button::create();
//
//    backButton->addTouchEventListener([&](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
//        switch (type) {
//            case cocos2d::ui::Widget::TouchEventType::ENDED: {
//                onQuit();
//            }
//                break;
//            default:
//                break;
//        }
//    });
//    backButton->setPosition(Vec2(_visibleSize.width / 2,
//                                 backButton->getBoundingBox().size.height / 2 + _bg->getBoundingBox().getMinY() + 25.f));
//    this->addChild(backButton, 3);

//    cocos2d::UserDefault *def = cocos2d::UserDefault::getInstance();
//
//    _musicState = def->getBoolForKey("MUSIC", true);
//    _effectsState = def->getBoolForKey("EFFECTS", true);
//
//    def->flush();
//
//    _reloadButtons();
//
//    auto music = cocos2d::Label::createWithTTF(  LocalizedStrings::getInstance()->getString("MUSIC"), Variables::FONT_NAME,
//                                                 Variables::FONT_SIZE());
//    music->setPosition(
//            Vec2(_musicButton->getBoundingBox().getMinX() - music->getBoundingBox().size.width / 2 - 50.f,
//                 _musicButton->getPosition().y));
//
//    this->addChild(music, 2);
//
//    auto sounds = cocos2d::Label::createWithTTF(  LocalizedStrings::getInstance()->getString("SOUNDS"), Variables::FONT_NAME,
//                                                  Variables::FONT_SIZE());
//    sounds->setPosition(
//            Vec2(_effectsButton->getBoundingBox().getMinX() - sounds->getBoundingBox().size.width / 2 - 50.f,
//                 _effectsButton->getPosition().y));
//
//
//    this->addChild(sounds, 2);
//
//
//    _language = def->getStringForKey("LANGUAGE", "ENGLISH");
//
//    _languageBox = cocos2d::ui::Button::create();
//
//    _languageBox->addTouchEventListener([&](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
//        switch (type) {
//            case cocos2d::ui::Widget::TouchEventType::ENDED: {
//                _showScrollView();
//            }
//                break;
//            default:
//                break;
//        }
//    });
//    _languageBox->setPosition(
//            Vec2(_bg->getBoundingBox().getMinX() + 150.f + _languageBox->getBoundingBox().size.width / 2,
//                 _bg->getPositionY()));
//    auto languageBox_title = cocos2d::Label::createWithTTF(_language.c_str(), Variables::FONT_NAME,
//                                                           Variables::FONT_SIZE());
//    languageBox_title->setColor(Color3B::BLACK);
//    languageBox_title->setPosition(_languageBox->getContentSize().width / 2,
//                                   _languageBox->getContentSize().height / 2);
//    _languageBox->addChild(languageBox_title, 4);
//
//    this->addChild(_languageBox, 3);
//
//    auto language = cocos2d::Label::createWithTTF(  LocalizedStrings::getInstance()->getString("LANGUAGE"), Variables::FONT_NAME,
//                                                    Variables::FONT_SIZE());
//    language->setPosition(_languageBox->getPosition().x,
//                          _languageBox->getPosition().y + _languageBox->getBoundingBox().size.height / 2 +
//                          language->getBoundingBox().size.height);
//
//    this->addChild(language, 2);
//
//    this->setPosition(_visibleSize.width, 0);

    _keyboardListener = cocos2d::EventListenerKeyboard::create();
    _keyboardListener->onKeyReleased = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
        switch (keyCode) {
            case EventKeyboard::KeyCode::KEY_BREAK:
            case EventKeyboard::KeyCode::KEY_ESCAPE:
            case EventKeyboard::KeyCode::KEY_BACKSPACE: {
                _removeAllWidgets();
                onQuit();
            }
                break;
            default:
                break;
        }
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_keyboardListener, this);

    _touch = -1;
    const auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(Settings::_touchHandlerBegin, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(Settings::_touchHandlerMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Settings::_touchHandlerEnd, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    _color = Color4B(79, 127, 204, 255);
    _fillArea(2, 14, 1, Variables::FACTOR - 1);

    return true;
}

void Settings::onEnter() {
    Layer::onEnter();

}

void Settings::onQuit() {
    ParentLayer::onQuit();
    this->runAction(Sequence::create(
            DelayTime::create(1.2f),
            CallFunc::create([&]() {
                MainScene::getInstance()->replaceMain(MainMenu::create());
            }),
            NULL)
    );
}

void Settings::_reloadButtons() {
//    if (_musicButton != nullptr) {
//        _musicButton->removeFromParent();
//    }
//
//    if (_effectsButton != nullptr) {
//        _effectsButton->removeFromParent();
//    }
//
//    string music = Variables::MUSIC_ON_BUTTON;
//    string effects = Variables::EFFECTS_ON_BUTTON;
//
//    if (!_musicState) {
//        music = Variables::MUSIC_OFF_BUTTON;
//    }
//
//    if (!_effectsState) {
//        effects = Variables::EFFECTS_OFF_BUTTON;
//    }
//
//    _musicButton = cocos2d::ui::Button::create();
//    _musicButton->loadTextureNormal(music, cocos2d::ui::Widget::TextureResType::PLIST);
//
//    _musicButton->addTouchEventListener([&](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
//        switch (type) {
//            case cocos2d::ui::Widget::TouchEventType::ENDED: {
//                cocos2d::UserDefault *def = cocos2d::UserDefault::getInstance();
//                _musicState = !_musicState;
//                def->setBoolForKey("MUSIC", _musicState);
//                this->_reloadButtons();
//            }
//                break;
//            default:
//                break;
//        }
//    });
//    _musicButton->setPosition(
//            Vec2(_bg->getBoundingBox().getMaxX() - 3.f * _musicButton->getBoundingBox().size.width,
//                 _bg->getPositionY() - _musicButton->getBoundingBox().size.height));
//    this->addChild(_musicButton, 3);
//
//    _effectsButton = cocos2d::ui::Button::create();
//    _effectsButton->loadTextureNormal(effects, cocos2d::ui::Widget::TextureResType::PLIST);
//    _effectsButton->addTouchEventListener([&](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
//        switch (type) {
//            case cocos2d::ui::Widget::TouchEventType::ENDED: {
//                cocos2d::UserDefault *def = cocos2d::UserDefault::getInstance();
//                _effectsState = !_effectsState;
//                def->setBoolForKey("EFFECTS", _effectsState);
//                this->_reloadButtons();
//            }
//                break;
//            default:
//                break;
//        }
//    });
//    _effectsButton->setPosition(
//            Vec2(_musicButton->getPositionX(),
//                 _bg->getPositionY() + _effectsButton->getBoundingBox().size.height));
//    this->addChild(_effectsButton, 3);
}

void Settings::_showScrollView() {
//
//    _scrollView = cocos2d::ui::ScrollView::create();
//    _scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
//    _scrollView->setContentSize(Size(_languageBox->getContentSize().width, _bg->getContentSize().height * 0.8f));
//    _scrollView->setInnerContainerSize(
//            Size(_languageBox->getContentSize().width, _languageBox->getContentSize().height * 9));
//    _scrollView->setBackGroundImage(Variables::GRAY_BUTTON, cocos2d::ui::Widget::TextureResType::PLIST);
//    _scrollView->setBackGroundImageScale9Enabled(true);
//    _scrollView->setBounceEnabled(true);
//    _scrollView->setInertiaScrollEnabled(true);
//    _scrollView->setAnchorPoint(Vec2(0, 0));
//    _scrollView->setPosition(Vec2(_languageBox->getPosition().x - _scrollView->getContentSize().width / 2,
//                                  Director::getInstance()->getVisibleSize().height / 2 -
//                                  _scrollView->getContentSize().height / 2));
//
//    std::vector<std::string> language_list = {"ENGLISH",
//                                              "GERMAN",
//                                              "FRENCH",
//                                              "ITALIAN",
//                                              "SPANISH",
//                                              "PORTUGUESE",
//                                              "RUSSIAN",
//                                              "JAPANESE",
//                                              "CHINESE",
//                                              "KOREAN"
//    };
//    for (unsigned long i = 0; i < language_list.size(); i++) {
//        auto language = language_list.at(i);
//        auto languageButton = cocos2d::ui::Button::create();
//        languageButton->setTitleText(language);
//        languageButton->setTitleFontSize(Variables::FONT_SIZE());
//        languageButton->setTitleFontName(Variables::FONT_NAME);
//        languageButton->setColor(Color3B::BLACK);
//        languageButton->addTouchEventListener(
//                [&, language](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
//                    switch (type) {
//                        case cocos2d::ui::Widget::TouchEventType::ENDED: {
//                            cocos2d::UserDefault *def = cocos2d::UserDefault::getInstance();
//                            def->setStringForKey("LANGUAGE", language);
//                            LocalizedStrings::getInstance()->setLanguage(language);
//                            onQuit();
//                            break;
//                        }
//                        default:
//                            break;
//                    }
//                });
//        languageButton->setPosition(Vec2(_scrollView->getInnerContainerSize().width / 2,
//                                         _scrollView->getInnerContainerSize().height - 25.f -
//                                         i * _languageBox->getContentSize().height));
//        _scrollView->addChild(languageButton, 3);
//
//    }
//    this->addChild(_scrollView, 4);
}

void Settings::_enterFrameHandler(float passedTime) {

}

