//
//  GameScene.h
//  MyTestGame
//
//  Created by shutup on 15-7-15.
//
//

#ifndef __HillClimbRacing__GameScene__
#define __HillClimbRacing__GameScene__

#include "cocos2d.h"
#include "TerrainTest.h"

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    virtual void onEnter();
    //单色渐变
    cocos2d::Sprite *spriteWithColor(cocos2d::Color4F bgColor, float textureWidth, float textureHeight);
    //渐变加条纹
    cocos2d::Sprite * spriteWithColor1AndColor2(cocos2d::Color4F c1, cocos2d::Color4F c2, float textureWidth, float textureHeight, int nStripes);
    
    //随机颜色
    cocos2d::Color4F randombrightColor();
    //生成背景
    void genBackground();
    //触屏事件
    bool touchFunc(cocos2d::Touch *pTouches, cocos2d::Event *pEvent);
    virtual void update(float dt);
    GameScene();
    virtual ~GameScene();
   
    //绘制条纹的回调
    void drawStripes(cocos2d::Color4F c2, float textureWidth, float textureHeight, int nStripes);
    //绘制渐变的回调
    void drawGridient(float textureWidth, float textureHeight);
    void addCar(cocos2d::Vec2 position);
    private :
    bool isFirst;
    cocos2d::Sprite* _background;
    cocos2d::CustomCommand _customCommand;
    cocos2d::CustomCommand _customCommand1;
    TerrainTest* _terrain;
};
#endif /* defined(__MyTestGame__TextureTestScene__) */
