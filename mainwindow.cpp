#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{    
    ui->setupUi(this);

    connect(ui->editSearch, SIGNAL(textChanged(QString)), this, SLOT(changeHolderTextColor()));
    connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(removeTODO(QListWidgetItem*)));
    ui->editSearch->setStyleSheet("QLineEdit { color: gray; }");

    QJsonObject jObject;

    readJson("./config.json", jObject);

    qDebug() << jObject["title"].toString();

    this->setWindowTitle(jObject["title"].toString());
    updateOptions(jObject["style"].toString() + ".css");

    QPushButton* button1 = new QPushButton(this);
    button1->setGeometry(6, 6, 20, 20);
    button1->show();
    button1->setIcon(QIcon("./optionsIcon.png"));
    button1->setStyleSheet("background-color: rgba(0,0,0,0);");
    button1->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
    connect(button1, SIGNAL(clicked()), this, SLOT(openOptionForm()));

    readJson("./todos.json", jObject);
    for (auto iter : jObject["list"].toArray().toVariantList())
        ui->listWidget->addItem(iter.toString());
}

MainWindow::~MainWindow()
{
    QJsonObject todos;

    QJsonArray jArray;

    for (int i = 0; i < ui->listWidget->count(); i++)
        jArray.append(QJsonValue::fromVariant(ui->listWidget->item(i)->text()));

    qDebug() << jArray;

    todos["list"] = jArray;

    writeJson("./todos.json", todos);        // TODO

    delete ui;
}

void MainWindow::addItem()
{
    if (!ui->editAdd->text().isEmpty())
    {
        ui->listWidget->addItem(ui->editAdd->text());
        ui->editAdd->clear();
        ui->listWidget->item(ui->listWidget->count() - 1)->setIcon(QIcon("./iconGarbage.png"));
    }
}

void MainWindow::updateOptions(QString fileName)
{
    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly))
        this->setStyleSheet(file.readAll());
    file.close();
}

void MainWindow::readJson(QString fileName, QJsonObject& jObject)
{
    QFile json(fileName);

    if (json.open(QIODevice::ReadOnly))
    {
        QByteArray data = json.readAll();
        QJsonDocument doc(QJsonDocument::fromJson(data));
        jObject = doc.object();
    }
    else
    {
        qDebug() << "json file not found";
    }

    json.close();
}

void MainWindow::writeJson(QString fileName, QJsonObject &jObject)
{
    QFile json(fileName);
    json.open(QIODevice::WriteOnly);
    json.write(QJsonDocument(jObject).toJson());
    json.close();
}


void MainWindow::on_pushButton_clicked()
{
    updateOptions("./obsidian.css");

    /*QJsonObject jObject;
    jObject.insert("Title", QJsonValue::fromVariant("TODO List"));
    jObject.insert("style", QJsonValue::fromVariant("default"));

    writeJson("config.json", jObject);*/
}


void MainWindow::on_editAdd_returnPressed()
{
    addItem();
}

void MainWindow::openOptionForm()
{
    QMessageBox::information(this, "Information", "TODO...\t\t\t\t\t");
}

void MainWindow::changeHolderTextColor()
{
    if (ui->editSearch->text() == "")
        ui->editSearch->setStyleSheet("QLineEdit { color: gray; }");
    else
    {
        QFile file("./style.css");

        if (file.open(QIODevice::ReadOnly))
        {
            ui->editSearch->setStyleSheet(file.readAll());
            file.close();
        }
    }
}

void MainWindow::removeTODO(QListWidgetItem* item)
{
    qDebug() << "Removing " + item->text();

    qDeleteAll(ui->listWidget->selectedItems());
    ui->listWidget->clearSelection();
}

