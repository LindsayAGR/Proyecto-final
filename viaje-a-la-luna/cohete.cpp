#include "cohete.h"
#include <QtMath>
#include <QTimer>
#include "asteroide.h"

Cohete::Cohete(const QPixmap &pix, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), pixmap(pix)
{



    // Poner la imagen rotada
    QTransform t;
    t.rotate(90);
    QPixmap px = pix.transformed(t);
    setPixmap(px);
    setTransformOriginPoint(boundingRect().center());



    vel = 10;
    banLeft = banRigth = banUp = banDown = false;

    // Timers
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Cohete::actualizarMovimiento);
    timer->start(16);

    oscTimer = new QTimer(this);
    connect(oscTimer, &QTimer::timeout, this, &Cohete::moverOscilacion);

    launchTimer = new QTimer(this);
    connect(launchTimer, &QTimer::timeout, this, &Cohete::moverLanzamiento);

    collTimer = new QTimer(this);
    connect(collTimer, &QTimer::timeout, this, &Cohete::checkcoll);
    collTimer->start(50);


}

void Cohete::moveLeft()
{
    if(banLeft){
        int newX = x() - vel;
        if(checkBounds(newX, y()))
            setPos(newX, y());
    }
}

void Cohete::moveRight()
{
    if(banRigth){
        int newX = x() + vel;
        if(checkBounds(newX, y()))
            setPos(newX, y());
    }
}

void Cohete::moveUp()
{
    if(banUp){
        int newY = y() - vel;
        if(checkBounds(x(), newY))
            setPos(x(), newY);
    }
}

void Cohete::moveDown()
{
    if(banDown){
        int newY = y() + vel;
        if(checkBounds(x(), newY))
            setPos(x(), newY);
    }
}

void Cohete::moverOscilacion()
{
    angulo += velo;
    float dx = qSin(angulo) * amp;
    setX(posInicialX + dx);
}

void Cohete::lanzarC()
{
    detenerOscilacion();
    launchTimer->start(16);

    if (!sceneNivel1Lanza) return;

    // Crear humo (tu código)
    QPixmap px(":/imagenes/humoCohete.png");
    humo = new QGraphicsPixmapItem(px);
    humo->setScale(0.4);
    humo->setZValue(50);
    humo->setPos(500,500);
    sceneNivel1Lanza->addItem(humo);

    // dectar colisiones

    QList<QGraphicsItem*> colList = collidingItems();

    for (QGraphicsItem* item : colList) {
        if (typeid(*item) == typeid(Asteroide)) {

            detenerTodo();        // detiene fondo y cohete
            mostrarExplosion();   // aparece explosión
            emit coheteExplotado(); // avisa al widget
            return;
        }
    }
}

void Cohete::moverLanzamiento()
{
    setY(y() - 10);
}

void Cohete::setSceneNivel1Lanza(QGraphicsScene *scene)
{
    sceneNivel1Lanza = scene;
}

bool Cohete::checkBounds(int newX, int newY)
{
    return (newX >= sceneBounds.left()) &&
           (newX + boundingRect().width()*scale() <= sceneBounds.right()) &&
           (newY >= sceneBounds.top()) &&
           (newY + boundingRect().height()*scale() <= sceneBounds.bottom());
}

void Cohete::setSceneBounds(const QRectF &rect)
{
    sceneBounds = rect;
}

void Cohete::borrarHumo()
{
    if(!humo) return;
    if(sceneNivel1Lanza) sceneNivel1Lanza->removeItem(humo);
    delete humo;
    humo = nullptr;
}

void Cohete::actualizarMovimiento()
{

    qDebug() << "COHETE POS =" << x() << y();

    int dx = 0;
    int dy = 0;

    if (banLeft)  dx -= vel;
    if (banRigth) dx += vel;
    if (banUp)    dy -= vel;
    if (banDown)  dy += vel;

    int newX = x() + dx;
    int newY = y() + dy;

    // Evita que se salga de la pantalla
    if (checkBounds(newX, newY))
        setPos(newX, newY);
}

void Cohete::iniciarOscilacion() { oscTimer->start(16); }
void Cohete::detenerOscilacion() { oscTimer->stop(); }

void Cohete::checkcoll()
{
    if(!scene()) return;
    for(auto item : scene()->items())
    {
        Asteroide *as = dynamic_cast<Asteroide*>(item);
        if(as)

        {
            if(this->collidesWithItem(as))

            {

                detenerTodo();

                emit colisionCohete();

                //esconder cohete
                emit detenerTodoSignal();

                this->hide();

               //crear explosion
                QPixmap pxExplo(":/imagenes/explosion.png");
                explo = new QGraphicsPixmapItem(pxExplo);
                explo->setScale(0.5);
                explo->setZValue(200);     // para que quede encima
                //poss exacta

                QPointF centroCohete = this->mapToScene(this->boundingRect().center());
                QRectF brExplo = explo->boundingRect();

                explo->setPos(
                    centroCohete.x() - brExplo.width() * explo->scale() / 2,
                    centroCohete.y() - brExplo.height() * explo->scale() / 2
                    );

                scene()->addItem(explo);

                QTimer::singleShot(400, this, [this]() {
                    if (explo) {
                        scene()->removeItem(explo);
                        delete explo;
                        explo = nullptr;
                    }
                });

                return;
            }

        }
    }
}
void Cohete::detenerTodo()
{
    timer->stop();
    collTimer->stop();
    oscTimer->stop();
    launchTimer->stop();
}

void Cohete::mostrarExplosion()
{
    auto *boom = new QGraphicsPixmapItem(QPixmap(":/imagenes/explosion.png"));
    boom->setScale(0.5);
    boom->setZValue(200);
    boom->setPos(this->pos());
    scene()->addItem(boom);

    QTimer::singleShot(1000, [boom]() {
        delete boom;
    });
}

void Cohete::detenerAsteroides()
{
    emit detenerAsteroidesSignal();
}

void Cohete::reiniciarJuego()
{
    QTimer::singleShot(20000, [this]() {
        emit reiniciarSignal();
    });
}

