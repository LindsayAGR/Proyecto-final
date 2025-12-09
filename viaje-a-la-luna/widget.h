#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include "astronauta.h"
#include <QTextBrowser>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>
#include <QPushButton>
#include "panel.h"
#include<QKeyEvent>
#include"cohete.h"
#include <QList>
#include "asteroide.h"
#include "nivel2.h"



QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:    //funciones
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void mostrarInicio();
    void iniciarIntroduccion();
    void iniciarNivel1();
    void iniciarGasolina();
    void iniciarOxigeno();
    void iniciarTemperatura();
    void iniciarLanzamiento();
    void iniciarOscilacion();
    void iniciarNivel2();


protected://hay una
    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event1) override;

    void setBgVel(int v) {bgvel = v;}


public slots: //sii conectar timer
    void bgMoveN1();
    void bgMoveN2();
    void spawnAsteroids();
    void removeAst(Asteroide *as);
    void detenerEspacio();
    void detenerAsteroides();
    void reiniciarTodo();


private:
    Ui::Widget *ui;
    QGraphicsScene *scene1, *sceneNivel1, *sceneInicio, *sceneNivel1Lanza, *sceneEsp;
    QGraphicsPixmapItem *bgImage1, *bgImage2, *bgimageN1, *bgimageGas, *imgFallo, *imgGameOver, *imgAcierto,*bgimageOx, *bgimagetemp,*bgImage3,*bgImage4, *humo,
        *imageEsp1, *imageEsp2;
    astronauta *astro;
    QGraphicsTextItem *texto;
    QMediaPlayer *intro1, *introfon, *introinicio, *SoniPanel;
    QTimer *bgTimer,*EspTimer;
    QPushButton *btnStart, *btnNivel1, *btnGas, *btnOxig, *btnTemp, *btnSigte,*btnlanza, *btnNivel2;
    QAudioOutput *audioPanel;
    panel *p= nullptr;
    Cohete *cohete;


    bool procesandoResultado = false;
    bool gameOver = false;


   int vidas = 3;
   void actualizarVidas();
   QGraphicsPixmapItem *vida1;
   QGraphicsPixmapItem *vida2;
   QGraphicsPixmapItem *vida3;

   panel *mipanel;


   int humoTimer = 0;


   //nivel2
   QTimer *asTimer;
   QList<Asteroide *> Asteroides;
   int bgVelmove = numAst;
   int bgvel, numAst;
   Nivel2 *nivel2;

};
#endif // WIDGET_H
