#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

class MyWidget : public QWidget {
public:
    MyWidget(QWidget *parent = nullptr) : QWidget(parent) {
        resize(320, 240);
        setWindowTitle("Startseite");

        QLabel* label = new QLabel("Was möchten Sie tun?", this);
        label->setGeometry(120, 20, 150, 30);

        QPushButton *button1 = new QPushButton("Neue Notiz erstellen", this);
        button1->setGeometry(120, 50, 150, 30);
        connect(button1, &QPushButton::clicked, this, &MyWidget::knopf1Gedrueckt);

        QPushButton* button2 = new QPushButton("Notiz öffnen", this);
        button2->setGeometry(120, 100, 150, 30);
        connect(button2, &QPushButton::clicked, this, &MyWidget::knopf2Gedrueckt);

        QPushButton* button3 = new QPushButton("Notizen sortieren", this);
        button3->setGeometry(120, 150, 150, 30);
        connect(button3, &QPushButton::clicked, this, &MyWidget::knopf3Gedrueckt);
//Idee: später noch als Möglichkeit zu button 2 hinzufügen
        QPushButton* button4 = new QPushButton("Notiz bearbeiten", this);
        button4->setGeometry(120, 200, 150, 30);
        connect(button4, &QPushButton::clicked, this, &MyWidget::knopf4Gedrueckt);
    }

public slots:

    //NEW:Funktion zum Notiz erstellen und speichern
    void knopf1Gedrueckt() {
        QWidget *neuesWidget = new QWidget;
        QVBoxLayout *layout = new QVBoxLayout(neuesWidget);

        QLabel *label = new QLabel("Neue Notiz:", neuesWidget);
        layout->addWidget(label);
        //Textfeld
        QTextEdit *textEdit = new QTextEdit(neuesWidget);
        layout->addWidget(textEdit);

        QPushButton *saveButton = new QPushButton("Speichern", neuesWidget);
        layout->addWidget(saveButton);
        connect(saveButton, &QPushButton::clicked, [textEdit]() {
            QString fileName = QFileDialog::getSaveFileName(nullptr, "Datei speichern", "", "Text Dateien (*.txt);;Alle Dateien (*)");
            if (fileName.isEmpty()) {
                return;
            }
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QMessageBox::warning(nullptr, "Fehler", "Konnte die Datei nicht öffnen");
                return;
            }
            QTextStream out(&file);
            out << textEdit->toPlainText();
            file.close();
        });

        neuesWidget->setLayout(layout);
        neuesWidget->show();
    }

    void knopf2Gedrueckt() {
        //Idee: Zuerst Auswahl von Notizen treffen ("Welche Notiz wollen sie öffnen?")
        QWidget *neuesWidget = new QWidget;
        QLabel *label = new QLabel("Die Notiz wurde geöffnet", neuesWidget);
        QVBoxLayout *layout = new QVBoxLayout(neuesWidget);
        layout->addWidget(label);
        neuesWidget->show();
    }

    void knopf3Gedrueckt() {
        QWidget *neuesWidget = new QWidget;
        QLabel *label = new QLabel("Die Notizen können sortiert werden", neuesWidget);
        QVBoxLayout *layout = new QVBoxLayout(neuesWidget);
        layout->addWidget(label);
        neuesWidget->show();
    }

    void knopf4Gedrueckt() {
        QWidget *neuesWidget = new QWidget;
        QLabel *label = new QLabel("Die Notizen können bearbeitet werden", neuesWidget);
        QVBoxLayout *layout = new QVBoxLayout(neuesWidget);
        layout->addWidget(label);
        neuesWidget->show();
    }
};


int main(int argc, char* argv[]) {
    QApplication appl(argc, argv);
    MyWidget widget;
    widget.show();
    return appl.exec();
}
