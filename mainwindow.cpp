#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

#include "resolver.h"
#include <functional>
#include <future>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db.load("sanat.txt");

    connect(ui->resolvePushButton, &QPushButton::clicked, this, &MainWindow::resolve);
    connect(ui->foundListWidget, &QListWidget::currentRowChanged, this, &MainWindow::currentRowChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resolve()
{
    if (!grid.loadFromText(ui->textGridEdit->toPlainText())) {
        QMessageBox::critical(this, "Failed to parse grid", "Failed to parse grid");
        return;
    }

    ui->resolveViewWidget->setGrid(grid);

    ui->foundListWidget->clear();
    resolutions.clear();

    auto runResolver = [this](int x, int y) {
        Resolver r(db, grid);
        r.resolveFromCell(x, y);
        return r.getFoundWords();
    };


    QStringList foundWords;

    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            auto results = runResolver(x, y);

            resolutions.insert(resolutions.end(), results.begin(), results.end());
            for (auto& w : results) {
                foundWords.append(w.word);
            }
        }
    }
    foundWords.removeDuplicates();
    foundWords.sort();

    std::stable_sort(foundWords.begin(), foundWords.end(), [](const QString& a, const QString& b) {
        return a.size() > b.size();
    });

    /*std::vector<std::future<QStringList>> foundWordFutures;
    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            foundWordFutures.push_back(std::async(std::launch::async, [&runResolver, x, y]() {
                return runResolver(x, y);
            }));
        }
    }

    for (auto& f : foundWordFutures) {
        foundWords.append(f.get());
    }*/


    for (auto& word : foundWords) {
        QListWidgetItem* item = new QListWidgetItem(word);

        int index = 0;
        for (auto& r : resolutions) {
            if (r.word == word) {
                item->setData(Qt::UserRole, QVariant(index));
            }
            ++index;
        }
        ui->foundListWidget->addItem(item);
    }

    QScrollBar *vScrollBar = ui->foundListWidget->verticalScrollBar();
    vScrollBar->triggerAction(QScrollBar::SliderToMinimum);
}

void MainWindow::currentRowChanged(int row)
{
    if (row == -1) return;

    QListWidgetItem *item = ui->foundListWidget->item(row);
    if (item != nullptr) {
        int index = item->data(Qt::UserRole).toInt();
        ui->resolveViewWidget->setResolution(resolutions[index]);
        //qDebug() << "Selected row " << row << ", setting resolution index " << index;
    }
}

