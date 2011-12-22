#ifndef DISPLAYAREA_H
#define DISPLAYAREA_H

#include <QLabel>
#include <QMouseEvent>

class DisplayArea : public QLabel
{
    Q_OBJECT
public:
    explicit DisplayArea(QWidget *parent = 0);

signals:
    void leftClickImage(int x, int y);
    void mouseMove(int x, int y);

public slots:

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // DISPLAYAREA_H
