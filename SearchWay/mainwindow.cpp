#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clickablerectitem.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(pressed()), this, SLOT(CreateGrid()));
    connect(ui->searhPath, &QPushButton::pressed, ui->graphicsView->GetScene(), &GridScene::SearchPath);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreateGrid()
{
    int Width = ui->spinBox->value();
    int Height = ui->spinBox_2->value();

    ui->graphicsView->GetScene()->createGrid(Width, Height);
}

