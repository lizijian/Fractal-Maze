#include "displayarea.h"

DisplayArea::DisplayArea(QWidget *parent) :
    QLabel(parent)
{
    setMouseTracking(true);
}

void DisplayArea::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    emit leftClickImage(pos.x(), pos.y());
}

void DisplayArea::mouseMoveEvent(QMouseEvent *event){
    QPoint pos = event->pos();
    emit mouseMove(pos.x(), pos.y());
}
