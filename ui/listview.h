#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QtGui>
#include <QtCore>
#include <QListview>

class MyListView : public QListView {
    Q_OBJECT

public:
    QFileSystemModel *filemodel;
    MyListView(QString path);

private:
    QString sPath;
};

#endif
