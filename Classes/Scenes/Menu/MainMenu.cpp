//
// Created by igor on 24.01.18.
//

#include <cocos/ui/UIButton.h>
#include <Global/Localization/LocalizedStrings.h>
#include <Global/Variables.h>
#include <Global/Utils.h>
#include <Objects/BasicBlock.h>
#include "MainMenu.h"
#include "MainScene.h"
#include "Settings.h"

USING_NS_CC;

MainMenu *MainMenu::create() {
    MainMenu *ret = new(std::nothrow) MainMenu();
    if (ret && ret->init()) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
    }
    return ret;

}

bool MainMenu::init() {
    if (!LayerColor::initWithColor(Color4B(46, 51, 58, 255))) {
        return false;
    }

    _visibleSize = Director::getInstance()->getVisibleSize();
//
//    auto settingsButton = cocos2d::ui::Button::create();
//    settingsButton->loadTextures(Variables::SETTINGS_BUTTON, Variables::SETTINGS_PRESSED_BUTTON,
//                                 Variables::SETTINGS_BUTTON, cocos2d::ui::Widget::TextureResType::PLIST);
//
//    settingsButton->addTouchEventListener([&](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
//        switch (type) {
//            case cocos2d::ui::Widget::TouchEventType::ENDED: {
//                MainScene::getInstance()->replaceMain(Settings::create());
//            }
//                break;
//            default:
//                break;
//        }
//    });
//    settingsButton->setPosition(Vec2(_visibleSize.width - settingsButton->getBoundingBox().size.width / 2 - 15.f,
//                                     settingsButton->getBoundingBox().size.height / 2 + 15.f));
//    this->addChild(settingsButton);

    cocos2d::Director::getInstance()->getScheduler()->schedule(
            schedule_selector(MainMenu::_enterFrameHandler),
            this, 0.f, false
    );

    _keyboardListener = cocos2d::EventListenerKeyboard::create();
    _keyboardListener->onKeyReleased = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
        switch (keyCode) {
            case EventKeyboard::KeyCode::KEY_BREAK:
            case EventKeyboard::KeyCode::KEY_ESCAPE:
            case EventKeyboard::KeyCode::KEY_BACKSPACE: {
//                auto popUp = this->getChildByName("PopUp");
//                if (popUp == nullptr) {
//                    auto label = cocos2d::Label::createWithTTF(
//                            LocalizedStrings::getInstance()->getString("EXIT THE GAME?"),
//                            Variables::FONT_NAME,
//                            Variables::FONT_SIZE());
//                    label->setColor(cocos2d::Color3B::BLACK);
//                    popUp = MainMenuPopUp::create(LocalizedStrings::getInstance()->getString("ARE YOU SURE?"),
//                                                  label,
//                                                  true);
//                    showPopUp(popUp);
//                } else {
//                    popUp->removeFromParent();
//                }

                this->removeFromParent();
                Director::getInstance()->end();
                #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                                exit(0);
                #endif

            }
                break;
            default:
                break;
        }
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_keyboardListener, this);

    const auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(MainMenu::_touchHandlerBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    _fillArea();

    return true;
}

void MainMenu::_enterFrameHandler(float passedTime) {

}

void MainMenu::onEnter() {
    Layer::onEnter();

}

void MainMenu::onPushScene(int id) {
//    auto scene = BattleParent::createScene(id);
//    Director::getInstance()->pushScene(scene);
}

bool MainMenu::_touchHandlerBegin(const cocos2d::Touch *touch, cocos2d::Event *event) {
    return true;
}

void MainMenu::showPopUp(Node* popUp) {
    if (this->getChildByName("PopUp") == nullptr) {
        auto size = Director::getInstance()->getVisibleSize();

        popUp->setPosition(size.width / 2, -size.height);
        this->addChild(popUp, 0, "PopUp");
    }
}

void MainMenu::_fillArea() {
    auto size = Utils::_getBlockSize(_visibleSize);
    auto widthFactor = _visibleSize.width / Variables::FACTOR;
    auto color = Color4F(Color4B(79, 127, 204, 255));

    for(int i = 0; i < Variables::FACTOR; i++){
        for(int j = 0; j < widthFactor; j++){
            auto pos = Vec2(j * size.width, i * size.width);

            auto block = BasicBlock::create(size, color);
            block->setPosition(pos);
            this->addChild(block);
        }
    }

}
