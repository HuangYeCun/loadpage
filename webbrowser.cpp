#include "webbrowser.h"

#include <QMessageBox>
#include <QMainWindow>
#include <QWebEngineDownloadItem>
#include <QWebEngineProfile>
#include <QDir>

WebBrowser::WebBrowser(QWidget* parent) : QWebEngineView(parent) {
  connect(QWebEngineProfile::defaultProfile(),
          &QWebEngineProfile::downloadRequested, this,
          &WebBrowser::on_download_requested);
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

void WebBrowser::on_download_requested(QWebEngineDownloadItem* downloaditem) {
//  QString filename = QFileInfo(softdownload->downloadDirectory()).fileName();
    QString filename = QFileInfo(downloaditem->path()).fileName();
//  QString directory("/home/dong/Downloads/DownloadTest");
    QString directory("G:\\Download\\webengineview\\");
//  softdownload->setDownloadDirectory(QDir(directory).filePath(filename));
  downloaditem->setPath(QDir(directory).filePath(filename));

  downloaditem->accept();
  connect(downloaditem, &QWebEngineDownloadItem::downloadProgress, this,
          &WebBrowser::on_setcurrent_progress);
  connect(downloaditem, &QWebEngineDownloadItem::finished, [this,downloaditem]() {
      AccessFinished(downloaditem);
  });

}

void WebBrowser::on_setcurrent_progress(qint64 bytesreceived,
                                        qint64 bytestotal) {
  emit data_changed_signal(bytesreceived, bytestotal);
}

void WebBrowser::AccessFinished(QWebEngineDownloadItem* downloaditem) { qDebug() << "accessFinishedSlot ...."; }

void WebBrowser::on_status_changed(QWebEngineDownloadItem* downloaditem) {
        qDebug() << downloaditem->state();
        if (downloaditem->state() == QWebEngineDownloadItem::DownloadCompleted) {
            downloaditem->deleteLater();	//释放downloaditem，重要
            itemlist.removeOne(downloaditem);
        }
        if (downloaditem->state() == QWebEngineDownloadItem::DownloadRequested) {
        }
        if (downloaditem->state() == QWebEngineDownloadItem::DownloadInProgress) {
            qDebug() << "DownloadInProgress ....";
        }
        if (downloaditem->state() == QWebEngineDownloadItem::DownloadInterrupted) {
            //Download has been interrupted(by the server or because of lost connectivity)
            qDebug() << "DownloadInterrupted ....";
        }
        if (downloaditem->state() == QWebEngineDownloadItem::DownloadCancelled) {
            //qDebug() << downloaditem->state();
            downloaditem->deleteLater();	//释放downloaditem，重要

            qDebug() << "DownloadCancelled ....";
        }
    }
