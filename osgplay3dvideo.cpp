#include "osgplay3dvideo.h"
#include "GeodeVideoCallback.h"
#if 0
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





//通过回调函数进行视频帧的贴图，走通
class tankNodeCallbacks : public osg::NodeCallback
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
    int texUnit;
    EyeFishGz* gz_ys_fish;
    Mat calbrationFrame;
    cv::Mat dst;
    char srcImage[30];
    char dstImage[30];


public:
    tankNodeCallbacks::tankNodeCallbacks(/*osg::ref_ptr<osg::Image> image*/string localPath,int texUnit,EyeFishGz* gz_ys_fish)
    {
       yss = new osg::Texture2D();

       this->texUnit = texUnit;
       this->gz_ys_fish = gz_ys_fish;

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

    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
    {
        sprintf(srcImage,"F:\\software\\vs2015_workplace\\qt\\TestProgramTeam\\srcImage\\%d.jpg",count);
        sprintf(dstImage,"F:\\software\\vs2015_workplace\\qt\\TestProgramTeam\\dstImage\\%d.jpg",count);
        count++;
        osg::ref_ptr<osg::Geode> my = dynamic_cast<osg::Geode*>(node);
        if(my)
        {
            if(!ys)
            {
                cout<<"ys is NULL"<<endl;
            }
#if 1
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
            else
            {
                 cout<<"current count is"<<count<<endl;
            }
#endif

        }
   }
    void Rotates(double angle){
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

 };
#endif


//由三角形创建节点(此函数是对华为会议室进行顶点坐标和纹理坐标的匹配,无适用性)
/**
   @author shanye
 * @brief OsgPlay3DVideo::createNodeByTriangle
 */
void OsgPlay3DVideo::createNodeByTriangle1()
{

    //设置顶点坐标
    osg::ref_ptr<osg::Vec3Array> vc = new osg::Vec3Array();

/*
    vc->push_back(osg::Vec3(-1.0f, -0.5f, 0.375f));
    vc->push_back(osg::Vec3(0.32f, -0.5f, -0.5f));
    vc->push_back(osg::Vec3(0.32f, 0.5f, -0.5f));
    vc->push_back(osg::Vec3(0.32f, 0.5f, -0.5f));
    vc->push_back(osg::Vec3(-1.0f, 0.5f, 0.375f));
    vc->push_back(osg::Vec3(-1.0f, -0.5f, 0.375f));

    vc->push_back(osg::Vec3(0.32f, -0.5f, -0.5f));
    vc->push_back(osg::Vec3(1.0f, -0.5f, -0.09f));
    vc->push_back(osg::Vec3(1.0f, 0.5f, -0.09f));
    vc->push_back(osg::Vec3(1.0f, 0.5f, -0.09f));
    vc->push_back(osg::Vec3(0.32f,0.5f,-0.5f));
    vc->push_back(osg::Vec3(0.32f, -0.5f, -0.5f));

    vc->push_back(osg::Vec3(0.32f, -0.5f, -0.5f));
    vc->push_back(osg::Vec3(1.0f, -0.5f, -0.09f));
    vc->push_back(osg::Vec3(1.0f, -0.5f, 0.5f));
    vc->push_back(osg::Vec3(1.0f, -0.5f, 0.5f));
    vc->push_back(osg::Vec3(-1.0f, -0.5f, 0.375f));
    vc->push_back(osg::Vec3(0.32f, -0.5f, -0.5f));
*/

    vc->push_back(osg::Vec3(-5.0f, -2.5f, 6.875f));
    vc->push_back(osg::Vec3(1.60f, -2.5f,2.5f));
    vc->push_back(osg::Vec3(1.60f, 2.5f, 2.5f));
    vc->push_back(osg::Vec3(1.60f, 2.5f, 2.5f));
    vc->push_back(osg::Vec3(-5.0f, 2.5f, 6.875f));
    vc->push_back(osg::Vec3(-5.0f, -2.5f,6.875f));

    vc->push_back(osg::Vec3(1.60f, -2.5f, 2.5f));
    vc->push_back(osg::Vec3(5.0f, -2.5f, 4.55f));
    vc->push_back(osg::Vec3(5.0f, 2.5f,4.55f));
    vc->push_back(osg::Vec3(5.0f, 2.5f,4.55f));
    vc->push_back(osg::Vec3(1.60f,2.5f,2.5f));
    vc->push_back(osg::Vec3(1.60f, -2.5f,2.5f));

    vc->push_back(osg::Vec3(1.60f, -2.5f, 2.5f));
    vc->push_back(osg::Vec3(5.0f, -2.5f, 4.55f));
    vc->push_back(osg::Vec3(5.0f, -2.5f, 7.5f));
    vc->push_back(osg::Vec3(5.0f, -2.5f, 7.5f));
    vc->push_back(osg::Vec3(-5.0f, -2.5f, 6.875f));
    vc->push_back(osg::Vec3(1.60f, -2.5f, 2.5f));

    geom->setVertexArray(vc.get());


    //设置纹理坐标
    osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array();

    geom->setTexCoordArray(this->texUnit,vt.get());

    vt->push_back(osg::Vec2(0.0f,0.875f));
    vt->push_back(osg::Vec2(0.66f,0.44f));
    vt->push_back(osg::Vec2(0.66f,0.125f));
    vt->push_back(osg::Vec2(0.66f,0.125f));
    vt->push_back(osg::Vec2(0.0f,0.0f));
    vt->push_back(osg::Vec2(0.0f,0.875f));

    vt->push_back(osg::Vec2( 0.66f, 0.44f));
    vt->push_back(osg::Vec2(1.0f, 0.59f));
    vt->push_back(osg::Vec2(1.0f,0.29f));
    vt->push_back(osg::Vec2(1.0f,0.29f));
    vt->push_back(osg::Vec2(0.66f,0.0f));
    vt->push_back(osg::Vec2(0.66f, 0.44f));

    vt->push_back(osg::Vec2(0.66f, 0.44f));
    vt->push_back(osg::Vec2(1.0f, 0.59f));
    vt->push_back(osg::Vec2(1.0f, 1.0f));
    vt->push_back(osg::Vec2( 1.0f, 1.0f));
    vt->push_back(osg::Vec2(0.0f, 0.875f));
    vt->push_back(osg::Vec2(0.66f, 0.44f));



    //设置法线
    osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
    nc->push_back(osg::Vec3(0.0f,-1.0f,0.0f));

    geom->setNormalArray(nc.get());
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

    //添加图元
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES,0,18));
}




