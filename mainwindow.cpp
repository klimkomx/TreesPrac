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
#include <QGraphicsTextItem>
#include <QBrush>
#include <QPen>

#include "AvlTree.h"
#include "RedBlackTree.h"
#include "SplayTree.cpp"

const int WIDTHCONST = 6, HEIGHTCONST = 40, DELTA = 15;

QLineEdit *insertEraseArea;
QPushButton * insert, * erase, *plusSize, *minusSize;
QGraphicsScene *pool;
QComboBox *chooseTree;
QGraphicsView * place;
const QBrush * brushr = new QBrush(Qt::GlobalColor::red),
*brushb = new QBrush(Qt::GlobalColor::black),
*brushw = new QBrush(Qt::GlobalColor::white);
const QColor* white = new QColor(Qt::GlobalColor::white);
const QPen * pen = new QPen();
namespace trees {
int displayed = 0;
RedBlackTree * RedBlack = new RedBlackTree();
AvlTree * AVL = new AvlTree();
splayTree * SP = new splayTree();
}
int getrasr(long long value) {
    int ans = 0;
    while (value != 0) {
        ans++;
        value /= 10ll;
    }
    return ans+1;
}

int reDrawRB(RedBlackTreeNode * root, int x = 0, int h = 0, bool isLeft = 0, int lele = 0) {
    if (root == trees::RedBlack -> nil)
        return -1;
    int xcord = x;
    int xcordf = xcord, xcords = xcord;
    int length = getrasr(root -> value);
    if (root -> left != trees::RedBlack -> nil) {
        xcords = xcord = reDrawRB(root -> left, xcord, h + 1, 1, length);
    }
    if (root -> color) {
        pool -> addRect(xcord, h*(HEIGHTCONST + DELTA), length *WIDTHCONST+DELTA, HEIGHTCONST, *pen, *brushr);
        QGraphicsTextItem* tItem = new QGraphicsTextItem(QString::number(root -> value));
        tItem -> setPos(xcord, h*(HEIGHTCONST+DELTA));
        if (root == trees::RedBlack -> root) {
            place -> centerOn(xcord, h*(HEIGHTCONST + DELTA));
        }
        pool -> addItem(tItem);
    } else {
        pool -> addRect(xcord, h*(HEIGHTCONST + DELTA), length *WIDTHCONST+DELTA,  HEIGHTCONST, *pen, *brushb);
        QGraphicsTextItem* tItem = new QGraphicsTextItem(QString::number(root -> value));
        tItem -> setDefaultTextColor(*white);
        tItem -> setPos(xcord, h*(HEIGHTCONST+DELTA));
        pool -> addItem(tItem);
    }
    if (root == trees::RedBlack -> root) {
        place -> centerOn(xcord, h*(HEIGHTCONST + DELTA));
    }
    xcord+=length*WIDTHCONST+2*DELTA;
    if (root -> right != trees::RedBlack -> nil) {
        xcord = reDrawRB(root -> right, xcord, h+1, 0, length);
    }
    if (root != trees::RedBlack -> root) {
        if (!isLeft)
            pool -> addLine(xcords, h*(HEIGHTCONST + DELTA), xcordf - DELTA, h*(HEIGHTCONST + DELTA) - DELTA);
        else
            pool -> addLine(xcords+length *WIDTHCONST+DELTA, h*(HEIGHTCONST + DELTA), xcord, h*(HEIGHTCONST + DELTA) - DELTA);
    }
    return xcord;
}
int reDrawAVL(AvlTreeNode* root, int x = 0, int h = 0, bool isLeft = 0, int lele = 0) {
    if (root == nullptr)
        return -1;
    int xcord = x;
    int xcordf = xcord, xcords = xcord;
    int length = getrasr(root -> value);
    if (root -> left != nullptr) {
        xcords = xcord = reDrawAVL(root -> left, xcord, h + 1, 1, length);
    }
    pool -> addRect(xcord, h*(HEIGHTCONST + DELTA), length *WIDTHCONST+DELTA,  HEIGHTCONST, *pen, *brushb);
    QGraphicsTextItem* tItem = new QGraphicsTextItem(QString::number(root -> value));
    tItem -> setDefaultTextColor(*white);
    tItem -> setPos(xcord, h*(HEIGHTCONST+DELTA));
    if (root == trees::AVL -> root) {
        place -> centerOn(xcord, h*(HEIGHTCONST + DELTA));
    }
    pool -> addItem(tItem);

    xcord+=length*WIDTHCONST+2*DELTA;
    if (root -> right != nullptr) {
        xcord = reDrawAVL(root -> right, xcord, h+1, 0, length);
    }
    if (root != trees::AVL -> root) {
        if (!isLeft)
            pool -> addLine(xcords, h*(HEIGHTCONST + DELTA), xcordf - DELTA, h*(HEIGHTCONST + DELTA) - DELTA);
        else
            pool -> addLine(xcords+length *WIDTHCONST+DELTA, h*(HEIGHTCONST + DELTA), xcord, h*(HEIGHTCONST + DELTA) - DELTA);
    }
    return xcord;
}
int reDrawSP(SplayTreeNode* root, int x = 0, int h = 0, bool isLeft = 0, int lele = 0) {
    if (root == nullptr)
        return -1;
    int xcord = x;
    int xcordf = xcord, xcords = xcord;
    int length = getrasr(root -> val);
    if (root -> l != nullptr) {
        xcords = xcord = reDrawSP(root -> l, xcord, h + 1, 1, length);
    }
    pool -> addRect(xcord, h*(HEIGHTCONST + DELTA), length *WIDTHCONST+DELTA,  HEIGHTCONST, *pen, *brushb);
    QGraphicsTextItem* tItem = new QGraphicsTextItem(QString::number(root -> val));
    tItem -> setDefaultTextColor(*white);
    tItem -> setPos(xcord, h*(HEIGHTCONST+DELTA));
    if (root == trees::SP -> root) {
        place -> centerOn(xcord, h*(HEIGHTCONST + DELTA));
    }
    pool -> addItem(tItem);

    xcord+=length*WIDTHCONST+2*DELTA;
    if (root -> r != nullptr) {
        xcord = reDrawSP(root -> r, xcord, h+1, 0, length);
    }
    if (root != trees::SP -> root) {
        if (!isLeft)
            pool -> addLine(xcords, h*(HEIGHTCONST + DELTA), xcordf - DELTA, h*(HEIGHTCONST + DELTA) - DELTA);
        else
            pool -> addLine(xcords+length *WIDTHCONST+DELTA, h*(HEIGHTCONST + DELTA), xcord, h*(HEIGHTCONST + DELTA) - DELTA);
    }
    return xcord;
}
void reDraw() {
    pool -> clear();
    if (trees::displayed == 0) {
        reDrawRB(trees::RedBlack -> root);
    } else if (trees::displayed == 1) {
        reDrawAVL(trees::AVL -> root);
    } else {
        reDrawSP(trees::SP -> root);
    }
    pool -> update();
    return;
}

