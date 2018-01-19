//
// Created by igor on 19.01.18.
//

#include "Variables.h"


Resolution Variables::_resolution = Resolution::HD;

const std::string Variables::FONT_NAME = "Marker Felt.ttf";

void Variables::setResolution(Resolution resolution) {
    Variables::_resolution = resolution;
}

float Variables::FONT_SIZE_S() {
    switch(Variables::_resolution){
        case SD:
            return 10.f;
        case HD:
            return 21.f;
        case IPAD:
            return 34.f;
    }
}

float Variables::FONT_SIZE() {
    switch(Variables::_resolution){
        case SD:
            return 20.f;
        case HD:
            return 42.f;
        case IPAD:
            return 68.f;
    }
}

float Variables::FONT_SIZE_2() {
    switch(Variables::_resolution){
        case SD:
            return 30.f;
        case HD:
            return 60.f;
        case IPAD:
            return 80.f;
    }
}

float Variables::H_FONT_SIZE() {
    switch(Variables::_resolution){
        case SD:
            return 42.f;
        case HD:
            return 72.f;
        case IPAD:
            return 134.f;
    }
}

long Variables::getCurrentTime() {
    std::time_t now= std::time(0);
    std::tm* now_tm= std::gmtime(&now);
    return mktime(now_tm) * 1000;
}
