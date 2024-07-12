#include "startwindow.h"
#include "ui_startwindow.h"
#include "widget.h"

StartWindow::StartWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StartWindow)
{
    ui->setupUi(this);
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::on_pushButton_clicked()
{
    emit speedChanged(800);
    Widget *gameWidget = new Widget();
    connect(this, &StartWindow::speedChanged, gameWidget, &Widget::setSpeed);
    gameWidget->show();
    this->close();
}


void StartWindow::on_pushButton_2_clicked()
{
    emit speedChanged(400);
    Widget *gameWidget = new Widget();
    connect(this, &StartWindow::speedChanged, gameWidget, &Widget::setSpeed);
    gameWidget->show();
    this->close();
}

