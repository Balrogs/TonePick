//
// Created by igor on 11.05.18.
//

#include <Global/Variables.h>
#include "Clocks.h"


bool Clocks::init() {
    if(!Node::init()){
        return false;
    }

    _startTime = Variables::getCurrentTime();
    _current = Variables::getCurrentTime();

    _clock = cocos2d::Label::createWithTTF("", Variables::FONT_NAME, Variables::FONT_SIZE());
    _clock->setString(_convertTimestamp(0));
    this->addChild(_clock);

    this->schedule(SEL_SCHEDULE(&Clocks::update), .1f);

    return true;
}

void Clocks::update(float dt) {
    Node::update(dt);

    _current += 100;

    _clock->setString(_convertTimestamp(_current - _startTime));
}

long Clocks::getTime() {
    return _current;
}

std::string Clocks::_convertTimestamp(long timestamp) {
    int hours   = (int) ((timestamp / (1000 * 60 * 60)) % 24);
    int minutes = (int) ((timestamp / (1000 * 60)) % 60);
    int seconds = (int) (timestamp / 1000) % 60;
    int millis = (int) (timestamp % 1000 / 100);

    if(hours <= 0){
        return StringUtils::format("%02d:%02d,%01d", minutes, seconds, millis);
    } else {
        return StringUtils::format("%02d:%02d:%02d,%01d", hours, minutes, seconds, millis);
    }
}

Rect Clocks::getBoundingBox() const {
    return _clock->getBoundingBox();
}
