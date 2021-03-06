#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vtkTransformPolyDataFilter.h>
#include <vtkPolyVertex.h>
#include <vtkFloatArray.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkDoubleArray.h>
#include <vtkFloatArray.h>


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
	setWindowTitle("VTK 7  - Multi-Object");

	//step 0: set it to a window:
	auto vw = new  QVTKOpenGLWidget(this) ;
	 renWin = vw->GetRenderWindow();
	 createTexture();


	render= vtkRenderer::New();

	render->SetBackground( 0.1, 0.2, 0.4 );

	createAxis();
	createBody()->SetTexture(texture);
	createHead()->SetTexture(texture);
	createFoot(-0.5,-2.5,0)->SetTexture(texture);
	createFoot(0.5,-2.5,0)->SetTexture(texture);

	createHand(-0.5,-1.2,0,60);

	createHand(0.5,-1,0,-60);

	renWin->AddRenderer( render );


	setCentralWidget(vw);

}

MainWindow::~MainWindow()
{
	delete ui;
}

vtkSmartPointer<vtkActor> MainWindow::createHead()
{

	vtkSmartPointer<vtkConeSource> coneSource = vtkSmartPointer<vtkConeSource>::New();
	coneSource->SetRadius(1);
	coneSource->SetHeight(2);
	coneSource->SetCenter(0, 0, 0);

	vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
	  //transform->RotateWXYZ(double angle, double x, double y, double z);
	 // transform->RotateWXYZ(80, 0, 0, 1);

	  transform->Translate(0,-1.3,0);
	  transform->RotateWXYZ(90, 0, 0, 1);
	  vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter =
			vtkSmartPointer<vtkTransformPolyDataFilter>::New();

		transformFilter->SetTransform(transform);
		transformFilter->SetInputConnection(coneSource->GetOutputPort());
		transformFilter->Update();

	vtkSmartPointer<vtkPolyDataMapper> coneMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
	coneMapper->SetInputConnection(coneSource->GetOutputPort());
	vtkSmartPointer<vtkActor> coneActor =
			vtkSmartPointer<vtkActor>::New();
	coneActor->SetMapper(coneMapper);

	coneActor->SetUserTransform(transform);

	render->AddActor(coneActor);
	return coneActor;
}

vtkSmartPointer<vtkActor> MainWindow::createBody()
{
	int i;
	//???????????????????????????????????????
	static float x[8][3]={{0,0,0,},{1,0,0},{-1,-1,0},{0,-1,0},{0,0,1},{1,0,1},{1,1,1},{0,1,1}};

	vtkPolyData *cube=vtkPolyData::New();//??????????????????????????????
	vtkPoints *points=vtkPoints ::New();//??????vtkPoints???????????????

	for(i=0;i<8;i++)points->InsertPoint(i,x[i]);//??????????????????vtkPoints?????????

	cube->SetPoints(points);//???????????????????????????????????????

	vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
	cubeSource->SetInputData(cube);


	vtkSmartPointer<vtkPolyDataMapper> cubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	cubeMapper->SetInputConnection(cubeSource->GetOutputPort());
	vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();
	cubeActor->SetMapper(cubeMapper);

	render->AddActor(cubeActor);


	return cubeActor;
}

vtkSmartPointer<vtkActor> MainWindow::createHand(float x,float y,float z,float angle)
{
	vtkSmartPointer<vtkCylinderSource> cylindeSource = vtkSmartPointer<vtkCylinderSource>:: New();
	cylindeSource->SetCenter(0,0,0);
	cylindeSource->SetHeight(1);
	cylindeSource->SetRadius(0.1);

	vtkSmartPointer<vtkPolyDataMapper> dataMap = vtkSmartPointer<vtkPolyDataMapper>::New();

	dataMap->SetInputConnection( cylindeSource->GetOutputPort());

	vtkSmartPointer<vtkActor> act = vtkSmartPointer<vtkActor>::New();
	act->SetMapper(dataMap);

	vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
	//transform->RotateWXYZ(double angle, double x, double y, double z);
	transform->RotateWXYZ(angle, 0, 0, 1);

	transform->Translate(x,y,z);
	// transform->RotateWXYZ(90, 0, 0, 1);
	vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter =
			vtkSmartPointer<vtkTransformPolyDataFilter>::New();

	transformFilter->SetTransform(transform);
	transformFilter->SetInputConnection(cylindeSource->GetOutputPort());
	transformFilter->Update();

	act->SetUserTransform(transform);

	render->AddActor(act);
	return act;

}

void MainWindow::createTexture()
{

	vtkSmartPointer<vtkBMPReader> texReader =
			vtkSmartPointer<vtkBMPReader>::New();
	texReader->SetFileName("/Users/rong/dfnet/user.bmp");

	texture = vtkSmartPointer<vtkTexture>::New();
	texture->SetInputConnection(texReader->GetOutputPort());
	texture->InterpolateOn();
}

vtkSmartPointer<vtkActor> MainWindow::createFoot(float x,float y,float z)
{
	vtkSmartPointer<vtkCylinderSource> cylindeSource = vtkSmartPointer<vtkCylinderSource>:: New();
	cylindeSource->SetCenter(0,0,0);
	cylindeSource->SetHeight(1);
	cylindeSource->SetRadius(0.1);

	vtkSmartPointer<vtkPolyDataMapper> dataMap = vtkSmartPointer<vtkPolyDataMapper>::New();

	dataMap->SetInputConnection( cylindeSource->GetOutputPort());

	vtkSmartPointer<vtkActor> act = vtkSmartPointer<vtkActor>::New();
	act->SetMapper(dataMap);

	vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
	//transform->RotateWXYZ(double angle, double x, double y, double z);
	// transform->RotateWXYZ(80, 0, 0, 1);

	transform->Translate(x,y,z);
	// transform->RotateWXYZ(90, 0, 0, 1);
	vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter =
			vtkSmartPointer<vtkTransformPolyDataFilter>::New();

	transformFilter->SetTransform(transform);
	transformFilter->SetInputConnection(cylindeSource->GetOutputPort());
	transformFilter->Update();

	act->SetUserTransform(transform);

	render->AddActor(act);
	return act;
}

