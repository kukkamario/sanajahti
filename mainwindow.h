#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "worddb.h"
#include "wordgrid.h"
#include "resolver.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void resolve();
    void currentRowChanged(int row);

private:
    void resolver(int x, int y);

    Ui::MainWindow *ui;
    WordDb db;
    WordGrid grid;
    std::vector<Resolution> resolutions;
};
#endif // MAINWINDOW_H
