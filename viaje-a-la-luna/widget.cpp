#include "widget.h"
#include "ui_widget.h"
#include "astronauta.h"
#include "panel.h"
#include "cohete.h"
#include "nivel2.h"

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
    btnStart->setFocusPolicy(Qt::NoFocus);

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
    connect(bgTimer, &QTimer::timeout, this, &Widget::bgMoveN1);
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
    btnNivel1->setFocusPolicy(Qt::NoFocus);

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
    btnGas->setFocusPolicy(Qt::NoFocus);

    //boton2 oxigeno
    btnOxig = new QPushButton("Oxigeno",this);
    btnOxig->setGeometry(485,670,90,45);
    btnOxig->raise();
    btnOxig->show();

    connect(btnOxig, &QPushButton::clicked, this, &Widget::iniciarOxigeno);
    btnOxig->setFocusPolicy(Qt::NoFocus);

    //boton3 temperatura

    btnTemp = new QPushButton("Temperatura", this);
    btnTemp->setGeometry(588,670,90,45);
    btnTemp->raise();
    btnTemp->show();
    connect(btnTemp, &QPushButton::clicked,this, &Widget::iniciarTemperatura);
    btnTemp->setFocusPolicy(Qt::NoFocus);


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

btnGas->hide();

}

void Widget::iniciarOxigeno()
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



    QPixmap Foxigeno(":/imagenes/oxigeno.png");
    bgimageOx = new QGraphicsPixmapItem(Foxigeno);
    bgimageOx->setScale(0.4);
    bgimageOx->setPos(0,20);
    bgimageOx->setZValue(1);
    sceneNivel1->addItem(bgimageOx);

    if (!p) {
        p = new panel(sceneNivel1);


    }

    p->iniciarOxigeno();

    p->setZManecilla(20);
    p->setZZona(10);

    //reiniciar posicion y encender timer
    p->resetManecillaOxigeno();
}







void Widget::iniciarTemperatura()
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



    QPixmap Ftemp(":/imagenes/temperatura.png");
    bgimagetemp = new QGraphicsPixmapItem(Ftemp);
    bgimagetemp->setScale(0.9);
    bgimagetemp->setPos(0,20);
    bgimagetemp->setZValue(1);
    sceneNivel1->addItem(bgimagetemp);
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A)
    {
        p->modoGasolina = true;
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


            // btnSigte = new QPushButton("Panel Principal", this);
            // btnSigte->setGeometry(688,500,140,95);
            // btnSigte->raise();
            // btnSigte->show();

            // connect(btnSigte, &QPushButton::clicked,this, &Widget::iniciarNivel1);
                btnGas->hide();

            btnlanza = new QPushButton("ir al lanzamiento", this);
            btnlanza->setGeometry(600,200,180,50);
            btnlanza->raise();
            btnlanza->show();
            connect(btnlanza, &QPushButton::clicked,this, &Widget::iniciarLanzamiento);
            btnlanza->setFocusPolicy(Qt::NoFocus);

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

                    // //salir al inicio si perdio

                    // btnInicio = new QPushButton("Ir al inicio",  this);
                    // btnInicio->setGeometry(688,500,140,95);
                    // btnInicio->raise();
                    // btnInicio->show();
                    // connect(btnInicio, &QPushButton::clicked, this, &Widget::iniciarIntroduccion);
                    // btnInicio->setFocusPolicy(Qt::NoFocus);


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
    // oxígeno
    if (event->key() == Qt::Key_S)
    {
        if (p)
            p->presionarOxigeno();

    }
    if (event->key() == Qt::Key_D)   // tecla para temperatura
    {
        if (p->tempCorrecta())
        {
            // ACERTASTE
            imgAcierto = new QGraphicsPixmapItem(QPixmap(":/imagenes/acertaste.png"));
            imgAcierto->setScale(0.5);
            imgAcierto->setZValue(20);
            imgAcierto->setPos(200,220);
            sceneNivel1->addItem(imgAcierto);

            QMediaPlayer *son = new QMediaPlayer(this);
            QAudioOutput *out = new QAudioOutput(this);
            son->setAudioOutput(out);
            son->setSource(QUrl("qrc:/audios/acertaste.mp3"));
            out->setVolume(0.8);
            son->play();

            QTimer::singleShot(1200, this, [this](){
                sceneNivel1->removeItem(imgAcierto);
                delete imgAcierto;

            //     btnSigte = new QPushButton("Panel Principal", this);
            //     btnSigte->setGeometry(688,500,140,95);
            //     btnSigte->raise();
            //     btnSigte->show();
            //     connect(btnSigte, &QPushButton::clicked, this, &Widget::iniciarNivel1);
            //     btnSigte->setFocusPolicy(Qt::NoFocus);
            });
        }
        else
        {
            vidas--;
            actualizarVidas();

            imgFallo = new QGraphicsPixmapItem(QPixmap(":/imagenes/fallaste.png"));
            imgFallo->setScale(0.5);
            imgFallo->setZValue(20);
            imgFallo->setPos(200,220);
            sceneNivel1->addItem(imgFallo);

            QMediaPlayer *son = new QMediaPlayer(this);
            QAudioOutput *out = new QAudioOutput(this);
            son->setAudioOutput(out);
            son->setSource(QUrl("qrc:/audios/fail.mp3"));
            out->setVolume(0.8);
            son->play();

            QTimer::singleShot(1200, this, [this](){
                sceneNivel1->removeItem(imgFallo);
                delete imgFallo;

                if (vidas <= 0) {
                    // GAME OVER
                    imgGameOver = new QGraphicsPixmapItem(QPixmap(":/imagenes/gameOver.png"));
                    imgGameOver->setScale(0.5);
                    imgGameOver->setZValue(20);
                    imgGameOver->setPos(150,220);
                    sceneNivel1->addItem(imgGameOver);
                }
            });
        }

    }


    if (event->key() == Qt::Key_S)
    {
        if (p)
            p->presionarOxigeno();
    }

    if(!cohete) return;

    if(event->key() == Qt::Key_W)
    {
        cohete->detenerOscilacion();
        cohete->lanzarC();
    }

    if (event->key() == Qt::Key_S)
    {
        if (p)
            p->presionarOxigeno();
    }
    if(event->key() == Qt::Key_Left)
        cohete->setBanLeft(true);
    else if(event->key() == Qt::Key_Right)
        cohete->setBanRigth(true);
    else if(event->key() == Qt::Key_Up)
        cohete->setBanUp(true);
    else if(event->key() == Qt::Key_Down)
        cohete->setBanDown(true);


}