void MainWindow::createCenter()
{
	//????????????
		vtkSmartPointer<vtkPoints> points=vtkSmartPointer<vtkPoints>::New();
	//    points->SetNumberOfPoints(5);//??????????????????
		points->InsertPoint(0,0,0,0);
		points->InsertPoint(1,1,0.0,0);
		points->InsertPoint(2,2,0,0);
		points->InsertPoint(3,3,0,0);
		points->InsertPoint(4,0,3,0);
		//????????????
		vtkSmartPointer<vtkPolyVertex>polyVertex=vtkSmartPointer<vtkPolyVertex>::New();
		polyVertex->GetPointIds()->SetNumberOfIds(5);//????????????Id??????????????????????????????????????????
		polyVertex->GetPointIds()->SetId(0,0);//????????????????????????point???ID?????????2????????????????????????Id???
		polyVertex->GetPointIds()->SetId(1,1);
		polyVertex->GetPointIds()->SetId(2,2);
		polyVertex->GetPointIds()->SetId(3,3);
		polyVertex->GetPointIds()->SetId(4,4);
		//????????????
		vtkSmartPointer<vtkFloatArray>pointsScalars=vtkSmartPointer<vtkFloatArray>::New();
		pointsScalars->SetNumberOfTuples(5);//??????????????????
		pointsScalars->InsertValue(0,0);//???1????????????points??????Id??????2??????????????????????????????
		pointsScalars->InsertValue(1,0);//???1????????????points??????Id??????2??????????????????????????????
		pointsScalars->InsertValue(2,0);//???1????????????points??????Id??????2??????????????????????????????
		pointsScalars->InsertValue(3,0);//???1????????????points??????Id??????2??????????????????????????????
		pointsScalars->InsertValue(4,0);//???1????????????points??????Id??????2??????????????????????????????
		//?????????????????????????????????????????????vtkUnstructureGrid
		vtkSmartPointer<vtkUnstructuredGrid> aGrid=vtkSmartPointer<vtkUnstructuredGrid>::New();
		aGrid->Allocate(1,1);
		aGrid->SetPoints(points);
		aGrid->GetPointData()->SetScalars(pointsScalars);
		aGrid->InsertNextCell(polyVertex->GetCellType(),polyVertex->GetPointIds());

		//???????????????
		   vtkSmartPointer<vtkDataSetMapper> aMapper=vtkSmartPointer<vtkDataSetMapper>::New();
		   aMapper->SetInputData(aGrid);
		   aMapper->ScalarVisibilityOn();
		   vtkSmartPointer<vtkActor> anActor=vtkSmartPointer<vtkActor>::New();
		   anActor->SetMapper(aMapper);
		   anActor->GetProperty()->SetRepresentationToPoints();
		   anActor->GetProperty()->SetDiffuseColor(1,0,0);
		   anActor->GetProperty()->SetPointSize(10);

		   render->AddActor(anActor);
}

void MainWindow::createAxis()
{
	//????????????
	vtkSmartPointer<vtkPoints> points=vtkSmartPointer<vtkPoints>::New();
	//    points->SetNumberOfPoints(5);//??????????????????
	int index = 0;
	int total = 15;
	for (int n=0; n <5;n++) {
		points->InsertPoint(index++,n,0,0);
		points->InsertPoint(index++,0,3-n,0);
		points->InsertPoint(index++,0,0,-n);
	}

	//????????????
	vtkSmartPointer<vtkPolyVertex>polyVertex=vtkSmartPointer<vtkPolyVertex>::New();
	polyVertex->GetPointIds()->SetNumberOfIds(total);//????????????Id??????????????????????????????????????????

	for (int n=0; n <total;n++) {
		polyVertex->GetPointIds()->SetId(n,n);//????????????????????????point???ID?????????2????????????????????????Id???
	}

	//????????????
	vtkSmartPointer<vtkFloatArray>pointsScalars=vtkSmartPointer<vtkFloatArray>::New();
	pointsScalars->SetNumberOfTuples(total);//??????????????????
	for (int n=0; n <total;n++) {
		pointsScalars->InsertValue(n,0);//???1????????????points??????Id??????2??????????????????????????????
	}



	//?????????????????????????????????????????????vtkUnstructureGrid
	vtkSmartPointer<vtkUnstructuredGrid> aGrid=vtkSmartPointer<vtkUnstructuredGrid>::New();
	aGrid->Allocate(1,1);
	aGrid->SetPoints(points);
	aGrid->GetPointData()->SetScalars(pointsScalars);
	aGrid->InsertNextCell(polyVertex->GetCellType(),polyVertex->GetPointIds());

	//???????????????
	vtkSmartPointer<vtkDataSetMapper> aMapper=vtkSmartPointer<vtkDataSetMapper>::New();
	aMapper->SetInputData(aGrid);
	aMapper->ScalarVisibilityOn();
	vtkSmartPointer<vtkActor> anActor=vtkSmartPointer<vtkActor>::New();
	anActor->SetMapper(aMapper);
	anActor->GetProperty()->SetRepresentationToPoints();
	anActor->GetProperty()->SetDiffuseColor(1,0,0);
	anActor->GetProperty()->SetPointSize(10);

	render->AddActor(anActor);

}

