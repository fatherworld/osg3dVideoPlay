#ifndef OSGPLAY3DVIDEO_H
#define OSGPLAY3DVIDEO_H
#include<iostream>
#include<stdio.h>
#include<string>
#include<vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <QDebug>
#include<osgViewer/Viewer>
#include<osgDB/ReadFile>
#include<osg/DrawPixels>
#include<osg/Geode>
#include<osg/MatrixTransform>
#include<osgViewer/ViewerEventHandlers>
#include<osgGA/StateSetManipulator>
#include<iostream>
#include<osgUtil/Optimizer>
#include"F:\software\vs2015_workplace\qt\EyeFishGz\eyefishgz.h"
#include "GeodeVideoCallback.h"

using namespace std;
using namespace cv;
enum NodeType
{
    gz_Trangle,
    gz_QUad
};



class OsgPlay3DVideo
{
private:
    osg::ref_ptr<osg::Geode> geode ;//返回的geode节点
    osg::ref_ptr<osg::StateSet> stateset;//返回的纹理状态
    osg::ref_ptr<osg::Texture2D> texture;//纹理单元
    osg::ref_ptr<osg::Geometry> geom;//几何体集合
    string videoPath;//视频路径
    osg::ref_ptr<osg::Image> image; //单帧先验图片
    int texUnit;    //纹理单元编号
    //顶点坐标
    osg::ref_ptr<osg::Vec3Array> vc ;
    //纹理坐标
    osg::ref_ptr<osg::Vec2Array> vt;
    //摄像头的类型
    VideoType videoT;
    //鱼眼摄像头处理
    EyeFishGz* gz_ys_fish;

public:

    OsgPlay3DVideo(string VideoPath,string ImagePath,int texUnit,VideoType videoT);
    void createNodeByQuad();
    void setFish(EyeFishGz* gz_ys_fish);

    void processGeode(NodeType nt);
    void setVerticeCoor(osg::ref_ptr<osg::Vec3Array> vc);
    void setTextureCoor(osg::ref_ptr<osg::Vec2Array> vt);
    void createTexture2DState();
    void closeModelLight();
    void createNodeByTriangle();
    void createNodeByTriangle1();
    osg::ref_ptr<osg::Geode> Get3dVideoNode();
};

#endif // OSGPLAY3DVIDEO_H
