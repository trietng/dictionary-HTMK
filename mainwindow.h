#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "mainprogram.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    MainProgram* program;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setProgram(MainProgram* pointer);

private slots:
    void on_inputSearch_returnPressed();

    void on_resultList_itemClicked(QListWidgetItem *item);

    void on_buttonSearch_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
