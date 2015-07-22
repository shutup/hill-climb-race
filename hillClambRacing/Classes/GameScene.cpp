//
//  GameScene.cpp
//  MyTestGame
//
//  Created by shutup on 15-7-15.
//
//

#include "GameScene.h"
#include "Constant.h"
USING_NS_CC;
GameScene::GameScene() {
    // TODO Auto-generated constructor stub
    _background = nullptr;
}

GameScene::~GameScene() {
    // TODO Auto-generated destructor stub
}


bool GameScene::init() {
    if ( !Layer::init() )
    {
        return false;
    }

    isFirst = true;
    return true;
}

Scene* GameScene::createScene() {
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer= GameScene::create();
    
    scene->addChild(layer);

    return scene;
}

void GameScene::onEnter()
{
    
    Layer::onEnter();
    //add terrain
    _terrain = TerrainTest::create();
    
    this->addChild(_terrain,100);
    
    genBackground();
    
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    listener1->onTouchBegan = CC_CALLBACK_2(GameScene::touchFunc, this);
    listener1->onTouchEnded = [](Touch *pTouches, Event *pEvent){
        
    };
    auto eventDisp=Director::getInstance()->getEventDispatcher();
    eventDisp->addEventListenerWithSceneGraphPriority(listener1, this);
    //    this->scheduleUpdate();
}

void GameScene::update(float dt)
{
    float PIXELS_PER_SECOND = 100;
    static float offset = 0;
    offset += PIXELS_PER_SECOND * dt;
    
    Size textureSize = _background->getTextureRect().size;
    _background->setTextureRect(Rect(offset, 0, textureSize.width, textureSize.height));
    //add terrain
    _terrain->setOffsetX(offset);
}

//bool TextureTestScene::onTouchBegan(Touch *pTouches, Event *pEvent)
//{
////    this->genBackground();
//    Vec2 location = pTouches->getLocation();
//    static float force=1;
//    float step =5;
//    if (!isFirst) {
//        auto backTire = getChildByTag(CAR_TIRE_BACK);
//        auto backTireBody = backTire->getPhysicsBody();
//        auto frontTire = getChildByTag(CAR_TIRE_FRONT);
//        auto frontTireBody = frontTire->getPhysicsBody();
//        auto carBody = getChildByTag(CAR_BODY);
//        auto carBodyBody = carBody->getPhysicsBody();
//        if(location.x<Director::getInstance()->getVisibleSize().width/4){
//            force+=step;
//            backTireBody->applyForce(Vec2(-force, 0));
//            frontTireBody->applyForce(Vec2(-force, 0));
//            carBodyBody->applyForce(Vec2(-force, 0));
//            backTireBody->setAngularVelocity(3.0f);
//            frontTireBody->setAngularVelocity(2.0f);
//        }else if(location.x>Director::getInstance()->getVisibleSize().width/4*3){
//            backTireBody->setAngularVelocity(-2.0f);
//            frontTireBody->setAngularVelocity(-3.0f);
//            backTireBody->applyForce(Vec2(force, 0));
//            frontTireBody->applyForce(Vec2(force, 0));
//            carBodyBody->applyForce(Vec2(force, 0));
//        }
//    }else{
//        addCar(location);
//        isFirst=false;
//    }
//    return true;
//}

