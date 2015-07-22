//
//  TerrainTest.h
//  MyTestGame
//
//  Created by shutup on 15-7-16.
//
//

#ifndef __HillClambRacing__TerrainTest__
#define __HillClambRacing__TerrainTest__

#include "cocos2d.h"

#define kMaxHillKeyPoints 10
#define kHillSegmentWidth 10
#define kMaxHillVertices 4000
#define kMaxBorderVertices 800

class TerrainTest : public cocos2d::Node
{
public:
    TerrainTest(void);
    ~TerrainTest(void);
    void generateHills();
    void resetHillVertices();
    void resetHillBody();
    virtual bool init();
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);
    void setOffsetX(float newOffsetX);
    CREATE_FUNC(TerrainTest);
    CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*, _stripes, Stripes);
    void drawHill();
private:
    int _offsetX;
    cocos2d::Point _hillKeyPoints[kMaxHillKeyPoints];
    int _fromKeyPointI;
    int _toKeyPointI;
    
    int _nHillVertices;
    cocos2d::Point _hillVertices[kMaxHillVertices];
    cocos2d::Point _hillBodyVertices[20];
    cocos2d::Point _hillTexCoords[kMaxHillVertices];
    int _nBorderVertices;
    cocos2d::Point _borderVertices[kMaxBorderVertices];
    cocos2d::CustomCommand _customCommand;
    cocos2d::PhysicsBody* hillBody;
};

#endif /* defined(__MyTestGame__TerrainTest__) */
