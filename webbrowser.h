#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QWebEngineView>

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

signals:
  void downloadRequestedSignal(QWebEngineDownloadItem *softdownload);
  void dataChangedSignal(qint64, qint64);

 public slots:
  void downloadJumpSlot(QWebEngineDownloadItem *softdownload);

  void setCurrentProgressSlot(qint64 bytesreceived, qint64 bytestotal);
  void accessFinishedSlot();

 private:
  WebBrowser *pview = Q_NULLPTR;
};

#endif  // WEBBROWSER_H
