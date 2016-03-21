TEMPLATE = subdirs

#
#git clone https://github.com/qtproject/qtcharts
#

#.subdir #Use the specified subdirectory instead of SUBDIRS value.
#.file #Specify the subproject pro file explicitly. Cannot be used in conjunction with .subdir modifier.
#.depends #This subproject depends on specified subproject.
#.makefile #The makefile of subproject. Available only on platforms that use makefiles.
#.target #Base string used for makefile targets related to this subproject. Available only on platforms that use makefiles.

OpenCVUtility.file = $$PWD/OpenCVUtility/OpenCVUtility.pro
FirstTest.file = $$PWD/FirstTest/FirstTest.pro
CoreMat.file = $$PWD/Core/Mat/Mat.pro
CoreMatx.file = $$PWD/Core/Matx/Matx.pro
CoreVec.file = $$PWD/Core/Vec/Vec.pro
CoreMatImage.file = $$PWD/Core/MatImage/MatImage.pro
CoreMatSaveLoad.file = $$PWD/Core/MatSaveLoad/MatSaveLoad.pro
CoreMatRGB.file = $$PWD/Core/MatRGB/MatRGB.pro
CoreMatLAB.file = $$PWD/Core/MatLAB/MatLAB.pro
CoreMatHSV.file = $$PWD/Core/MatHSV/MatHSV.pro
CoreMatHLS.file = $$PWD/Core/MatHLS/MatHLS.pro
CoreMatXYZ.file = $$PWD/Core/MatXYZ/MatXYZ.pro
CoreMatLUV.file = $$PWD/Core/MatLUV/MatLUV.pro
CoreMatPaint.file = $$PWD/Core/Paint/Paint.pro
CoreMatROI.file = $$PWD/Core/MatROI/ImgROI.pro
CoreRect.file = $$PWD/Core/Rect/Rect.pro

FilterBox.file = $$PWD/Filter/BoxFilter/BoxFilter.pro
FilterBlur.file = $$PWD/Filter/Blur/Blur.pro
FilterBilateral.file = $$PWD/Filter/Bilateral/Bilateral.pro

GeometricImageTransformationsPolar.file  = $$PWD/GeometricImageTransformations/Polar/Polar.pro
GeometricImageTransformationsAffine.file = $$PWD/GeometricImageTransformations/Affine/Affine.pro
GeometricImageTransformationsRemap.file  = $$PWD/GeometricImageTransformations/Remap/Remap.pro
GeometricImageTransformationsResize.file = $$PWD/GeometricImageTransformations/Resize/Resize.pro
GeometricImageTransformationsPerspective.file = $$PWD/GeometricImageTransformations/Perspective/Perspective.pro

CoreMat.depends += OpenCVUtility
CoreMatx.depends += OpenCVUtility
CoreVec.depends += OpenCVUtility
CoreMatImage.depends += OpenCVUtility
CoreMatSaveLoad.depends += OpenCVUtility
CoreMatRGB.depends += OpenCVUtility
CoreMatLAB.depends += OpenCVUtility
CoreMatHSV.depends += OpenCVUtility
CoreMatHLS.depends += OpenCVUtility
CoreMatLUV.depends += OpenCVUtility
CoreRect.depends += OpenCVUtility
CoreMatXYZ.depends += OpenCVUtility
CoreMatROI.depends += OpenCVUtility
CoreMatPaint.depends += OpenCVUtility
FilterBilateral.depends += OpenCVUtility
FilterBlur.depends+=OpenCVUtility

GeometricImageTransformationsPolar.depends+=OpenCVUtility
GeometricImageTransformationsResize.depends+=OpenCVUtility
GeometricImageTransformationsRemap.depends+=OpenCVUtility
GeometricImageTransformationsAffine.depends+=OpenCVUtility
GeometricImageTransformationsPerspective.depends+=OpenCVUtility

FirstTest.depends += OpenCVUtility

SUBDIRS += OpenCVUtility
SUBDIRS += FirstTest
SUBDIRS += CoreMatROI
SUBDIRS += CoreMat
SUBDIRS += CoreMatx
SUBDIRS += CoreVec
SUBDIRS += CoreRect
SUBDIRS += CoreMatSaveLoad
SUBDIRS += CoreMatImage
SUBDIRS += CoreMatLAB
SUBDIRS += CoreMatRGB
SUBDIRS += CoreMatHSV
SUBDIRS += CoreMatHLS
SUBDIRS += CoreMatLUV
SUBDIRS += CoreMatXYZ
SUBDIRS += CoreMatPaint
SUBDIRS += GeometricImageTransformationsPolar
SUBDIRS += GeometricImageTransformationsResize
SUBDIRS += GeometricImageTransformationsPerspective
SUBDIRS += GeometricImageTransformationsAffine
SUBDIRS += GeometricImageTransformationsRemap
SUBDIRS += FilterBilateral
SUBDIRS += FilterBlur
SUBDIRS += FilterBox
