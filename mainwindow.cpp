#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QMessageBox>
#include <QString>
#include <QEvent>
#include <QThread>
#include <QFileDialog>
VTK_MODULE_INIT(vtkRenderingOpenGL) //initialize object factory for Marching Cubes
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL) //initialize object factory for Ray Caster
VTK_MODULE_INIT(vtkInteractionStyle) //initialize object factory for default interation style in 2D
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // vtkObject::GlobalWarningDisplayOff();//turn off the error display
}

MainWindow::~MainWindow()
{
    delete ui;
}  
void MainWindow::on__2D_Image_ResetCamera_clicked()
{
    defaultCamera();
    imageViewerDCMSeriesX->Render();
}
void MainWindow::drawDCMSeries(std::string folderDCM)
{   try{
        readerDCMSeries->SetDirectoryName(folderDCM.c_str()); //read the directory
        readerDCMSeries->Update(); //update directory
        volume->DeepCopy(readerDCMSeries->GetOutput()); //copy the dataset to new one
        imageViewerDCMSeriesX->SetInputConnection(readerDCMSeries->GetOutputPort()); //get dataset to viewer
        mMinSliderX = imageViewerDCMSeriesX->GetSliceMin();
        mMaxSliderX = imageViewerDCMSeriesX->GetSliceMax();
        ui->_2D_Image_Slicer->setMinimum(mMinSliderX);
        ui->_2D_Image_Slicer->setMaximum(mMaxSliderX);
        imageViewerDCMSeriesX->SetRenderWindow(ui->_2D_Image_Renderer->GetRenderWindow()); //set renderwindow to display
        imageViewerDCMSeriesX->SetSlice(mMinSliderX);
        imageViewerDCMSeriesX->Render();
        imageViewerDCMSeriesX->GetRenderer()->GetActiveCamera()->GetPosition(x,y,z); //get active camera position
        if(mMaxSliderX > 0){
            ui->_2D_Information_ID_out->setText(readerDCMSeries->GetStudyID());
            ui->_2D_Information_Name_out->setText(readerDCMSeries->GetPatientName());
            ui->_2D_Information_Height_out->setText(QString::number(readerDCMSeries->GetHeight()));
            ui->_2D_Information_Width_out->setText(QString::number(readerDCMSeries->GetWidth()));
            ui->_2D_Information_DesName_out->setText(readerDCMSeries->GetDescriptiveName());
            ui->_2D_Information_Location_out->setText(readerDCMSeries->GetDirectoryName());
        }
        throw mMaxSliderX;
    }
    catch (int err){ //catch error if there are no DICOM files
        if (err <=0){
            QMessageBox::critical(this, "DRR",
                                  "Folder you open does not contain any DICOM images, please retry .",
                                  QMessageBox::Ok);
        }
    }

}
void MainWindow::openDCMFolder()
{   if (ex == 0){
        initialize();
        QString folderNameDCM = QFileDialog::getExistingDirectory(this,tr("Open DCM Folder"),QDir::currentPath(),QFileDialog::ShowDirsOnly);
        std::string stdstrFolderNameDCM = folderNameDCM.toUtf8().constData();
        drawDCMSeries(stdstrFolderNameDCM);
    }
 /*   old code
  * else {
       //delete the pipeline to ensure the uniform of data from 2D to 3D
        initialize();
        QString folderNameDCM = QFileDialog::getExistingDirectory(this,tr("Open DCM Folder"),QDir::currentPath(),QFileDialog::ShowDirsOnly);
        std::string stdstrFolderNameDCM = folderNameDCM.toUtf8().constData();
        drawDCMSeries(stdstrFolderNameDCM);
    }
    */
}

