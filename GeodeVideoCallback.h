#ifndef GEODEVIDEOCALLBACK_H
#define GEODEVIDEOCALLBACK_H

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
using namespace std;
using namespace cv;




enum VideoType{
    EyeFish,
    Common
};

class GeodeVideoCallback : public osg::NodeCallback
{
private:
    int count;
    Mat frame;
    Mat resizeDsts;
    osg::ref_ptr<osg::Image> image;
    osg::ref_ptr<osg::Texture2D> yss;
    VideoCapture* ys;
    osg::ref_ptr<osg::StateSet> stateset;
    osg::ref_ptr<osg::Image> signal_image;
    VideoType videoT;
    int texUnit;
    EyeFishGz* gz_ys_fish;
    Mat calbrationFrame;
    cv::Mat dst;
    char srcImage[30];
    char dstImage[30];

public:
    GeodeVideoCallback::GeodeVideoCallback (/*osg::ref_ptr<osg::Image> image*/string localPath,int texUnit,VideoType videoT);

    void processFishVideo(osg::Node* node);

    void set_Fish(EyeFishGz* gz_ys_fish);

    void processCommonVideo(osg::Node* node);

    void Rotates(double angle);

    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
    {
        if(videoT ==  Common)
        {
             cout<<"process common"<<endl;
             processCommonVideo(node);
        }
        else if(videoT == EyeFish)
        {

            cout<<"process Eyefish"<<endl;
            processFishVideo(node);
        }
    }
};



#endif // GEODEVIDEOCALLBACK_H
