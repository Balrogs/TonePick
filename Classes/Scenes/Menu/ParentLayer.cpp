#include <Global/Utils.h>
#include <Global/Variables.h>
#include "ParentLayer.h"

void ParentLayer::_fillArea(int xOffset, int width, int yOffset, int height) {
    _xOffset = xOffset;
    _width = width;
    _yOffset = yOffset;
    _height = height;

    auto size = Utils::_getBlockSize(_visibleSize);
    auto color = Color4F(_color);

    auto delay = 0.f;

    for(int i = yOffset; i < height; i++){
        std::vector<MenuBlock*> row;

        for(int j = xOffset; j < width; j++){
            auto pos = Vec2(j * size.width, i * size.width);

            auto block = MenuBlock::create(size, color);
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
    node->setScale(0);
    _widgets.push_back(node);
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
                        ScaleTo::create(0.2f, 1.2f),
                        MoveTo::create(0.2f, Vec2(_focused->getPosition().x - _focused->getBoundingBox().size.width * .2f / 2,_focused->getPosition().y - _focused->getBoundingBox().size.height * .2f / 2)),
                        NULL));
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


bool ParentLayer::_touchHandlerEnd(const cocos2d::Touch *touch, cocos2d::Event *event) {
    if (_touch == touch->getID()) {
        _touch = -1;
    } else {
        return false;
    }

    if(_focused != nullptr){
        _focused->runAction(Spawn::create(
                ScaleTo::create(0.2f, 1.f),
                MoveTo::create(0.2f, Vec2(_focused->getPosition().x + _focused->getBoundingBox().size.width * .2f / 2,_focused->getPosition().y + _focused->getBoundingBox().size.height * .2f / 2)),
                NULL));
        if(_focused->getBoundingBox().containsPoint(touch->getLocation()))
            _focused->hide();
    }

    _focused = nullptr;

    return true;
}

void ParentLayer::_removeWidgetByTag(int tag, float duration) {
    this->getChildByTag(tag)->runAction(Sequence::create(
            ScaleTo::create(duration, 0.f),
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
                ScaleTo::create(.5f, 0.f),
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
                    DelayTime::create((i + j) / 20.f),
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
                    DelayTime::create((i + j) / 20.f),
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
