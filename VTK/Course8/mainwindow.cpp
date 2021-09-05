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
#include <vtkMath.h>
#include <QGridLayout>
#include <vtkJPEGReader.h>
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkTextureMapToPlane.h>
#include <vtkUnstructuredGrid.h>
#include <vtkAppendPolyData.h>
#include <vtkCubeAxesActor2D.h>
#include <vtkPolyDataNormals.h>
#include <vtkPNGReader.h>

#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>


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
	setWindowTitle("VTK 8  - Multi-Object");

	//step 0: set it to a window:
	auto vw = new  QVTKOpenGLWidget(this) ;
	 renWin = vw->GetRenderWindow();
	 createTexture();


	render= vtkRenderer::New();

	render->SetBackground( 0.1, 0.2, 0.4 );

	createTexture();
	//createAxis();
	createHead();
	createBody();
	createHand(0,0,0,0);

	vtkSmartPointer<vtkAssembly> ass = vtkSmartPointer<vtkAssembly>::New() ;

	ltAssembly << ass;

	ass->AddPart(header.getActor());//this can be multiple
	ass->AddPart(body.getActor());//this can be multiple

	//cubeActor->SetTexture(texture);
	ass->AddPart(hand_left.getActor());//this can be multiple
	ass->AddPart(hand_right.getActor());//this can be multiple
	ass->AddPart(foot_left.getActor());//this can be multiple
	ass->AddPart(foot_right.getActor());//this can be multiple

	rotateHand(hand_left,30,1,0,0, 0.2,-0.2,0);
	rotateHand(hand_right,-30,0,0,0, -0.1,-0.2,0);
	ass->SetOrigin(0,0,0);
	render->AddActor(ass);

	//render->AddActor( createCubeerrr());

	//setBodyTexture();
	setHeadTexture();
	hand_left.setTexture("/Users/rong/work/bb.jpeg");
	hand_right.setTexture("/Users/rong/work/bb.jpeg");
	foot_left.setTexture("/Users/rong/work/bb.jpeg");
	foot_right.setTexture("/Users/rong/work/bb.jpeg");

	body.setTexture("/Users/rong/dfnet/suit.jpg");


	//绘制
	   vtkCamera *camera = vtkCamera::New();
	  camera->SetPosition(1,1,20);
	  camera->SetFocalPoint(0,0,0);

	render->SetActiveCamera(camera);

	renWin->AddRenderer( render );


	//setCentralWidget(vw);
	QGridLayout * layout1 = new QGridLayout(this);
	vw->setSizePolicy( QSizePolicy::Expanding,QSizePolicy::Expanding);
	layout1->addWidget(vw,0,0);
	ui->frame->setLayout(layout1);


	comBox = new QComboBox(this);
	QStringList lt;
	for (int n=0; n< 9 ;n++)
		lt << "item- "+QString::number(n);
	comBox->addItems( lt);
	ui->toolBar->addWidget(comBox);


	connect(ui->horizontalSlider_2,&QSlider::valueChanged, this, &MainWindow::on_mv_valueChanged);
	connect(ui->horizontalSlider_3,&QSlider::valueChanged, this, &MainWindow::on_mv_valueChanged);
	connect(ui->horizontalSlider,&QSlider::valueChanged, this, &MainWindow::on_mv_valueChanged);

	connect(ui->verticalSlider,&QSlider::valueChanged, this, &MainWindow::on_rotate_valueChanged);
	connect(ui->verticalSlider_2,&QSlider::valueChanged, this, &MainWindow::on_rotate_valueChanged);
	connect(ui->verticalSlider_3,&QSlider::valueChanged, this, &MainWindow::on_rotate_valueChanged);

}

MainWindow::~MainWindow()
{
	delete ui;
}

vtkSmartPointer<vtkActor> MainWindow::createHead()
{

	vtkSmartPointer<vtkSphereSource> coneSource = vtkSmartPointer<vtkSphereSource>::New();
	coneSource->SetRadius(1);
	//coneSource->SetHeight(2);
	coneSource->SetCenter(0, 3, 0);

	header.setSource( coneSource);

	//render->AddActor(header.getActor());
	return header.getActor();
}

