#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //configurar primera esena
    scene = new QGraphicsScene(ui->graphicsView->rect(), this);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(scene);

    //Añadir fondo
    QPixmap originalImage(":/imagenes/fondo1.png");
    bgImage = new QGraphicsPixmapItem(originalImage);
    bgImage->setPos(0,0);
    scene->addItem(bgImage);

    //     //añadir astronauta
    // QPixmap pixmapPlayer(":/imagenes/astronauta.png");
    // astronauta = new astronauta(pixmapPlayer, this);
    // astronauta->setScale(0.07);
    // astronauta->setpos(50,150);
    // scene->addItem(astronauta);

}

Widget::~Widget()
{
    delete ui;
}