void MainWindow::redrawByTrees(int num) {
    trees::displayed = num;
    reDraw();
}
void MainWindow::insertInTree() {
    int InsElem = insertEraseArea -> text().toInt();
    trees::AVL->insert(InsElem);
    trees::RedBlack->insert(InsElem);
    trees::SP -> insert(InsElem);
    insertEraseArea -> clear();
    reDraw();
}

void MainWindow::eraseFromTree() {
    int InsElem = insertEraseArea -> text().toInt();
    trees::AVL->erase(InsElem);
    trees::RedBlack->erase(InsElem);
    trees::SP -> erase(InsElem);
    insertEraseArea -> clear();
    reDraw();
}

void MainWindow::sizeMore() {
    place ->scale(1.25, 1.25);
}

void MainWindow::sizeLess() {
    place -> scale(0.8, 0.8);
}

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    this -> setCentralWidget(centralWidget);
//    this -> setStyleSheet("background-color : rgb(80, 80, 80);");

    insert = new QPushButton();
    insert -> setStyleSheet("QPushButton {background-color : rgb(64, 212, 51); font : 20px; color : beige; border-style : outset; min-height : 2em;}"
                               "QPushButton:hover{background-color : rgb(184, 247, 178); font : 20px; color : beige;}");
    insert -> setText(QString("Add value."));

    insertEraseArea = new QLineEdit();

    erase = new QPushButton();
    erase -> setStyleSheet("QPushButton {background-color : rgb(64, 212, 51); font : 20px; color : beige; border-style : outset; min-height : 2em;}"
                               "QPushButton:hover{background-color : rgb(184, 247, 178); font : 20px; color : beige;}");
    erase -> setText(QString("Erase value."));
    plusSize = new QPushButton();
    plusSize -> setStyleSheet("{font : 30px; color : beige; border-style : outset;}");
    plusSize -> setText(QString("+"));

    minusSize = new QPushButton();
    minusSize -> setStyleSheet("{font : 30px; color : beige; border-style : outset;}");
    minusSize -> setText(QString("-"));

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
    layout -> addWidget(plusSize, 3, 10);
    layout -> addWidget(minusSize, 3, 11);
    this -> centralWidget() -> setLayout(layout);
    QObject::connect(chooseTree, SIGNAL(currentIndexChanged(int)), this, SLOT(redrawByTrees(int)));
    QObject::connect(insert, SIGNAL(clicked()), this, SLOT(insertInTree()));
    QObject::connect(erase, SIGNAL(clicked()), this, SLOT(eraseFromTree()));
    QObject::connect(plusSize, SIGNAL(clicked()), this, SLOT(sizeMore()));
    QObject::connect(minusSize, SIGNAL(clicked()), this, SLOT(sizeLess()));
//    pool -> addRect(0, 0, 15, 20);
//    pool -> addText("k");
}

MainWindow::~MainWindow()
{

}