vtkSmartPointer<vtkActor> MainWindow::createBody()
{
	vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();

	cubeSource->SetCenter(0,1,0);
	cubeSource->SetXLength(2);
	cubeSource->SetYLength(2.5);
	cubeSource->SetZLength(1);
	body.setSource(cubeSource);
	//render->AddActor(body.getActor());
	return body.getActor();
}

vtkSmartPointer<vtkActor> MainWindow::createHand(float x,float y,float z,float angle)
{
	vtkSmartPointer<vtkCylinderSource> cylindeSourceLeft = vtkSmartPointer<vtkCylinderSource>:: New();
	cylindeSourceLeft->SetCenter(2,1,0);
	cylindeSourceLeft->SetHeight(1);
	cylindeSourceLeft->SetRadius(0.3);

	hand_left.setSource(cylindeSourceLeft);

	//render->AddActor(hand_left.getActor());


	vtkSmartPointer<vtkCylinderSource> cylindeSourceRight = vtkSmartPointer<vtkCylinderSource>:: New();
	cylindeSourceRight->SetCenter(-2,1,0);
	cylindeSourceRight->SetHeight(1);
	cylindeSourceRight->SetRadius(0.3);

	hand_right.setSource(cylindeSourceRight);

	//render->AddActor(hand_right.getActor());

	vtkSmartPointer<vtkCylinderSource> cylindeSourceFL = vtkSmartPointer<vtkCylinderSource>:: New();
	cylindeSourceFL->SetCenter(-0.6,-1,0);
	cylindeSourceFL->SetHeight(1);
	cylindeSourceFL->SetRadius(0.3);

	foot_left.setSource(cylindeSourceFL);

	//render->AddActor(foot_left.getActor());


	vtkSmartPointer<vtkCylinderSource> cylindeSourceFR = vtkSmartPointer<vtkCylinderSource>:: New();
	cylindeSourceFR->SetCenter(0.6,-1,0);
	cylindeSourceFR->SetHeight(1);
	cylindeSourceFR->SetRadius(0.3);

	foot_right.setSource(cylindeSourceFR);

	//render->AddActor(foot_right.getActor());

	return hand_left.getActor();

//	vtkSmartPointer<vtkPolyDataMapper> dataMap = vtkSmartPointer<vtkPolyDataMapper>::New();

//	dataMap->SetInputConnection( cylindeSource->GetOutputPort());

//	vtkSmartPointer<vtkActor> act = vtkSmartPointer<vtkActor>::New();
//	act->SetMapper(dataMap);

//	vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
//	//transform->RotateWXYZ(double angle, double x, double y, double z);
//	transform->RotateWXYZ(angle, 0, 0, 1);

//	transform->Translate(x,y,z);
//	// transform->RotateWXYZ(90, 0, 0, 1);
//	vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter =
//			vtkSmartPointer<vtkTransformPolyDataFilter>::New();

//	transformFilter->SetTransform(transform);
//	transformFilter->SetInputConnection(cylindeSource->GetOutputPort());
//	transformFilter->Update();

//	act->SetUserTransform(transform);

//	render->AddActor(act);



//	auto polydata = cylindeSource->GetOutput();
//	auto dd = cylindeSource->GetCenter();
//	qDebug()  <<" point: =------------------------ ";// << dd[0] << dd[1] << dd[2];
//	vtkPoints *pts = polydata->GetPoints();
//	for(int i=0; i < polydata->GetNumberOfPoints(); i++)
//	{
//		auto dd = polydata->GetPoint(i);
//		qDebug()  <<" Center: " << dd[0] << dd[1] << dd[2];

//	}





}

