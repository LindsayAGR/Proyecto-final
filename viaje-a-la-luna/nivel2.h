#ifndef NIVEL2_H
#define NIVEL2_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "cohete.h"
#include <QPushButton>
#include "asteroide.h"
#include <QGraphicsProxyWidget>
#include "nivel3.h"
#include <QTimer>

class Nivel2 : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Nivel2(QWidget *parent = nullptr);

    void mostrarSuperado();
    void  irASiguienteNivel();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    QGraphicsScene *sceneEsp;
    Cohete *cohete;
    QPushButton *btnN3;
    QGraphicsProxyWidget *btnProxy;

    void crearCohete();
    QGraphicsPixmapItem *imgSuperado;

    QTimer *timerSuperado;


    nivel3 *n3;
};

#endif//NIVEL2_H
