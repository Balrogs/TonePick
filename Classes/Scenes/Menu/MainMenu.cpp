//
// Created by igor on 24.01.18.
//

#include <cocos/ui/UIButton.h>
#include <Global/Localization/LocalizedStrings.h>
#include <Global/Variables.h>
#include <Global/Utils.h>
#include <Objects/MenuBlock.h>
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

    _touch = -1;
    const auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(MainMenu::_touchHandlerBegin, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(MainMenu::_touchHandlerMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(MainMenu::_touchHandlerEnd, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    _color = Color4B(79, 127, 204, 255);
    _fillArea();

    cocos2d::Director::getInstance()->getScheduler()->schedule(
            schedule_selector(MainMenu::_enterFrameHandler),
            this, 1.f, false
    );

    return true;
}

void MainMenu::_enterFrameHandler(float passedTime) {
    _updateColor();
}

void MainMenu::onEnter() {
    Layer::onEnter();

}

void MainMenu::onPushScene(int id) {
//    auto scene = BattleParent::createScene(id);
//    Director::getInstance()->pushScene(scene);
}

bool MainMenu::_touchHandlerBegin(const cocos2d::Touch *touch, cocos2d::Event *event) {
    if (_touch < 0) {
        _touch = touch->getID();
    } else {
        return false;
    }

    for(auto i = 0; i < _blocks.size(); i++){
        for(auto j = 0; j < _blocks[i].size(); j++) {
            auto  box = _blocks[i][j]->getBoundingBox();
            if(box.containsPoint(touch->getLocation())){
                _focused = _blocks[i][j];
                _focused->runAction(Spawn::create(
                        ScaleTo::create(0.2f, 1.2f),
                        MoveTo::create(0.2f, Vec2(_focused->getPosition().x - _focused->getBoundingBox().size.width * .2f / 2,_focused->getPosition().y - _focused->getBoundingBox().size.height * .2f / 2)),
                        NULL));
                return true;
            }
        }
    }

    return true;
}

bool MainMenu::_touchHandlerMoved(const cocos2d::Touch *touch, cocos2d::Event *event) {
    for(auto i = 0; i < _blocks.size(); i++){
        for(auto j = 0; j < _blocks[i].size(); j++) {
            auto  box = _blocks[i][j]->getBoundingBox();
            if(box.containsPoint(touch->getLocation())){
                if(_focused != nullptr ){
                    if(_focused != _blocks[i][j])
                        _focused->runAction(Spawn::create(
                                ScaleTo::create(0.2f, 1.f),
                                MoveTo::create(0.2f, Vec2(_focused->getPosition().x + _focused->getBoundingBox().size.width * .2f / 2,_focused->getPosition().y + _focused->getBoundingBox().size.height * .2f / 2)),
                                NULL));
                    else
                        return true;
                }
                _focused = _blocks[i][j];
                _focused->runAction(Spawn::create(
                        ScaleTo::create(0.2f, 1.2f),
                        MoveTo::create(0.2f, Vec2(_focused->getPosition().x - _focused->getBoundingBox().size.width * .2f / 2,_focused->getPosition().y - _focused->getBoundingBox().size.height * .2f / 2)),
                        NULL));
                return true;
            }
        }
    }
}


bool MainMenu::_touchHandlerEnd(const cocos2d::Touch *touch, cocos2d::Event *event) {
    if (_touch == touch->getID()) {
        _touch = -1;
    } else {
        return false;
    }

    if(_focused != nullptr){
        if(_focused->getBoundingBox().containsPoint(touch->getLocation()))
            _focused->hide();
        else
            _focused->runAction(Spawn::create(
                    ScaleTo::create(0.2f, 1.f),
                    MoveTo::create(0.2f, Vec2(_focused->getPosition().x + _focused->getBoundingBox().size.width * .2f / 2,_focused->getPosition().y + _focused->getBoundingBox().size.height * .2f / 2)),
                    NULL));
    }

    _focused = nullptr;

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
    auto widthFactor = 12;
//    auto widthFactor = _visibleSize.width / Variables::FACTOR;
    auto color = Color4F(_color);
    for(unsigned int i = 0; i < Variables::FACTOR; i++){
        vector<BasicBlock*> row;

        for(unsigned int j = 4; j < widthFactor; j++){
            auto pos = Vec2(j * size.width, i * size.width);

            auto block = BasicBlock::create(size, color);
            block->setPosition(pos);
            this->addChild(block);

            this->runAction(Sequence::create(
                    DelayTime::create((i + j) / 20.f),
                    CallFunc::create([block]{
                        block->appear();
                    }),
                    NULL
            ));

            row.push_back(block);
        }
        _blocks.push_back(row);
    }
}

void MainMenu::_updateColor() {
    _color = Color4B(_color.r, (GLubyte) (_color.g + 2), _color.b, _color.a);
    for(auto i = 0; i < _blocks.size(); i++){
        for(auto j = 0; j < _blocks[i].size(); j++) {
            _blocks[i][j]->paint(Color4F(_color));
        }
    }
}