#include "GameScene.h"


GameScene* GameScene::_instance = nullptr;

GameScene *GameScene::getInstance() {
    return _instance;
}

GameScene *GameScene::createScene(int type) {
    GameScene *ret = new(std::nothrow) GameScene();
    if (ret && ret->init(type)) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
    }
    _instance = ret;
    return ret;
}

bool GameScene::init(int type) {
    if (!Scene::init()) {
        return false;
    }
    auto backgroundLayer = LayerColor::create(Color4B(46, 51, 58, 255));
    this->addChild(backgroundLayer);

    _visibleSize = Director::getInstance()->getVisibleSize();
    auto blockSize = Utils::_getBlockSize(_visibleSize);
    _touch = -1;

    const auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::_touchHandlerBegin, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::_touchHandlerMove, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::_touchHandlerEnd, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
        switch (keyCode) {
            case EventKeyboard::KeyCode::KEY_BREAK:
            case EventKeyboard::KeyCode::KEY_ESCAPE:
            case EventKeyboard::KeyCode::KEY_BACKSPACE: {
                Director::getInstance()->popScene();
            }
                break;
            default:
                break;
        }
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);


    auto panel = Panel::create(blockSize, 10, Color4F(Color3B(80, 90, 255)), Color4F(Color3B(140, 90, 255)), 0);
    panel->setPosition(_visibleSize.width / 2 - blockSize.width * 10 / 2 , _visibleSize.height / 2);
    this->addChild(panel);
    panel->appear();

    _panels.push_back(panel);

    CCLOG("Equality: %d%%", panel->countEquality());

    return true;
}

bool GameScene::isPaused() {
    return _isPaused;
}

void GameScene::pauseScene() {
    _pause(true);
}

void GameScene::unPause() {
    _pause(false);
}

void GameScene::_pause(bool pause) {
    if(_isPaused == pause)
        return;

    _isPaused = pause;
}

void GameScene::onQuit() {

}

void GameScene::_keyBoardPressedHandler(EventKeyboard::KeyCode keyCode, Event *event) {

}

void GameScene::_keyBoardReleasedHandler(EventKeyboard::KeyCode keyCode, Event *event) {

}

bool GameScene::_touchHandlerBegin(const Touch *touch, Event *event) {
    for(auto panel: _panels){
        _focused = panel->checkTouch(touch->getLocation());
        if(_focused != nullptr){
            if(_focused->isStatic()){
                _focused = nullptr;
            } else {
                _focusedStartPos = _focused->getPosition();
//                _focused->runAction(Spawn::create(
//                        ScaleTo::create(.4f, 1.1f),
//                        MoveTo::create(.4f, _focused->getPosition() - 0.1f * _focused->getContentSize() / 2),
//                        NULL
//                ));
            }
            return true;
        }
    }

    return false;
}

bool GameScene::_touchHandlerMove(const Touch *touch, Event *event) {
    if(_focused == nullptr){
        return false;
    } else {
        auto panel = dynamic_cast<Panel*>(_focused->getParent());
        panel->move(_focused, + touch->getDelta().x);
        return true;
    }
}

bool GameScene::_touchHandlerEnd(const Touch *touch, Event *event) {
    if(_focused != nullptr){
        auto panel = dynamic_cast<Panel*>(_focused->getParent());

        panel->setBlockPosition(_focused);

        _focused = nullptr;
        _focusedStartPos = Vec2();
        return true;
    }
    return true;
}

bool GameScene::_isGameOver() {
    return false;
}

bool GameScene::_checkIntersection() {
    return false;
}
