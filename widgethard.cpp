#include "widgethard.h"
#include "ui_widgethard.h"

widgethard::widgethard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widgethard)
{
    ui->setupUi(this);
}

widgethard::~widgethard()
{
    delete ui;
}
