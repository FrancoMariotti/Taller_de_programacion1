#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QVBoxLayout>
#include <QWindow>

#include "iostream"

class Ovalo : public QWidget {
public:
    Ovalo();
    void paintEvent(QPaintEvent* event) override;
    ~Ovalo();
};

Ovalo::Ovalo() {
    //this->resize(alto, ancho);  
    //std::cout<< "Ancho:" << this->width();
}

void Ovalo::paintEvent(QPaintEvent *event)  {
    QRectF rectangle(0, 0,this->width(),this->height());
    QPainter painter(this);
    //Comentando esta linea se obtiene una elipse sin relleno
    QBrush my_brush(Qt::red, Qt::SolidPattern);
    painter.setBrush(my_brush);
    painter.drawEllipse(rectangle);
}

Ovalo::~Ovalo() {}



int main(int argc, char *argv[]) {
    QApplication app(argc,argv);
    // Creo un layout para que disponga a los widgets en forma vertical
    Ovalo ovalo;
    ovalo.show();

    return app.exec();
}
