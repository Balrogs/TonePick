//
// Created by igor on 24.01.18.
//

#include "Utils.h"
#include "Variables.h"

Size Utils::_getBlockSize(Size visibleSize) {
    auto factor = Variables::FACTOR;
    auto side = visibleSize.height / factor;
    return Size(side, side);
}