bool GameScene::touchFunc(Touch *pTouches, Event *pEvent)
{
//    this->genBackground();
    Vec2 location = pTouches->getLocation();
    static float force=1;
    float step =5;
    if (!isFirst) {
        auto backTire = getChildByTag(CAR_TIRE_BACK);
        auto backTireBody = backTire->getPhysicsBody();
        auto frontTire = getChildByTag(CAR_TIRE_FRONT);
        auto frontTireBody = frontTire->getPhysicsBody();
        auto carBody = getChildByTag(CAR_BODY);
        auto carBodyBody = carBody->getPhysicsBody();
        if(location.x<Director::getInstance()->getVisibleSize().width/4){
            force+=step;
            backTireBody->applyForce(Vec2(-force, 0));
            frontTireBody->applyForce(Vec2(-force, 0));
            carBodyBody->applyForce(Vec2(-force, 0));
            backTireBody->setAngularVelocity(3.0f);
            frontTireBody->setAngularVelocity(2.0f);
        }else if(location.x>Director::getInstance()->getVisibleSize().width/4*3){
            backTireBody->setAngularVelocity(-2.0f);
            frontTireBody->setAngularVelocity(-3.0f);
            backTireBody->applyForce(Vec2(force, 0));
            frontTireBody->applyForce(Vec2(force, 0));
            carBodyBody->applyForce(Vec2(force, 0));
        }
    }else{
        addCar(location);
        isFirst=false;
    }
    return true;
}
void GameScene::addCar(Vec2 p)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto boxC = Sprite::create(CAR_BODY_IMG);
    boxC->setPosition(origin + p);
    
    auto boxCBody = PhysicsBody::create();
    
    
    //row 1, col 1
    int num = 19;
    Vec2 verts[] = {
        Vec2(-38.0f / PTM_RATIO, -47.0f / PTM_RATIO),
        Vec2(-80.0f / PTM_RATIO, -38.0f / PTM_RATIO),
        Vec2(-123.0f / PTM_RATIO, 5.0f / PTM_RATIO),
        Vec2(-125.0f / PTM_RATIO, 8.0f / PTM_RATIO),
        Vec2(-125.0f / PTM_RATIO, 9.0f / PTM_RATIO),
        Vec2(-124.0f / PTM_RATIO, 10.0f / PTM_RATIO),
        Vec2(-121.0f / PTM_RATIO, 11.0f / PTM_RATIO),
        Vec2(30.0f / PTM_RATIO, 32.0f / PTM_RATIO),
        Vec2(105.0f / PTM_RATIO, 8.0f / PTM_RATIO),
        Vec2(109.0f / PTM_RATIO, 6.0f / PTM_RATIO),
        Vec2(116.0f / PTM_RATIO, -1.0f / PTM_RATIO),
        Vec2(118.0f / PTM_RATIO, -4.0f / PTM_RATIO),
        Vec2(121.0f / PTM_RATIO, -10.0f / PTM_RATIO),
        Vec2(122.0f / PTM_RATIO, -13.0f / PTM_RATIO),
        Vec2(122.0f / PTM_RATIO, -15.0f / PTM_RATIO),
        Vec2(121.0f / PTM_RATIO, -16.0f / PTM_RATIO),
        Vec2(85.0f / PTM_RATIO, -37.0f / PTM_RATIO),
        Vec2(82.0f / PTM_RATIO, -38.0f / PTM_RATIO),
        Vec2(41.0f / PTM_RATIO, -47.0f / PTM_RATIO)
    };
    
    auto boxCShape = PhysicsShapePolygon::create(verts, num);
    boxCBody->addShape(boxCShape);
    boxC->setPhysicsBody(boxCBody);
    boxCBody->setCategoryBitmask(0x01);
    boxCBody->setCollisionBitmask(0x01);
    
    addChild(boxC, 5, CAR_BODY);
    
    auto boxA = Sprite::create(CAR_TIRE_IMG);
    boxA->setPosition(origin + p +Vec2(-84,-42));
    auto boxABody = PhysicsBody::createCircle(boxA->getContentSize().width/2);
    boxABody->setCategoryBitmask(0x10);
    boxABody->setCollisionBitmask(0x10);
    boxA->setPhysicsBody(boxABody);
    addChild(boxA, 10, CAR_TIRE_BACK);
    
    auto boxB = Sprite::create(CAR_TIRE_IMG);
    boxB->setPosition(origin + p + Vec2(84, -45));
    auto boxBBody = PhysicsBody::createCircle(boxB->getContentSize().width/2);
    boxBBody->setCategoryBitmask(0x10);
    boxBBody->setCollisionBitmask(0x10);
    boxB->setPhysicsBody(boxBBody);
    addChild(boxB, 10, CAR_TIRE_FRONT);
    
    
    auto world = this->getScene()->getPhysicsWorld();
    
    
    PhysicsJointLimit* jointCALimit = PhysicsJointLimit::construct(boxABody, boxCBody, Vec2::ZERO, Vec2(-84, -42), 0.0f, 5.0f);
    PhysicsJointSpring* jointCASpring = PhysicsJointSpring::construct(boxABody,boxCBody,Vec2(0, 0), Vec2(0,0),0,0);
    
    
    PhysicsJointLimit* jointCBLimit = PhysicsJointLimit::construct(boxBBody, boxCBody, Vec2::ZERO, Vec2(84, -45), 0.0f, 5.0f);
    PhysicsJointSpring* jointCBSpring = PhysicsJointSpring::construct(boxBBody,boxCBody,Vec2(0, 0), Vec2(0,0),500,0);
    
    PhysicsJointDistance* jointABDistance = PhysicsJointDistance::construct(boxABody,
                                                                            boxBBody, Vec2(0, 0), Vec2(0,0));
    
    world->addJoint(jointCALimit);
    world->addJoint(jointCASpring);
    world->addJoint(jointCBLimit);
    world->addJoint(jointCBSpring);
    world->addJoint(jointABDistance);
}
Color4F GameScene::randombrightColor()
{
    while(true)
    {
        float requiredBrightness = 192;
        Color4B randomColor = Color4B(rand()%255,rand()%255,rand()%255,255);
        if(randomColor.r > requiredBrightness || randomColor.g > requiredBrightness || randomColor.b >requiredBrightness)
        {
            return Color4F(randomColor);
        }
    }
    return Color4F();
}

