#ifndef BOX_H
#define BOX_H

#include <QtGui>
#include <QtCore>
#include "QMessageBox"

class MyBox : public QMessageBox {
    Q_OBJECT

public:
    MyBox(QString message);
};

#endif //BOX_H
