#include"GeodeVideoCallback.h"
#include <QDebug>
/**将图像旋转固定角度
 * @brief Rotates
 * @param angle
 */
void GeodeVideoCallback::Rotates(double angle){
     /*
      cv::Mat src = cv::imread(imagepath.c_str());
      cv::imshow("src", src);
*/
      cv::Point2f center(calbrationFrame.cols / 2, calbrationFrame.rows / 2);
      cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1);
      cv::Rect bbox = cv::RotatedRect(center, calbrationFrame.size(), angle).boundingRect();

      rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
      rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;

      cv::warpAffine(calbrationFrame, dst, rot, bbox.size());
}



/**
   opencv中图像转osg图像需要注意opencv中的rb通道与osg中通道相反
 * @brief CVMat_2_OSGImage
 * @author shanye
 * @param cvimg
 * @return
 */
static osg::ref_ptr<osg::Image> CVMat_2_OSGImage(cv::Mat& cvimg)
{
//    osg::Image osgframe2();
    osg::Image* osgframe = new osg::Image();
    osgframe->setImage(cvimg.cols, cvimg.rows, 3,
        GL_RGB, GL_BGR, GL_UNSIGNED_BYTE, cvimg.data,
        osg::Image::NO_DELETE, 1);
    return osgframe;
}

GeodeVideoCallback::GeodeVideoCallback (/*osg::ref_ptr<osg::Image> image*/string localPath,int texUnit,VideoType videoT)
{
    this->videoT = videoT;
    this->texUnit = texUnit;
    yss = new osg::Texture2D();

    yss->setDataVariance(osg::Object::DYNAMIC);
    #if 0
    ys = new VideoCapture(0);
    #else
    ys = new VideoCapture(localPath);
    if(!ys)
    {
        cout<<"create ys failed"<<endl;

    }
    count  = 0;
    #endif
    //  this->count =  count;
    //  signal_image =  image;

    stateset = new osg::StateSet();

}

void GeodeVideoCallback::set_Fish(EyeFishGz* gz_ys_fish)
{
    if(!gz_ys_fish)
    {
        cout<<"error is gz_ys_fish is NULL"<<endl;
        return;
    }
    this->gz_ys_fish = gz_ys_fish;
}


void GeodeVideoCallback::processFishVideo(osg::Node* node)
{
    sprintf(srcImage,"F:\\software\\vs2015_workplace\\qt\\TestProgramTeam\\srcImage\\%d.jpg",count);
    sprintf(dstImage,"F:\\software\\vs2015_workplace\\qt\\TestProgramTeam\\dstImage\\%d.jpg",count);

    cout<<"processFishVideo"<<endl;

    osg::ref_ptr<osg::Geode> my = dynamic_cast<osg::Geode*>(node);
    if(my)
    {

        qDebug()<<"it my not null";
        if(ys)
        {
            qDebug()<<"ys is not NULL";
        }
#if 0
        (*ys)>>frame;
        stateset = my->getStateSet();

        yss = dynamic_cast<osg::Texture2D *>(stateset->getTextureAttribute(texUnit,osg::StateAttribute::TEXTURE)->asTexture());
        if (yss)
        {
#if 0
        image =  CVMat_2_OSGImage(frame);
#else


        calbrationFrame = gz_ys_fish->CalibrationMat(frame);

        imwrite(dstImage,calbrationFrame);

        Rotates(8);

   //     imwrite(dstImage,dst);
#if 0

        imshow("res",frame);
        waitKey(1);

#endif

        image =  CVMat_2_OSGImage(dst);

#endif
        if(image)
        {
            cout<<"image is not NULL"<<endl;
        }
        yss->setImage(image.get());
      //  yss->setImage(signal_image.get());
        cout<<"hello world"<<endl;
        }
#endif
    }
}

void GeodeVideoCallback::processCommonVideo(osg::Node* node)
{
    osg::ref_ptr<osg::Geode> my = dynamic_cast<osg::Geode*>(node);
    if(my)
    {
        (*ys)>>frame;
        stateset = my->getStateSet();

        yss = dynamic_cast<osg::Texture2D *>(stateset->getTextureAttribute(texUnit,osg::StateAttribute::TEXTURE)->asTexture());
        if (yss)
        {
#if 0
            imshow("res",frame);
            waitKey(1);
#endif
     //   cv::resize(frame,resizeDsts,Size(2048,1024),0, 0, INTER_LINEAR);


        image =  CVMat_2_OSGImage(frame);
        if(image)
        {
            cout<<"image is not NULL"<<endl;
        }
        yss->setImage(image.get());
      //  yss->setImage(signal_image.get());
        cout<<"hello world"<<endl;
        }
        else
        {
             cout<<"current count is"<<count<<endl;
        }

    }
}
