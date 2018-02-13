

#ifndef TONEPICK_PARENTLAYER_H
#define TONEPICK_PARENTLAYER_H


#include <cocos/2d/CCLayer.h>
#include <Objects/MenuBlock.h>

class ParentLayer : public cocos2d::Layer {
public:
    virtual void onQuit();

protected:
    int _touch;
    MenuBlock* _focused;
    std::vector<std::vector<MenuBlock*>> _blocks;
    std::vector<cocos2d::Node*> _widgets;
    cocos2d::Size _visibleSize;
    Color4B _color;

    void _fillArea(int xOffset, int width, int yOffset, int height);
    void _refill();
    void _updateColor();

    bool _touchHandlerBegin(const cocos2d::Touch *touch, cocos2d::Event *event);
    bool _touchHandlerMoved(const cocos2d::Touch *touch, cocos2d::Event *event);
    bool _touchHandlerEnd(const cocos2d::Touch *touch, cocos2d::Event *event);

    virtual void _enterFrameHandler(float passedTime);

    void _addWidget(cocos2d::Node* node, float delay);
    void _removeWidgetByTag(int tag, float duration);
    void _removeAllWidgets();

private:
    int _xOffset;
    int _width;
    int _yOffset;
    int _height;
};

#endif //TONEPICK_PARENTLAYER_H
