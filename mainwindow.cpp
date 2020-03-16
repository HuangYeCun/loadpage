#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWebEngineWidgets>
#include <QVBoxLayout>

#include "webbrowser.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  //  pwebengine = new QWebEngineView(this);
  //  pwebengine->load(QUrl("http://www.bing.com"));
  //  pwebengine->show();

  pwebbrowser = new WebBrowser(this);
  // pwebbrowser->load(QUrl("http://localhost:8080/VideoMeetingManage/main/index"));
  pwebbrowser->load(QUrl("https://wenku.baidu.com/apps?fr=1011"));
  setCentralWidget(pwebbrowser);

  connect(pwebbrowser, &WebBrowser::dataChangedSignal, this,
          &MainWindow::appendSlot);
}

MainWindow::~MainWindow() { delete ui; }

// void MainWindow::resizeEvent(QResizeEvent *) {
//  //  pwebengine->resize(this->size());
//}

void MainWindow::appendSlot(qint64 bytesreceived, qint64 bytestotal) {
  // progressBar->setValue(bytesreceived);
  // progressBar->setMaximum(bytestotal);
  // if (bytesreceived == bytestotal){
  //	progressBar->hide();
  //	qDebug() << QString("ÏÂÔØÍê³É");
  //}

  // if (bytesreceived != bytestotal){
  //	progressBar->show();
  //	qDebug() << QString("ÕýÔÚÏÂÔØ");
  //}
}
