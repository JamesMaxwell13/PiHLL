#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("D:/BSUIR/course work/3rd sem PiHLL/src/archiver/icons/icon.ico"));
    setWindowTitle("Huffman archiver");

    widget = new QWidget;
    setCentralWidget(widget);

    QString sPath = "";
    treeview = new MyTreeView(sPath);
    listview = new MyListView(sPath);

    compress = new QPushButton("Compress file", this);
    compress->setCheckable(true);
    decompress = new QPushButton("Decompress file", this);
    decompress->setCheckable(true);

    views = new QHBoxLayout;
    views->setSpacing(10);
    views->addWidget(treeview);
    views->addWidget(listview);

    buttons = new QHBoxLayout;
    buttons->setSpacing(10);
    buttons->addWidget(compress);
    buttons->addWidget(decompress);

    statusBar()->showMessage("© Created by Gorokh Andrew, FCSAN");

    vlayout = new QVBoxLayout;
    vlayout->setSpacing(10);
    vlayout->addLayout(buttons);
    vlayout->addLayout(views);
    widget->setLayout(vlayout);

    timer = new QTimer(this);

    connect(treeview, &QTreeView::clicked, this, &MainWindow::on_treeView_clicked);
    connect(listview, &QListView::doubleClicked, this, &MainWindow::on_listView_clicked);
    connect(listview, &QListView::clicked, this, &MainWindow::working_file);

    connect(compress, &QPushButton::clicked, this, [this] {
        compress->setChecked(true);
        connect(timer, QTimer::timeout, this,
                    [this] { compress->setChecked(false); timer->stop(); } );
                timer->start(3000); } );
    connect(decompress, &QPushButton::clicked, this, [this] {
        decompress->setChecked(true);
        connect(timer, QTimer::timeout, this,
                    [this] { decompress->setChecked(false); timer->stop(); });
                timer->start(3000); } );
}

MainWindow::~MainWindow()
{
    delete treeview;
    delete listview;
    delete compress;
    delete decompress;
    delete ui;
}

void MainWindow::working_file(const QModelIndex &index) {
    if(compress->isChecked() && decompress->isChecked()) {
        compress->setChecked(false);
        decompress->setChecked(false);
    }
    else {
        QString sPath = listview->filemodel->fileInfo(index).absoluteFilePath();
        std::string path = sPath.toStdString();
        if(compress->isChecked()) {
            Huffman_code file(path);
            QString res = QString::fromStdString(file.compress_file());
            compress->setChecked(false);
            MyBox *compressBox = new MyBox(res);
            compressBox->exec();
            delete compressBox;
        }
        if(decompress->isChecked()) {
            Huffman_code file(path);
            QString res = QString::fromStdString(file.decompress_file());
            decompress->setChecked(false);
            MyBox *decompressBox = new MyBox(res);;
            decompressBox->exec();
            delete decompressBox;
        }
    }
}

void MainWindow::on_treeView_clicked(const QModelIndex &index) {
    QString sPath = treeview->dirmodel->fileInfo(index).absoluteFilePath();
    listview->setRootIndex(listview->filemodel->setRootPath(sPath));
}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    QString sPath = listview->filemodel->fileInfo(index).absoluteFilePath();
    QDesktopServices::openUrl(QUrl::fromLocalFile(sPath));
}
