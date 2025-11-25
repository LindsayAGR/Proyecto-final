#include "widget.h"
#include "ui_widget.h"
#include "astronauta.h"
#include "panel.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    p= nullptr;

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
    QAudioOutput *sonidoinicio = new QAudioOutput(this);
    introinicio->setAudioOutput(sonidoinicio);
    introinicio->setSource(QUrl("qrc:/audios/inicioJu.mp3"));
    sonidoinicio->setVolume(0.3);
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

    btnNivel1 = new QPushButton("Iniciar Nivel1",this);

    btnNivel1->setGeometry(700,500,180,50);
    btnNivel1->raise();  // asegurarte que quede al frente
    btnNivel1->show();

    connect(btnNivel1, &QPushButton::clicked, this, &Widget::iniciarNivel1);
}

void Widget::iniciarNivel1()
{




    //eliminar boton de start

    btnNivel1->hide();
    intro1->stop();
    introfon->stop();

    sceneNivel1 = new QGraphicsScene(ui->graphicsView->rect(), this);
    ui->graphicsView->setScene(sceneNivel1);

    //Añadir fondo
    QPixmap originalImage(":/imagenes/panel1.png");
    bgimageN1 = new QGraphicsPixmapItem(originalImage);
    bgimageN1->setScale(2);
    bgimageN1->setPos(-100,40);
    sceneNivel1->addItem(bgimageN1);

    //añadir musiquita
    SoniPanel = new QMediaPlayer(this);
    audioPanel = new QAudioOutput(this);

    QAudioOutput *sonidoPanel = new QAudioOutput(this);
    SoniPanel->setAudioOutput(sonidoPanel);
    SoniPanel->setSource(QUrl("qrc:/audios/Sonpanel.mp3"));
    sonidoPanel->setVolume(0.09);
    // Reproducir automáticamente
    SoniPanel->play();

    //boton1 gasolina

    btnGas = new QPushButton("Gasolina", this);
    btnGas->setGeometry(380,670,90,45);
    btnGas->raise();  // asegurarte que quede al frente
    btnGas->show();

    connect(btnGas, &QPushButton::clicked, this, &Widget::iniciarGasolina);

    //boton2 oxigeno
    btnOxig = new QPushButton("Oxigeno",this);
    btnOxig->setGeometry(485,670,90,45);
    btnOxig->raise();
    btnOxig->show();

    connect(btnOxig, &QPushButton::clicked, this, &Widget::iniciarOxigeno);

    //boton3 temperatura

    btnTemp = new QPushButton("Temperatura", this);
    btnTemp->setGeometry(588,670,90,45);
    btnTemp->raise();
    btnTemp->show();

    connect(btnTemp, &QPushButton::clicked,this, &Widget::iniciarTemperatura);




}
void Widget::iniciarGasolina()
{


    vida1 = new QGraphicsPixmapItem(QPixmap(":/imagenes/vidas1.png"));
    vida1->setPos(650, 0);
    vida1->setScale(0.2);
    vida1->setZValue(10);
    sceneNivel1->addItem(vida1);

    vida2 = new QGraphicsPixmapItem(QPixmap(":/imagenes/vidas2.png"));
    vida2->setPos(650, 0);
    vida2->setScale(0.2);
    vida2->setZValue(10);
    sceneNivel1->addItem(vida2);

    vida3 = new QGraphicsPixmapItem(QPixmap(":/imagenes/vidas3.png"));
    vida3->setPos(650, 0);
    vida3->setScale(0.2);
    vida3->setZValue(10);
    sceneNivel1->addItem(vida3);



    //Añadir fondo

    QPixmap originalImage(":/imagenes/gasolina.png");
    bgimageGas = new QGraphicsPixmapItem(originalImage);
    bgimageGas->setScale(1);
    bgimageGas->setPos(0,0);
    bgimageGas->setZValue(1);
    sceneNivel1->addItem(bgimageGas);

    if (!p){
        p = new panel(sceneNivel1);
    }

    p->iniciarGasolina();

    vidas = 3;
    actualizarVidas();


}

void Widget::iniciarOxigeno()
{

}

void Widget::iniciarTemperatura()
{

}
void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A)
    {
        p->detenerFlecha();

        if (p->zonacorrecta())
        {

            // MOSTRAR ACERTASTE
            imgAcierto = new QGraphicsPixmapItem(QPixmap(":/imagenes/acertaste.png"));
            imgAcierto->setScale(0.5);
            imgAcierto->setZValue(20);
            imgAcierto->setPos(200,220);
            sceneNivel1->addItem(imgAcierto);

            // sonido
            QMediaPlayer *son = new QMediaPlayer(this);
            QAudioOutput *out = new QAudioOutput(this);
            son->setAudioOutput(out);
            son->setSource(QUrl("qrc:/audios/acertaste.mp3"));
            out->setVolume(0.8);
            son->play();

            QTimer::singleShot(1200, this, [this](){
                sceneNivel1->removeItem(imgAcierto);
                delete imgAcierto;





            btnSigte = new QPushButton("Panel Principal", this);
            btnSigte->setGeometry(688,500,140,95);
            btnSigte->raise();
            btnSigte->show();

            connect(btnSigte, &QPushButton::clicked,this, &Widget::iniciarNivel1);

            });
        }
        else
        {
            vidas--;
            actualizarVidas();
            // MOSTRAR FÁLLASTE
            imgFallo = new QGraphicsPixmapItem(QPixmap(":/imagenes/fallaste.png"));
            imgFallo->setScale(0.5);
            imgFallo->setZValue(20);
            imgFallo->setPos(200,220);
            sceneNivel1->addItem(imgFallo);

            // sonido
            QMediaPlayer *son = new QMediaPlayer(this);
            QAudioOutput *out = new QAudioOutput(this);
            son->setAudioOutput(out);
            son->setSource(QUrl("qrc:/audios/fail.mp3"));
            out->setVolume(0.8);
            son->play();

            // QUITAR IMAGEN DESPUÉS DE UN TIEMPO
            QTimer::singleShot(1200, this, [this](){
                sceneNivel1->removeItem(imgFallo);
                delete imgFallo;

                if (vidas > 0)
                {
                    p->reanudarFlecha();  // SIGUE EL JUEGO
                }
                else
                {
                    imgGameOver = new QGraphicsPixmapItem(QPixmap(":/imagenes/gameOver.png"));
                    imgGameOver->setScale(0.5);
                    imgGameOver->setZValue(20);
                    imgGameOver->setPos(150,220);
                    sceneNivel1->addItem(imgGameOver);

                    // sonido game over
                    QMediaPlayer *sonOver = new QMediaPlayer(this);
                    QAudioOutput *Sonfail = new QAudioOutput(this);
                    sonOver->setAudioOutput(Sonfail);
                    sonOver->setSource(QUrl("qrc:/audios/gameOver.mp3"));
                    Sonfail->setVolume(0.8);
                    sonOver->play();
                }
            });
        }
    }
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

void Widget::actualizarVidas()
{
    vida1->setVisible(vidas == 1);
    vida2->setVisible(vidas == 2);
    vida3->setVisible(vidas == 3);

}



