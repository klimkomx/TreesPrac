//
// Created by Dell G-3 on 16.10.2019.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void redrawByTrees(int);
    void insertInTree();
    void eraseFromTree();
    void sizeMore();
    void sizeLess();
//    void redraw();
};
#endif // MAINWINDOW_H
