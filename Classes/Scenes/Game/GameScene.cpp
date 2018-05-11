#include <UI/Clocks.h>
#include "GameScene.h"
#include "PauseLayer.h"

const int BACKGROUND_LEVEL = 1;
const int GAME_OBJECTS_LEVEL = 2;
const int UI_LEVEL = 3;
const int PAUSE_LAYER_LEVEL = 4;
const std::string PAUSE_LAYER_NAME = "PauseLayer";

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
    this->addChild(backgroundLayer, BACKGROUND_LEVEL);

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
                pauseScene();
            }
                break;
            default:
                break;
        }
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // TODO add pause button

    auto clocks = Clocks::create();
    clocks->setPosition(Vec2(
            _visibleSize.width / 2,
            _visibleSize.height - clocks->getBoundingBox().size.height * 1.2f
    ));
    this->addChild(clocks, UI_LEVEL);

    auto panel = Panel::create(blockSize, 10, Color4F(Color3B(80, 90, 255)), Color4F(Color3B(140, 90, 255)), 0);
    panel->setPosition(_visibleSize.width / 2 - blockSize.width * 10 / 2 , _visibleSize.height / 2);
    this->addChild(panel, GAME_OBJECTS_LEVEL);
    panel->appear();

    _panels.push_back(panel);

    return true;
}

bool GameScene::_touchHandlerBegin(const Touch *touch, Event *event) {
    if (_touch < 0) {
        _touch = touch->getID();
    } else {
        return false;
    }

    for(auto panel: _panels){
        _focused = panel->checkTouch(touch->getLocation());
        if(_focused != nullptr){
            if(_focused->isStatic()){
                _focused = nullptr;
            } else {
                _focused->setLocalZOrder(Panel::FOCUSED_BLOCK_LEVEL);
                _focused->runAction(Spawn::create(
                        ScaleTo::create(Panel::ACTION_TIME_INTERVAL, 1.1f),
                        MoveTo::create(Panel::ACTION_TIME_INTERVAL, _focused->getPosition() - 0.1f * _focused->getContentSize() / 2),
                        NULL
                ));
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
    if (_touch != touch->getID()) {
        return false;
    }

    return _touchEnd();
}

bool GameScene::_touchEnd() {
    _touch = -1;

    if(_focused != nullptr){
        auto panel = dynamic_cast<Panel*>(_focused->getParent());

        panel->setBlockPosition(_focused);

        _focused->setLocalZOrder(Panel::DEFAULT_LEVEL);
        _focused = nullptr;
        return true;
    }
    return true;
}

bool GameScene::isPaused() {
    return _isPaused;
}

void GameScene::pauseScene() {
    _touchEnd();

    _pause(true);
}

void GameScene::unPause() {
    _pause(false);
}

void GameScene::_pause(bool pause) {
    if(_isPaused == pause)
        return;

    _isPaused = pause;

    _pauseRecursive(this, _isPaused);

    auto pauseLayer = this->getChildByName(PAUSE_LAYER_NAME);
    if(pause){
        pauseLayer = PauseLayer::create();
        this->addChild(pauseLayer, PAUSE_LAYER_LEVEL, PAUSE_LAYER_NAME);
    } else {
        pauseLayer->removeFromParent();
    }
}

void GameScene::_pauseRecursive(Node *_node, bool _pause) {
    if (_pause)
        _node->pause();
    else
        _node->resume();

    auto &children = _node->getChildren();
    for (size_t i = 0; i < children.size(); i++) {
        _pauseRecursive(children.at(i), _pause);
    }
}

void GameScene::onQuit() {
    Director::getInstance()->popScene();
}
