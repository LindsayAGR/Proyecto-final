#ifndef ASTEROIDE_H
#define ASTEROIDE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>

class Asteroide : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Asteroide(QObject *parent = nullptr);
    void detener();
    void reanudar();

public slots:
    void move();

signals:
    void removeList(Asteroide *as);


private:
    int velMove;
    QTimer *timer;


};

#endif // ASTEROIDE_H
