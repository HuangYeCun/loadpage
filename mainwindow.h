#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QWebEngineView;
class WebBrowser;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void appendSlot(qint64 bytesreceived, qint64 bytestotal);

 protected:
  //  void resizeEvent(QResizeEvent *);

 private:
  Ui::MainWindow *ui;

  QWebEngineView *pwebengine = Q_NULLPTR;
  //  QQuickWidget *pWidget;
  WebBrowser *pwebbrowser = Q_NULLPTR;
};
#endif  // MAINWINDOW_H