void GameScene::genBackground()
{
    if (_background)
    {
        _background->removeFromParentAndCleanup(true);
    }
    Size winSize = Director::getInstance()->getVisibleSize();
    //渐变纹理
    Color4F bgColor = this->randombrightColor();
//    auto widthNum = (int)ceilf( winSize.width/512);
//    auto heightNum = (int)ceilf( winSize.height/512);
//    while (widthNum%2!=0) {
//        widthNum++;
//    }
//    while(heightNum%2!=0) {
//        heightNum++;
//    }
//    log("widthNum:%d heightNum:%d",widthNum,heightNum);
    _background = this->spriteWithColor(bgColor, 512, 512);
    _background->setScaleX(Director::getInstance()->getVisibleSize().width/_background->getContentSize().width);
    _background->setScaleY(Director::getInstance()->getVisibleSize().height/_background->getContentSize().height);
    
    //条纹纹理
//    Color4F bgColor = this->randombrightColor();
//    Color4F color2 = this->randombrightColor();
//    int nStripes =((rand() % 4) + 1) * 2;
//    _background = this->spriteWithColor1AndColor2(bgColor, color2, 512, 512, nStripes);
    
    
    
    _background->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    //repeat
    Texture2D::TexParams tp = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
    _background->getTexture()->setTexParameters(tp);
    this->addChild(_background);
    
    //add terrain
    Color4F color3 = this->randombrightColor();
    Color4F color4 = this->randombrightColor();
    Sprite *stripes = this->spriteWithColor1AndColor2(color3, color4, 512, 512, 4);
    Texture2D::TexParams tp2 = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_CLAMP_TO_EDGE};
//    Texture2D::TexParams tp2 = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
    stripes->getTexture()->setTexParameters(tp2);
//    stripes->setPosition(winSize.width/2-256,winSize.height/2 );
//    this->addChild(stripes);
    _terrain->setStripes(stripes);
}

Sprite* GameScene::spriteWithColor(Color4F bgColor,float textureWidth,float textureHeight) {
    
    RenderTexture* rt = RenderTexture::create(textureWidth,textureHeight);
    rt->beginWithClear(bgColor.r,bgColor.g,bgColor.b,bgColor.a);
    //draw the gradient
    
    _customCommand1.init(_globalZOrder);
    _customCommand1.func = CC_CALLBACK_0(GameScene::drawGridient, this,textureWidth,textureHeight);
    auto renderer = Director::getInstance()->getRenderer();
    renderer->addCommand(&_customCommand1);
    
    //do something more
//    draw the noise
    Sprite* noise = Sprite::create("Noise.png");
    BlendFunc blendFunc = {GL_DST_COLOR,GL_ZERO};
    Size noiseSize=noise->getContentSize();
//    noise->setScaleX(Director::getInstance()->getVisibleSize().width/noiseSize.width);
//    noise->setScaleY(Director::getInstance()->getVisibleSize().height/noiseSize.height);
    noise->setBlendFunc(blendFunc);
    noise->setPosition(Vec2(textureWidth/2,textureHeight/2));
    noise->visit();
    
    rt->end();
//    renderer->render();
    return Sprite::createWithTexture(rt->getSprite()->getTexture());
}
Sprite * GameScene::spriteWithColor1AndColor2(Color4F c1, Color4F c2, float textureWidth, float textureHeight, int nStripes)
{
    // 1: Create new RenderTexture
    RenderTexture *rt = RenderTexture::create(textureWidth, textureHeight);
    
    // 2: Call CCRenderTexture:begin
    rt->beginWithClear(c1.r, c1.g, c1.b, c1.a);
    
    // 3: Draw into the texture
    
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(GameScene::drawStripes, this,c2,textureWidth,textureHeight,nStripes);
    auto renderer = Director::getInstance()->getRenderer();
    renderer->addCommand(&_customCommand);
    // Layer 4: Noise
    Sprite *noise = Sprite::create("Noise.png");
    BlendFunc blendFunc = {GL_DST_COLOR, CC_BLEND_DST};
    noise->setBlendFunc(blendFunc);
    noise->setPosition(Vec2(textureWidth / 2, textureHeight / 2));
    noise->visit();
    
    // 4: Call CCRenderTexture:end
    rt->end();
    
    // 5: Create a new Sprite from the texture
    return Sprite::createWithTexture(rt->getSprite()->getTexture());
}

