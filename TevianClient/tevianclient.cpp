#include "tevianclient.h"
#include "ui_tevianclient.h"

TevianClient::TevianClient() : ui(new Ui::TevianClient), manager(this)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    ui->statusBar->setContentsMargins(0, 2, 15, 2 );
    progressBar = new QProgressBar;
    progressBar->setValue(0);
    progressBar->setFixedSize(200, 20);
    progressBar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    progressBar->setTextVisible(false);
    ui->statusBar->addPermanentWidget(progressBar);

    connect(this, &TevianClient::signal_passFileName, &manager, &Manager::postImage);
    connect(&manager, &Manager::onReady, this, &TevianClient::on_facesReceived);
    connect(this, &TevianClient::signal_updateRect, this, &TevianClient::on_updateRect);
    connect(this, &TevianClient::signal_updateView, this, &TevianClient::on_updateView);
}

TevianClient::~TevianClient()
{
    delete ui;
    delete progressBar;
    delete scene;
}

void TevianClient::on_actionOpenFiles_triggered()
{
    openedFiles = QFileDialog::getOpenFileNames(this, "Open files", {}, "Images (*.jpeg *.jpg *.png);; All files (*.*)");
    emit signal_updateView();
}

void TevianClient::on_actionOpenDirectory_triggered()
{
    QString dirPath = QFileDialog::getExistingDirectory(this, "Open directory");
    if (dirPath.size())
    {
        QDir dir(dirPath);
        openedFiles = dir.entryList(QStringList() << "*.jpeg" << "*.jpg" << "*.png", QDir::Files);
        for (auto& image : openedFiles)
        {
            image.prepend(dirPath.toUtf8() + '/');
        }
        emit signal_updateView();
    }
}

void TevianClient::on_actionFaceReco_triggered()
{
    ui->actionFaceReco->setEnabled(false);
    for (const QString file : openedFiles)
    {
        QTest::qWait(2000);
        emit signal_passFileName(file);
    }
}


void TevianClient::on_facesReceived(QVector<MyRect> faces)
{
    progressBar->setValue(progressBar->value() + 1);
    facesOnFiles.push_back(faces);

    emit signal_updateRect();
}

void TevianClient::on_actionNextFile_triggered()
{
    if (index_fileName < openedFiles.size() - 1)
    {
        index_fileName++;
        scene->clear();
        ui->graphicsView->resetTransform();
        ui->graphicsView->scale(1, 1);

        fileName = openedFiles.at(index_fileName);

        ui->statusBar->showMessage(fileName);

        QImage image(fileName);
        QGraphicsItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));

        scene->addItem(item);

        if (index_fileName == openedFiles.size() - 1) 
        {
            ui->actionNextFile->setEnabled(false);
            ui->actionPrevFile->setEnabled(true);
        }
        else
        {
            ui->actionNextFile->setEnabled(true);
            ui->actionPrevFile->setEnabled(true);
        }

        rectShown = false;
        emit signal_updateRect();
    }
    
}

void TevianClient::on_actionPrevFile_triggered()
{
    if (index_fileName > 0)
    {
        scene->clear();
        ui->graphicsView->resetTransform();
        ui->graphicsView->scale(1, 1);

        index_fileName--;
        fileName = openedFiles.at(index_fileName);

        ui->statusBar->showMessage(fileName);

        QImage image(fileName);
        QGraphicsItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));

        scene->addItem(item);

        if (index_fileName == 0)
        {
            ui->actionPrevFile->setEnabled(false);
            ui->actionNextFile->setEnabled(true);
        }
        else
        {
            ui->actionPrevFile->setEnabled(true);
            ui->actionNextFile->setEnabled(true);
        }

        rectShown = false;
        emit signal_updateRect();
    }

}

void TevianClient::on_updateRect()
{  
    if (!rectShown && !facesOnFiles.empty() && index_fileName < facesOnFiles.size())
    {
        rectShown = true;
        for (auto rect : facesOnFiles.at(index_fileName))
        {
            scene->addRect(rect.x, rect.y, rect.width, rect.height, { Qt::green, 3 });
            auto text = scene->addText(rect.gender + ", " + QString::number(rect.age), { "Helvetica", 18 });
            text->setPos(rect.x + 5.0, rect.y);
            text->setDefaultTextColor(Qt::green);           
        }
    }
}

void TevianClient::on_updateView()
{
    if (openedFiles.size())
    {
        index_fileName = 0;
        rectShown = false;
        facesOnFiles.clear();
    
        ui->actionPrevFile->setEnabled(false);
        if (openedFiles.size() > 1) 
        {
            ui->actionNextFile->setEnabled(true);
        }
        ui->actionFaceReco->setEnabled(true);

        fileName = openedFiles.at(index_fileName);

        ui->statusBar->showMessage(fileName);

        scene->clear();
    
        QImage image(fileName);
        QGraphicsItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));

        progressBar->setValue(0);
        progressBar->setMaximum(openedFiles.size());
        scene->addItem(item);
    }
}