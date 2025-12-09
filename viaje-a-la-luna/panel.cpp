#include "panel.h"


panel::panel(QGraphicsScene *sceneN1)
{
    sceneMa = sceneN1;
    sceneO  = sceneN1;
    sceneN1->addItem(this);

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


void panel::iniciarOxigeno()
{
    // Asegúrate de poner z-values altos para que esté encima del fondo
    setZValue(20);

    // Manecilla
    QPixmap manec(":/imagenes/manecilla.png");
    manecillaOxi = new QGraphicsPixmapItem(manec);
    manecillaOxi->setZValue(100);
    manecillaOxi->setPos(100, 100);   // posición inicial
    manecillaOxi->setScale(1.0);
    sceneMa->addItem(manecillaOxi);

    // Zona correcta
    QPixmap zona(":/imagenes/oxigeno.png");
    zonaMedia = new QGraphicsPixmapItem(zona);
    zonaMedia->setZValue(15);
    zonaMedia->setPos(500, 250);
    sceneMa->addItem(zonaMedia);

    // Timer para mover manecillas
    TiempoOxi = new QTimer(this);
    connect(TiempoOxi, &QTimer::timeout, this, &panel::moverManecilla);
    TiempoOxi->start(16);
}

void panel::presionarOxigeno()
{
    oxiPresion = true;
    TiempoOxi->start(20);
}

void panel::soltarOxigeno()
{
    oxiPresion = false;
    TiempoOxi->stop();
    evaluarOxigeno();
}

bool panel::evaluarOxigeno()
{
    QPointF posM = manecillaOxi->mapToScene(manecillaOxi->boundingRect().center());
    QPointF posZ = zonaMedia->mapToScene(zonaMedia->boundingRect().center());

    int tolerancia = 15; // píxeles de margen

    bool aciertoFlag = (posM.y() > posZ.y() - tolerancia &&
                        posM.y() < posZ.y() + tolerancia);

    if (aciertoFlag) {
        emit acierto();
    } else {
        emit fallo();
    }

    return aciertoFlag;   // <--  DEVUELVE BOOL
}

void panel::moverManecilla()
{
    // solo mover si el usuario está presionando
    if (!oxiPresion) return;

    // bajar/subir la manecilla;
    qreal nuevaY = manecillaOxi->y() - 2;
    if (nuevaY < 250) nuevaY = 250; // tope superior
    manecillaOxi->setY(nuevaY);
}

void panel::resetManecillaOxigeno()
{
    if (manecillaOxi)
        manecillaOxi->setY(500);
}

void panel::iniciarTimerOxigeno()
{
    if (TiempoOxi) TiempoOxi->start(20);
}

void panel::setZManecilla(int z)
{
    if (manecillaOxi) manecillaOxi->setZValue(z);
}

void panel::setZZona(int z)
{
    if (zonaMedia) zonaMedia->setZValue(z);
}


void panel::iniciarTemperatura()
{
    setZValue(20);

    // termómetro base
    QPixmap img(":/imagenes/temperatura.png");
    termometro = new QGraphicsPixmapItem(img);
    termometro->setPos(350,150);
    addToGroup(termometro);

    // barra roja
    barraTemp = new QGraphicsRectItem(0,0,20,80);
    barraTemp->setBrush(Qt::red);
    barraTemp->setPos(395, 330);
    addToGroup(barraTemp);

    // zona verde (rango correcto)
    zonaVerde = new QGraphicsRectItem(0,0,20,50);
    zonaVerde->setBrush(Qt::green);
    zonaVerde->setOpacity(0.4);
    zonaVerde->setPos(395, 250);
    addToGroup(zonaVerde);

    // timer del movimiento
    timerTemp = new QTimer(this);
    connect(timerTemp, &QTimer::timeout, this, &panel::moverTemperatura);
    timerTemp->start(20);
}
void panel::moverTemperatura()
{
    if (tempDetenida) return;

    tempY += 1;

    // movimiento oscilante
    double base = 330;
    double amp = 80;
    double newY = base + amp * sin(tempY * 0.03);

    barraTemp->setPos(395, newY);
}
bool panel::tempCorrecta()
{
    QPointF posB = barraTemp->mapToScene(barraTemp->boundingRect().center());
    QPointF posZ = zonaVerde->mapToScene(zonaVerde->boundingRect().center());

    return (posB.y() > posZ.y() - 25 &&
            posB.y() < posZ.y() + 25);
}

