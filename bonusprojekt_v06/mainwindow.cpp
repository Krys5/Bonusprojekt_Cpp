#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    resize(320, 240);
    setWindowTitle("Startseite");

    QLabel* label = new QLabel("Was möchten Sie tun?", this);
    label->setGeometry(120, 20, 150, 30);

    QPushButton *button1 = new QPushButton("Neue Notiz erstellen", this);
    button1->setGeometry(120, 50, 150, 30);
    connect(button1, &QPushButton::clicked, this, &MainWindow::Button1Clicked);

    QPushButton* button2 = new QPushButton("Notiz öffnen", this);
    button2->setGeometry(120, 100, 150, 30);
    connect(button2, &QPushButton::clicked, this, &MainWindow::Button2Clicked);
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::Button1Clicked() {
    QWidget *neuesWidget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(neuesWidget);

    QLabel *label = new QLabel("Neue Notiz:", neuesWidget);
    layout->addWidget(label);

    QTextEdit *textEdit = new QTextEdit(neuesWidget);
    layout->addWidget(textEdit);

    QPushButton *saveButton = new QPushButton("Speichern", neuesWidget);
    layout->addWidget(saveButton);
    connect(saveButton, &QPushButton::clicked, [textEdit]() {
        try {
            QString fileName = QFileDialog::getSaveFileName(nullptr, "Datei speichern", "", "Text Dateien (*.txt);;Alle Dateien (*)");
            if (fileName.isEmpty()) {
                return;
            }

            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                throw std::runtime_error("Konnte die Datei nicht öffnen");
            }

            QTextStream out(&file);
            out << textEdit->toPlainText();
            file.close();
        } catch (const std::exception &e) {
            QMessageBox::warning(nullptr, "Fehler", e.what());
        }
    });

    neuesWidget->setLayout(layout);
    neuesWidget->show();
}



void MainWindow::Button2Clicked() {
    try {
        QString fileName = QFileDialog::getOpenFileName(this, "Datei öffnen", "", "Text Dateien (*.txt);;Alle Dateien (*)");
        if (fileName.isEmpty()) {
            return;
        }

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            throw std::runtime_error("Konnte die Datei nicht öffnen");
        }

        QTextStream in(&file);
        QString fileContent = in.readAll();
        file.close();

        QWidget *neuesWidget = new QWidget;
        QVBoxLayout *layout = new QVBoxLayout(neuesWidget);

        QLabel *label = new QLabel("Notizinhalt:", neuesWidget);
        layout->addWidget(label);

        QTextEdit *textEdit = new QTextEdit(neuesWidget);
        textEdit->setText(fileContent);
        layout->addWidget(textEdit);

        QPushButton *saveButton = new QPushButton("Speichern", neuesWidget);
        layout->addWidget(saveButton);
        connect(saveButton, &QPushButton::clicked, [textEdit]() {
            try {
                QString fileName = QFileDialog::getSaveFileName(nullptr, "Datei speichern", "", "Text Dateien (*.txt);;Alle Dateien (*)");
                if (fileName.isEmpty()) {
                    return;
                }

                QFile file(fileName);
                if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    throw std::runtime_error("Konnte die Datei nicht öffnen");
                }

                QTextStream out(&file);
                out << textEdit->toPlainText();
                file.close();
            } catch (const std::exception &e) {
                QMessageBox::warning(nullptr, "Fehler", e.what());
            }
        });

        neuesWidget->setLayout(layout);
        neuesWidget->show();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Fehler", e.what());
    }
}