//由三角形创建节点
/**
 * @brief OsgPlay3DVideo::createNodeByTriangle
 */
void OsgPlay3DVideo::createNodeByTriangle()
{
#if 0
    //设置顶点坐标
//    osg::ref_ptr<osg::Vec3Array> vc = new osg::Vec3Array();

/*
    vc->push_back(osg::Vec3(-1.0f, -0.5f, 0.375f));
    vc->push_back(osg::Vec3(0.32f, -0.5f, -0.5f));
    vc->push_back(osg::Vec3(0.32f, 0.5f, -0.5f));
    vc->push_back(osg::Vec3(0.32f, 0.5f, -0.5f));
    vc->push_back(osg::Vec3(-1.0f, 0.5f, 0.375f));
    vc->push_back(osg::Vec3(-1.0f, -0.5f, 0.375f));

    vc->push_back(osg::Vec3(0.32f, -0.5f, -0.5f));
    vc->push_back(osg::Vec3(1.0f, -0.5f, -0.09f));
    vc->push_back(osg::Vec3(1.0f, 0.5f, -0.09f));
    vc->push_back(osg::Vec3(1.0f, 0.5f, -0.09f));
    vc->push_back(osg::Vec3(0.32f,0.5f,-0.5f));
    vc->push_back(osg::Vec3(0.32f, -0.5f, -0.5f));

    vc->push_back(osg::Vec3(0.32f, -0.5f, -0.5f));
    vc->push_back(osg::Vec3(1.0f, -0.5f, -0.09f));
    vc->push_back(osg::Vec3(1.0f, -0.5f, 0.5f));
    vc->push_back(osg::Vec3(1.0f, -0.5f, 0.5f));
    vc->push_back(osg::Vec3(-1.0f, -0.5f, 0.375f));
    vc->push_back(osg::Vec3(0.32f, -0.5f, -0.5f));
*/

    vc->push_back(osg::Vec3(-5.0f, -2.5f, 6.875f));
    vc->push_back(osg::Vec3(1.60f, -2.5f,2.5f));
    vc->push_back(osg::Vec3(1.60f, 2.5f, 2.5f));
    vc->push_back(osg::Vec3(1.60f, 2.5f, 2.5f));
    vc->push_back(osg::Vec3(-5.0f, 2.5f, 6.875f));
    vc->push_back(osg::Vec3(-5.0f, -2.5f,6.875f));

    vc->push_back(osg::Vec3(1.60f, -2.5f, 2.5f));
    vc->push_back(osg::Vec3(5.0f, -2.5f, 4.55f));
    vc->push_back(osg::Vec3(5.0f, 2.5f,4.55f));
    vc->push_back(osg::Vec3(5.0f, 2.5f,4.55f));
    vc->push_back(osg::Vec3(1.60f,2.5f,2.5f));
    vc->push_back(osg::Vec3(1.60f, -2.5f,2.5f));

    vc->push_back(osg::Vec3(1.60f, -2.5f, 2.5f));
    vc->push_back(osg::Vec3(5.0f, -2.5f, 4.55f));
    vc->push_back(osg::Vec3(5.0f, -2.5f, 7.5f));
    vc->push_back(osg::Vec3(5.0f, -2.5f, 7.5f));
    vc->push_back(osg::Vec3(-5.0f, -2.5f, 6.875f));
    vc->push_back(osg::Vec3(1.60f, -2.5f, 2.5f));

    geom->setVertexArray(vc.get());


    //设置纹理坐标
 //   osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array();

    geom->setTexCoordArray(this->texUnit,vt.get());

    vt->push_back(osg::Vec2(0.0f,0.875f));
    vt->push_back(osg::Vec2(0.66f,0.44f));
    vt->push_back(osg::Vec2(0.66f,0.125f));
    vt->push_back(osg::Vec2(0.66f,0.125f));
    vt->push_back(osg::Vec2(0.0f,0.0f));
    vt->push_back(osg::Vec2(0.0f,0.875f));

    vt->push_back(osg::Vec2( 0.66f, 0.44f));
    vt->push_back(osg::Vec2(1.0f, 0.59f));
    vt->push_back(osg::Vec2(1.0f,0.29f));
    vt->push_back(osg::Vec2(1.0f,0.29f));
    vt->push_back(osg::Vec2(0.66f,0.0f));
    vt->push_back(osg::Vec2(0.66f, 0.44f));

    vt->push_back(osg::Vec2(0.66f, 0.44f));
    vt->push_back(osg::Vec2(1.0f, 0.59f));
    vt->push_back(osg::Vec2(1.0f, 1.0f));
    vt->push_back(osg::Vec2( 1.0f, 1.0f));
    vt->push_back(osg::Vec2(0.0f, 0.875f));
    vt->push_back(osg::Vec2(0.66f, 0.44f));



    //设置法线
    osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
    nc->push_back(osg::Vec3(0.0f,-1.0f,0.0f));

    geom->setNormalArray(nc.get());
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

    //添加图元
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES,0,18));
#else

    geom->setVertexArray(vc.get());



    geom->setTexCoordArray(this->texUnit,vt.get());


    //设置法线

    osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
    nc->push_back(osg::Vec3(0.0f,-1.0f,0.0f));

    geom->setNormalArray(nc.get());
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

    //添加图元
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES,0,this->vc->size()));


