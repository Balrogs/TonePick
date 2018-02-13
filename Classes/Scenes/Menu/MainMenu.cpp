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

enum {
    kTagStartButton = 100,
    kTagSettingsButton = 101,
};

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
    if (!Layer::init()) {
        return false;
    }

    _visibleSize = Director::getInstance()->getVisibleSize();

    _keyboardListener = cocos2d::EventListenerKeyboard::create();
    _keyboardListener->onKeyReleased = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
        switch (keyCode) {
            case EventKeyboard::KeyCode::KEY_BREAK:
            case EventKeyboard::KeyCode::KEY_ESCAPE:
            case EventKeyboard::KeyCode::KEY_BACKSPACE: {
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
    auto color = Color4F(_color);

    auto delay = 0.f;

    for(unsigned int i = 1; i < Variables::FACTOR - 1; i++){
        vector<BasicBlock*> row;

        for(unsigned int j = 4; j < widthFactor; j++){
            auto pos = Vec2(j * size.width, i * size.width);

            auto block = BasicBlock::create(size, color);
            block->setPosition(pos);
            this->addChild(block, 2);
            delay = (i + j) / 20.f;
            this->runAction(Sequence::create(
                    DelayTime::create(delay),
                    CallFunc::create([block]{
                        block->appear();
                    }),
                    NULL
            ));

            row.push_back(block);
        }
        _blocks.push_back(row);
    }

    delay += .5f;

    auto startButton = cocos2d::ui::Button::create();
    startButton->setTitleText("START");
    startButton->setTitleFontName(Variables::FONT_NAME);
    startButton->setTitleFontSize(size.height * .8f);
    startButton->addTouchEventListener([&](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) {
            case cocos2d::ui::Widget::TouchEventType::ENDED: {
                this->runAction(Sequence::create(
                        CallFunc::create([&](){
                            onQuit();
                            this->getChildByTag(kTagStartButton)->runAction(Sequence::create(
                                    DelayTime::create(.5f),
                                    ScaleTo::create(.5f, 0.f),
                                    RemoveSelf::create(),
                                    NULL
                            ));
                            this->getChildByTag(kTagSettingsButton)->runAction(Sequence::create(
                                    ScaleTo::create(.5f, 0.f),
                                    RemoveSelf::create(),
                                    NULL
                            ));
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

    startButton->setPosition(Vec2(_visibleSize.width / 2,  size.height * 6 - size.height / 2));
    startButton->setTag(kTagStartButton);

    auto settingsButton = cocos2d::ui::Button::create();
    settingsButton->setTitleText("SETTINGS");
    settingsButton->setTitleFontName(Variables::FONT_NAME);
    settingsButton->setTitleFontSize(size.height * .5f);
    settingsButton->addTouchEventListener([&](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) {
            case cocos2d::ui::Widget::TouchEventType::ENDED: {
                this->runAction(Sequence::create(
                        CallFunc::create([&](){
                            onQuit();
                            this->getChildByTag(kTagSettingsButton)->runAction(Sequence::create(
                                    DelayTime::create(.5f),
                                    ScaleTo::create(.5f, 0.f),
                                    RemoveSelf::create(),
                                    NULL
                            ));
                            this->getChildByTag(kTagStartButton)->runAction(Sequence::create(
                                    ScaleTo::create(.5f, 0.f),
                                    RemoveSelf::create(),
                                    NULL
                            ));
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
    settingsButton->setPosition(Vec2(_visibleSize.width / 2, size.height * 3 - size.height / 2));
    settingsButton->setTag(kTagSettingsButton);
    _addWidget(startButton, delay);
    _addWidget(settingsButton, delay);
}

void MainMenu::_updateColor() {
    _color = Color4B(_color.r, (GLubyte) (_color.g + 2), _color.b, _color.a);
    for(auto i = 0; i < _blocks.size(); i++){
        for(auto j = 0; j < _blocks[i].size(); j++) {
            _blocks[i][j]->paint(Color4F(_color));
        }
    }
}

void MainMenu::onQuit() {
    for(auto i = 0; i < _blocks.size(); i++){
        for(auto j = 0; j < _blocks[i].size(); j++) {
            this->runAction(Sequence::create(
                    DelayTime::create((i + j) / 20.f),
                    CallFunc::create([&, i, j](){
                        _blocks[i][j]->hide();
                    }),
                    NULL
            ));
        }
    }
}

void MainMenu::_addWidget(cocos2d::Node *node, float delay) {
    node->setScale(0);
    this->addChild(node, 1);

    this->runAction(Sequence::create(
            DelayTime::create(delay),
            CallFunc::create([&, node](){
                for(auto i = 0; i < _blocks.size(); i++){
                    for(auto j = 0; j < _blocks[i].size(); j++) {
                        if(_blocks[i][j]->getBoundingBox().intersectsRect(node->getBoundingBox()))
                            _blocks[i][j]->hide();
                    }
                }
            }),
            DelayTime::create(.2f),
            CallFunc::create([&, node]{
                node->runAction(ScaleTo::create(.5f, .8f));
            }),
            NULL
    ));
}
