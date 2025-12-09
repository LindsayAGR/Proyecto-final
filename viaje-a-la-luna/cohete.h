#ifndef COHETE_H
#define COHETE_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>

class Cohete : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Cohete(const QPixmap &pix, QGraphicsItem *parent = nullptr);

    void setBanLeft(bool b) { banLeft = b; }
    void setBanRigth(bool b) { banRigth = b; }
    void setBanUp(bool b) { banUp = b; }
    void setBanDown(bool b) { banDown = b; }

    void lanzarC();
    void setSceneBounds(const QRectF &rect);
    float posInicialX = 300;

    void setSceneNivel1Lanza(QGraphicsScene *scene);
    void iniciarOscilacion();
    void detenerOscilacion();
    bool checkBounds(int newX, int newY);
    void detenerTodo();
    void detenerMovimiento() ;
    void mostrarExplosion();
    void detenerAsteroides();
    void reiniciarJuego();

    QTimer *collTimer;
    QTimer *timer;

private slots:
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void moverOscilacion();
    void moverLanzamiento();
    void checkcoll();
    void borrarHumo();

signals:
    void detenerTodoSignal();

    void colisionCohete();   // avisa al widget

    void coheteExplotado();
    void detenerAsteroidesSignal();
    void reiniciarSignal();

protected:


private:
    QPixmap pixmap;
    int vel;
    bool banLeft, banRigth, banUp, banDown;


    QTimer *oscTimer;
    QTimer *launchTimer;

    QRectF sceneBounds;

    // Oscilacion
    float angulo = 0;
    float velo = 0.05;
    float amp = 10;


    // Lanzamiento
    QGraphicsPixmapItem *humo = nullptr, *explo;
    QGraphicsScene *sceneNivel1Lanza = nullptr;
    void actualizarMovimiento();




};

#endif // COHETE_H
