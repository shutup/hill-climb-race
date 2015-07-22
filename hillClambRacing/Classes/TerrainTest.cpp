//
//  TerrainTest.cpp
//  MyTestGame
//
//  Created by shutup on 15-7-16.
//
//

#include "TerrainTest.h"
USING_NS_CC;

TerrainTest::TerrainTest(void)
{
    _stripes = nullptr;
    _offsetX = 0;
    _fromKeyPointI = 0;
    _toKeyPointI = 0;
}

TerrainTest::~TerrainTest(void)
{
    CC_SAFE_RELEASE_NULL(_stripes);
}

void TerrainTest::generateHills()
{
    Size winSize = Director::getInstance()->getVisibleSize();
    float x = 0;
    float y = winSize.height / 2;
    for (int i = 0; i < kMaxHillKeyPoints; ++i)
    {
        _hillKeyPoints[i] = Point(x, y);
        x += winSize.width / 2;
        y = rand() % (int)winSize.height;
    }
}

void TerrainTest::resetHillVertices()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    static int prevFromKeyPointI = -1;
    static int prevToKeyPointI = -1;
    
    // key points interval for drawing
    while (_hillKeyPoints[_fromKeyPointI + 1].x < _offsetX - winSize.width / 8 / this->getScale())
    {
        _fromKeyPointI++;
    }
    while (_hillKeyPoints[_toKeyPointI].x < _offsetX + winSize.width * 9 / 8 / this->getScale())
    {
        _toKeyPointI++;
    }
    
    if (prevFromKeyPointI != _fromKeyPointI || prevToKeyPointI != _toKeyPointI)
    {
        // vertices for visible area
        _nHillVertices = 0;
        _nBorderVertices = 0;
        Point p0, p1, pt0, pt1;
        p0 = _hillKeyPoints[_fromKeyPointI];
        for (int i = _fromKeyPointI + 1; i < _toKeyPointI + 1; ++i)
        {
            p1 = _hillKeyPoints[i];
            
            // triangle strip between p0 and p1
            int hSegments = floorf((p1.x - p0.x) / kHillSegmentWidth);
            float dx = (p1.x - p0.x) / hSegments;
            float da = M_PI / hSegments;
            float ymid = (p0.y + p1.y) / 2;
            float ampl = (p0.y - p1.y) / 2;
            pt0 = p0;
            _borderVertices[_nBorderVertices++] = pt0;
            for (int j = 1; j < hSegments + 1; ++j)
            {
                pt1.x = p0.x + j * dx;
                pt1.y = ymid + ampl * cosf(da * j);
                _borderVertices[_nBorderVertices++] = pt1;
                
                _hillVertices[_nHillVertices] = Point(pt0.x, 0);
                _hillTexCoords[_nHillVertices++] = Point(pt0.x / 512, 1.0f);
                _hillVertices[_nHillVertices] = Point(pt1.x, 0);
                _hillTexCoords[_nHillVertices++] = Point(pt1.x / 512, 1.0f);
                
                _hillVertices[_nHillVertices] = Point(pt0.x, pt0.y);
                _hillTexCoords[_nHillVertices++] = Point(pt0.x / 512, 0);
                _hillVertices[_nHillVertices] = Point(pt1.x, pt1.y);
                _hillTexCoords[_nHillVertices++] = Point(pt1.x / 512, 0);
                
                pt0 = pt1;
            }
            
            p0 = p1;
        }
        
        prevFromKeyPointI = _fromKeyPointI;
        prevToKeyPointI = _toKeyPointI;
    }
}
void TerrainTest::resetHillBody()
{
    if (hillBody) {
        hillBody->removeFromWorld();
    }
    hillBody = PhysicsBody::createEdgeChain(_borderVertices, _nBorderVertices);
    hillBody ->setDynamic(false);
    setPhysicsBody(hillBody);
}
bool TerrainTest::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Node::init());
        this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE));
        this->generateHills();
        this->resetHillVertices();
        this->resetHillBody();
        bRet = true;
    } while (0);
    
    return bRet;
}

void TerrainTest::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
    Node::draw(renderer,transform,flags);
//    CC_NODE_DRAW_SETUP();
    
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(TerrainTest::drawHill, this);
    renderer->addCommand(&_customCommand);
//    GL::bindTexture2D(_stripes->getTexture()->getName());
////    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_TexCoords);
//    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
//    ccDrawColor4F(1.0f, 1.0f, 1.0f, 1.0f);
//    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, _hillVertices);
//    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, _hillTexCoords);
//    
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)_nHillVertices);
//    
//    
//    for (int i = MAX(_fromKeyPointI, 1); i <= _toKeyPointI; ++i)
//    {
//        ccDrawColor4F(1.0, 0, 0, 1.0);
//        ccDrawLine(_hillKeyPoints[i - 1], _hillKeyPoints[i]);
//        
//        ccDrawColor4F(1.0, 1.0, 1.0, 1.0);
//        Point p0 = _hillKeyPoints[i - 1];
//        Point p1 = _hillKeyPoints[i];
//        int hSegments = floorf((p1.x - p0.x) / kHillSegmentWidth);
//        float dx = (p1.x - p0.x) / hSegments;
//        float da = M_PI / hSegments;
//        float ymid = (p0.y + p1.y) / 2;
//        float ampl = (p0.y - p1.y) / 2;
//        
//        Point pt0, pt1;
//        pt0 = p0;
//        for (int j = 0; j < hSegments + 1; ++j)
//        {
//            pt1.x = p0.x + j * dx;
//            pt1.y = ymid + ampl * cosf(da * j);
//            
//            ccDrawLine(pt0, pt1);
//            
//            pt0 = pt1;
//        }
//    }
}
void TerrainTest::drawHill()
{
    CC_NODE_DRAW_SETUP();
    GL::bindTexture2D(_stripes->getTexture()->getName());
    //    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_TexCoords);
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
    ccDrawColor4F(1.0f, 1.0f, 1.0f, 1.0f);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, _hillVertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, _hillTexCoords);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)_nHillVertices);
    
}
void TerrainTest::setOffsetX(float newOffsetX)
{
    _offsetX = newOffsetX;
//    setScale(0.25);
    this->setPosition(Point(-_offsetX * this->getScale(), 0));
    this->resetHillVertices();
    this->resetHillBody();
}