#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPicture>
#include <QImage>

#include <QWidget>
#include <QPalette>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDropEvent>
#include <QScrollArea>
#include <QLabel>
#include <QListView>
#include <QGridLayout>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    QColor myPenColor = Qt::black;
    int myPenSize = 5;

    enum SHAPES {NOT_SELECTED, BRUSH, LINE, ROUND, SQUARE, TRIANGLE};
    SHAPES _choosenShape = NOT_SELECTED;
    bool _ShouldDraw = false;
    bool _HavingDroppedImg = false;

    bool _Pushed = false;
    QPoint _Start;
    QPoint _End;
    QLabel label;
    QPixmap pixmap;
    QPainter painter;
    QImage image;
    QPen pen;





private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();


    void on_actionSave_as_2_triggered();


    void on_actionClean_triggered();


protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    void resizeImage(QImage *image, const QSize &newSize);


private:
    QPainterPath _MainPath;

    Ui::MainWindow *ui;

public:
    virtual void dragEnterEvent(QDragEnterEvent* event) override;
    virtual void dropEvent(QDropEvent *event) override;

private slots:

    void on_spinBox_valueChanged(int arg1);

    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_MainWindow_iconSizeChanged(const QSize &iconSize);
};
#endif // MAINWINDOW_H