void Widget::keyReleaseEvent(QKeyEvent *event1)
{
    if (gameOver) {
        QWidget::keyReleaseEvent(event1);
        return;
    }

    // solo procesar S (oxígeno)
    if (event1->key() == Qt::Key_S)
    {
        if (!p) return;

        // evita procesar si ya estamos mostrando resultado
        if (procesandoResultado) return;
        procesandoResultado = true;

        // detener acción y evaluar
        p->soltarOxigeno(); // deja la manecilla en su posición / para timer
        bool acerto = p->evaluarOxigeno(); // ahora usamos valor booleano claro

        if (acerto)
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

            QTimer::singleShot(1200, this, [this, son]() {
                // eliminar imagen y liberar memoria
                sceneNivel1->removeItem(imgAcierto);
                delete imgAcierto;
                imgAcierto = nullptr;

                // / volver al panel principal
                // btnSigte = new QPushButton("Panel Principal", this);
                // btnSigte->setGeometry(688,500,140,95);
                // btnSigte->raise();
                // btnSigte->show();
                // connect(btnSigte, &QPushButton::clicked, this, &Widget::iniciarNivel1);
                //btnSigte->setFocusPolicy(Qt::NoFocus);

                procesandoResultado = false;
            });
        }
        else
        {
            vidas--;
            if (vidas < 0) vidas = 0;
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

            QTimer::singleShot(1200, this, [this, son]() {
                sceneNivel1->removeItem(imgFallo);
                delete imgFallo;
                imgFallo = nullptr;

                if (vidas > 0)
                {
                    p->reanudarFlecha();  // sigues jugando
                    procesandoResultado = false;
                }
                else
                {
                    // game over
                    imgGameOver = new QGraphicsPixmapItem(QPixmap(":/imagenes/gameOver.png"));
                    imgGameOver->setScale(0.5);
                    imgGameOver->setZValue(20);
                    imgGameOver->setPos(150,220);
                    sceneNivel1->addItem(imgGameOver);

                    QMediaPlayer *sonOver = new QMediaPlayer(this);
                    QAudioOutput *Sonfail = new QAudioOutput(this);
                    sonOver->setAudioOutput(Sonfail);
                    sonOver->setSource(QUrl("qrc:/audios/gameOver.mp3"));
                    Sonfail->setVolume(0.8);
                    sonOver->play();

                    // Bloquea entradas adicionales
                    gameOver = true;
                    procesandoResultado = false;

                   //  btnInicio = new QPushButton("Ir al inicio",  this);
                   //  btnInicio->setGeometry(688,500,140,95);
                   //  btnInicio->raise();
                   //  btnInicio->show();
                   //  connect(btnInicio, &QPushButton::clicked, this, &Widget::iniciarIntroduccion);
                    //btnInicio->setFocusPolicy(Qt::NoFocus);

                }
            });
        }
    }



