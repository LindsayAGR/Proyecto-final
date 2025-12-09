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
    explicit panel(QGraphicsScene *sceneN1);

    void iniciarGasolina();
    void detenerFlecha();
    void reanudarFlecha();
    bool zonacorrecta();

    // Oxígeno
    void iniciarOxigeno();
    void presionarOxigeno();   // llama cuando presionas O (empieza a subir)
    void soltarOxigeno();      // llama cuando sueltas O (detiene y evalúa)
    bool evaluarOxigeno();     // comprueba si acertaste/fallaste
    void moverManecilla();
    void resetManecillaOxigeno();
    void iniciarTimerOxigeno();


    void setZManecilla(int z);
    void setZZona(int z);
    bool modoGasolina = false;
    bool modoOxigeno = false;

    // temperatura
    void iniciarTemperatura();
    void moverTemperatura();
    bool tempCorrecta();
    QGraphicsPixmapItem *termometro;
    QGraphicsRectItem *barraTemp;
    QGraphicsRectItem *zonaVerde;

    QTimer *timerTemp;
    bool tempDetenida = false;
    double tempY = 0;

signals:
    void acierto();
    void fallo();

private slots:
    void moverFlecha();


private:
    QGraphicsPixmapItem *flecha, *manecillaOxi, *zonaMedia;
    QGraphicsRectItem *zonaRoja;

    QTimer *TiempoMovimiento, *TiempoOxi;

    QGraphicsScene *sceneMa, *sceneO;



    double tiempo = 0;
    bool detenida = false;
    bool oxiPresion = false;

};

#endif // PANEL_H
