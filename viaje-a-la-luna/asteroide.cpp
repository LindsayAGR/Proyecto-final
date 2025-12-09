#include "asteroide.h"

Asteroide::Asteroide(QObject *parent)
    : QObject{parent}
{
    srand(time(NULL));
    int randAsteroide = rand()% 6+1;
    int x = 750;
    int randy;

    switch (randAsteroide)
    {
    case 1:
        setPixmap(QPixmap(":/imagenes/Asteroide1.png"));
        randy = rand() % 300 +50;
        break;
    case 2:
        setPixmap(QPixmap(":/imagenes/Asteroide2.png"));
        randy = rand() % 300 +50;
        break;
    case 3:
        setPixmap(QPixmap(":/imagenes/Asteroide3.png"));
        randy = rand() % 300 +50;
        break;
    case 4:
        setPixmap(QPixmap(":/imagenes/Asteroide4.png"));
        randy = rand() % 300 +50;
        break;
    case 5:
        setPixmap(QPixmap(":/imagenes/Asteroide5.png"));
        randy = rand() % 300 +50;
        break;
    case 6:
        setPixmap(QPixmap(":/imagenes/Asteroide3.png"));
        randy = rand() % 300 +50;
        break;
    default:
        setPixmap(QPixmap(":/imagenes/Asteroide1.png"));
        randy = rand() % 300 +50;
        break;
        break;
    }

    setPos(x , randy);

    velMove = 5;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Asteroide::move);
    timer->start(20);


}

void Asteroide::move()
{
    int newX = x() - velMove;
    setPos(newX, y());

    if (newX + pixmap().width()<= 0)
    {
        emit removeList(this);                   //1. eliminar de las listas
        if (scene()) scene()->removeItem(this);  //2. eliminaar dela esena
        deleteLater();                           //3. eliminar de la memoria
        return;
    }
}

void Asteroide::detener()
{
    timer->stop();
}

void Asteroide::reanudar()
{
    timer->start(20);
}

