#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStandardPaths>
#include <QMainWindow>
#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QSpinBox>
#include <QThread>
#include <QFile>
#include <QDir>

#include "duplicatfinder.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    virtual void closeEvent(QCloseEvent *a_event);

signals:

    void startFind();

private slots:

    /**
     * @brief findDuplicates
     * @details Функция производит поиск дубликатов в выбраных папках
     */
    void findDuplicates();

    /**
     * @brief clearResult
     * @details Очистка результата поиска дубликатов
     */
    void clearResult();

private:
    Ui::MainWindow *ui;
    DuplicatFinder *m_df;
    QThread *m_workThread;
};
#endif // MAINWINDOW_H
