#ifndef COHETE_H
#define COHETE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>

class Cohete : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Cohete(const QPixmap pixmap, QObject *parent = nullptr);

    void iniciarOscilacion();
    void detenerOscilacion();
    void lanzarC();
    float posInicialX = 0;

    void setSceneNivel1Lanza(QGraphicsScene *scene);

    bool checkBounds(int newX, int newY);

    inline void setBanLeft() {banLeft = true;}
    inline void setBanRigth() {banRigth  = true;}
    inline void setBanUp() {banUp = true;}
    inline void setBanDowm() {banDown  = true;}

    inline void resetBanLeft() {banLeft = false;}
    inline void resetBanRigth() {banRigth  = false;}
    inline void resetBanUp() {banUp  = false;}
    inline void resetBanDowm() {banDown  = false;}


signals:

private slots:  //asociado a un timer
    void moverOscilacion();
    void moverLanzamiento();
    void borrarHumo();


    //mover cohete
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();




private:
    QPixmap pixmap;

    QTimer *oscTimer = nullptr;
    QTimer *launchTimer = nullptr;

    float angulo =90;
    float amp =20;
    float velo =0.1;

    QGraphicsPixmapItem *humo = nullptr;
    QGraphicsScene *sceneNivel1Lanza = nullptr;
    int humoTimer = 0;

    QTimer *timer;

    bool banLeft, banRigth, banUp, banDown;

    QRectF sceneBounds;
    int vel;
};

#endif // COHETE_H
