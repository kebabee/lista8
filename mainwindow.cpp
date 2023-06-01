#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->przycisk, SIGNAL(clicked()), this, SLOT(switchImg()));
    connect(ui->action_Koniec, SIGNAL(triggered()), this, SLOT(koniec_programu()) );
    ui->przycisk->setIcon(QIcon(":/img/media-playback-pause.png"));
    ui->action_Koniec->setIcon(QIcon(":/img/media-turn-off.png"));
    ui->action_O_programie->setIcon(QIcon(":/img/media-about.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::koniec_programu()
{
    QMessageBox msgBox(QMessageBox::Question, "Quit", "Are you sure you want to quit?", QMessageBox::Yes | QMessageBox::No);
    QIcon icon(":/img/media-question.png");
    QPixmap pix = icon.pixmap(QSize(64, 64));
    msgBox.setIconPixmap(pix);

    int result = msgBox.exec(); // .exec() przy wybraniu "Yes" zwraca int = 0x00004000,
    if (result == 0x00004000) {
        qApp->quit();
    }
}

void MainWindow::switchImg() {
    if (!isPaused) {
        ui->przycisk->setIcon(QIcon(":/img/media-playback-start.png"));
    } else {
        ui->przycisk->setIcon(QIcon(":/img/media-playback-pause.png"));
    }
    isPaused = !isPaused;
}

void MainWindow::on_action_O_programie_triggered()
{
    QMessageBox::aboutQt(this,"O wspaniałym programie");
}
