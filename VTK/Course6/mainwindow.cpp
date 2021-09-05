#include "mainwindow.h"
#include "ui_mainwindow.h"

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

VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType );
VTK_MODULE_INIT(vtkRenderingContextOpenGL2);
VTK_MODULE_INIT(vtkRenderingGL2PSOpenGL2);



class vtkMyCallback : public vtkCommand
{
public:
  static vtkMyCallback *New()
	{ return new vtkMyCallback; }
  void Execute(vtkObject *caller, unsigned long, void*) override
  {
	  vtkTransform *t = vtkTransform::New();
	  vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
	  widget->GetTransform(t);
	  widget->GetProp3D()->SetUserTransform(t);
	  t->Delete();
  }
};


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowTitle("VTK Course 5 - Cube Texture");

	//step 0: set it to a window:
	auto vw = new  QVTKOpenGLWidget(this) ;
	vtkRenderWindow *renWin = vw->GetRenderWindow();


	vtkRenderer *render= vtkRenderer::New();

	render->SetBackground( 0.1, 0.2, 0.4 );

	int i;
	//定义点在三维坐标系中的坐标
	static float x[8][3]={{0,0,0,},{0.3,0,0},{-0.3,-0.3,0},{0,-0.3,0},{0,0,0.3},{0.3,0,0.3},{0.3,0.3,0.3},{0,0.3,0.3}};

	vtkPolyData *cube=vtkPolyData::New();//创建数据集对象的实例
	vtkPoints *points=vtkPoints ::New();//创建vtkPoints对象的实例

	for(i=0;i<8;i++)points->InsertPoint(i,x[i]);//将点坐标插入vtkPoints对象中

	cube->SetPoints(points);//为数据集添加点，定义其几何

	vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
	cubeSource->SetInputData(cube);


	vtkSmartPointer<vtkPolyDataMapper> cubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	cubeMapper->SetInputConnection(cubeSource->GetOutputPort());
	vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();
	cubeActor->SetMapper(cubeMapper);
	render->AddActor(cubeActor);

	render->AddActor(cubeActor);
	renWin->AddRenderer( render );

	vtkSmartPointer<vtkBMPReader> texReader =
			vtkSmartPointer<vtkBMPReader>::New();
	texReader->SetFileName("/Users/rong/dfnet/user.bmp");

	vtkSmartPointer<vtkTexture> texture =
			vtkSmartPointer<vtkTexture>::New();
	texture->SetInputConnection(texReader->GetOutputPort());
	texture->InterpolateOn();


	cubeActor->SetTexture(texture);


	setCentralWidget(vw);

}

MainWindow::~MainWindow()
{
	delete ui;
}