void GameScene::drawStripes(Color4F c2, float textureWidth, float textureHeight, int nStripes)
{
    this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
    CC_NODE_DRAW_SETUP();
    
    {
        // Layer 1: Stripes
        Point *vertices = new Point[nStripes * 6];
        Color4F *colors = new Color4F[nStripes * 6];
        
        int nVertices = 0;
        float x1 = -textureHeight;
        float x2;
        float y1 = textureHeight;
        float y2 = 0;
        float dx = textureWidth / nStripes * 2;
        float stripeWidth = dx / 2;
        for (int i = 0; i < nStripes; ++i)
        {
            x2  = x1 + textureHeight;
            
            vertices[nVertices] = Point(x1, y1);
            colors[nVertices++] = Color4F(c2.r, c2.g, c2.b, c2.a);
            
            vertices[nVertices] = Point(x1 + stripeWidth, y1);
            colors[nVertices++] = Color4F(c2.r, c2.g, c2.b, c2.a);
            
            vertices[nVertices] = Point(x2, y2);
            colors[nVertices++] = Color4F(c2.r, c2.g, c2.b, c2.a);
            
            vertices[nVertices] = vertices[nVertices - 2];
            colors[nVertices++] = Color4F(c2.r, c2.g, c2.b, c2.a);
            
            vertices[nVertices] = vertices[nVertices - 2];
            colors[nVertices++] = Color4F(c2.r, c2.g, c2.b, c2.a);
            
            vertices[nVertices] = Point(x2 + stripeWidth, y2);
            colors[nVertices++] = Color4F(c2.r, c2.g, c2.b, c2.a);
            x1 += dx;
        }
        
//      glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION|GLProgram::VERTEX_ATTRIB_COLOR);
        GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
        
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, colors);
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)nVertices);
        //通知cocos2d-x 的renderer，让它在合适的时候调用这些OpenGL命令
//        CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 3);
        //如果出错了，可以使用这个函数来获取出错信息
        CHECK_GL_ERROR_DEBUG();
        CC_SAFE_DELETE_ARRAY(vertices);
        CC_SAFE_DELETE_ARRAY(colors);
        
    }
    
    {float gradientAlpha = 0.7f;
        Point vertices[4];
        Color4F colors[4];
        int nVertices =0;
        vertices[nVertices] = Point(0,0);
        colors[nVertices++] = Color4F(0,0,0,0);
        vertices[nVertices] = Point(textureWidth,0);
        colors[nVertices++] = Color4F(0,0,0,0);
        vertices[nVertices] = Point(0,textureHeight);
        colors[nVertices++] = Color4F(0,0,0,gradientAlpha);
        vertices[nVertices] = Point(textureWidth,textureHeight);
        colors[nVertices++] = Color4F(0,0,0,gradientAlpha);
        //这句有点问题
//        	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION|GLProgram::VERTEX_ATTRIB_COLOR);
        GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION,2,GL_FLOAT,GL_FALSE,0,vertices);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR,4,GL_FLOAT,GL_FALSE,0,colors);
        glBlendFunc(CC_BLEND_SRC,CC_BLEND_DST);
        glDrawArrays(GL_TRIANGLE_STRIP,0,(GLsizei)nVertices);
        CHECK_GL_ERROR_DEBUG();
    }
}

void GameScene::drawGridient(float textureWidth, float textureHeight)
{
    this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
    CC_NODE_DRAW_SETUP();
    
    {
        float gradientAlpha = 0.7f;
        Point vertices[4];
        Color4F colors[4];
        int nVertices =0;
        vertices[nVertices] = Point(0,0);
        colors[nVertices++] = Color4F(0,0,0,0);
        vertices[nVertices] = Point(textureWidth,0);
        colors[nVertices++] = Color4F(0,0,0,0);
        vertices[nVertices] = Point(0,textureHeight);
        colors[nVertices++] = Color4F(0,0,0,gradientAlpha);
        vertices[nVertices] = Point(textureWidth,textureHeight);
        colors[nVertices++] = Color4F(0,0,0,gradientAlpha);
        //这句有点问题
//        	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION|GLProgram::VERTEX_ATTRIB_COLOR);
        GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION,2,GL_FLOAT,GL_FALSE,0,vertices);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR,4,GL_FLOAT,GL_FALSE,0,colors);
        glBlendFunc(CC_BLEND_SRC,CC_BLEND_DST);
        glDrawArrays(GL_TRIANGLE_STRIP,0,(GLsizei)nVertices);
        CHECK_GL_ERROR_DEBUG();
    }
}