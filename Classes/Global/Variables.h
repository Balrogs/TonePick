//
// Created by igor on 19.01.18.
//

#ifndef TONEPICK_VARIABLES_H
#define TONEPICK_VARIABLES_H

#include "cocos2d.h"

enum Resolution {
    SD,
    HD,
    IPAD
};

class Variables {
public:

    static const std::string EFFECTS_ON_BUTTON;
    static const std::string EFFECTS_OFF_BUTTON;
    static const std::string BACK_BUTTON;


    static const std::string FONT_NAME;
    static float FONT_SIZE_S();
    static float FONT_SIZE();
    static float FONT_SIZE_2();
    static float H_FONT_SIZE();

    static long getCurrentTime();
    static void setResolution(Resolution resolution);

    static const int FACTOR;
private:
    static Resolution _resolution;

};

#endif //TONEPICK_VARIABLES_H
