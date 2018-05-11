#include <Global/Utils.h>
#include <Global/Variables.h>
#include "ParentLayer.h"

const float ParentLayer::ADD_REMOVE_SPEED = 0.5f;
const float ZOOM_SPEED = 0.2f;
const float DEFAULT_SCALE = 1.f;
const float HIDE_SCALE = 0.f;
const float ZOOM_SCALE = 1.2f;

const float DELAY_FACTOR = 30.f;



bool ParentLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    _visibleSize = Director::getInstance()->getVisibleSize();
    _blockSize = Utils::_getBlockSize(_visibleSize);
    _viewTag = -1;
    _touch = -1;

    _keyboardListener = cocos2d::EventListenerKeyboard::create();
    _keyboardListener->onKeyReleased = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
        switch (keyCode) {
            case EventKeyboard::KeyCode::KEY_BREAK:
            case EventKeyboard::KeyCode::KEY_ESCAPE:
            case EventKeyboard::KeyCode::KEY_BACKSPACE: {
                _backButtonHandler();
            }
                break;
            default:
                break;
        }
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_keyboardListener, this);


    const auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(ParentLayer::_touchHandlerBegin, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(ParentLayer::_touchHandlerMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(ParentLayer::_touchHandlerEnd, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    cocos2d::Director::getInstance()->getScheduler()->schedule(
            schedule_selector(ParentLayer::_enterFrameHandler),
            this, 1.f, false
    );


    return true;
}


void ParentLayer::_fillArea(int xOffset, int width, int yOffset, int height, int zorder) {
    _xOffset = xOffset;
    _width = width;
    _yOffset = yOffset;
    _height = height;

    auto size = Utils::_getBlockSize(_visibleSize);
    auto color = Color4F(_color);

    float delay;

    for(int i = yOffset; i < height; i++){
        std::vector<MenuBlock*> row;

        for(int j = xOffset; j < width; j++){
            auto pos = Vec2(j * size.width, i * size.width);

            auto block = MenuBlock::create(size, color);
            block->setPosition(pos);
            this->addChild(block, zorder);
            delay = (i + j) / DELAY_FACTOR;
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
}

void ParentLayer::_updateColor() {
    _color = Color4B(_color.r, (GLubyte) (_color.g + 2), _color.b, _color.a);
    for(auto i = 0; i < _blocks.size(); i++){
        for(auto j = 0; j < _blocks[i].size(); j++) {
            _blocks[i][j]->paint(Color4F(_color));
        }
    }
}


void ParentLayer::_addWidget(cocos2d::Node *node, float delay) {
    node->setVisible(false);
    _widgets.push_back(node);
    this->addChild(node, 1);

    this->runAction(Sequence::create(
            DelayTime::create(delay),
            CallFunc::create([&, node](){
                for(auto i = 0; i < _blocks.size(); i++){
                    for(auto j = 0; j < _blocks[i].size(); j++) {
                        if(_blocks[i][j]->getBoundingBox().intersectsRect(node->getBoundingBox())){
                            _blocks[i][j]->hide();
                        }
                    }
                }
            }),
            DelayTime::create(ZOOM_SPEED),
            CallFunc::create([&, node]{
                node->setVisible(true);
                node->setScale(0);
                node->runAction(ScaleTo::create(ADD_REMOVE_SPEED, .8f));
            }),
            NULL
    ));
}

bool ParentLayer::_touchHandlerBegin(const cocos2d::Touch *touch, cocos2d::Event *event) {
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
                        ScaleTo::create(ZOOM_SPEED, ZOOM_SCALE),
                        MoveTo::create(ZOOM_SPEED, Vec2(
                                _focused->getPosition().x - _focused->getBoundingBox().size.width * (ZOOM_SCALE - DEFAULT_SCALE) / 2,
                                _focused->getPosition().y - _focused->getBoundingBox().size.height * (ZOOM_SCALE - DEFAULT_SCALE) / 2
                        )),
                        NULL
                ));
                return true;
            }
        }
    }

    return true;
}

