#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>

class MyWidget : public QWidget {
public:
    MyWidget(QWidget *parent = nullptr) : QWidget(parent) {
        resize(320, 240);
        setWindowTitle("Startseite");


        QLabel* label = new QLabel("Was möchten Sie tun?", this);
        label->setGeometry(120, 20, 150, 30);

        QPushButton *button1 = new QPushButton("Notizen öffnen", this);
        button1->setGeometry(120, 50, 150, 30);
        connect(button1, &QPushButton::clicked, this, &MyWidget::knopf1Gedrueckt);

        QPushButton* button2 = new QPushButton("Notizen bearbeiten", this);
        button2->setGeometry(120, 100, 150, 30);
        connect(button2, &QPushButton::clicked, this, &MyWidget::knopf2Gedrueckt);

        QPushButton* button3 = new QPushButton("Notizen sortieren", this);
        button3->setGeometry(120, 150, 150, 30);
        connect(button3, &QPushButton::clicked, this, &MyWidget::knopf3Gedrueckt);
    }

public slots:
    void knopf1Gedrueckt() {
        QWidget *neuesWidget = new QWidget;
        QLabel *label = new QLabel("Die Notizen wurden geöffnet", neuesWidget);
        QVBoxLayout *layout = new QVBoxLayout(neuesWidget);
        layout->addWidget(label);
        neuesWidget->show();
    }

    void knopf2Gedrueckt() {
        QWidget *neuesWidget = new QWidget;
        QLabel *label = new QLabel("Die Notizen können bearbeitet werden", neuesWidget);
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
};



int main(int argc, char* argv[]) {
    QApplication appl(argc, argv);
    MyWidget widget;
    widget.show();
    return appl.exec();
}
