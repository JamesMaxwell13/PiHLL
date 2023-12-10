#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QtGui>
#include <QtCore>
#include <QTreeView>

class MyTreeView : public QTreeView {
    Q_OBJECT

public:
    QFileSystemModel *dirmodel;
    MyTreeView(QString path);

private:
    QString sPath;
    int nameWidth = 240;
};

#endif

