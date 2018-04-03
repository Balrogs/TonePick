#include <Objects/GameBlock.h>
#include <Global/Utils.h>
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

    auto block = GameBlock::create(blockSize, Color4F(Color4B(79, 127, 204, 255)));

    block->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height / 2));

    this->addChild(block);

    block->appear();

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
    return false;
}

bool GameScene::_touchHandlerMove(const Touch *touch, Event *event) {
    return false;
}

bool GameScene::_touchHandlerEnd(const Touch *touch, Event *event) {
    return false;
}

bool GameScene::_isGameOver() {
    return false;
}
