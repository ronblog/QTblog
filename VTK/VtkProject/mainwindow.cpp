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
#include <vtkTextureMapToSphere.h>

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

#define NFACE 6
#define NLINE 4
#define M_GET_LENGTH3D(x, y, z)			sqrt((double)((x)*(x) + (y)*(y) + (z)*(z)))

//---------------------------------------------------------
 struct VTKPoint3D
{
	double	m_x, m_y, m_z;
	VTKPoint3D()
	{
		m_x = 0;
		m_y = 0;
		m_z = 0;
	}
	VTKPoint3D(double x1, double y1, double z1)
	{
		m_x = x1;
		m_y = y1;
		m_z= z1;
	}
};



 vtkSmartPointer<vtkActor> createPlane()
 {
	 // Create a plane
	 vtkSmartPointer<vtkPlaneSource> plane = vtkSmartPointer<vtkPlaneSource>::New();
	 plane->SetCenter(0.0, 0.0, 0.0);
	 plane->SetNormal(0.0, 0.0, 1.0);

	 vtkSmartPointer<vtkTextureMapToPlane> texturePlane = vtkSmartPointer<vtkTextureMapToPlane>::New();
	 texturePlane->SetInputConnection(plane->GetOutputPort());

	 vtkSmartPointer<vtkPolyDataMapper> planeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	 planeMapper->SetInputConnection(texturePlane->GetOutputPort());

	 vtkSmartPointer<vtkActor> texturedPlane = vtkSmartPointer<vtkActor>::New();

	 // Read JPG image
	 vtkSmartPointer<vtkJPEGReader> JPEGReader = vtkSmartPointer<vtkJPEGReader>::New();
	 JPEGReader->SetFileName("/Users/rong/work/cube.jpeg");
	 JPEGReader->Update();




	 auto texture = vtkSmartPointer<vtkTexture>::New();
	 texture->SetInputConnection(JPEGReader->GetOutputPort());
	 texture->InterpolateOn();

	 texturedPlane->SetTexture(texture);

	 return texturedPlane;
//	 texturedPlane->SetMapper(planeMapper);
//	 texturedPlane->SetTexture(m_texture);
//	 m_pRender->AddActor(texturedPlane);

}

