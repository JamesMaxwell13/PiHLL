#include "box.h"
MyBox::MyBox(QString message) {
    setIcon(QMessageBox::Information);
    setText(message);
    setStyleSheet("QLabel { text-align: center; }");
    addButton(QMessageBox::Ok);
}