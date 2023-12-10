#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QTreeView>
#include <QBoxLayout>
#include <QPushButton>
#include <QAbstractButton>
#include <QUrl>
#include <QDesktopServices>
#include <QTimer>
#include <QIcon>
#include "box.h"
#include "listview.h"
#include "treeview.h"
#include "../algorythm/huffman.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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