#endif
}

//由四边形创建节点
/**
 * @brief OsgPlay3DVideo::createNodeByTriangle
 */
void OsgPlay3DVideo::createNodeByQuad()
{
#if 0
    //设置顶点坐标
//    osg::ref_ptr<osg::Vec3Array> vc = new osg::Vec3Array();

/*
    vc->push_back(osg::Vec3(-1.0f, -0.5f, 0.375f));
    vc->push_back(osg::Vec3(0.32f, -0.5f, -0.5f));
    vc->push_back(osg::Vec3(0.32f, 0.5f, -0.5f));
    vc->push_back(osg::Vec3(0.32f, 0.5f, -0.5f));
    vc->push_back(osg::Vec3(-1.0f, 0.5f, 0.375f));
    vc->push_back(osg::Vec3(-1.0f, -0.5f, 0.375f));

    vc->push_back(osg::Vec3(0.32f, -0.5f, -0.5f));
    vc->push_back(osg::Vec3(1.0f, -0.5f, -0.09f));
    vc->push_back(osg::Vec3(1.0f, 0.5f, -0.09f));
    vc->push_back(osg::Vec3(1.0f, 0.5f, -0.09f));
    vc->push_back(osg::Vec3(0.32f,0.5f,-0.5f));
    vc->push_back(osg::Vec3(0.32f, -0.5f, -0.5f));

    vc->push_back(osg::Vec3(0.32f, -0.5f, -0.5f));
    vc->push_back(osg::Vec3(1.0f, -0.5f, -0.09f));
    vc->push_back(osg::Vec3(1.0f, -0.5f, 0.5f));
    vc->push_back(osg::Vec3(1.0f, -0.5f, 0.5f));
    vc->push_back(osg::Vec3(-1.0f, -0.5f, 0.375f));
    vc->push_back(osg::Vec3(0.32f, -0.5f, -0.5f));
*/

    vc->push_back(osg::Vec3(-5.0f, -2.5f, 6.875f));
    vc->push_back(osg::Vec3(1.60f, -2.5f,2.5f));
    vc->push_back(osg::Vec3(1.60f, 2.5f, 2.5f));
    vc->push_back(osg::Vec3(1.60f, 2.5f, 2.5f));
    vc->push_back(osg::Vec3(-5.0f, 2.5f, 6.875f));
    vc->push_back(osg::Vec3(-5.0f, -2.5f,6.875f));

    vc->push_back(osg::Vec3(1.60f, -2.5f, 2.5f));
    vc->push_back(osg::Vec3(5.0f, -2.5f, 4.55f));
    vc->push_back(osg::Vec3(5.0f, 2.5f,4.55f));
    vc->push_back(osg::Vec3(5.0f, 2.5f,4.55f));
    vc->push_back(osg::Vec3(1.60f,2.5f,2.5f));
    vc->push_back(osg::Vec3(1.60f, -2.5f,2.5f));

    vc->push_back(osg::Vec3(1.60f, -2.5f, 2.5f));
    vc->push_back(osg::Vec3(5.0f, -2.5f, 4.55f));
    vc->push_back(osg::Vec3(5.0f, -2.5f, 7.5f));
    vc->push_back(osg::Vec3(5.0f, -2.5f, 7.5f));
    vc->push_back(osg::Vec3(-5.0f, -2.5f, 6.875f));
    vc->push_back(osg::Vec3(1.60f, -2.5f, 2.5f));

    geom->setVertexArray(vc.get());


    //设置纹理坐标
 //   osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array();

    geom->setTexCoordArray(this->texUnit,vt.get());

    vt->push_back(osg::Vec2(0.0f,0.875f));
    vt->push_back(osg::Vec2(0.66f,0.44f));
    vt->push_back(osg::Vec2(0.66f,0.125f));
    vt->push_back(osg::Vec2(0.66f,0.125f));
    vt->push_back(osg::Vec2(0.0f,0.0f));
    vt->push_back(osg::Vec2(0.0f,0.875f));

    vt->push_back(osg::Vec2( 0.66f, 0.44f));
    vt->push_back(osg::Vec2(1.0f, 0.59f));
    vt->push_back(osg::Vec2(1.0f,0.29f));
    vt->push_back(osg::Vec2(1.0f,0.29f));
    vt->push_back(osg::Vec2(0.66f,0.0f));
    vt->push_back(osg::Vec2(0.66f, 0.44f));

    vt->push_back(osg::Vec2(0.66f, 0.44f));
    vt->push_back(osg::Vec2(1.0f, 0.59f));
    vt->push_back(osg::Vec2(1.0f, 1.0f));
    vt->push_back(osg::Vec2( 1.0f, 1.0f));
    vt->push_back(osg::Vec2(0.0f, 0.875f));
    vt->push_back(osg::Vec2(0.66f, 0.44f));



    //设置法线
    osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
    nc->push_back(osg::Vec3(0.0f,-1.0f,0.0f));

    geom->setNormalArray(nc.get());
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

    //添加图元
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES,0,18));
#else

    geom->setVertexArray(vc.get());



    geom->setTexCoordArray(this->texUnit,vt.get());


    //设置法线

    osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
    nc->push_back(osg::Vec3(0.0f,-1.0f,0.0f));

    geom->setNormalArray(nc.get());
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

    //添加图元
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,this->vc->size()));


