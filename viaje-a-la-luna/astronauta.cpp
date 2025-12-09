#include "astronauta.h"

astronauta::astronauta(const QPixmap pixmapPlayer, QObject *parent)
    : QObject{parent},QGraphicsPixmapItem(), pixmapPlayer{pixmapPlayer}
{
    setPixmap(pixmapPlayer);
}
