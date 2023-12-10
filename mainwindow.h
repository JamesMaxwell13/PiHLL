#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include "QMessageBox"
#include "QTreeView"
#include "QListview"
#include <QBoxLayout>
#include <QPushButton>
#include <QAbstractButton>
#include <QUrl>
#include <QDesktopServices>
#include <QTimer>
#include <QIcon>
#include "algorythm/huffman.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MyTreeView : public QTreeView {
    Q_OBJECT

public:
    QFileSystemModel *dirmodel;
    MyTreeView(QString path);

private:
    QString sPath;
    int nameWidth = 240;
};


class MyListView : public QListView {
    Q_OBJECT

public:
    QFileSystemModel *filemodel;
    MyListView(QString path);

private:
    QString sPath;
};

class MyBox : public QMessageBox {
    Q_OBJECT

public:
    MyBox(QString message);
};


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWidget *widget;
    QPushButton *compress;
    QPushButton *decompress;
    MyTreeView *treeview;
    MyListView *listview;
    QHBoxLayout *views;
    QHBoxLayout *buttons;
    QVBoxLayout *vlayout;
    QTimer *timer;
    void working_file(const QModelIndex &index);
    void on_treeView_clicked(const QModelIndex &index);
    void on_listView_clicked(const QModelIndex &index);
    void throw_message_box(QString message);
};

#endif // MAINWINDOW_H
