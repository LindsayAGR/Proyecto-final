#ifndef ASTRONAUTA_H
#define ASTRONAUTA_H

#include <QObject>
#include <QGraphicsPixmapItem>

class astronauta : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit astronauta(const QPixmap pixmapPlayer, QObject *parent = nullptr);

//signals:

private:
    QPixmap pixmapPlayer;
};

#endif // ASTRONAUTA_H
