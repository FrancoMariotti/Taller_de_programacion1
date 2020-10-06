#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QVBoxLayout>
#include <QWindow>

#include "iostream"

class Circulo : public QWidget {
public:
    Circulo();
    void paintEvent(QPaintEvent* event) override;
    ~Circulo();
};

Circulo::Circulo() {
    this->resize(this->height(),this->height());
}

void Circulo::paintEvent(QPaintEvent *event)  {
    QRectF rectangle(0, 0,this->width(),this->width());
    QPainter painter(this);
    //Comentando esta linea se obtiene una elipse sin relleno
    QBrush my_brush(Qt::green, Qt::SolidPattern);
    painter.setBrush(my_brush);
    painter.drawEllipse(rectangle);
}

Circulo::~Circulo() {}



int main(int argc, char *argv[]) {
    QApplication app(argc,argv);
    // Creo un layout para que disponga a los widgets en forma vertical
    Circulo circ;
    circ.show();

    return app.exec();
}
