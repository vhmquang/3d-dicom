#-------------------------------------------------
#
# Project created by QtCreator 2015-12-23T16:17:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DRR
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui
INCLUDEPATH += "C:\Program Files\VTK\include\vtk-6.3"
LIBS += "-LC:\Program Files\VTK\lib"
LIBS += -lvtkDomainsChemistry-6.3
LIBS += -lvtkFiltersFlowPaths-6.3
LIBS += -lvtkFiltersGeneric-6.3
LIBS += -lvtkFiltersHyperTree-6.3
LIBS += -lvtkFiltersParallelImaging-6.3
LIBS += -lvtkFiltersProgrammable-6.3
LIBS += -lvtkFiltersSelection-6.3
LIBS += -lvtkFiltersSMP-6.3
LIBS += -lvtkFiltersVerdict-6.3
LIBS += -lvtkverdict-6.3
LIBS += -lvtkGeovisCore-6.3
LIBS += -lvtkproj4-6.3
LIBS += -lvtkGUISupportQtOpenGL-6.3
LIBS += -lvtkGUISupportQtSQL-6.3
LIBS += -lvtkIOSQL-6.3
LIBS += -lvtksqlite-6.3
LIBS += -lvtkGUISupportQtWebkit-6.3
LIBS += -lvtkViewsQt-6.3
LIBS += -lvtkViewsInfovis-6.3
LIBS += -lvtkImagingMath-6.3
LIBS += -lvtkImagingMorphological-6.3
LIBS += -lvtkImagingStatistics-6.3
LIBS += -lvtkImagingStencil-6.3
LIBS += -lvtkInteractionImage-6.3
LIBS += -lvtkIOAMR-6.3
LIBS += -lvtkIOEnSight-6.3
LIBS += -lvtkIOExodus-6.3
LIBS += -lvtkIOExport-6.3
LIBS += -lvtkRenderingGL2PS-6.3
LIBS += -lvtkRenderingContextOpenGL-6.3
LIBS += -lvtkIOImport-6.3
LIBS += -lvtkIOInfovis-6.3
LIBS += -lvtklibxml2-6.3
LIBS += -lvtkIOLSDyna-6.3
LIBS += -lvtkIOMINC-6.3
LIBS += -lvtkIOMovie-6.3
LIBS += -lvtkoggtheora-6.3
LIBS += -lvtkIOParallel-6.3
LIBS += -lvtkjsoncpp-6.3
LIBS += -lvtkIOParallelXML-6.3
LIBS += -lvtkIOPLY-6.3
LIBS += -lvtkIOVideo-6.3
LIBS += -lvtkRenderingImage-6.3
LIBS += -lvtkRenderingLIC-6.3
LIBS += -lvtkRenderingLOD-6.3
LIBS += -lvtkRenderingQt-6.3
LIBS += -lvtkRenderingVolumeOpenGL-6.3
LIBS += -lvtkViewsContext2D-6.3
LIBS += -lvtkChartsCore-6.3
LIBS += -lvtkFiltersImaging-6.3
LIBS += -lvtkInfovisLayout-6.3
LIBS += -lvtkFiltersAMR-6.3
LIBS += -lvtkgl2ps-6.3
LIBS += -lvtkInfovisCore-6.3
LIBS += -lvtkexoIIc-6.3
LIBS += -lvtkFiltersParallel-6.3
LIBS += -lvtkIONetCDF-6.3
LIBS += -lvtkNetCDF_cxx-6.3
LIBS += -lvtkNetCDF-6.3
LIBS += -lvtkhdf5_hl-6.3
LIBS += -lvtkhdf5-6.3
LIBS += -lvtkParallelCore-6.3
LIBS += -lvtkIOXML-6.3
LIBS += -lvtkIOGeometry-6.3
LIBS += -lvtkIOXMLParser-6.3
LIBS += -lvtkexpat-6.3
LIBS += -lvtkIOLegacy-6.3
LIBS += -lvtkFiltersTexture-6.3
LIBS += -lvtkGUISupportQt-6.3
LIBS += -lvtkRenderingLabel-6.3
LIBS += -lvtkRenderingOpenGL-6.3
LIBS += -lvtkRenderingContext2D-6.3
LIBS += -lvtkViewsCore-6.3
LIBS += -lvtkInteractionWidgets-6.3
LIBS += -lvtkFiltersHybrid-6.3
LIBS += -lvtkImagingGeneral-6.3
LIBS += -lvtkImagingSources-6.3
LIBS += -lvtkFiltersModeling-6.3
LIBS += -lvtkImagingHybrid-6.3
LIBS += -lvtkIOImage-6.3
LIBS += -lvtkDICOMParser-6.3
LIBS += -lvtkIOCore-6.3
LIBS += -lvtkmetaio-6.3
LIBS += -lvtkpng-6.3
LIBS += -lvtktiff-6.3
LIBS += -lvtkjpeg-6.3
LIBS += -lvtkInteractionStyle-6.3
LIBS += -lvtkRenderingAnnotation-6.3
LIBS += -lvtkRenderingFreeType-6.3
LIBS += -lvtkftgl-6.3
LIBS += -lvtkfreetype-6.3
LIBS += -lvtkzlib-6.3
LIBS += -lvtkImagingColor-6.3
LIBS += -lvtkRenderingVolume-6.3
LIBS += -lvtkRenderingCore-6.3
LIBS += -lvtkCommonColor-6.3
LIBS += -lvtkFiltersExtraction-6.3
LIBS += -lvtkFiltersStatistics-6.3
LIBS += -lvtkalglib-6.3
LIBS += -lvtkImagingFourier-6.3
LIBS += -lvtkImagingCore-6.3
LIBS += -lvtkFiltersGeometry-6.3
LIBS += -lvtkFiltersSources-6.3
LIBS += -lvtkFiltersGeneral-6.3
LIBS += -lvtkFiltersCore-6.3
LIBS += -lvtkCommonExecutionModel-6.3
LIBS += -lvtkCommonComputationalGeometry-6.3
LIBS += -lvtkCommonDataModel-6.3
LIBS += -lvtkCommonMisc-6.3
LIBS += -lvtkCommonTransforms-6.3
LIBS += -lvtkCommonMath-6.3
LIBS += -lvtkCommonSystem-6.3
LIBS += -lvtkCommonCore-6.3
LIBS += -lvtksys-6.3