void MainWindow::on_actionOpen_DICOM_Folder_triggered()
{
    openDCMFolder();
}
void MainWindow::initialize(){
    rayCastFunction = vtkSmartPointer<vtkVolumeRayCastCompositeFunction>::New();
    volumeMapper = vtkSmartPointer<vtkVolumeRayCastMapper>::New();
    volumeColor = vtkSmartPointer<vtkColorTransferFunction>::New();
    volumeScalarOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
    volumeGradientOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
    volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
    volumeRaycaster = vtkSmartPointer<vtkVolume>::New();
    readerDCMSeries = vtkSmartPointer<vtkDICOMImageReader>::New();
    imageViewerDCMSeriesX = vtkSmartPointer<vtkImageViewer2>::New();
    volume = vtkSmartPointer<vtkImageData>::New();
    volumeTextureMapper = vtkSmartPointer<vtkVolumeTextureMapper3D>::New();
    mMaxSliderX = 0;
    surface = vtkSmartPointer<vtkMarchingCubes>::New();
    renderer = vtkSmartPointer<vtkRenderer>::New();
    mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    actor = vtkSmartPointer<vtkActor>::New();
    fixedPointVolumeRaycaster = vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
}
/* old code
 * void MainWindow::restart(){
    rayCastFunction->Delete();
    volumeMapper->Delete();
    mMaxSliderX=0;
    volumeColor->Delete();
    volumeScalarOpacity->Delete();
    volumeGradientOpacity->Delete();
    volumeProperty->Delete();
    volumeRaycaster->Delete();
    readerDCMSeries->Delete();
    imageViewerDCMSeriesX->Delete();
    volume->Delete();
    surface->Delete();
    renderer->Delete();
    mapper->Delete();
    actor->Delete();
    fixedPointVolumeRaycaster->Delete();

}
*/
void MainWindow::defaultCamera(){ //set the default position to make the 2D image viewable after interaction
    imageViewerDCMSeriesX->GetRenderer()->GetActiveCamera()->SetPosition(x,y,z);
    imageViewerDCMSeriesX->GetRenderer()->GetActiveCamera()->SetViewUp(0,1,0);
}


void MainWindow::on__2D_Image_AutoPlay_clicked()
{   //running the display through all slices
    int tempPosition = mMinSliderX;
    defaultCamera();
    while (tempPosition <= mMaxSliderX){
        imageViewerDCMSeriesX->SetSlice(tempPosition);
        imageViewerDCMSeriesX->Render();
        QThread::msleep((1000/ui->_2D_FPS->value())); //set the program the stop after interval for the each slice
        tempPosition++;

    }
}

void MainWindow::on__3D_Model_Generate_clicked()
{
    if (mMaxSliderX <= 0){ //check if there are DICOM files in pipeline
        QMessageBox::critical(this, "DRR",
                              "Please open DICOM file before generate 3D",
                              QMessageBox::Ok);
    }
    else {
        if (ui->_3D_Algorithm_ComboBox->currentIndex()==0){
            if (ex == 1)
                renderer = vtkSmartPointer<vtkRenderer>::New();
            surface->SetInputData(volume); //input the volume to Marching cube
            surface->SetValue(0,ui->_3D_InformationBox_Isovalue->value());//set the iso-value
            mapper->SetInputConnection(surface->GetOutputPort());//input for mapper
            mapper->ScalarVisibilityOff();
            actor->SetMapper(mapper);//bound mapper to actor
            renderer->AddActor(actor);//add actor to renderer
            renderer->SetBackground(.1, .2, .3);
            ui->_3D_Model_Renderer->GetRenderWindow()->AddRenderer(renderer);//add renderer to display window
            ui->_3D_Model_Renderer->GetRenderWindow()->Render();
        }
        else if (ui->_3D_Algorithm_ComboBox->currentIndex()==2)
        {
            if (ex == 1)
                renderer = vtkSmartPointer<vtkRenderer>::New();
             setVolumeProperty();
             volumeTextureMapper->SetInputData(volume);
             volumeRaycaster->SetMapper(volumeTextureMapper);
             volumeRaycaster->SetProperty(volumeProperty);
             renderer->AddViewProp(volumeRaycaster);
             ui->_3D_Model_Renderer->GetRenderWindow()->AddRenderer(renderer);
             ui->_3D_Model_Renderer->GetRenderWindow()->Render();
        }
        else {
            if (ex == 1)
                renderer = vtkSmartPointer<vtkRenderer>::New();
            setVolumeProperty(); //set volume attribute for raycasting algorithm
            if (volume->GetDataObjectType()==5){ // design which algorithm should be used for each data type
                volumeMapper->SetInputData(volume);
                volumeMapper->SetVolumeRayCastFunction(rayCastFunction);
                volumeRaycaster->SetMapper(volumeMapper);
                volumeRaycaster->SetProperty(volumeProperty);
                renderer->AddViewProp(volumeRaycaster);
                ui->_3D_Model_Renderer->GetRenderWindow()->AddRenderer(renderer);
                ui->_3D_Model_Renderer->GetRenderWindow()->Render();
            }
            else {
                fixedPointVolumeRaycaster->SetInputData(volume);
                fixedPointVolumeRaycaster->SetBlendModeToComposite();
                volumeRaycaster->SetMapper(fixedPointVolumeRaycaster);
                volumeRaycaster->SetProperty(volumeProperty);
                renderer->AddViewProp(volumeRaycaster);
                ui->_3D_Model_Renderer->GetRenderWindow()->RemoveAllObservers();
                ui->_3D_Model_Renderer->GetRenderWindow()->AddRenderer(renderer);
                ui->_3D_Model_Renderer->GetRenderWindow()->Render();
            }
        }

    }
    ex = 1;
}