vtkSmartPointer<vtkActor> cube_texture()
{
	double p[6] = {0,1,0,1,0,1};
	//获取当前坐标范围的中心点
	//m_vtkView->getCoordRange(p);
	double centerx = (p[0] + p[1]) / 2;
	double centery = (p[2] + p[3]) / 2;
	double centerz = (p[4] + p[5]) / 2;
	double cube_size = 1.0;
	//构造立方体
	std::list< VTKPoint3D > m_pts;

	m_pts.clear();
	m_pts.push_back(VTKPoint3D(centerx - cube_size / 2, centery - cube_size / 2, centerz - cube_size / 2));
	m_pts.push_back(VTKPoint3D(centerx + cube_size / 2, centery - cube_size / 2, centerz - cube_size / 2));
	m_pts.push_back(VTKPoint3D(centerx + cube_size / 2, centery + cube_size / 2, centerz - cube_size / 2));
	m_pts.push_back(VTKPoint3D(centerx - cube_size / 2, centery + cube_size / 2, centerz - cube_size / 2));
	m_pts.push_back(VTKPoint3D(centerx - cube_size / 2, centery - cube_size / 2, centerz + cube_size / 2));
	m_pts.push_back(VTKPoint3D(centerx + cube_size / 2, centery - cube_size / 2, centerz + cube_size / 2));
	m_pts.push_back(VTKPoint3D(centerx + cube_size / 2, centery + cube_size / 2, centerz + cube_size / 2));
	m_pts.push_back(VTKPoint3D(centerx - cube_size / 2, centery + cube_size / 2, centerz + cube_size / 2));
	// The ordering of the corner points on each face.
	std::array<std::array<vtkIdType, 4>, 6> ordering =
	{ {
	{ { 0, 1, 2, 3 } },
	{ { 4, 5, 6, 7 } },
	{ { 0, 1, 5, 4 } },
	{ { 1, 2, 6, 5 } },
	{ { 2, 3, 7, 6 } },
	{ { 3, 0, 4, 7 } } } };
	//
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkCellArray> polys = vtkSmartPointer<vtkCellArray>::New();
	VTKPoint3D pt;
	auto ppp = m_pts.begin();
	for (int index = 0; index < 8; ++index)
	{

		points->InsertPoint(index, ppp->m_x, ppp->m_y,ppp->m_z);
		ppp++;
	}
	for (auto&& i : ordering)
	{
		polys->InsertNextCell(vtkIdType(i.size()), i.data());
	}
	//将点和多边形加入polydata
	vtkIdType* indices;
	vtkIdType numberOfPoints;
	VTKPoint3D pt0, pt1, pt2;
	vtkSmartPointer<vtkAppendPolyData> polyDatas = vtkSmartPointer<vtkAppendPolyData>::New();

	int nn=0;
	for (polys->InitTraversal();polys->GetNextCell(numberOfPoints, indices);)
	{
		qDebug() << __LINE__;
		vtkSmartPointer<vtkPolyData> profile = vtkSmartPointer<vtkPolyData>::New();
		vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
		lines->InsertNextCell(numberOfPoints);
		for (vtkIdType i = 0; i < numberOfPoints; i++)
		{
			vtkIdType id = indices[i];
			lines->InsertCellPoint(id);
			double point[3];
			points->GetPoint(id, point);
			qDebug() << __LINE__ << point[0] << point[0];

			if (i == 0)
			{
				pt0.m_x = point[0];pt0.m_y = point[1];pt0.m_z = point[2];
			}
			if (i == 1)
			{
				pt1.m_x = point[0];pt1.m_y = point[1];pt1.m_z = point[2];
			}
			if (i == 2)
			{
				pt2.m_x = point[0];pt2.m_y = point[1];pt2.m_z = point[2];
			}
		}
		profile->SetPoints(points);
		profile->SetPolys(lines);
		////计算多边形的法向量
		vtkSmartPointer<vtkPolyDataNormals> normal = vtkSmartPointer<vtkPolyDataNormals>::New();
		normal->SetInputData(profile);
		////设置多边形纹理映射的模式
		////设置为plane模式
		vtkSmartPointer<vtkTextureMapToPlane> tmapper = vtkSmartPointer<vtkTextureMapToPlane>::New();
		tmapper->SetInputConnection(normal->GetOutputPort());
		//设置纹理st坐标系的顶点坐标 和两点坐标，定义了st坐标系
		tmapper->SetOrigin(pt1.m_x+nn, pt1.m_y, pt1.m_z);
		tmapper->SetPoint1(pt0.m_x, pt0.m_y, pt0.m_z);
		tmapper->SetPoint2(pt2.m_x, pt2.m_y, pt2.m_z);
		vtkSmartPointer<vtkTransformTextureCoords> xform = vtkSmartPointer<vtkTransformTextureCoords>::New();
		xform->SetInputConnection(tmapper->GetOutputPort());
		xform->SetScale(1, 1, 1);
		polyDatas->AddInputConnection(xform->GetOutputPort());
		nn++;
	}
	polyDatas->Update();
	vtkSmartPointer<vtkPolyDataMapper> cubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	cubeMapper->SetInputConnection(polyDatas->GetOutputPort());
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(cubeMapper);


	// Read JPG image
	vtkSmartPointer<vtkJPEGReader> JPEGReader = vtkSmartPointer<vtkJPEGReader>::New();
	JPEGReader->SetFileName("/Users/rong/work/cube.jpeg");
	JPEGReader->Update();




	auto texture = vtkSmartPointer<vtkTexture>::New();
	texture->SetInputConnection(JPEGReader->GetOutputPort());
	texture->InterpolateOn();

	actor->SetTexture(texture);

	return actor;

}