void MainWindow::createTexture()
{

	vtkSmartPointer<vtkBMPReader> texReader =
			vtkSmartPointer<vtkBMPReader>::New();//vtkJPEGReader
	texReader->SetFileName("/Users/rong/dfnet/suit.bmp");

	texture = vtkSmartPointer<vtkTexture>::New();
	texture->SetInputConnection(texReader->GetOutputPort());
	texture->InterpolateOn();


}

void MainWindow::rotateHand(MyVTKObject<vtkSmartPointer<vtkCylinderSource>> obj, float angle, int x, int y , int z,float mx, float my, float mz)
{
	vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
	//transform->RotateWXYZ(double angle, double x, double y, double z);
	transform->RotateWXYZ(angle, 0, 0, 1);

	transform->Translate(mx,my,mz);
	// transform->RotateWXYZ(90, 0, 0, 1);
	vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter =
			vtkSmartPointer<vtkTransformPolyDataFilter>::New();

	transformFilter->SetTransform(transform);
	transformFilter->SetInputConnection(obj.getSource()->GetOutputPort());
	transformFilter->Update();

	obj.getActor()->SetUserTransform(transform);
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
	//几何数据
		vtkSmartPointer<vtkPoints> points=vtkSmartPointer<vtkPoints>::New();
	//    points->SetNumberOfPoints(5);//此行可有可无
		points->InsertPoint(0,0,0,0);
		points->InsertPoint(1,1,0.0,0);
		points->InsertPoint(2,2,0,0);
		points->InsertPoint(3,3,0,0);
		points->InsertPoint(4,0,3,0);
		//拓扑数据
		vtkSmartPointer<vtkPolyVertex>polyVertex=vtkSmartPointer<vtkPolyVertex>::New();
		polyVertex->GetPointIds()->SetNumberOfIds(5);//必须设置Id个数，否则可以编译，不能运行
		polyVertex->GetPointIds()->SetId(0,0);//第一个参数是几何point的ID号，第2个参数是拓扑中的Id号
		polyVertex->GetPointIds()->SetId(1,1);
		polyVertex->GetPointIds()->SetId(2,2);
		polyVertex->GetPointIds()->SetId(3,3);
		polyVertex->GetPointIds()->SetId(4,4);
		//属性数据
		vtkSmartPointer<vtkFloatArray>pointsScalars=vtkSmartPointer<vtkFloatArray>::New();
		pointsScalars->SetNumberOfTuples(5);//此行可有可无
		pointsScalars->InsertValue(0,0);//第1个参数是points点的Id，第2个参数是该点的属性值
		pointsScalars->InsertValue(1,0);//第1个参数是points点的Id，第2个参数是该点的属性值
		pointsScalars->InsertValue(2,0);//第1个参数是points点的Id，第2个参数是该点的属性值
		pointsScalars->InsertValue(3,0);//第1个参数是points点的Id，第2个参数是该点的属性值
		pointsScalars->InsertValue(4,0);//第1个参数是points点的Id，第2个参数是该点的属性值
		//将以上三部分数据组合成一个结构vtkUnstructureGrid
		vtkSmartPointer<vtkUnstructuredGrid> aGrid=vtkSmartPointer<vtkUnstructuredGrid>::New();
		aGrid->Allocate(1,1);
		aGrid->SetPoints(points);
		aGrid->GetPointData()->SetScalars(pointsScalars);
		aGrid->InsertNextCell(polyVertex->GetCellType(),polyVertex->GetPointIds());

		//设置映射器
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
	//几何数据
	vtkSmartPointer<vtkPoints> points=vtkSmartPointer<vtkPoints>::New();
	//    points->SetNumberOfPoints(5);//此行可有可无
	int index = 0;

	int num = 16;
	int total = num*3;
	int half = num /2;
	for (int n=0; n <num;n++) {
		points->InsertPoint(index++,n-half,0,0);
		points->InsertPoint(index++,0,n-half,0);
		points->InsertPoint(index++,0,0,n-half);
	}

	//拓扑数据
	vtkSmartPointer<vtkPolyVertex>polyVertex=vtkSmartPointer<vtkPolyVertex>::New();
	polyVertex->GetPointIds()->SetNumberOfIds(total);//必须设置Id个数，否则可以编译，不能运行

	for (int n=0; n <total;n++) {
		polyVertex->GetPointIds()->SetId(n,n);//第一个参数是几何point的ID号，第2个参数是拓扑中的Id号
	}

	//属性数据
	vtkSmartPointer<vtkFloatArray>pointsScalars=vtkSmartPointer<vtkFloatArray>::New();
	pointsScalars->SetNumberOfTuples(total);//此行可有可无
	for (int n=0; n <total;n++) {
		pointsScalars->InsertValue(n,0);//第1个参数是points点的Id，第2个参数是该点的属性值
	}



	//将以上三部分数据组合成一个结构vtkUnstructureGrid
	vtkSmartPointer<vtkUnstructuredGrid> aGrid=vtkSmartPointer<vtkUnstructuredGrid>::New();
	aGrid->Allocate(1,1);
	aGrid->SetPoints(points);
	aGrid->GetPointData()->SetScalars(pointsScalars);
	aGrid->InsertNextCell(polyVertex->GetCellType(),polyVertex->GetPointIds());

	//设置映射器
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




vtkSmartPointer<vtkActor> MainWindow::createCylinder(float x,float y,float z)
{
	vtkSmartPointer<vtkCylinderSource> cylindeSource = vtkSmartPointer<vtkCylinderSource>:: New();
	cylindeSource->SetCenter(x,y,z);
	cylindeSource->SetHeight(1);
	cylindeSource->SetRadius(0.1);

	vtkSmartPointer<vtkPolyDataMapper> dataMap = vtkSmartPointer<vtkPolyDataMapper>::New();

	dataMap->SetInputConnection( cylindeSource->GetOutputPort());

	vtkSmartPointer<vtkActor> act = vtkSmartPointer<vtkActor>::New();
	act->SetMapper(dataMap);


	//set color
	auto r = vtkMath::Random(.4, 1.0);
	auto g = vtkMath::Random(.4, 1.0);
	auto b = vtkMath::Random(.4, 1.0);
	act->GetProperty()->SetDiffuseColor(r, g, b);

	//other
	act->GetProperty()->SetDiffuse(.8);
	act->GetProperty()->SetSpecular(.5);
	act->GetProperty()->SetSpecularColor(1.0,1.0,1.0);
	act->GetProperty()->SetSpecularPower(30.0);


	vtkSmartPointer<vtkAssembly> ass = vtkSmartPointer<vtkAssembly>::New() ;

	ltAssembly << ass;
	auto c = cylindeSource->GetCenter();
	ass->AddPart(act);//this can be multiple
	ass->SetOrigin(c[0],c[1],c[2]);
	render->AddActor(ass);

	return act;
}



vtkSmartPointer<vtkActor> MainWindow::createCylinder(float x,float y,float z,float mx, float my, float mz,float angle)
{
	vtkSmartPointer<vtkCylinderSource> cylindeSource = vtkSmartPointer<vtkCylinderSource>:: New();
	cylindeSource->SetCenter(x,y,z);
	cylindeSource->SetHeight(1);
	cylindeSource->SetRadius(0.1);

	vtkSmartPointer<vtkPolyDataMapper> dataMap = vtkSmartPointer<vtkPolyDataMapper>::New();

	dataMap->SetInputConnection( cylindeSource->GetOutputPort());

	vtkSmartPointer<vtkActor> act = vtkSmartPointer<vtkActor>::New();
	act->SetMapper(dataMap);

	vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
	transform->RotateWXYZ(angle, 0, 0, 1);
	transform->Translate(mx,my,mz);
	vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter =vtkSmartPointer<vtkTransformPolyDataFilter>::New();

	transformFilter->SetTransform(transform);
	transformFilter->SetInputConnection(cylindeSource->GetOutputPort());
	transformFilter->Update();

	act->SetUserTransform(transform);
	//render->AddActor(act);
	return act;
}
void MainWindow::on_actionRY1_triggered()
{
	qDebug() << "RY1";
	ltAssembly[comBox->currentIndex()]->RotateZ(45);
	renWin->Render();
	//update();
}

void MainWindow::on_actionRY2_triggered()
{
	qDebug() << "RY2";
	ltAssembly[comBox->currentIndex()]->RotateZ(45);
	renWin->Render();
}
void MainWindow::on_actionMX1_triggered()
{
	qDebug() << "RY1";
	//ltAssembly[comBox->currentIndex()]->
	renWin->Render();
}

void MainWindow::on_actionMX2_triggered()
{


}

void MainWindow::on_mv_valueChanged(int value)
{
	qDebug() << __FUNCTION__ << value;
	vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();

	int x = ui->horizontalSlider->value();
	int y = ui->horizontalSlider_2->value();
	int z = ui->horizontalSlider_3->value();
	transform->Translate(x,y,z);
	transform->RotateWXYZ(90, 0, 0, 1);
	vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter =
			vtkSmartPointer<vtkTransformPolyDataFilter>::New();

	transformFilter->SetTransform(transform);
	transformFilter->SetInputConnection(header.getSource()->GetOutputPort());
	transformFilter->Update();
	header.getActor()->SetUserTransform(transform);
	renWin->Render();
}

void MainWindow:: on_rotate_valueChanged(int value)
{
	qDebug() << __FUNCTION__ << value;
	render->GetActiveCamera()->SetPosition (0, 0, value);//设视角位置
	renWin->Render();
}

void MainWindow::on_btn1_clicked()
{
	render->GetActiveCamera()->SetViewUp(0, 1 ,0 );
	render->GetActiveCamera()->Azimuth(180);
	renWin->Render();
}

void MainWindow::on_btn2_clicked()
{
	render->GetActiveCamera()->SetViewUp(0, -1 ,0 );
	render->GetActiveCamera()->Azimuth(-180);
	renWin->Render();
}

void MainWindow::on_btn3_clicked()
{
	double n = -90.0f;
	render->GetActiveCamera()->Roll(n);
	renWin->Render();
}

void MainWindow::on_btn4_clicked()
{
	render->GetActiveCamera()->SetViewAngle( render->GetActiveCamera()->GetViewAngle()+40);
	renWin->Render();
}

void MainWindow::on_btn9_clicked()
{
	render->ResetCamera();
	renWin->Render();
}


void MainWindow::createCube()
{

}

void MainWindow::textureToCube()
{
	// Read JPG image
	vtkSmartPointer<vtkJPEGReader> JPEGReader = vtkSmartPointer<vtkJPEGReader>::New();
	JPEGReader->SetFileName("/Users/rong/work/bb.jpeg");
	JPEGReader->Update();


	vtkSmartPointer<vtkTexture> texture1 = vtkSmartPointer<vtkTexture>::New();
	texture1->SetInputConnection(JPEGReader->GetOutputPort());


	// 设置立方体代码：
	// Setup cube
	vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
	cubeSource->Update();
	vtkSmartPointer<vtkTextureMapToPlane> cubeMapper = vtkSmartPointer<vtkTextureMapToPlane>::New();
	cubeMapper->SetInputConnection(cubeSource->GetOutputPort());

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(cubeMapper->GetOutputPort());


	vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();
	cubeActor->SetMapper(mapper);
	cubeActor->GetProperty()->SetDiffuseColor(.3, .6, .4);


	cubeActor->SetTexture(texture1);

//# Generate a cube
//cube = vtk.vtkCubeSource()

//# Read the image data from a file
//reader = vtk.vtkJPEGReader()
//reader.SetFileName("yourimage.jpg")

//# Create texture object
//texture = vtk.vtkTexture()
//texture.SetInputConnection(reader.GetOutputPort())

//#Map texture coordinates
//map_to_plane = vtk.vtkTextureMapToPlane()
//map_to_plane.SetInputConnection(cube.GetOutputPort())

//# Create mapper and set the mapped texture as input
//mapper = vtk.vtkPolyDataMapper()
//mapper.SetInputConnection(map_to_plane.GetOutputPort())

//# Create actor and set the mapper and the texture
//actor = vtk.vtkActor()
//actor.SetMapper(mapper)
//actor.SetTexture(texture)

	render->AddActor(cubeActor);
}

void MainWindow::setBodyTexture()
{
	// Read JPG image
//	vtkSmartPointer<vtkJPEGReader> JPEGReader = vtkSmartPointer<vtkJPEGReader>::New();
//	JPEGReader->SetFileName("/Users/rong/work/bb.jpeg");
//	JPEGReader->Update();


	vtkSmartPointer<vtkBMPReader> texReader =
			vtkSmartPointer<vtkBMPReader>::New();//vtkJPEGReader
	texReader->SetFileName("/Users/rong/dfnet/suit.bmp");


	vtkSmartPointer<vtkTexture> texture1 = vtkSmartPointer<vtkTexture>::New();
	texture1->SetInputConnection(texReader->GetOutputPort());


	// 设置立方体代码：
	// Setup cube
	vtkSmartPointer<vtkCubeSource> cubeSource = body.getSource();//vtkSmartPointer<vtkCubeSource>::New();
	cubeSource->Update();
	vtkSmartPointer<vtkTextureMapToPlane> cubeMapper = vtkSmartPointer<vtkTextureMapToPlane>::New();
	cubeMapper->SetInputConnection(cubeSource->GetOutputPort());



	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(cubeMapper->GetOutputPort());


	vtkSmartPointer<vtkActor> cubeActor = body.getActor();//vtkSmartPointer<vtkActor>::New();
	cubeActor->SetMapper(mapper);
	cubeActor->GetProperty()->SetDiffuseColor(.3, .6, .4);


	cubeActor->SetTexture(texture1);
}


void MainWindow::setHeadTexture()
{
	// Read JPG image
	vtkSmartPointer<vtkPNGReader> JPEGReader = vtkSmartPointer<vtkPNGReader>::New();
	JPEGReader->SetFileName("/Users/rong/work/git/SharkLib/pic/UcXjh.png");
	JPEGReader->Update();

	vtkSmartPointer<vtkTexture> texture1 = vtkSmartPointer<vtkTexture>::New();
	texture1->SetInputConnection(JPEGReader->GetOutputPort());

	vtkSmartPointer<vtkTextureMapToPlane> cubeMapper = vtkSmartPointer<vtkTextureMapToPlane>::New();
	cubeMapper->SetInputConnection(header.getSource()->GetOutputPort());

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(cubeMapper->GetOutputPort());


	header.getActor()->SetMapper(mapper);
	header.getActor()->GetProperty()->SetDiffuseColor(.3, .6, .4);

	header.getActor()->SetTexture(texture1);

}

void MainWindow::setCylinderTexture(MyVTKObject<vtkSmartPointer<vtkCylinderSource>> obj)
{
	// Read JPG image
	vtkSmartPointer<vtkJPEGReader> JPEGReader = vtkSmartPointer<vtkJPEGReader>::New();
	JPEGReader->SetFileName("/Users/rong/work/bb.jpeg");
	JPEGReader->Update();

	vtkSmartPointer<vtkTexture> texture1 = vtkSmartPointer<vtkTexture>::New();
	texture1->SetInputConnection(JPEGReader->GetOutputPort());

	vtkSmartPointer<vtkTextureMapToPlane> cubeMapper = vtkSmartPointer<vtkTextureMapToPlane>::New();
	cubeMapper->SetInputConnection(obj.getSource()->GetOutputPort());

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(cubeMapper->GetOutputPort());


	obj.getActor()->SetMapper(mapper);
	obj.getActor()->GetProperty()->SetDiffuseColor(.3, .6, .4);

	obj.getActor()->SetTexture(texture1);

}


