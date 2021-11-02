#pragma once

#include <QMainWindow>
#include <qfiledialog.h>
#include <qtextstream.h>

#include <qpixmap.h>
#include <qimage.h>
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <qprogressbar.h>
#include <qrect.h>

#include <qtimer.h>
#include <qthread.h>
#include <qtestsupport_core.h>

#include "customview.h"
#include "manager.h"
#include "myrect.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TevianClient; }
QT_END_NAMESPACE

class TevianClient : public QMainWindow
{
    Q_OBJECT

public:
    TevianClient();
    ~TevianClient();

private slots:
    void on_actionOpen_triggered();
    void on_actionFaceReco_triggered();
    void on_actionNextFile_triggered();
    void on_actionPrevFile_triggered();
    void on_facesReceived(QVector<MyRect>);
    void on_updateImage();

signals:
    void signal_passFileName(QString);
    void signal_updateImage();

private:
    Ui::TevianClient *ui;
    QProgressBar* progressBar;
    QGraphicsScene* scene;
    QStringList openedFiles;
    size_t index_fileName = -1;
    QVector<QVector<MyRect>> facesOnFiles;
    QString fileName;
    Manager manager;

    bool rectShown = false;
};
