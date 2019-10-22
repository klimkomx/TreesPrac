//
// Created by Dell G-3 on 16.10.2019.
//
#include "mainwindow.h"

#include <stdio.h>
#include <vector>
#include <utility>
#include <QScrollArea>
#include <QGridLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QTableWidget>
#include <QPair>
#include <QWidget>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QStringList>
#include <QTableWidgetItem>
#include <QMap>
#include <QVector>
#include <QColor>
#include <QHeaderView>
#include <QDebug>
#include <QCoreApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QComboBox>
#include <QSpinBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QCheckBox>
#include <QPair>

#include "AvlTree.h"
#include "RedBlackTree.h"
//#include "SplayTree.h"

QSpinBox *insertEraseArea;
QPushButton * insert, * erase;
QGraphicsScene *pool;
QComboBox *chooseTree;
QGraphicsView * place;

namespace trees {
int displayed = 0;
RedBlackTree * RedBlack = new RedBlackTree();
AvlTree * AVL = new AvlTree();
}
int getrasr(long long value) {
    int ans = 0;
    long long ex = 1;
    while (value/ex != 0) {
        ans++;
    }
    return ans-1;
}

int reDrawRB(RedBlackTreeNode * root, int x = 0, int h = 0) {
    int xcord = 0;
    if (root -> left != nullptr) xcord = reDrawRB(root -> left, xcord, h + 1);

    if (root -> left != nullptr) xcord = reDrawRB(root -> left, xcord, h + 1);
    return xcord;
}
void reDrawAVL() {

}
void reDrawSP() {

}
void reDraw() {
    if (trees::displayed == 0) {

    } else if (trees::displayed == 1) {

    } else {

    }
}

void MainWindow::redrawByTrees(int num) {
    trees::displayed = num;
    reDraw();
}
void MainWindow::insertInTree() {

    trees::AVL->insert(1);
    trees::RedBlack->insert(1);
    reDraw();
}

void MainWindow::eraseFromTree() {

    reDraw();
}

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    this -> setCentralWidget(centralWidget);
//    this -> setStyleSheet("background-color : rgb(80, 80, 80);");

    insert = new QPushButton();
    insert -> setStyleSheet("QPushButton {background-color : rgb(64, 212, 51); font : 20px; color : beige; border-style : outset;}"
                               "QPushButton:hover{background-color : rgb(184, 247, 178); font : 20px; color : beige;}");
    insert -> setText(QString("Add value."));

    insertEraseArea = new QSpinBox();

    erase = new QPushButton();
    erase -> setStyleSheet("QPushButton {background-color : rgb(64, 212, 51); font : 20px; color : beige; border-style : outset;}"
                               "QPushButton:hover{background-color : rgb(184, 247, 178); font : 20px; color : beige;}");
    erase -> setText(QString("Erase value."));

    pool = new QGraphicsScene();
    chooseTree = new QComboBox();
    place = new QGraphicsView(pool);

    chooseTree ->addItem("Red-Black tree");
    chooseTree ->addItem("AVL tree");
    chooseTree ->addItem("Splay tree");
    QGridLayout *layout = new QGridLayout(this);
    layout -> addWidget(place, 0, 0, 5, 10);
    layout -> addWidget(chooseTree, 0, 10, 1, 2);
    layout -> addWidget(insertEraseArea, 1, 10, 1, 2);
    layout -> addWidget(insert, 2, 10);
    layout -> addWidget(erase, 2, 11);
    this -> centralWidget() -> setLayout(layout);
    QObject::connect(chooseTree, SIGNAL(currentIndexChanged(int)), this, SLOT(redrawByTrees(int)));
}

MainWindow::~MainWindow()
{

}
