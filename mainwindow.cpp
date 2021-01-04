#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    qDebug() << " [M] MainWindow::MainWindow";

    m_df = new DuplicatFinder(nullptr);
    m_workThread = new QThread(this);
    m_df->moveToThread(m_workThread);
    m_workThread->start();

    auto connectButtonWithLine = [](QPushButton *a_btn, QLineEdit *a_line) {
        connect(a_btn, &QPushButton::pressed, [a_line](){
            QString tempPath = QFileDialog::getExistingDirectory(nullptr, tr("Open directory"), QDir::homePath()
                                                                 , QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
            a_line->setText(tempPath);
        });
    };

    connectButtonWithLine(ui->btn_choseFolder1, ui->line_folder1);
    connectButtonWithLine(ui->btn_choseFolder2, ui->line_folder2);

    connect(ui->btn_findDuplicates, &QPushButton::pressed, this, &MainWindow::findDuplicates);
    connect(ui->btn_clearResult, &QPushButton::pressed, this, &MainWindow::clearResult);

    connect(ui->line_folder1, &QLineEdit::textChanged, m_df, &DuplicatFinder::changeCheckDir1);
    connect(ui->line_folder2, &QLineEdit::textChanged, m_df, &DuplicatFinder::changeCheckDir2);

    connect(ui->sb_ingnoreSize, QOverload<int>::of(&QSpinBox::valueChanged), m_df, &DuplicatFinder::ignoreFileSizeLess);
    connect(ui->cbb_hashAlgo, &QComboBox::currentTextChanged, m_df, &DuplicatFinder::chancheHashAlgorithm);

    connect(this, &MainWindow::startFind, m_df, &DuplicatFinder::checkDuplicates);
}

MainWindow::~MainWindow() {
    qDebug() << " [M] MainWindow::~MainWindow";
    delete ui;
    m_workThread->deleteLater();
}

void MainWindow::closeEvent(QCloseEvent *a_event) {
    qDebug() << " [V] MainWindow::closeEvent";

    if (m_workThread->isRunning()){
        m_workThread->exit();
//        m_workThread->terminate();
        m_workThread->wait();
    }

    QMainWindow::closeEvent(a_event);
}

/* Задачи:
 * №3 реализовать бинарную проверку файлов на идентичность
 * №4 Реализовать проверку файлов по MD5
 */

void MainWindow::findDuplicates() {
    qDebug() << " [S] MainWindow::findDuplicates";
    auto checkFolderExists = [](QLineEdit *line) {
        if (line == nullptr) return false;

        QDir dir;
        if (!dir.exists(line->text())) {
            qDebug() << " [S] MainWindow::findDuplicates путь указан не верно: " << line->text();
            QMessageBox::critical(nullptr, tr("Selected folder is not exists!")
                                  , QString("Выбраная директория не существует \n %1").arg(line->text()));

            return false;
        }
        return true;
    };

    if (!checkFolderExists(ui->line_folder1) || !checkFolderExists(ui->line_folder2)) {
        return;
    }

    emit startFind();
}

void MainWindow::clearResult() {
    qDebug() << " [S] MainWindow::clearResult";
    // TODO: do it
}

