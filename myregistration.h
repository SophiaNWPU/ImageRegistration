#ifndef MYREGISTRATION_H
#define MYREGISTRATION_H
#include <QWidget>
#include <QString>
#include <QStringList>
#include <QMessageBox>

#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>

#include "itktypesandincludes.h"

class MyImageClass;
class ImageRegistration;

class MyRegistration
{
public:
    explicit MyRegistration(ImageRegistration *myimreg, MyImageClass* fixed_image,
                            MyImageClass* moving_images);
    ~MyRegistration();
    void SaveDICOMSeries(QString save_path);
    void StartRegistration();
    void ShowResultingFit();
    void SetSlicePositionResult(int position);

private:
    QMessageBox msg_box_;
    void ComputeDifference();
    ImageRegistration* imreg_;
    MyImageClass* fixed_image_;
    MyImageClass* moving_images_;

    FilterType::Pointer connector_result_;
    itk::GDCMImageIO::Pointer gdcmIO_;
    itk::GDCMSeriesFileNames::Pointer namesGenerator_;
    vtkSmartPointer<vtkImageViewer2> imageViewerDCMSeriesX_result_;


    MetricType::Pointer metric_;
    TransformType::Pointer transform_;
    OptimizerType::Pointer optimizer_;
    InterpolatorType::Pointer interpolator_;
    RegistrationType::Pointer registration_;
    ResampleFilterType::Pointer resampler_;
    DifferenceFilterType::Pointer difference_;
    RescalerType::Pointer intensity_rescaler_;

    int mMinSliderX_result_;
    int mMaxSliderX_result_;

};

#endif // MYREGISTRATION_H