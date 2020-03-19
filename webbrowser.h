#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QWebEngineView>

class QWebEngineDownloadItem;

class WebBrowser : public QWebEngineView {
  Q_OBJECT
 public:
  WebBrowser(QWidget *parent);
  ~WebBrowser();

 protected:
  /**
  * @brief createWindow 重载
  * @param type
  * @return
  */
  QWebEngineView *createWindow(QWebEnginePage::WebWindowType type);
  void AccessFinished(QWebEngineDownloadItem* downloaditem);

signals:
  void status_changed_signal();
  void data_changed_signal(qint64, qint64);

 public slots:
  void on_download_requested(QWebEngineDownloadItem *softdownload);
  void on_setcurrent_progress(qint64 bytesreceived, qint64 bytestotal);
  void on_status_changed(QWebEngineDownloadItem* downloaditem);

 private:
  WebBrowser *pview = Q_NULLPTR;
};

#endif  // WEBBROWSER_H
