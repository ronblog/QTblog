#include "vtkplugin.h"
#include <QWidget>
#include <QDebug>
//Q_EXPORT_PLUGIN2(plugin, myPlugin);


#include <vtkQImageToImageSource.h>
#include <vtkSmartPointer.h>
#include <QLabel>
#include <QVTKOpenGLNativeWidget.h>
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

VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType );
VTK_MODULE_INIT(vtkRenderingContextOpenGL2);
VTK_MODULE_INIT(vtkRenderingGL2PSOpenGL2);

//
// Similar to Cone2.cxx, we define a callback for interaction.
//
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


VTKPlugin::VTKPlugin(QObject *parent)
	: QGenericPlugin(parent), MyPluginInterface(parent)
{
	setObjectName("Test");
}

void VTKPlugin::slot_add()
{
	qDebug() << "added";
}

QObject *VTKPlugin::create(const QString &name, const QString &spec)
{
	//static_assert(false, "You need to implement this function");
	return new QObject();
}


QWidget *VTKPlugin::createWidget(QWidget* parent)
{
	QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
	//step 0: set it to a window:
	auto vw = new  QVTKOpenGLWidget(parent) ;
	vtkRenderWindow *renWin = vw->GetRenderWindow();

	vtkRenderer *render= vtkRenderer::New();

	render->SetBackground( 0.1, 0.2, 0.4 );

	vtkSmartPointer<vtkConeSource> coneSource =
			vtkSmartPointer<vtkConeSource>::New();
		coneSource->SetRadius(.2);
		coneSource->SetHeight(.5);
		coneSource->SetCenter(0, 0, 0);
		vtkSmartPointer<vtkPolyDataMapper> coneMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		coneMapper->SetInputConnection(coneSource->GetOutputPort());
		vtkSmartPointer<vtkActor> coneActor =
			vtkSmartPointer<vtkActor>::New();
		coneActor->SetMapper(coneMapper);

		vtkSmartPointer<vtkActor> oriConeActor =
			vtkSmartPointer<vtkActor>::New();
		oriConeActor->SetMapper(coneMapper);

	render->AddActor(oriConeActor);
	renWin->AddRenderer( render );
	return vw;

}

QMenu *VTKPlugin::createMenu(QWidget* parent)
{
	QMenu* menu = new QMenu(parent);
	auto rc = menu->addAction("Add");
	connect(rc, &QAction::triggered, this, &VTKPlugin::slot_add);
	menu->addAction("Delete");
	return menu;
}