// QWidget::keyReleaseEvent(event1);

}

void Widget::bgMoveN1()
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

void Widget::bgMoveN2()
{
//espacio

// mover los dos fondos
imageEsp1->setX(imageEsp1->x() - 2);
imageEsp2->setX(imageEsp2->x() - 2);

// si bgImage1 sale completamente de pantalla
if (imageEsp1->x() + imageEsp1->pixmap().width() < 0) {
    imageEsp1->setX(imageEsp2->x() + imageEsp2->pixmap().width());
}

// si bgImage2 sale completamente de pantalla
if (imageEsp2->x() + imageEsp2->pixmap().width() < 0) {
    imageEsp2->setX(imageEsp1->x() + imageEsp1->pixmap().width());
}

}

void Widget::spawnAsteroids()
{
    if (Asteroides.count()<5)
    {
        Asteroide *as = new Asteroide(this);
        sceneEsp ->addItem(as);
        Asteroides.append(as);
        connect(as, &Asteroide::removeList, this, &Widget::removeAst);
    }
}

void Widget::removeAst(Asteroide *as)
{
    Asteroides.removeOne(as);
}

void Widget::detenerEspacio()
{
    if (EspTimer) EspTimer->stop();   // detiene el fondo
    if (asTimer) asTimer->stop();     // detiene asteroides


}

void Widget::actualizarVidas()
{
    vida1->setVisible(vidas == 1);
    vida2->setVisible(vidas == 2);
    vida3->setVisible(vidas == 3);

}

void Widget::iniciarLanzamiento()
{


    btnlanza->hide();

    SoniPanel->stop();
    btnGas->hide();
    btnOxig->hide();
    btnTemp->hide();

    //configurar primera esena
    sceneNivel1Lanza = new QGraphicsScene(ui->graphicsView->rect(), this);
    // ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(sceneNivel1Lanza);

    //Añadir fondo
    QPixmap originalImage(":/imagenes/fondo1.png");
    bgImage1 = new QGraphicsPixmapItem(originalImage);
    bgImage2 = new QGraphicsPixmapItem(originalImage);
    bgImage1->setPos(0, 0);
    bgImage2->setPos(originalImage.width(), 0);
    sceneNivel1Lanza->addItem(bgImage1);
    sceneNivel1Lanza->addItem(bgImage2);

    //timer para mover fondo
    bgTimer = new QTimer(this);
    connect(bgTimer, &QTimer::timeout, this, &Widget::bgMoveN1);
    bgTimer->start(16);

    //añadir cohete

    cohete  = new Cohete(QPixmap(":/imagenes/nave.png"));
    cohete->setScale(0.5);
    cohete->setPos(100,-24);
    cohete->setZValue(100);
    sceneNivel1Lanza->addItem(cohete);

    cohete->setSceneNivel1Lanza(sceneNivel1Lanza);





    // GUARDA LA POSICIÓN REAL DESPUÉS DE ESTAR EN LA ESCENA
    QTimer::singleShot(30,this, [=](){
        cohete->setRotation(-90);
        cohete->posInicialX = cohete->x();
        cohete->iniciarOscilacion();
    });

    //añadir musiquita
    introfon = new QMediaPlayer(this);
    QAudioOutput *sonidointro = new QAudioOutput(this);
    introfon->setAudioOutput(sonidointro);
    introfon->setSource(QUrl("qrc:/audios/introfondo.mp3"));
    sonidointro->setVolume(0.1);
    // Reproducir automáticamente
    introfon->play();

    // QPixmap pixHumo(":/imagenes/humoCohete.png");
    // humo = new QGraphicsPixmapItem(pixHumo);
    // humo->setScale(0.4);
    // humo->setZValue(50);    // detrás del cohete
    // sceneNivel1Lanza->addItem(humo);

    // // Posición inicial del humo (debajo del cohete)
    // humo->setPos(cohete->x() + cohete->boundingRect().width()*0.2,
    //              cohete->y() + cohete->boundingRect().height()*0.6);

    btnNivel2 = new QPushButton("Iniciar Nivel2",this);
    btnNivel2->setGeometry(700,500,180,50);
    btnNivel2->raise();  // asegurarte que quede al frente
    btnNivel2->show();

    connect(btnNivel2, &QPushButton::clicked, this, &Widget::iniciarNivel2);
    btnNivel2->setFocusPolicy(Qt::NoFocus);




}

