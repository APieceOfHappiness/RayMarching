
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <camera.h>
#include <pointlight.h>.h>
#include <circle.h>

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

    QImage image = QImage(image_weight, image_height, QImage::Format_RGB32);
    size_t x, y;

    QVector3D circle_center(0, 0, 5);
    RayMarching::Circle circle(QVector3D(1, 0.5, 3), 0.7);
    RayMarching::Circle circle2(QVector3D(-2, -0.5, 3), 1);

    RayMarching::PointLight light(QVector3D(1.2, 1.2, 1.2), 100);
    RayMarching::PointLight light2(QVector3D(-1.2, -1, 1.2), 3);

    RayMarching::Camera camera;
    camera.set_inner_scene(image);
    camera.set_position(QVector3D(0, 0, 0));

    camera.add_object(circle);
    camera.add_object(circle2);
    camera.add_object(light);
    camera.add_object(light2);

    camera.render_the_scene();

    QGraphicsScene *graphic = new QGraphicsScene(this);

    graphic->addPixmap(QPixmap::fromImage(image));
    ui->graphicsView->setScene(graphic);
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


//    for (size_t i = 0; i < image_weight; ++i) {
//        for (size_t j = 0; j < image_height; ++j) {
//            QVector3D pixel_color = evaluatePixelColor(i, j);
//            image.setPixel(i, j, qRgb(pixel_color.x(), pixel_color.y(), pixel_color.z()));
//        }
//    }

//-----------------------------------------

//const size_t image_weight = 1000;
//const size_t image_height = 550;
//const int MAX_STEPS = 100;
//const double MAX_DIST = 100;
//const double COLLISION_ACCURACY = 0.01;
//const QVector3D CAMERA_POSITION(0, 0, 0);

//double circleDist(QVector3D point, QVector3D center, double radius) {
//    return (point - center).length() - radius;
//}

//double rayMarch(QVector3D ro, QVector3D rd) {
//    double dO = 0;

//    QVector3D point;
//    for (int i = 0; i < MAX_STEPS; ++i) {
//        point = ro + dO * rd;
//        dO += circleDist(point, QVector3D(0, 0, 5), 1);
//        if (dO > MAX_DIST || dO < COLLISION_ACCURACY) {
//            if (dO > MAX_DIST) {
//                dO = 100;
//            }
//            break;
//        }
//    }

//    return dO;
//}

//QVector3D evaluatePixelColor(double in_x, double in_y)
//{
//    double screen_resolution_aspect = static_cast<double>(image_weight) / image_height;
//    double norm_x = (in_x / image_weight - 0.5) * screen_resolution_aspect;
//    double norm_y = (in_y / image_height - 0.5);
//    QVector3D ro(-CAMERA_POSITION);
//    QVector3D rd(QVector3D(norm_x, norm_y, 1).normalized());

//    double dist = rayMarch(ro, rd) / 100 * 255;
////    qDebug() << ro.x() << "," << ro.y() << "," << ro.z();
////    qDebug() << rd.x() << "," << rd.y() << "," << rd.z();
////    qDebug() << dist;
//    return QVector3D(dist, dist, dist);
//}