bool ParentLayer::_touchHandlerMoved(const cocos2d::Touch *touch, cocos2d::Event *event) {
    for(auto i = 0; i < _blocks.size(); i++){
        for(auto j = 0; j < _blocks[i].size(); j++) {
            auto  box = _blocks[i][j]->getBoundingBox();
            if(box.containsPoint(touch->getLocation())){
                if(_focused != nullptr ){
                    if(_focused != _blocks[i][j])
                        _focused->runAction(Spawn::create(
                                ScaleTo::create(ZOOM_SPEED, DEFAULT_SCALE),
                                MoveTo::create(ZOOM_SPEED, Vec2(
                                        _focused->getPosition().x + _focused->getBoundingBox().size.width * (ZOOM_SCALE - DEFAULT_SCALE) / 2,
                                        _focused->getPosition().y + _focused->getBoundingBox().size.height * (ZOOM_SCALE - DEFAULT_SCALE) / 2
                                )),
                                NULL
                        ));
                    else
                        return true;
                }
                _focused = _blocks[i][j];
                _focused->runAction(Spawn::create(
                        ScaleTo::create(ZOOM_SPEED, ZOOM_SCALE),
                        MoveTo::create(ZOOM_SPEED, Vec2(
                                _focused->getPosition().x - _focused->getBoundingBox().size.width * (ZOOM_SCALE - DEFAULT_SCALE)/ 2,
                                _focused->getPosition().y - _focused->getBoundingBox().size.height * (ZOOM_SCALE - DEFAULT_SCALE) / 2
                        )),
                        NULL
                ));
                return true;
            }
        }
    }
}


bool ParentLayer::_touchHandlerEnd(const cocos2d::Touch *touch, cocos2d::Event *event) {
    if (_touch == touch->getID()) {
        _touch = -1;
    } else {
        return false;
    }

    if(_focused != nullptr){
        _focused->runAction(Spawn::create(
                ScaleTo::create(ZOOM_SPEED, DEFAULT_SCALE),
                MoveTo::create(ZOOM_SPEED, Vec2(
                        _focused->getPosition().x + _focused->getBoundingBox().size.width * (ZOOM_SCALE - DEFAULT_SCALE) / 2,
                        _focused->getPosition().y + _focused->getBoundingBox().size.height * (ZOOM_SCALE - DEFAULT_SCALE) / 2
                )),
                NULL
        ));
        if(_focused->getBoundingBox().containsPoint(touch->getLocation()))
            _focused->hide();
    }

    _focused = nullptr;

    return true;
}

void ParentLayer::_removeWidgetByTag(int tag, float duration) {
    this->getChildByTag(tag)->runAction(Sequence::create(
            ScaleTo::create(duration, HIDE_SCALE),
            RemoveSelf::create(),
            CallFunc::create([&, tag, duration](){
                for (auto it = _widgets.begin() ; it != _widgets.end(); ++it){
                    if((*it)->getTag() == tag){
                        _widgets.erase(it);
                        break;
                    }
                }
            }),
            NULL));
}

void ParentLayer::_removeAllWidgets() {
    for(auto widget : _widgets){
        widget->runAction(Sequence::create(
                ScaleTo::create(ADD_REMOVE_SPEED, HIDE_SCALE),
                RemoveSelf::create(),
                NULL
        ));
    }
    _widgets.clear();
}

void ParentLayer::_refill() {
    for(auto i = 0; i < _blocks.size(); i++){
        for(auto j = 0; j < _blocks[i].size(); j++) {
            this->runAction(Sequence::create(
                    DelayTime::create((i + j) / DELAY_FACTOR),
                    CallFunc::create([&, i, j](){
                        _blocks[i][j]->appear();
                    }),
                    NULL
            ));
        }
    }
}

void ParentLayer::onQuit() {
    for(auto i = 0; i < _blocks.size(); i++){
        for(auto j = 0; j < _blocks[i].size(); j++) {
            this->runAction(Sequence::create(
                    DelayTime::create((i + j) / DELAY_FACTOR),
                    CallFunc::create([&, i, j](){
                        _blocks[i][j]->hide();
                    }),
                    NULL
            ));
        }
    }
}

void ParentLayer::_enterFrameHandler(float passedTime) {
    _updateColor();
}
