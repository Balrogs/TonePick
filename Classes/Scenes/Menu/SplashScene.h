#ifndef TONEPICK_SPLASHSCENE_H
#define TONEPICK_SPLASHSCENE_H

#include "cocos2d.h"

class SplashScene : public cocos2d::LayerColor {
public:
    CREATE_FUNC(SplashScene);
    static cocos2d::Scene* createScene();

    virtual bool init();

private:
    void GoToMainMenuScene(float dt);
};


#endif //TONEPICK_SPLASHSCENE_H
