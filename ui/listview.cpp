#include "listview.h"

MyListView::MyListView(QString path) {
    filemodel = new QFileSystemModel(this);
    filemodel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    filemodel->setRootPath(path);

    setModel(filemodel);
}