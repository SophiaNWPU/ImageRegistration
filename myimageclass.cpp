#include "myimageclass.h"
#include "imageregistration.h"

#include <QVTKWidget.h>
#include <itkImageSeriesWriter.h>

#include <itkCastImageFilter.h>


// Includes from a Sample... Still to figure out why
// they where included here...

//#include <vtkPolyDataMapper.h>
//#include <vtkActor.h>
//#include <vtkRenderer.h>
//#include <vtkRenderWindow.h>
//#include <vtkDICOMImageReader.h>
//#include <vtkObjectFactory.h>
//#include <vtkRenderWindowInteractor.h>
//#include <vtkInteractorStyleImage.h>
//#include <vtkActor2D.h>
//#include <vtkTextProperty.h>
//#include <vtkTextMapper.h>




MyImageClass::MyImageClass(ImageRegistration *myimreg):
    imreg_(myimreg)
{
  imageViewerDCMSeriesX_ = vtkSmartPointer<vtkImageViewer2>::New();

}
MyImageClass::~MyImageClass()
{
}

void MyImageClass::LoadDICOM()
{
  try
  {
    if(imreg_->listWidget->currentIndex().isValid() == false &&
            imreg_->listWidgetMoving->currentIndex().isValid() == false)
    {
        throw exception_;
    }
    if(imreg_->listWidget->currentIndex().isValid() == true && imreg_->stackedWidget->currentIndex() == 1)
    {
      const ReaderType::FileNamesContainer & filenames =
                             namesGenerator_->GetFileNames(imreg_->listWidget->currentItem()->
                                                          text().toStdString());
      reader_ = ReaderType::New();
      reader_->SetImageIO(gdcmIO_);
      reader_->SetFileNames (filenames);
    }
    else
    {
      const ReaderType::FileNamesContainer & filenames =
                                 namesGenerator_->GetFileNames(imreg_->listWidgetMoving->currentItem()->
                                                              text().toStdString());
      reader_ = ReaderType::New();
      reader_->SetImageIO(gdcmIO_);
      reader_->SetFileNames (filenames);
    }


    reader_->Update();
    }
    catch( itk::ExceptionObject &excp)
    {
        throw excp;
    }
    DrawDICOMImg();
}



void MyImageClass::SetFileName(QString mypath, QStringList myfiles)
{
    path_ = mypath;
    files_ = myfiles;
}


void MyImageClass::DrawDICOMImg()
{
  connector_ = FilterType::New();

  connector_->SetInput(reader_->GetOutput());
  connector_->Update();

  imageViewerDCMSeriesX_->SetInputData(connector_->GetOutput());

  mMinSliderX_ = imageViewerDCMSeriesX_->GetSliceMin();
  mMaxSliderX_ = imageViewerDCMSeriesX_->GetSliceMax();


  if(imreg_->stackedWidget->currentIndex() == 1)
  {
      imreg_->hSliderFixed->setMinimum(mMinSliderX_);
      imreg_->hSliderFixed->setMaximum(mMaxSliderX_);
      imageViewerDCMSeriesX_->SetRenderWindow(imreg_->vtkRenderer1->GetRenderWindow());
      imageViewerDCMSeriesX_->Render();
  }
  else
  {
      imreg_->hSliderMoving->setMinimum(mMinSliderX_);
      imreg_->hSliderMoving->setMaximum(mMaxSliderX_);
      imageViewerDCMSeriesX_->SetRenderWindow(imreg_->vtkRenderer2->GetRenderWindow());
      imageViewerDCMSeriesX_->Render();
  }
}

void MyImageClass::SetSlicePosition(int position)
{
    imageViewerDCMSeriesX_->SetSlice(position);;
    imageViewerDCMSeriesX_->Render();
}


void MyImageClass::GetDICOMSeries()
{
  gdcmIO_ = ImageIOType::New();
  namesGenerator_ = NamesGeneratorType::New();

  namesGenerator_->SetInputDirectory(path_.toLocal8Bit().data());

  std::vector<std::string > dcm_ids = namesGenerator_->GetSeriesUIDs();
  if(imreg_->stackedWidget->currentIndex() == 1)
  {
    imreg_->listWidget->clear();
    for(int i = 0; i < dcm_ids.size(); i++)
    {
      imreg_->listWidget->addItem(dcm_ids.at(i).c_str());
    }
  }
  else
  {
      imreg_->listWidgetMoving->clear();
      for(int i = 0; i < dcm_ids.size(); i++)
      {
        imreg_->listWidgetMoving->addItem(dcm_ids.at(i).c_str());
      }
  }
}

void MyImageClass::DrawDicomImg()
{
  imreg_->hSliderMoving->setMinimum(mMinSliderX_);
  imreg_->hSliderMoving->setMaximum(mMaxSliderX_);
  imageViewerDCMSeriesX_->Render();
}

ReaderType::Pointer MyImageClass::GetReader()
{
    return reader_;
}