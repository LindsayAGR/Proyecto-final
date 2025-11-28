#include "cohete.h"
#include <QtMath>
#include <QTimer>
Cohete::Cohete(const QPixmap pix, QObject *parent)
    : QObject(parent),
      QGraphicsPixmapItem(),
      pixmap(pix)

{
    QTransform t;
    t.rotate(90);    // |
    QPixmap pixVertical = pix.transformed(t);

    setPixmap(pixVertical);

    setTransformOriginPoint(boundingRect().center());//objeto rote desde su centro, no desde la esquina.


    vel =10;

    banLeft = false;
    banRigth = false;
    banUp = false;
    banDown = false;

    // setRotation(-90);

    // posInicialX = x();

    // Timers
    oscTimer = new QTimer(this);
    connect(oscTimer, &QTimer::timeout, this, &Cohete::moverOscilacion);

    launchTimer = new QTimer(this);
    connect(launchTimer, &QTimer::timeout, this, &Cohete::moverLanzamiento);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Cohete::moveLeft);
    connect(timer, &QTimer::timeout, this, &Cohete::moveRight);
    connect(timer, &QTimer::timeout, this, &Cohete::moveUp);
    connect(timer, &QTimer::timeout, this, &Cohete::moveDown);
    timer->start(10);



}

void Cohete::iniciarOscilacion()
{
    oscTimer->start(16);
}

void Cohete::detenerOscilacion()
{
    oscTimer->stop();

}

void Cohete::moverOscilacion()
{

    angulo += velo;

    float dx = qSin(angulo) * amp;

    setX(posInicialX + dx);
}


void Cohete::lanzarC()
{
    detenerOscilacion();
    launchTimer->start(16);


        QPixmap px(":/imagenes/humoCohete.png");


        humo = new QGraphicsPixmapItem(px);
        humo->setScale(0.4);
        humo->setZValue(50); // detrás del cohete
        humo-> setPos(500,500);
        if (sceneNivel1Lanza) {
            sceneNivel1Lanza->addItem(humo);
        }



        humoTimer = 0;

        QTimer::singleShot(900, this, SLOT(borrarHumo()));

}

void Cohete::moverLanzamiento()
{
    setY(y() - 9);

}

void Cohete::setSceneNivel1Lanza(QGraphicsScene *scene)
{
    sceneNivel1Lanza = scene;
}

bool Cohete::checkBounds(int newX, int newY)
{
    return(newX>=sceneBounds.left()) &&
          (newX + boundingRect().width() * scale()<= sceneBounds.right())&&
          (newY>=sceneBounds.top()) &&
           (newY + boundingRect().height() * scale()<= sceneBounds.bottom());
}

void Cohete::borrarHumo()
{
    if (!humo) return;

    if (sceneNivel1Lanza)
        sceneNivel1Lanza->removeItem(humo);

    delete humo;
    humo = nullptr;

}

void Cohete::moveLeft()
{
    if(banLeft)
    {
        int newX = x() - vel;
        if(checkBounds(newX, y()))
            setPos(newX,y());
    }
}

void Cohete::moveRight()
{
    if(banRigth)
    {
        int newX = x() + vel;
        if(checkBounds(newX, y()))
            setPos(newX,y());
    }
}
void Cohete::moveUp()
{

    if(banUp)
    {
        int newY = y() - vel;
        if(checkBounds(x(), newY))
            setPos(x(), newY);
    }
}

void Cohete::moveDown()
{
    if(banDown)
    {
        int newY = y() + vel;
        if(checkBounds(x(), newY))
            setPos(x(), newY);
    }
}

