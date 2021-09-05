QT += gui widgets charts multimedia

TEMPLATE = lib
CONFIG += plugin

CONFIG += c++11
INCLUDEPATH += /Users/rong/work/include/vtk-8.2
INCLUDEPATH += /Users/rong/work/include

CONFIG(debug, debug|release) {
    DESTDIR = ../../debug/App/plugin
    OBJECTS_DIR = ../../debug/App/plugin
    MOC_DIR = ../../debug/App/plugin
    RCC_DIR = ../../debug/App/plugin
    UI_DIR = ../../debug/App/plugin
} else {
    DESTDIR = ../../release/App/plugin
    OBJECTS_DIR = ../../release/App/plugin
    MOC_DIR = ../../release/App/plugin
    RCC_DIR = ../../release/App/plugin
    UI_DIR = ../../release/App/plugin
}

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../MyApplication/myplugininterface.cpp \
    vtkplugin.cpp

HEADERS += \
    ../MyApplication/myplugininterface.h \
    vtkplugin.h

DISTFILES += FisrtWidnow.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target




LIBS += -L/usr/local/lib/  -lvtkChartsCore-8.2.1

LIBS += -L/usr/local/lib/  -lvtkCommonColor-8.2.1

LIBS += -L/usr/local/lib/  -lvtkCommonComputationalGeometry-8.2.1

LIBS += -L/usr/local/lib/  -lvtkCommonCore-8.2.1

LIBS += -L/usr/local/lib/  -lvtkCommonDataModel-8.2.1

LIBS += -L/usr/local/lib/  -lvtkCommonExecutionModel-8.2.1

LIBS += -L/usr/local/lib/  -lvtkCommonMath-8.2.1

LIBS += -L/usr/local/lib/  -lvtkCommonMisc-8.2.1

LIBS += -L/usr/local/lib/  -lvtkCommonSystem-8.2.1

LIBS += -L/usr/local/lib/  -lvtkCommonTransforms-8.2.1

LIBS += -L/usr/local/lib/  -lvtkDICOMParser-8.2.1

LIBS += -L/usr/local/lib/  -lvtkDomainsChemistry-8.2.1

LIBS += -L/usr/local/lib/  -lvtkDomainsChemistryOpenGL2-8.2.1

LIBS += -L/usr/local/lib/  -lvtkFiltersAMR-8.2.1

LIBS += -L/usr/local/lib/  -lvtkFiltersCore-8.2.1

LIBS += -L/usr/local/lib/  -lvtkFiltersExtraction-8.2.1

LIBS += -L/usr/local/lib/  -lvtkFiltersFlowPaths-8.2.1

LIBS += -L/usr/local/lib/  -lvtkFiltersGeneral-8.2.1

LIBS += -L/usr/local/lib/  -lvtkFiltersGeneric-8.2.1

LIBS += -L/usr/local/lib/  -lvtkFiltersGeometry-8.2.1

LIBS += -L/usr/local/lib/  -lvtkFiltersHybrid-8.2.1

LIBS += -L/usr/local/lib/  -lvtkFiltersHyperTree-8.2.1

LIBS += -L/usr/local/lib/  -lvtkFiltersImaging-8.2.1

LIBS += -L/usr/local/lib/  -lvtkFiltersModeling-8.2.1

LIBS += -L/usr/local/lib/  -lvtkFiltersParallel-8.2.1

LIBS += -L/usr/local/lib/  -lvtkFiltersParallelImaging-8.2.1

LIBS += -L/usr/local/lib/  -lvtkFiltersPoints-8.2.1

LIBS += -L/usr/local/lib/  -lvtkFiltersProgrammable-8.2.1

LIBS += -L/usr/local/lib/  -lvtkFiltersSMP-8.2.1

LIBS += -L/usr/local/lib/  -lvtkFiltersSelection-8.2.1

LIBS += -L/usr/local/lib/  -lvtkFiltersSources-8.2.1

LIBS += -L/usr/local/lib/  -lvtkFiltersStatistics-8.2.1

LIBS += -L/usr/local/lib/  -lvtkFiltersTexture-8.2.1

LIBS += -L/usr/local/lib/  -lvtkFiltersTopology-8.2.1

LIBS += -L/usr/local/lib/  -lvtkFiltersVerdict-8.2.1

LIBS += -L/usr/local/lib/  -lvtkGUISupportQt-8.2.1

LIBS += -L/usr/local/lib/  -lvtkGUISupportQtSQL-8.2.1

LIBS += -L/usr/local/lib/  -lvtkGeovisCore-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOAMR-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOAsynchronous-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOCityGML-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOCore-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOEnSight-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOExodus-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOExport-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOExportOpenGL2-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOExportPDF-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOGeometry-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOImage-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOImport-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOInfovis-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOLSDyna-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOLegacy-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOMINC-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOMovie-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIONetCDF-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOPLY-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOParallel-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOParallelXML-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOSQL-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOSegY-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOTecplotTable-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOVeraOut-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOVideo-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOXML-8.2.1

LIBS += -L/usr/local/lib/  -lvtkIOXMLParser-8.2.1

