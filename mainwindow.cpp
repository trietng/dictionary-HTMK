#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    program = nullptr;
    //ui->tabWidget->tabBar()->setStyle(new styleVerticalTabBar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setProgram(MainProgram* pointer) {
    program = pointer;
}

void MainWindow::on_inputSearch_returnPressed()
{
    if (!ui->inputSearch->text().isEmpty()) {
        ui->resultList->clear();
        ui->definitionBox->clear();
        auto input = ui->inputSearch->text().toStdString();
        if (ui->typeSearch->currentIndex() == 0) program->search_word(input);
        else program->search_definition(input);
        if (program->search_result.empty()) return;
        for (auto result : program->search_result) {
            QListWidgetItem* item = new QListWidgetItem;
            item->setText(QString::fromStdString(result->key));
            item->setData(Qt::UserRole, QString::fromStdString(result->value));
            ui->resultList->addItem(item);
        }
    }
}


void MainWindow::on_resultList_itemClicked(QListWidgetItem *item)
{
    int index = item->listWidget()->row(item);
    entry* clicked_entry = program->search_result[index];
    ui->definitionBox->setText(QString::fromStdString(
        "<h1>"+ clicked_entry->key + "</h1><p>" + clicked_entry->value + "</p>"
    ));
}


void MainWindow::on_buttonSearch_clicked()
{
    if (!ui->inputSearch->text().isEmpty()) {
        ui->resultList->clear();
        ui->definitionBox->clear();
        auto input = ui->inputSearch->text().toStdString();
        if (ui->typeSearch->currentIndex() == 0) program->search_word(input);
        else program->search_definition(input);
        if (program->search_result.empty()) return;
        for (auto result : program->search_result) {
            QListWidgetItem* item = new QListWidgetItem;
            item->setText(QString::fromStdString(result->key));
            item->setData(Qt::UserRole, QString::fromStdString(result->value));
            ui->resultList->addItem(item);
        }
    }
}
