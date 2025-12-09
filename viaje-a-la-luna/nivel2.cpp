#include "nivel2.h"
#include <QDebug>

Nivel2::Nivel2(QWidget *parent)
    : QGraphicsView(parent)
{
    // Escena
    scene = new QGraphicsScene(this);
    setScene(scene);
    setFixedSize(800,600);
    scene->setSceneRect(0,0,800,600);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // Crear cohete
    cohete = new Cohete(QPixmap(":/imagenes/nave.png"));
    scene->addItem(cohete);
    cohete->setPos(300,400);
    cohete->setSceneBounds(scene->sceneRect());


    connect(cohete, &Cohete::detenerTodoSignal, this, [this]() {
        timerSuperado->stop();
    });

    // --- ARREGLO DEL FOCO ---
    // La vista sí debe recibir foco para poder captar teclas
    setFocusPolicy(Qt::StrongFocus);
    setFocus();

    qDebug() << "Nivel2 focus?" << this->hasFocus();

    timerSuperado = new QTimer(this);
    timerSuperado->setSingleShot(true);

    connect(timerSuperado, &QTimer::timeout, this, [this]() {
        qDebug() << "NIVEL COMPLETADO POR TIEMPO";
        mostrarSuperado();
    });

    // Iniciar el tiempo de sobrevivencia
    timerSuperado->start(20000);



}

void Nivel2::mostrarSuperado()
{
    qDebug() << "Ejecutando mostrarSuperado()";

    // Detener cohete
    cohete->detenerOscilacion();
    cohete->timer->stop();
    cohete->collTimer->stop();

    // Detener asteroides
    emit cohete->detenerAsteroidesSignal();

    // Mostrar imagen
    imgSuperado = new QGraphicsPixmapItem(QPixmap(":/imagenes/superado.png"));
    imgSuperado->setScale(0.6);
    imgSuperado->setZValue(999);
    imgSuperado->setPos(150, 80);
    scene->addItem(imgSuperado);

    // Botón
    btnN3 = new QPushButton("Siguiente nivel");
    QGraphicsProxyWidget *proxy = scene->addWidget(btnN3);
    proxy->setPos(300,400);
    proxy->setZValue(999);

    btnN3->setFocusPolicy(Qt::NoFocus);
    proxy->setFlag(QGraphicsItem::ItemIsFocusable, false);

    connect(btnN3, &QPushButton::clicked, this, &Nivel2::irASiguienteNivel);

    setFocus();
}



void Nivel2::irASiguienteNivel()
{
    qDebug() << "Cambiando al siguiente nivel...";

    // Crear el siguiente nivel
    nivel3 *n3 = new nivel3();

    // Mostrarlo
    n3->show();

    // Cerrar el nivel actual
    this->close();
}


void Nivel2::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "KEY EVENT :" << event->key();
    qDebug() << "Cohete recibe tecla!";

    if(event->key() == Qt::Key_Left)
        cohete->setBanLeft(true);
    else if(event->key() == Qt::Key_Right)
        cohete->setBanRigth(true);
    else if(event->key() == Qt::Key_Up)
        cohete->setBanUp(true);
    else if(event->key() == Qt::Key_Down)
        cohete->setBanDown(true);
    else if(event->key() == Qt::Key_W)
        cohete->lanzarC();
}


void Nivel2::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
        cohete->setBanLeft(false);
    else if(event->key() == Qt::Key_Right)
        cohete->setBanRigth(false);
    else if(event->key() == Qt::Key_Up)
        cohete->setBanUp(false);
    else if(event->key() == Qt::Key_Down)
        cohete->setBanDown(false);
}