void MainWindow::setVolumeProperty(){
    volumeColor->AddRGBPoint(*controlPoint1,    *(controlPoint1+1),  *(controlPoint1+2),  *(controlPoint1+3));
    volumeColor->AddRGBPoint(*controlPoint2,   *(controlPoint2+1),  *(controlPoint2+2),  *(controlPoint2+3));
    volumeColor->AddRGBPoint(*controlPoint3,  *(controlPoint3+1),  *(controlPoint3+2),  *(controlPoint3+3));
    volumeScalarOpacity->AddPoint(*controlPoint1,     *(controlPoint1+4));
    volumeScalarOpacity->AddPoint(*controlPoint2,   *(controlPoint2+4));
    volumeScalarOpacity->AddPoint(*controlPoint3,  *(controlPoint3+4));
    volumeGradientOpacity->AddPoint(*controlPoint1,    *(controlPoint1+4));
    volumeGradientOpacity->AddPoint(*controlPoint2,   *(controlPoint2+4));
    volumeGradientOpacity->AddPoint(*controlPoint3,  *(controlPoint3+4));
    volumeProperty->SetColor(volumeColor);
    volumeProperty->SetScalarOpacity(volumeScalarOpacity);
    volumeProperty->SetGradientOpacity(volumeGradientOpacity);
    volumeProperty->SetInterpolationTypeToLinear();
    volumeProperty->ShadeOn();
    volumeProperty->SetAmbient(*lightSettings);
    volumeProperty->SetDiffuse(*(lightSettings+1));
    volumeProperty->SetSpecular(*(lightSettings+2));
}

void MainWindow::on__3D_Model_ZoomIn_pressed()
{
    if(mMaxSliderX > 0){
        renderer->GetActiveCamera()->Zoom(1+((float)(ui->_3D_InformationBox_ZoomValue->value())/10.00));
        ui->_3D_Model_Renderer->GetRenderWindow()->Render();
    }
}
void MainWindow::on__3D_Model_ZoomOut_pressed()
{
    if(mMaxSliderX > 0){
        renderer->GetActiveCamera()->Zoom(1-((float)(ui->_3D_InformationBox_ZoomValue->value())/20.00));
        ui->_3D_Model_Renderer->GetRenderWindow()->Render();
    }
}

void MainWindow::on__3D_Model_Up_clicked()
{
    if (mMaxSliderX > 0){
        renderer->GetActiveCamera()->Elevation(ui->_3D_InformationBox_RotateValue->value());
        ui->_3D_Model_Renderer->GetRenderWindow()->Render();
    }
}

void MainWindow::on__3D_Model_Down_clicked()
{
    if (mMaxSliderX > 0){
        renderer->GetActiveCamera()->Elevation(-ui->_3D_InformationBox_RotateValue->value());
        ui->_3D_Model_Renderer->GetRenderWindow()->Render();
    }
}


void MainWindow::on__3D_Model_Left_clicked()
{
    if (mMaxSliderX > 0){
        renderer->GetActiveCamera()->Azimuth(ui->_3D_InformationBox_RotateValue->value());
        ui->_3D_Model_Renderer->GetRenderWindow()->Render();
    }
}

void MainWindow::on__3D_Model_Right_clicked()
{
    if (mMaxSliderX > 0){
        renderer->GetActiveCamera()->Azimuth(-ui->_3D_InformationBox_RotateValue->value());
        ui->_3D_Model_Renderer->GetRenderWindow()->Render();
    }
}

void MainWindow::on__2D_Image_Slicer_valueChanged(int position)
{
    imageViewerDCMSeriesX->SetSlice(position);
    defaultCamera();
    imageViewerDCMSeriesX->Render();
}

void MainWindow::on_actionHelp_triggered()
{
    QMessageBox::information(this,"Help","Use arrow to rotate model\n Q and E to zoom in and zoom out\n To generate 3D model, input iso-value and press Generate 3D Model",QMessageBox::Ok);
}

void MainWindow::on_actionMarching_Cubes_Settings_triggered()
{

}

void MainWindow::on_actionRay_Casting_Settings_triggered()
{
    Dialog *rayCastUI = new Dialog;
    if(rayCastUI->exec()){
        controlPoint1 = rayCastUI->point1Settings();
        controlPoint2 = rayCastUI->point2Settings();
        controlPoint3 = rayCastUI->point3Settings();
        lightSettings = rayCastUI->lightSettings();
    }
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if (index == 0)
    ui->_2D_Image_Renderer->GetRenderWindow()->Render();
    else
    ui->_3D_Model_Renderer->GetRenderWindow()->Render();
}
