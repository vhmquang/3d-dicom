#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkDICOMImageReader.h>
#include <vtkImageViewer2.h>
#include <vtkMarchingCubes.h>
#include <vtkRenderWindow.h>
#include <vtkImageData.h>
#include <vtkCamera.h>
#include <vtkObject.h>
#include <vtkOutputWindow.h>
#include <vtkVolume.h>
#include <vtkVolumeRayCastMapper.h>
#include <vtkVolumeRayCastCompositeFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkWin32OutputWindow.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkVolumeTextureMapper3D.h>
#include <vtkAutoInit.h>
#include <QVTKWidget.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void openDCMFolder();
    void drawDCMSeries(std::string folderDCM);

    void on__2D_Image_ResetCamera_clicked();

    void on_actionOpen_DICOM_Folder_triggered();
    void initialize();
    void defaultCamera();
    void on__2D_Image_AutoPlay_clicked();
    void on__3D_Model_Generate_clicked();

    void on__3D_Model_ZoomIn_pressed();

    void on__3D_Model_ZoomOut_pressed();

    void on__3D_Model_Up_clicked();

    void on__3D_Model_Down_clicked();

    void on__3D_Model_Left_clicked();

    void on__3D_Model_Right_clicked();

    void on__2D_Image_Slicer_valueChanged(int position);

    void on_actionHelp_triggered();

    void setVolumeProperty();

    void on_actionMarching_Cubes_Settings_triggered();

    void on_actionRay_Casting_Settings_triggered();

    void on_tabWidget_tabBarClicked(int index);

private:
      Ui::MainWindow *ui;
      vtkSmartPointer<vtkDICOMImageReader> readerDCMSeries;
      vtkSmartPointer<vtkImageViewer2> imageViewerDCMSeriesX;
      vtkSmartPointer<vtkImageData> volume;
      vtkSmartPointer<vtkMarchingCubes> surface;
      vtkSmartPointer<vtkRenderer> renderer;
      vtkSmartPointer<vtkPolyDataMapper> mapper ;
      vtkSmartPointer<vtkActor> actor;
      vtkSmartPointer<vtkCamera> camera;
      vtkSmartPointer<vtkVolumeRayCastCompositeFunction> rayCastFunction;
      vtkSmartPointer<vtkVolumeRayCastMapper> volumeMapper;
      vtkSmartPointer<vtkColorTransferFunction>volumeColor;
      vtkSmartPointer<vtkPiecewiseFunction> volumeScalarOpacity;
      vtkSmartPointer<vtkPiecewiseFunction> volumeGradientOpacity;
      vtkSmartPointer<vtkVolumeProperty> volumeProperty;
      vtkSmartPointer<vtkVolume> volumeRaycaster;
      vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> fixedPointVolumeRaycaster;
      vtkSmartPointer<vtkVolumeTextureMapper3D> volumeTextureMapper;
      int mMinSliderX;
      int mMaxSliderX;
      double x;
      double y;
      double z;
      int ex = 0;
      bool isZoom = true;
      bool isNotZoom = true;
      double *controlPoint1;
      double *controlPoint2;
      double *controlPoint3;
      double *lightSettings;
};

#endif // MAINWINDOW_H
