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


protected:
    void keyPressEvent(QKeyEvent *event) override;


public slots: //sii conectar timer
    void bgMove();

private:
    Ui::Widget *ui;
    QGraphicsScene *scene1, *sceneNivel1, *sceneInicio;
    QGraphicsPixmapItem *bgImage1, *bgImage2, *bgimageN1, *bgimageGas, *imgFallo, *imgGameOver, *imgAcierto;
    astronauta *astro;
    QGraphicsTextItem *texto;
    QMediaPlayer *intro1, *introfon, *introinicio, *SoniPanel;
    QTimer *bgTimer;
    QPushButton *btnStart, *btnNivel1, *btnGas, *btnOxig, *btnTemp, *btnSigte;
    QAudioOutput *audioPanel;
    panel *p= nullptr;


   detenerFlecha();
   zonacorrecta();

   int vidas = 3;
   void actualizarVidas();
   QGraphicsPixmapItem *vida1;
   QGraphicsPixmapItem *vida2;
   QGraphicsPixmapItem *vida3;
};
#endif // WIDGET_H
