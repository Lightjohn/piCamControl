#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QList>
#include <QComboBox>
#include <QGridLayout>
#include <QDebug>
#include <network.h>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();

private:
    QLabel *img;
    QPushButton *upb;
    QPushButton *downb;
    QPushButton *rightb;
    QPushButton *leftb;
    QComboBox *qualityb;

    QPushButton *refreshb;

    network *net;
    int limit_x_left;
    int limit_x_right;
    int limit_y_bottom;
    int limit_y_top;
    int x;
    int y;
    int inc;


public slots:
    void up();
    void down();
    void right();
    void left();
    void refresh();
    void quality(QString text);
};

#endif // MAINWINDOW_H
