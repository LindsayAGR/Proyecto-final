#include "panel.h"


panel::panel(QGraphicsScene *sceneGaso) {

    sceneGaso->addItem(this);

}

void panel::iniciarGasolina()
{
    setZValue(20);
    flecha = new QGraphicsPixmapItem(QPixmap(":/imagenes//flechaAz.png"));
    flecha->setZValue(21);
    flecha-> setScale(0.1);

    flecha-> setPos (300,200);
    addToGroup(flecha);


    //zona roja
    zonaRoja = new QGraphicsRectItem(298,340,50,10);
    zonaRoja->setBrush(Qt::red);
    zonaRoja->setOpacity(0.5);
    zonaRoja->setZValue(15);
    addToGroup(zonaRoja);

    //timer movimiento
    TiempoMovimiento = new QTimer(this);
    connect(TiempoMovimiento, &QTimer::timeout, this, &panel::moverFlecha);
    TiempoMovimiento->start(16);

}

void panel::  moverFlecha()
{
    if(detenida) return;

    tiempo += 0.05;

//mov armonico simple
    double baseY = 300;
    double amplitud = 110;

    double nuevaY = baseY + amplitud * sin(tiempo);

    flecha->setY(nuevaY);

}
void panel:: detenerFlecha()
{
    detenida= true;
}
void panel:: reanudarFlecha()
{
    detenida=false;

}

bool panel:: zonacorrecta() //
{
    QPointF posF = flecha->mapToScene(flecha->boundingRect().center());
    QPointF posZ = zonaRoja->mapToScene(zonaRoja->boundingRect().center());

    return (posF.y() > posZ.y() - 10 && posF.y() < posZ.y() + 10);
}

// panel::panel(QGraphicsScene *sceneOxig){

// }


// panel::panel(QGraphicsScene *sceneTemp){

// }
