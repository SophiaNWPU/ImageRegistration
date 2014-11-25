#ifndef IMAGEREGISTRATION_H
#define IMAGEREGISTRATION_H

#include "ui_imageregistration.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QVTKWidget.h>
#include <vector>



#define FIXED 1
#define MOVING 2


class MyRegistration;
class LoadFile;
class MyImageClass;

class ImageRegistration : public QMainWindow, public Ui::mainWindow
{
    Q_OBJECT

public:
    explicit ImageRegistration(QMainWindow *parent = 0);
    ~ImageRegistration();
    
private:
    MyImageClass *fixed_image_;
    std::vector<MyImageClass*> moving_image_vec_;
    QMessageBox msg_box_;
    LoadFile *load_files_hdd_;
    std::vector<MyRegistration*> registration_;




private slots:
    void ShowFileLoad();
    void ShowMoving();
    void ShowComputing();
    void SliderMovedFixed(int position);
    void SliderMovedMoving(int position);
    void SaveFiles();
    void StartRegistration();
    void ShowResultingFit();
    void SliderMovedResult(int);
    void AddMovingSeries();
    void SelectMovingSeries(int);

};

#endif // IMAGEREGISTRATION_H