#ifndef PANEL_H
#define PANEL_H

#include<QGraphicsItem>
#include<QGraphicsPixmapItem>
#include<QTimer>
#include<QGraphicsItemGroup>
#include<QtMath>
#include<QObject>
#include<QGraphicsScene>
#include <QGraphicsRectItem>


class panel : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT

public:
    explicit panel(QGraphicsScene *sceneGaso);

    void iniciarGasolina();
    void detenerFlecha();
    void reanudarFlecha();
    bool zonacorrecta();

    // explicit panel(QGraphicsScene *sceneOxig);

    // void iniciarOxigeno();

    // explicit panel(QGraphicsScene *sceneTemp);
    // void iniciarTemperatura();
signals:
    void acierto();
    void fallo();

private slots:
    void moverFlecha();


private:
    QGraphicsPixmapItem *flecha;
    QGraphicsRectItem *zonaRoja;

    QTimer *TiempoMovimiento;

    double tiempo = 0;
    bool detenida = false;
};

#endif // PANEL_H
