//
// Created by igor on 03.04.18.
//

#ifndef TONEPICK_PAUSELAYER_H
#define TONEPICK_PAUSELAYER_H

#include <Scenes/Menu/ParentLayer.h>
#include "cocos2d.h"

class PauseLayer : public ParentLayer {
public:
    CREATE_FUNC(PauseLayer);

    bool init();

protected:
    virtual void  _backButtonHandler() override;
    void  _addContent();
    void onQuit() override;

};


#endif //TONEPICK_PAUSELAYER_H