void Widget::iniciarNivel2()
{
    //eliminar boton de start

    btnNivel2->hide();
    introfon->stop();


    //configurar primera esena


    ui->graphicsView->setFocus(); // MUY IMPORTANTE


    sceneEsp = new QGraphicsScene(ui->graphicsView->rect(), this);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(sceneEsp);

    sceneEsp->setSceneRect(ui->graphicsView->rect());

    this->setFocus();


    //Añadir fondo
    QPixmap originalImageEsp(":/imagenes/espacio.png");
    imageEsp1 = new QGraphicsPixmapItem(originalImageEsp);
    imageEsp1->setScale(2.1);
    imageEsp2 = new QGraphicsPixmapItem(originalImageEsp);
    imageEsp2->setScale(2.1);
    imageEsp1->setPos(0, 0);
    imageEsp2->setPos(originalImageEsp.width(), 0);
    sceneEsp->addItem(imageEsp1);
    sceneEsp->addItem(imageEsp2);


    //timer para mover fondo
    EspTimer = new QTimer(this);
    connect(EspTimer, &QTimer::timeout, this, &Widget::bgMoveN2);
    EspTimer->start(16);


    //añadir cohete

    QPixmap pixmap(":/imagenes/nave.png");
    cohete = new Cohete(pixmap);
    cohete->setScale(0.2);
    cohete->setPos(-350,50);
    cohete->setZValue(100);
    cohete->setRotation(0);
    sceneEsp->addItem(cohete);

    connect(cohete, &Cohete::detenerTodoSignal, this, &Widget::detenerEspacio);
    connect(cohete, &Cohete::colisionCohete, this, &Widget::detenerEspacio);
    connect(cohete, &Cohete::detenerAsteroidesSignal, this, &Widget::detenerAsteroides);
    connect(cohete, &Cohete::reiniciarSignal, this, &Widget::reiniciarTodo);



    cohete->setSceneBounds(sceneEsp->sceneRect());   // <- imprescindible
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->setFocus();

    //crear asteroides
    numAst = 0;
    asTimer = new QTimer(this);
    connect(asTimer, &QTimer::timeout, this, &Widget::spawnAsteroids);
    asTimer->start(2000);


    ui->graphicsView->setInteractive(true);
    ui->graphicsView->setFocus();

}

void Widget::detenerAsteroides()
{
    for (Asteroide *as : Asteroides) {
        if (as) as->detener();   // usa as->detener() que TÚ ya tienes
    }

    // detener generación de nuevos asteroides
    if (asTimer) asTimer->stop();
}

void Widget::reiniciarTodo()
{
    // 1. ELIMINAR ASTEROIDES
    for (Asteroide *as : Asteroides)
    {
        if (!as) continue;
        if (as->scene()) sceneEsp->removeItem(as);
        delete as;
    }
    Asteroides.clear();

    // 2. MOSTRAR COHETE REINICIADO
    if (cohete)
    {
        cohete->show();
        cohete->setPos(-350, 50);       // POSICIÓN ORIGINAL DEL NIVEL 2
        cohete->setRotation(0);
        cohete->setScale(0.2);

        // IMPORTANTE: actualizar límites y activar timers del COHETE
        cohete->setSceneBounds(sceneEsp->sceneRect());
        if (cohete->timer)      cohete->timer->start(10);
        if (cohete->collTimer)  cohete->collTimer->start(50);
        cohete->iniciarOscilacion();
    }

    // 3. REINICIAR FONDO
    if (EspTimer) EspTimer->start(16);

    // 4. REINICIAR GENERACIÓN DE ASTEROIDES
    if (asTimer) asTimer->start(2000);
}
