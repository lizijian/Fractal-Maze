//    This file is part of Fractal Maze.
//
//    Foobar is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Fractal Maze is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
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
