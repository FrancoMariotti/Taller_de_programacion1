#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QVBoxLayout>
#include <QWindow>


class Ovalo : public QWidget
{
    int ancho;
    int alto;
public:
    Ovalo(int ancho,int alto);
    void paintEvent(QPaintEvent* event) override;
    ~Ovalo();
};

Ovalo::Ovalo(int alto,int ancho): alto(alto),ancho(ancho) {
    this->resize(alto, ancho);  
}

void Ovalo::paintEvent(QPaintEvent *event)  {
    QRectF rectangle(0, 0, alto,ancho);
    QPainter painter(this);
    QBrush my_brush(Qt::red, Qt::SolidPattern);
    painter.setBrush(my_brush);
    painter.drawEllipse(rectangle);
}

Ovalo::~Ovalo() {}



int main(int argc, char *argv[]) {
    QApplication app(argc,argv);
    // Creo un layout para que disponga a los widgets en forma vertical
    Ovalo ovalo(200,300);
    ovalo.show();

    return app.exec();
}