vtkSmartPointer<vtkActor> sphore_texture()
{
	vtkSmartPointer<vtkSphereSource> coneSource = vtkSmartPointer<vtkSphereSource>::New();
	coneSource->SetRadius(1);

	coneSource->SetCenter(0, 0, 0);

	vtkSmartPointer<vtkPolyDataMapper> coneMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
	coneMapper->SetInputConnection(coneSource->GetOutputPort());
	vtkSmartPointer<vtkActor> coneActor =
			vtkSmartPointer<vtkActor>::New();
	coneActor->SetMapper(coneMapper);

	//coneActor->SetUserTransform(transform);



	// Read JPG image
	vtkSmartPointer<vtkPNGReader> JPEGReader = vtkSmartPointer<vtkPNGReader>::New();
	JPEGReader->SetFileName("/Users/rong/work/git/SharkLib/pic/UcXjh.png");
	JPEGReader->Update();

	vtkSmartPointer<vtkTexture> texture1 = vtkSmartPointer<vtkTexture>::New();
	texture1->SetInputConnection(JPEGReader->GetOutputPort());

	vtkSmartPointer<vtkTextureMapToSphere> cubeMapper = vtkSmartPointer<vtkTextureMapToSphere>::New();
	cubeMapper->SetInputConnection(coneSource->GetOutputPort());

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(cubeMapper->GetOutputPort());


	coneActor->SetMapper(mapper);
	coneActor->GetProperty()->SetDiffuseColor(.3, .6, .4);

	coneActor->SetTexture(texture1);

	return coneActor;
}


vtkSmartPointer<vtkActor>  Cylinder_texture( )
{
   //对圆柱体渲染
   vtkSmartPointer<vtkCylinderSource> cylinder =
   vtkSmartPointer<vtkCylinderSource>::New();
   cylinder->SetHeight( 3.0 );
   cylinder->SetRadius( 1.0 );
   cylinder->SetResolution( 10 );

   //对球体渲染
 /*  vtkSmartPointer<vtkSphereSource> sphere =
	   vtkSmartPointer<vtkSphereSource>::New();
   sphere->SetRadius(2.0);
   sphere->SetThetaResolution(20);
   sphere->SetPhiResolution(20);*/

   vtkSmartPointer<vtkJPEGReader>bmpReader = vtkSmartPointer<vtkJPEGReader>::New();
   bmpReader->SetFileName("/Users/rong/work/git/SharkLib/pic/bb.jpeg");//读入纹理图
   vtkSmartPointer<vtkTexture>texture = vtkSmartPointer<vtkTexture>::New();
   texture->SetInputConnection(bmpReader->GetOutputPort());
   texture->InterpolateOn();

   vtkSmartPointer<vtkPolyDataMapper> cylinderMapper =
	   vtkSmartPointer<vtkPolyDataMapper>::New();
   cylinderMapper->SetInputConnection( cylinder->GetOutputPort() );
   //cylinderMapper->SetInputConnection( sphere->GetOutputPort() );//对球体渲染

   vtkSmartPointer<vtkActor> cylinderActor =
	   vtkSmartPointer<vtkActor>::New();
   cylinderActor->SetMapper( cylinderMapper );
   cylinderActor->SetTexture(texture);//纹理为actor的一种属性


   return cylinderActor;
}

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowTitle("VTK 7  - Multi-Object");

	//step 0: set it to a window:
	auto vw = new  QVTKOpenGLWidget(this) ;
	 renWin = vw->GetRenderWindow();

	render= vtkRenderer::New();

	render->SetBackground( 0.1, 0.2, 0.4 );



	vtkSmartPointer<vtkAssembly> ass = vtkSmartPointer<vtkAssembly>::New() ;

	ltAssembly << ass;

	qint64 iA = 1998888778918294;
	long lA = 1998888778918294;
	qDebug() << iA <<lA;



	render->AddActor( createPlane());
	render->AddActor( cube_texture());
	//render->AddActor( sphore_texture());
	//render->AddActor( Cylinder_texture());

/*
	//绘制
	vtkCamera *camera = vtkCamera::New();
	camera->SetPosition(1,1,5);
	camera->SetFocalPoint(0,0,0);

	render->SetActiveCamera(camera);
*/
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



