#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QPicture>
#include <QImage>
#include <QLabel>
#include <QStandardItem>

using namespace std;




MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    pen.setColor(myPenColor);
    pen.setWidth(myPenSize);

    //QSize mySize(1920, 1080);
    //image = QImage(mySize, QImage::Format_ARGB32_Premultiplied);
    ui->setupUi(this);

    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QString filePath = event->mimeData()->urls()[0].toLocalFile();
    pixmap = QPixmap(filePath);

    _HavingDroppedImg = true;

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    if (_HavingDroppedImg)
    {
        painter.begin(&image);
        painter.drawPixmap(0, 0, pixmap.size().width(), pixmap.size().height(), pixmap);
        painter.end();
        _HavingDroppedImg = false;
    }


    if (_ShouldDraw)
    {
        painter.begin(this);
        painter.setPen(pen);

        _MainPath.moveTo(_Start);
        if(_choosenShape == SQUARE)
        {
            painter.drawRect(QRect (_Start, _End));

            if (!_Pushed)
            {
                painter.end();
                painter.begin(&image);
                painter.setPen(pen);
                painter.drawRect(QRect (_Start, _End));
            }

        } else if (_choosenShape == ROUND)
        {
            painter.drawEllipse(QRect (_Start, _End));
            if (!_Pushed)
            {
                painter.end();
                painter.begin(&image);
                painter.setPen(pen);
                painter.drawEllipse(QRect (_Start, _End));
            }

        } else if (_choosenShape == TRIANGLE)
        {
            painter.drawLine(_Start.x(),_End.y(),  (_Start.x()+_End.x())/2, _Start.y());
            painter.drawLine((_Start.x()+_End.x())/2, _Start.y(), _End.x(), _End.y());
            painter.drawLine(_End.x(), _End.y(), _Start.x(),_End.y());
            if (!_Pushed)
            {
                painter.end();
                painter.begin(&image);
                painter.setPen(pen);

                painter.drawLine(_Start.x(),_End.y(),  (_Start.x()+_End.x())/2, _Start.y());
                painter.drawLine((_Start.x()+_End.x())/2, _Start.y(), _End.x(), _End.y());
                painter.drawLine(_End.x(), _End.y(), _Start.x(),_End.y());
            }

        }else if (_choosenShape == LINE) {
            painter.drawLine(_Start, _End);
            if (!_Pushed)
            {
                painter.end();
                painter.begin(&image);
                painter.setPen(pen);
                painter.drawLine(_Start, _End);
            }

        } else if (_choosenShape == BRUSH) {
            painter.end();
            painter.begin(&image);
            painter.setPen(pen);
            painter.drawLine(_Start, _End);
            _Start = _End;
        }

        painter.end();


        _ShouldDraw = false;


        painter.begin(this);
        QRect dirtyRect = event->rect();
        painter.drawImage(dirtyRect, image, dirtyRect);
        painter.end();

    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void MainWindow::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    _Start = event->pos();

    _Pushed = true;

    painter.setRenderHint(QPainter::Antialiasing, true);

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (_Pushed)
    {
        _End = event->pos();
        _ShouldDraw = true;
    }
    this->update();

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    _End = event->pos();

    _ShouldDraw = true;
    _Pushed = false;
    this->update();
}


void MainWindow::on_pushButton_3_clicked()
{
    _choosenShape = LINE;
}

void MainWindow::on_pushButton_clicked()
{
    _choosenShape = SQUARE;
}


void MainWindow::on_pushButton_2_clicked()
{
    _choosenShape = ROUND;
}


void MainWindow::on_pushButton_4_clicked()
{
    _choosenShape = BRUSH;
}


void MainWindow::on_pushButton_6_clicked()
{
    _choosenShape = TRIANGLE;
}

void MainWindow::on_pushButton_5_clicked()
{
    _choosenShape = NOT_SELECTED;
}

void MainWindow::on_actionSave_as_2_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
           tr("Save drawing"), "",
           tr("photo (*.png);;All Files (*)")
                                                    );

    if (fileName.isEmpty())
    {
        return;
    } else
    {
        image.save(fileName);
    }

}


void MainWindow::on_actionClean_triggered()
{
    setUpdatesEnabled(false);
    painter.end();
    image.fill(qRgb(255, 255, 255));
    setUpdatesEnabled(true);
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    pen.setWidth(arg1);
}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Black"){
        pen.setColor(Qt::black);

    } else if (arg1 == "Red"){
        pen.setColor(Qt::red);

    } else if (arg1 == "Blue"){
        pen.setColor(Qt::blue);

    } else if (arg1 == "Green"){
        pen.setColor(Qt::green);

    } else if (arg1 == "Yellow"){
        pen.setColor(Qt::yellow);
    }
    update();
}



void MainWindow::on_MainWindow_iconSizeChanged(const QSize &iconSize)
{
    update();
}

