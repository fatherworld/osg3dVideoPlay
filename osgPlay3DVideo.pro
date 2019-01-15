#-------------------------------------------------
#
# Project created by QtCreator 2018-11-27T15:34:22
#
#-------------------------------------------------

QT       -= gui
TARGET = osgPlay3DVideo
TEMPLATE = lib
CONFIG += staticlib

SOURCES += osgplay3dvideo.cpp \
    GeodeVideoCallback.cpp

HEADERS += osgplay3dvideo.h \
    GeodeVideoCallback.h

INCLUDEPATH += $$PWD/shared/opencv/include/opencv \
               $$PWD/shared/opencv/include \
               $$PWD/shared/opencv/include/opencv2\

INCLUDEPATH += C:/osg/osgmake/osgearth_bin/include \
               C:/osg/qt/qt-everywhere-opensource-src-4.8.6/include \
               C:/osg/qt/qt-everywhere-opensource-src-4.8.6/include/QtOpenGL

LIBS +=  $$PWD/shared/opencv/x64/vc10/lib/opencv_calib3d330d.lib \
         $$PWD/shared/opencv/x64/vc10/lib/opencv_core330d.lib \
         $$PWD/shared/opencv/x64/vc10/lib/opencv_dnn330d.lib \
         $$PWD/shared/opencv/x64/vc10/lib/opencv_features2d330d.lib \
         $$PWD/shared/opencv/x64/vc10/lib/opencv_flann330d.lib \
         $$PWD/shared/opencv/x64/vc10/lib/opencv_highgui330d.lib \
         $$PWD/shared/opencv/x64/vc10/lib/opencv_imgcodecs330d.lib \
         $$PWD/shared/opencv/x64/vc10/lib/opencv_imgproc330d.lib \
         $$PWD/shared/opencv/x64/vc10/lib/opencv_ml330d.lib \
         $$PWD/shared/opencv/x64/vc10/lib/opencv_objdetect330d.lib \
         $$PWD/shared/opencv/x64/vc10/lib/opencv_photo330d.lib \
         $$PWD/shared/opencv/x64/vc10/lib/opencv_shape330d.lib \
         $$PWD/shared/opencv/x64/vc10/lib/opencv_stitching330d.lib \
         $$PWD/shared/opencv/x64/vc10/lib/opencv_superres330d.lib \
         $$PWD/shared/opencv/x64/vc10/lib/opencv_video330d.lib \
         $$PWD/shared/opencv/x64/vc10/lib/opencv_videoio330d.lib \
         $$PWD/shared/opencv/x64/vc10/lib/opencv_videostab330d.lib \
         F:/software/vs2015_workplace/qt/EyeFishGz/mylibs/debug/EyeFishGz.lib

LIBS +=-LC:/osg/osgmake/osgearth_bin/lib \
    -losgd \
    -losgWidgetd \
    -losgUtild \
    -losgSimd \
    -losgTerraind \
    -losgDBd \
    -losgFXd \
    -losgViewerd \
    -losgTextd \
    -losgGAd \
    -losgQtd \
    -losgShadowd \
    -losgVolumed \
    -losgParticled \
    -losgAnimationd \
    -lOpenThreadsd \
    -losgEarthd \
    -losgEarthUtild \
    -losgEarthSymbologyd \
    -losgEarthAnnotationd \
    -losgEarthFeaturesd \
    -losgEarthQtd \
    -losgManipulatord \
    -lQtOpenGLd4 \
    -LC:/osg/Geo3D/build/bin \
    -learthLight \
    -learthSky \
    -lGeoCore \
    -lGeoUtil \
    -lGeoDrivers \
    -lGeoSymbology \
    -lGeoPluginFramework \
    -lGeoTimeAxis \
    -lGeoUI \
    -ldtUtil \
    -lgisAnalyzer \

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