#endif
}



//set顶点坐标
void OsgPlay3DVideo::setVerticeCoor(osg::ref_ptr<osg::Vec3Array> vc)
{
    if(vc->size() == 0)
    {
        cout<<"error is vc->size ==0 "<<endl;
        return;
    }
    this->vc = vc;

}

//set纹理坐标
void OsgPlay3DVideo::setTextureCoor(osg::ref_ptr<osg::Vec2Array> vt)
{
    if(vt->size() == 0)
    {
        cout<<"error is vt->size ==0 "<<endl;
        return;
    }
    this->vt = vt;

}


//创建二维纹理状态对象,参数是纹理单元编号
void OsgPlay3DVideo::createTexture2DState()
{
    //创建状态集对象
    stateset = new osg::StateSet();
    //创建二维纹理对象

    texture = new osg::Texture2D();

    texture->setDataVariance(osg::Object::DYNAMIC);

    //设置贴图
    texture->setImage(image.get());

    stateset->setTextureAttributeAndModes(texUnit,texture.get(),osg::StateAttribute::ON);
}


void OsgPlay3DVideo::setFish(EyeFishGz* gz_ys_fish)
{

    if(!gz_ys_fish)
    {
        cout<<"error is EyeFishGz Null" <<endl;
        return;
    }
    this->gz_ys_fish = gz_ys_fish;
}


