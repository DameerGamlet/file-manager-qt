#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QMainWindow>
#include <QTableWidget>
#include <qlineedit.h>

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

private:
  Ui::MainWindow *ui;

  QString currentPath;
  QTableWidget *fileTable;
  QLineEdit *pathEdit;
  QCompleter *completer;

  void updateFileList();
  void onBackClicked();
  void onPathEntered();
  void updateCompleter();
};
#endif // MAINWINDOW_H
