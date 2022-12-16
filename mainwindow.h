#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QLabel>
#include <QFile>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addItem();

    void updateOptions(QString fileName);

    void readJson(QString fileName, QJsonObject& jObject);

    void writeJson(QString fileName, QJsonObject& jObject);

private slots:
    void on_pushButton_clicked();

    void on_editAdd_returnPressed();

    void openOptionForm();

    void changeHolderTextColor();

    void removeTODO(QListWidgetItem* item);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
