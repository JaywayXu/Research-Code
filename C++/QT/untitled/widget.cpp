#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *quit = new QPushButton("Quit", this);
    quit->setFont(QFont("Times", 18, QFont::Bold));

    connect(quit, &QPushButton::clicked, &QApplication::quit);
}

Widget::~Widget()
{

}
