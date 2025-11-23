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

public slots: //sii conectar timer
    void bgMove();

private:
    Ui::Widget *ui;
    QGraphicsScene *scene1;
    QGraphicsPixmapItem *bgImage1, *bgImage2;
    astronauta *astro;
    QGraphicsTextItem *texto;
    QMediaPlayer *intro1, *introfon, *introinicio, *sonclick;
    QTimer *bgTimer;

    QGraphicsScene *sceneInicio;
    QPushButton *btnStart;



};
#endif // WIDGET_H
