#include "webbrowser.h"

#include <QMessageBox>
#include <QMainWindow>
#include <QWebEngineDownloadItem>
#include <QWebEngineProfile>
#include <QDir>

WebBrowser::WebBrowser(QWidget* parent) : QWebEngineView(parent) {
  connect(QWebEngineProfile::defaultProfile(),
          &QWebEngineProfile::downloadRequested, this,
          &WebBrowser::downloadJumpSlot);
}

WebBrowser::~WebBrowser() {}

QWebEngineView* WebBrowser::createWindow(
    QWebEnginePage::WebWindowType type =
        QWebEnginePage::WebWindowType::WebBrowserTab) {
  Q_UNUSED(type);
  WebBrowser* pview = new WebBrowser(this);

  pview->setAttribute(Qt::WA_DeleteOnClose);
  pview->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

  //  QMainWindow* dialog = new QMainWindow();
  //  dialog->setCentralWidget(pview);
  //  dialog->show();

  return pview;
}

void WebBrowser::downloadJumpSlot(QWebEngineDownloadItem* softdownload) {
  QString filename = QFileInfo(softdownload->downloadDirectory()).fileName();
  QString directory("/home/dong/Downloads/DownloadTest");
  softdownload->setDownloadDirectory(QDir(directory).filePath(filename));

  softdownload->accept();
  connect(softdownload, &QWebEngineDownloadItem::downloadProgress, this,
          &WebBrowser::setCurrentProgressSlot);
  connect(softdownload, &QWebEngineDownloadItem::finished, this,
          &WebBrowser::accessFinishedSlot);
}

void WebBrowser::setCurrentProgressSlot(qint64 bytesreceived,
                                        qint64 bytestotal) {
  emit dataChangedSignal(bytesreceived, bytestotal);
}

void WebBrowser::accessFinishedSlot() { qDebug() << "accessFinishedSlot ...."; }
