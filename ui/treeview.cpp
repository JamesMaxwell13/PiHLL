#include "treeview.h"

MyTreeView::MyTreeView(QString path) {
    dirmodel = new QFileSystemModel(this);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirmodel->setRootPath(path);

    setModel(dirmodel);
    setColumnWidth(0, nameWidth);
}