//
// Created by igor on 11.05.18.
//

#ifndef TONEPICK_CLOCKS_H
#define TONEPICK_CLOCKS_H

#include "cocos2d.h"

USING_NS_CC;

class Clocks : public Node {
public:
    CREATE_FUNC(Clocks);

    bool init();

    void update(float dt);

    long getTime();

    Rect getBoundingBox() const override;

private:
    Label* _clock;
    long _startTime;
    long _current;

    std::string _convertTimestamp(long timestamp);
};


#endif //TONEPICK_CLOCKS_H
