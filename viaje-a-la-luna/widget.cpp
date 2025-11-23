#include "widget.h"
#include "ui_widget.h"
#include "astronauta.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mostrarInicio();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mostrarInicio()
{
    sceneInicio = new QGraphicsScene(ui->graphicsView->rect(),this);
    ui->graphicsView->setScene(sceneInicio);

    //fondo portada
    QPixmap portada(":/imagenes/inicio.png");
    QGraphicsPixmapItem *inici = new QGraphicsPixmapItem(portada);
    inici->setPos(10,100);
    inici->setScale(1.6);
    sceneInicio->addItem(inici);


    //Boton Start

    btnStart = new QPushButton("",this);
    btnStart->setGeometry(430,680,180,50);

    connect(btnStart, &QPushButton::clicked, this, &Widget::iniciarIntroduccion);

    //añadir musiquita
    introinicio = new QMediaPlayer(this);
    QAudioOutput *sonidointro = new QAudioOutput(this);
    introinicio->setAudioOutput(sonidointro);
    introinicio->setSource(QUrl("qrc:/audios/inicio.mp3"));
    sonidointro->setVolume(0.3);
    // Reproducir automáticamente
    introinicio->play();

}

void Widget::iniciarIntroduccion()
{
    //eliminar boton de start
    btnStart->hide();
    introinicio->stop();

    //configurar primera esena
    scene1 = new QGraphicsScene(ui->graphicsView->rect(), this);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(scene1);

    //Añadir fondo
    QPixmap originalImage(":/imagenes/fondo1.png");
    bgImage1 = new QGraphicsPixmapItem(originalImage);
    bgImage2 = new QGraphicsPixmapItem(originalImage);
    bgImage1->setPos(0, 0);
    bgImage2->setPos(originalImage.width(), 0);
    scene1->addItem(bgImage1);
    scene1->addItem(bgImage2);

    //timer para mover fondo
    bgTimer = new QTimer(this);
    connect(bgTimer, &QTimer::timeout, this, &Widget::bgMove);
    bgTimer->start(16);


    //añadir astronauta
    QPixmap pixmapPlayer (":/imagenes/astrona.png");
    astro = new astronauta(pixmapPlayer, this);
    astro->setScale(1.1);
    astro->setPos(0,225);
    scene1->addItem(astro);


    //texto
    QGraphicsTextItem *texto = new QGraphicsTextItem("En 1969, el cohete Saturno 5 \n"
                                                     "el más poderosos jamás construido fue el encargado \n"
                                                     "de llevar a los astronautas de \n"
                                                     "la misión Apolo 11 hacia la luna.\n"
                                                     "Esto marcó un antes y un después en la historia.\n"
                                                     "Neil Armstrong fue el primer ser humano en pisar la Luna, \n"
                                                     "acompañado por Buzz Aldrin, mientras Michael Collins \n"
                                                     "permanecía en órbita.\n"
                                                     "Hoy, tú serás quien reviva esa misión histórica….");
    texto->setPos(450, 120);
    texto->setScale(1.5);
    scene1->addItem(texto);

    //añadir audio intro
    intro1 = new QMediaPlayer(this);
    QAudioOutput *audiointro = new QAudioOutput(this);
    intro1->setAudioOutput(audiointro);
    intro1->setSource(QUrl("qrc:/audios/intro.mp3"));
    audiointro->setVolume(1);
    // Reproducir automáticamente
    intro1->play();


    //añadir musiquita
    introfon = new QMediaPlayer(this);
    QAudioOutput *sonidointro = new QAudioOutput(this);
    introfon->setAudioOutput(sonidointro);
    introfon->setSource(QUrl("qrc:/audios/introfondo.mp3"));
    sonidointro->setVolume(0.1);
    // Reproducir automáticamente
    introfon->play();

}

void Widget::bgMove()
{

    // mover los dos fondos
    bgImage1->setX(bgImage1->x() - 2);
    bgImage2->setX(bgImage2->x() - 2);

    // si bgImage1 sale completamente de pantalla
    if (bgImage1->x() + bgImage1->pixmap().width() < 0) {
        bgImage1->setX(bgImage2->x() + bgImage2->pixmap().width());
    }

    // si bgImage2 sale completamente de pantalla
    if (bgImage2->x() + bgImage2->pixmap().width() < 0) {
        bgImage2->setX(bgImage1->x() + bgImage1->pixmap().width());
    }
}



