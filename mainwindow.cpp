#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QCompleter>
#include <QDir>
#include <QFileInfo>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QStringListModel>
#include <QTableWidget>
#include <QVBoxLayout>
#include <qlineedit.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      currentPath(QDir::homePath()) {
  ui->setupUi(this);

  QWidget *centralWidget = new QWidget(this);
  QVBoxLayout *layout = new QVBoxLayout(centralWidget);

  QLabel *label =
      new QLabel("My File Manager | Current path: " + currentPath, this);
  layout->addWidget(label);

  QLineEdit *pathEdit = new QLineEdit(this);
  pathEdit->setPlaceholderText("Enter path ...");
  layout->addWidget(pathEdit);
  connect(pathEdit, &QLineEdit::returnPressed, this,
          &MainWindow::onPathEntered);
  completer = new QCompleter(this);
  completer->setCaseSensitivity(Qt::CaseInsensitive); // Игнорируем регистр
  completer->setCompletionMode(
      QCompleter::PopupCompletion); // Включаем выпадающее меню
  pathEdit->setCompleter(completer);

  updateCompleter();

  completer = new QCompleter(this);
  completer->setCaseSensitivity(Qt::CaseInsensitive); // Игнорируем регистр
  completer->setCompletionMode(
      QCompleter::PopupCompletion); // Включаем выпадающее меню
  pathEdit->setCompleter(completer);

  QPushButton *backButton = new QPushButton("Back", this);
  layout->addWidget(backButton);
  connect(backButton, &QPushButton::clicked, this, &MainWindow::onBackClicked);

  fileTable = new QTableWidget(this);
  fileTable->setColumnCount(3);
  fileTable->setHorizontalHeaderLabels({"name", "type", "size"});

  fileTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  layout->addWidget(fileTable);

  QPushButton *refreshButton = new QPushButton("Refresh", this);
  layout->addWidget(refreshButton);
  connect(refreshButton, &QPushButton::clicked, this,
          &MainWindow::updateFileList);

  QPushButton *createFileButton = new QPushButton("Create file", this);
  layout->addWidget(createFileButton);

  QPushButton *createFolderButton = new QPushButton("Create folder", this);
  layout->addWidget(createFolderButton);

  QPushButton *deleteFileButton = new QPushButton("Delete selected", this);
  layout->addWidget(deleteFileButton);

  setCentralWidget(centralWidget);
  updateFileList();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onBackClicked() {
  QDir dir(currentPath);
  if (dir.cdUp()) {
    currentPath = dir.absolutePath();
    updateFileList();
  }
}

void MainWindow::updateFileList() {
  QDir dir(currentPath); // Работаем с текущей директорией
  // Используем фильтр для отображения всех файлов и директорий
  QFileInfoList fileList =
      dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);

  fileTable->setRowCount(0); // Очищаем таблицу перед обновлением

  // Настройки ширины колонок
  fileTable->horizontalHeader()->setSectionResizeMode(
      0, QHeaderView::Stretch); // Имя файла
  fileTable->horizontalHeader()->setSectionResizeMode(
      1, QHeaderView::ResizeToContents); // Тип
  fileTable->horizontalHeader()->setSectionResizeMode(
      2, QHeaderView::ResizeToContents); // Размер

  fileTable->setColumnWidth(0, this->width() * 0.6); // 60% для имени
  fileTable->setColumnWidth(1, this->width() * 0.2); // 20% для типа
  fileTable->setColumnWidth(2, this->width() * 0.2); // 20% для размера

  foreach (QFileInfo fileInfo, fileList) {
    int row = fileTable->rowCount();
    fileTable->insertRow(row);

    // Используем иконки для файлов и папок
    QIcon icon = fileInfo.isDir() ? QIcon::fromTheme("folder")
                                  : QIcon::fromTheme("text-x-generic");

    // Столбец 1: Имя файла/папки
    QTableWidgetItem *nameItem =
        new QTableWidgetItem(icon, fileInfo.fileName());
    fileTable->setItem(row, 0, nameItem);

    // Столбец 2: Тип (файл или папка)
    QString type = fileInfo.isDir() ? "Directory" : "File";
    QTableWidgetItem *typeItem = new QTableWidgetItem(type);
    fileTable->setItem(row, 1, typeItem);

    // Столбец 3: Размер файла или количество элементов в папке
    QString sizeText;
    if (fileInfo.isDir()) {
      // Для папок отображаем количество элементов
      QDir subdir(fileInfo.absoluteFilePath());
      sizeText = QString::number(
                     subdir.entryList(QDir::AllEntries | QDir::NoDotAndDotDot)
                         .count()) +
                 " items";
    } else {
      // Для файлов отображаем размер
      sizeText = QString::number(fileInfo.size() / 1024.0, 'f', 2) + " KB";
    }
    QTableWidgetItem *sizeItem = new QTableWidgetItem(sizeText);
    fileTable->setItem(row, 2, sizeItem);
  }
}

void MainWindow::onPathEntered() {
  QLineEdit *pathEdit = qobject_cast<QLineEdit *>(sender());
  QString enteredPath = pathEdit->text();

  QDir dir(enteredPath);
  if (dir.exists()) {
    currentPath = enteredPath;
    updateFileList();
  } else {
    // Сообщение об ошибке, если путь не существует
    pathEdit->setText(currentPath);
  }
}

void MainWindow::updateCompleter() {
  // Получаем список всех файлов и папок в текущем каталоге
  QDir dir(currentPath);
  QStringList entries = dir.entryList(QDir::AllEntries | QDir::NoDotAndDotDot);

  // Обновляем модель для комплитера
  QStringListModel *model = new QStringListModel(entries, completer);
  completer->setModel(model);
}