OsgPlay3DVideo::OsgPlay3DVideo(string VideoPath,string ImagePath,int texUnit,VideoType videoT)
{
   if(!gz_ys_fish)
   {
       cout<<"error is gz_ys_fish is NULL"<<endl;
       return;
   }


   if(VideoPath.length() == 0)
   {
       cout<<"error is VideoPath == 0"<<endl;
       return;
   }

   if(texUnit < 0 )
   {
       cout<<"error is texUnit  <0"<<endl;
       return;
   }

   this->videoT = videoT;

   this->gz_ys_fish = gz_ys_fish;

   this->texUnit = texUnit;

   this->image = osgDB::readRefImageFile(ImagePath);

   this->geom = new osg::Geometry();

   this->videoPath = VideoPath;

   this->geode = new osg::Geode();
   vc = new osg::Vec3Array();
   vt = new osg::Vec2Array();



}

/**
   osg模型发黑(光照的问题，直接把模型的光照关闭)
 * @brief OsgPlay3DVideo::closeModelLight
 */

void OsgPlay3DVideo::closeModelLight()
{
    //
    geode->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF|osg::StateAttribute::OVERRIDE);

}

/**
   处理模型节点的主逻辑
 * @brief OsgPlay3DVideo::processGeode
 */

void OsgPlay3DVideo::processGeode(NodeType nt)
{
    if(!this->geode)
    {
        return ;
    }


    if(nt == gz_Trangle)
    {
        createNodeByTriangle();
    }
    else if(nt == gz_QUad)
    {
        createNodeByQuad();
    }


    this->geode->addDrawable(geom.get());


    createTexture2DState();
    //使用二维纹理
    geode->setStateSet(stateset.get());




    GeodeVideoCallback* geodeVideoCb = new GeodeVideoCallback(this->videoPath,this->texUnit,this->videoT);

    if(this->videoT == EyeFish)
    {
        geodeVideoCb->set_Fish(this->gz_ys_fish);

    }
    geode->setUpdateCallback(geodeVideoCb);

    closeModelLight();

}

/**
 * 返回得到绑定了3d视频的纹理节点
 * @brief OsgPlay3DVideo::Get3dVideoNode
 * @return
 */
osg::ref_ptr<osg::Geode> OsgPlay3DVideo::Get3dVideoNode()
{
   return this->geode;
}

