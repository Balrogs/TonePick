//
// Created by igor on 24.01.18.
//

#include <Global/Localization/LocalizedStrings.h>
#include <Global/Variables.h>
#include "Settings.h"
#include "MainScene.h"
#include "MainMenu.h"

USING_NS_CC;

    std::vector<std::string> language_list = {
            "ENGLISH",
            "GERMAN",
            "FRENCH",
            "ITALIAN",
            "SPANISH",
            "PORTUGUESE",
            "RUSSIAN",
            "JAPANESE",
            "CHINESE",
            "KOREAN"
    };

enum {
    currLanguageTag = 11,
    allLanguagesTag = 12,
    kTagEffectsButton = 100,
    kTagLanguageButton = 101,
    kTagBackButton = 102,
    kTagEffectsLabel = 103,
    kTagLanguageLabel = 104,
    kTagExitLabel = 105,
    kTagTitleLabel = 106,
    WIDGETS_LEVEL = 2
};

bool Settings::init() {
    if (!ParentLayer::init()) {
        return false;
    }

    cocos2d::UserDefault *def = cocos2d::UserDefault::getInstance();

    _effectsState = def->getBoolForKey("EFFECTS", true);
    _language = def->getStringForKey("LANGUAGE", "ENGLISH");

    _color = Color4B(79, 127, 204, 255);
    _fillArea(2, 14, 1, Variables::FACTOR - 1, WIDGETS_LEVEL);

    _showTitle();
    _defaultButtons();
    _showLanguageTitle();
    _showCurrentLanguage();

    return true;
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

//void Settings::_showScrollView() {
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
//}


void Settings::_backButtonHandler() {
    _removeAllWidgets();
    onQuit();
}

void Settings::_showTitle() {
    auto titleLabel = Label::createWithTTF(LocalizedStrings::getInstance()->getString("SETTINGS"), Variables::FONT_NAME, _blockSize.height * .8f);
    titleLabel->setTag(kTagTitleLabel);
    titleLabel->setPosition(Vec2(_visibleSize.width / 2 + _blockSize.width * 3 + _blockSize.width / 2,  _blockSize.height * 8 - _blockSize.height / 2));

    auto backButton = cocos2d::ui::Button::create();
    backButton->loadTextureNormal(Variables::BACK_BUTTON, cocos2d::ui::Widget::TextureResType::PLIST);
    backButton->addTouchEventListener([&](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) {
            case cocos2d::ui::Widget::TouchEventType::ENDED: {
                _backButtonHandler();
                break;
            }
            default:
                break;
        }
    });

    backButton->setPosition(Vec2(_visibleSize.width / 2 - _blockSize.width * 4 - _blockSize.width / 2,  _blockSize.height * 7 - _blockSize.height / 2));
    backButton->setTag(kTagBackButton);

    auto delay = 1.f;

    _addWidget(titleLabel, delay);
    _addWidget(backButton, delay + 0.1f);
}

void Settings::_defaultButtons() {

    auto soundsLabel = Label::createWithTTF(LocalizedStrings::getInstance()->getString("EFFECTS"), Variables::FONT_NAME, _blockSize.height * .8f);
    soundsLabel->setTag(kTagEffectsLabel);
    soundsLabel->setPosition(Vec2(_visibleSize.width / 2 + 1.5f * _blockSize.width ,  _blockSize.height * 5 - _blockSize.height / 2));

    string effects = Variables::EFFECTS_ON_BUTTON;

    if (!_effectsState) {
        effects = Variables::EFFECTS_OFF_BUTTON;
    }
    
    auto sounds = cocos2d::ui::Button::create();
    sounds->loadTextureNormal(effects, cocos2d::ui::Widget::TextureResType::PLIST);
    sounds->addTouchEventListener([&](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) {
            case cocos2d::ui::Widget::TouchEventType::ENDED: {
                break;
            }
            default:
                break;
        }
    });

    float offset = (int) (soundsLabel->getContentSize().width / _blockSize.width) * _blockSize.width / 2;

    sounds->setPosition(Vec2(soundsLabel->getPosition().x + offset  +  1.5f * _blockSize.width,  soundsLabel->getPosition().y));
    sounds->setTag(kTagEffectsButton);
    
    auto delay = 1.2f;

    _addWidget(soundsLabel, delay);
    _addWidget(sounds, delay + 0.2f);
}

void Settings::_showCurrentLanguage() {
    if(_viewTag == currLanguageTag){
        return;
    }
    _viewTag = currLanguageTag;
    
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
}

void Settings::_showLanguages() {
    if(_viewTag == allLanguagesTag){
        return;
    }
    _viewTag = allLanguagesTag;
}

void Settings::_showLanguageTitle() {
    auto languageLabel = Label::createWithTTF(LocalizedStrings::getInstance()->getString("LANGUAGE"), Variables::FONT_NAME, _blockSize.height * .5f);
    languageLabel->setTag(kTagLanguageLabel);
    languageLabel->setPosition(Vec2(_visibleSize.width / 2 - 4.5f * _blockSize.width ,  _blockSize.height * 5 - _blockSize.height / 2));

    auto delay = 1.2f;

    _addWidget(languageLabel, delay);
}

