//
// Created by igor on 24.01.18.
//

#include "MainScene.h"
#include "MainMenu.h"

USING_NS_CC;


MainScene* MainScene::_instance = nullptr;

MainScene *MainScene::getInstance() {
    return _instance;
}

MainScene *MainScene::create() {
    MainScene *ret = new(std::nothrow) MainScene();
    if (ret && ret->init()) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
    }
    _instance = ret;
    return ret;
}

bool MainScene::init() {
    if (!Scene::initWithPhysics()) {
        return false;
    }
    auto backgroundLayer = LayerColor::create(Color4B(46, 51, 58, 255));

    this->addChild(backgroundLayer);

    _main = MainMenu::create();

    pushMain(_main);
    return true;
}

void MainScene::replaceMain(ParentLayer *layer) {
    while(_mainStack.size()){
        popMain();
    }
    pushMain(layer);
}

void MainScene::pushMain(ParentLayer *layer) {
    _main = layer;
    _mainStack.push(_main);
    this->addChild(_main, 4);
}

void MainScene::popMain() {
    if (!_mainStack.empty()) {
        this->removeChild(_mainStack.top());
        _mainStack.pop();
    }
}

ParentLayer *MainScene::getMain() {
    return _main;
}


void MainScene::popAndReplace() {
    while(_mainStack.size()){
        popMain();
    }
}
