#ifndef VTKOBJECT_H
#define VTKOBJECT_H

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

template<class TSource>
class MyVTKObject
{
public:
	MyVTKObject();
	TSource getSource() const;
	void setSource(const TSource &value);


	vtkSmartPointer<vtkPolyDataMapper> getDataMap() ;
	void setDataMap(const vtkSmartPointer<vtkPolyDataMapper> &value);

	vtkSmartPointer<vtkActor> getActor() ;
	void setActor(const vtkSmartPointer<vtkActor> &value);

	vtkSmartPointer<vtkAssembly> getAssembly() ;
	void setAssembly(const vtkSmartPointer<vtkAssembly> &value);

	void setTexture(QString fi);
	void setBmpTexture(QString fi);
	void setJpegTexture(QString fi);

private:

	vtkSmartPointer<vtkPolyDataMapper> dataMap;
	TSource  source;
	vtkSmartPointer<vtkActor> actor;
	//vtkSmartPointer<vtkAssembly> assembly;
	vtkSmartPointer<vtkTransform> transform;
};

#include <vtkTransformPolyDataFilter.h>
#include <vtkPolyVertex.h>
#include <vtkFloatArray.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkDoubleArray.h>
#include <vtkFloatArray.h>
#include <vtkMath.h>


template <class TSource>
MyVTKObject<TSource>::MyVTKObject()
{

}
template <class TSource>
TSource MyVTKObject<TSource>::getSource() const
{
	return source;
}
template <class TSource>
void MyVTKObject<TSource>::setSource(const TSource &value)
{
	source = value;

//	vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();

//	transform->Translate(0,-1.3,0);
//	transform->RotateWXYZ(90, 0, 0, 1);
//	vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter =
//			vtkSmartPointer<vtkTransformPolyDataFilter>::New();

//	transformFilter->SetTransform(transform);
//	transformFilter->SetInputConnection(source->GetOutputPort());
//	transformFilter->Update();

	dataMap = vtkSmartPointer<vtkPolyDataMapper>::New();
	dataMap->SetInputConnection(source->GetOutputPort());
	actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(dataMap);

	//actor->SetUserTransform(transform);

//	assembly = vtkSmartPointer<vtkAssembly>::New() ;

//	auto c = source->GetCenter();
//	assembly->AddPart(actor);//this can be multiple
//	assembly->SetOrigin(c[0],c[1],c[2]);

}
template <class TSource>
vtkSmartPointer<vtkPolyDataMapper> MyVTKObject<TSource>::getDataMap()
{
	return dataMap;
}
template <class TSource>
void MyVTKObject<TSource>::setDataMap(const vtkSmartPointer<vtkPolyDataMapper> &value)
{
	dataMap = value;
}
template <class TSource>
vtkSmartPointer<vtkActor> MyVTKObject<TSource>::getActor()
{
	return actor;
}
template <class TSource>
void MyVTKObject<TSource>::setActor(const vtkSmartPointer<vtkActor> &value)
{
	actor = value;
}
template <class TSource>
vtkSmartPointer<vtkAssembly> MyVTKObject<TSource>::getAssembly()
{
	return nullptr;
}
template <class TSource>
void MyVTKObject<TSource>::setAssembly(const vtkSmartPointer<vtkAssembly> &value)
{
	//assembly = value;
}


template <class TSource>
void MyVTKObject<TSource>::setTexture(QString fi)
{
	//assembly = value;
	// Read JPG image
	vtkSmartPointer<vtkJPEGReader> JPEGReader = vtkSmartPointer<vtkJPEGReader>::New();
	JPEGReader->SetFileName(fi.toUtf8());
	JPEGReader->Update();

	vtkSmartPointer<vtkTexture> texture = vtkSmartPointer<vtkTexture>::New();
	texture->SetInputConnection(JPEGReader->GetOutputPort());

	vtkSmartPointer<vtkTextureMapToPlane> mapper_plane = vtkSmartPointer<vtkTextureMapToPlane>::New();
	mapper_plane->SetInputConnection(source->GetOutputPort());

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(mapper_plane->GetOutputPort());


	actor->SetMapper(mapper);
	actor->GetProperty()->SetDiffuseColor(.3, .6, .4);

	actor->SetTexture(texture);
}

template <class TSource>
void MyVTKObject<TSource>::setBmpTexture(QString fi)
{
	//assembly = value;
	// Read JPG image

	vtkSmartPointer<vtkBMPReader> texReader =
			vtkSmartPointer<vtkBMPReader>::New();//vtkJPEGReader
	texReader->SetFileName(fi.toUtf8());

	vtkSmartPointer<vtkTexture> texture = vtkSmartPointer<vtkTexture>::New();
	texture->SetInputConnection(texReader->GetOutputPort());

	vtkSmartPointer<vtkTextureMapToPlane> mapper_plane = vtkSmartPointer<vtkTextureMapToPlane>::New();
	mapper_plane->SetInputConnection(source->GetOutputPort());

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(mapper_plane->GetOutputPort());


	actor->SetMapper(mapper);
	actor->GetProperty()->SetDiffuseColor(.3, .6, .4);

	actor->SetTexture(texture);
}

template <class TSource>
void MyVTKObject<TSource>::setJpegTexture(QString fi)
{
	//assembly = value;
	// Read JPG image
	vtkSmartPointer<vtkJPEGReader> JPEGReader = vtkSmartPointer<vtkJPEGReader>::New();
	JPEGReader->SetFileName(fi.toUtf8());
	JPEGReader->Update();

	vtkSmartPointer<vtkTexture> texture = vtkSmartPointer<vtkTexture>::New();
	texture->SetInputConnection(JPEGReader->GetOutputPort());

	vtkSmartPointer<vtkTextureMapToPlane> mapper_plane = vtkSmartPointer<vtkTextureMapToPlane>::New();
	mapper_plane->SetInputConnection(source->GetOutputPort());

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(mapper_plane->GetOutputPort());


	actor->SetMapper(mapper);
	actor->GetProperty()->SetDiffuseColor(.3, .6, .4);

	actor->SetTexture(texture);
}
#endif // VTKOBJECT_H
