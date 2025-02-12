
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <camera.h>
#include <pointlight.h>
#include <Sphere.h>

const size_t image_weight = 1000;
const size_t image_height = 550;
const int MAX_STEPS = 100;
const double MAX_DIST = 100;
const double COLLISION_ACCURACY = 0.01;
const QVector3D CAMERA_POSITION(0, 0, 0);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->resize(50, 50);

    RayMarching::Sphere *sphere = new RayMarching::Sphere(QVector3D(1, 0.5, 3), 0.7);
    RayMarching::Sphere *sphere2 = new RayMarching::Sphere(QVector3D(-2, -0.5, 3), 1);
    RayMarching::Sphere *sphere3 = new RayMarching::Sphere(QVector3D(-1, -2, 5), 1);

    RayMarching::PointLight *light = new RayMarching::PointLight(QVector3D(1.2, 1.2, 1.2), 100);
    RayMarching::PointLight *light2 = new RayMarching::PointLight(QVector3D(-1.2, -1, 1.2), 3);

    ui->camera->set_position(QVector3D(0, 0, 0));

    ui->camera->add_object(*sphere);
    ui->camera->add_object(*sphere2);
    ui->camera->add_object(*sphere3);
    ui->camera->add_object(*light);
    ui->camera->add_object(*light2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_released()
{
    ui->textEdit->resize(50, 50);
    ui->textEdit->setText("Text");
}

void MainWindow::on_pushButton_2_pressed()
{
    ui->textEdit->resize(90, 50);
    ui->textEdit->setText("The button is touched");
}