LIBS += -L/usr/local/lib/  -lvtkImagingColor-8.2.1

LIBS += -L/usr/local/lib/  -lvtkImagingCore-8.2.1

LIBS += -L/usr/local/lib/  -lvtkImagingFourier-8.2.1

LIBS += -L/usr/local/lib/  -lvtkImagingGeneral-8.2.1

LIBS += -L/usr/local/lib/  -lvtkImagingHybrid-8.2.1

LIBS += -L/usr/local/lib/  -lvtkImagingMath-8.2.1

LIBS += -L/usr/local/lib/  -lvtkImagingMorphological-8.2.1

LIBS += -L/usr/local/lib/  -lvtkImagingSources-8.2.1

LIBS += -L/usr/local/lib/  -lvtkImagingStatistics-8.2.1

LIBS += -L/usr/local/lib/  -lvtkImagingStencil-8.2.1

LIBS += -L/usr/local/lib/  -lvtkInfovisCore-8.2.1

LIBS += -L/usr/local/lib/  -lvtkInfovisLayout-8.2.1

LIBS += -L/usr/local/lib/  -lvtkInteractionImage-8.2.1

LIBS += -L/usr/local/lib/  -lvtkInteractionStyle-8.2.1

LIBS += -L/usr/local/lib/  -lvtkInteractionWidgets-8.2.1

LIBS += -L/usr/local/lib/  -lvtkNetCDF-8.2.1

LIBS += -L/usr/local/lib/  -lvtkParallelCore-8.2.1

LIBS += -L/usr/local/lib/  -lvtkRenderingAnnotation-8.2.1

LIBS += -L/usr/local/lib/  -lvtkRenderingContext2D-8.2.1

LIBS += -L/usr/local/lib/  -lvtkRenderingContextOpenGL2-8.2.1

LIBS += -L/usr/local/lib/  -lvtkRenderingCore-8.2.1

LIBS += -L/usr/local/lib/  -lvtkRenderingFreeType-8.2.1

LIBS += -L/usr/local/lib/  -lvtkRenderingGL2PSOpenGL2-8.2.1

LIBS += -L/usr/local/lib/  -lvtkRenderingImage-8.2.1

LIBS += -L/usr/local/lib/  -lvtkRenderingLOD-8.2.1

LIBS += -L/usr/local/lib/  -lvtkRenderingLabel-8.2.1

LIBS += -L/usr/local/lib/  -lvtkRenderingOpenGL2-8.2.1

LIBS += -L/usr/local/lib/  -lvtkRenderingQt-8.2.1

LIBS += -L/usr/local/lib/  -lvtkRenderingVolume-8.2.1

LIBS += -L/usr/local/lib/  -lvtkRenderingVolumeOpenGL2-8.2.1

LIBS += -L/usr/local/lib/  -lvtkViewsContext2D-8.2.1

LIBS += -L/usr/local/lib/  -lvtkViewsCore-8.2.1

LIBS += -L/usr/local/lib/  -lvtkViewsInfovis-8.2.1

LIBS += -L/usr/local/lib/  -lvtkViewsQt-8.2.1

LIBS += -L/usr/local/lib/  -lvtkdoubleconversion-8.2.1

LIBS += -L/usr/local/lib/  -lvtkexodusII-8.2.1

LIBS += -L/usr/local/lib/  -lvtkexpat-8.2.1

LIBS += -L/usr/local/lib/  -lvtkfreetype-8.2.1

LIBS += -L/usr/local/lib/  -lvtkgl2ps-8.2.1

LIBS += -L/usr/local/lib/  -lvtkglew-8.2.1

LIBS += -L/usr/local/lib/  -lvtkhdf5-8.2.1

LIBS += -L/usr/local/lib/  -lvtkhdf5_hl-8.2.1

LIBS += -L/usr/local/lib/  -lvtkjpeg-8.2.1

LIBS += -L/usr/local/lib/  -lvtkjsoncpp-8.2.1

LIBS += -L/usr/local/lib/  -lvtklibharu-8.2.1

LIBS += -L/usr/local/lib/  -lvtklibxml2-8.2.1

LIBS += -L/usr/local/lib/  -lvtklz4-8.2.1

LIBS += -L/usr/local/lib/  -lvtklzma-8.2.1

LIBS += -L/usr/local/lib/  -lvtkmetaio-8.2.1

LIBS += -L/usr/local/lib/  -lvtkogg-8.2.1

LIBS += -L/usr/local/lib/  -lvtkpng-8.2.1

LIBS += -L/usr/local/lib/  -lvtkproj-8.2.1

LIBS += -L/usr/local/lib/  -lvtkpugixml-8.2.1

LIBS += -L/usr/local/lib/  -lvtksqlite-8.2.1

LIBS += -L/usr/local/lib/  -lvtksys-8.2.1

LIBS += -L/usr/local/lib/  -lvtktheora-8.2.1

LIBS += -L/usr/local/lib/  -lvtktiff-8.2.1

LIBS += -L/usr/local/lib/  -lvtkverdict-8.2.1

LIBS += -L/usr/local/lib/  -lvtkzlib-8.2.1
