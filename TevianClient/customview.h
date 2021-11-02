#pragma once

#include <qwidget.h>
#include <qgraphicsview.h>
#include <qevent.h>

class CustomView : public QGraphicsView
{
public:
	CustomView(QWidget* parent = nullptr);
protected:
	virtual void wheelEvent(QWheelEvent* event);
};