#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>

#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <vtkPyramid.h>
#include <vtkCylinder.h>
#include <vtkAnimationCue.h>
#include <vtkAnimationScene.h>
#include <vtkCamera.h>
#include <vtkColor.h>
#include <vtkCommand.h>
#include <vtkConeSource.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkTDxInteractorStyle.h>
#include <vtkTDxInteractorStyleSettings.h>

#include <vtkEventQtSlotConnect.h>
#include "vtkGenericOpenGLRenderWindow.h"
#include <vtkDataObjectToTable.h>
#include <vtkElevationFilter.h>
#include "vtkGenericOpenGLRenderWindow.h"
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkQtTableView.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include "vtkSmartPointer.h"
#include <vtkVectorText.h>

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkVersion.h>
#include "vtkAutoInit.h"
#include <vtkTexture.h>
#include <vtkBMPReader.h>
#include <vtkAssembly.h>
#include <vtkCylinderSource.h>
#include <vtkTextSource.h>
#include <vtkBoxWidget.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkTransform.h>
#include <vtkCubeSource.h>
#include <vtkAxesActor.h>
#include <vtkCubeAxesActor.h>
#include <vtkTextProperty.h>
#include <vtkActorCollection.h>
#include <vtkCamera.h>
#include <QVTKOpenGLWidget.h>
#include <vtkTextActor.h>
#include <vtkPlaneSource.h>
#include <vtkTextureMapToCylinder.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkExtractGeometry.h>
#include <vtkImplicitBoolean.h>
#include <vtkNamedColors.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkQuadric.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSampleFunction.h>
#include <vtkShrinkFilter.h>
#include <vtkSphere.h>
#include <vtkTransform.h>
#include <vtkContourFilter.h>
#include <vtkTransformTextureCoords.h>
#include "vtkobject.h"

VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType );
VTK_MODULE_INIT(vtkRenderingContextOpenGL2);
VTK_MODULE_INIT(vtkRenderingGL2PSOpenGL2);


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	vtkSmartPointer<vtkActor> createHead();
	vtkSmartPointer<vtkActor> createBody();
	vtkSmartPointer<vtkActor> createHand(float x,float y,float z,float angle);
	vtkSmartPointer<vtkActor> createFoot(float x,float y,float z);

	vtkSmartPointer<vtkActor> createCylinder(float cx,float cy,float cz);
	vtkSmartPointer<vtkActor> createCylinder(float cx,float cy,float cz,float mx, float my, float mz,float angle);



private slots:
	void on_actionRY1_triggered();

	void on_actionRY2_triggered();

	void on_actionMX1_triggered();

	void on_actionMX2_triggered();

	void on_mv_valueChanged(int value);
	void on_rotate_valueChanged(int value);

	void on_btn1_clicked();

	void on_btn2_clicked();

	void on_btn3_clicked();

	void on_btn4_clicked();

	void on_btn9_clicked();

private:
	Ui::MainWindow *ui;

	vtkRenderWindow *renWin;
	vtkRenderer *render;
	vtkSmartPointer<vtkTexture> texture ;
	vtkSmartPointer<vtkTransformTextureCoords> transformTexture;
	QVector< vtkSmartPointer<vtkAssembly>> ltAssembly;
	QComboBox * comBox;





};
#endif // MAINWINDOW_H
