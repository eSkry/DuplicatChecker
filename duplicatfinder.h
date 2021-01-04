#ifndef DUPLICATFINDER_H
#define DUPLICATFINDER_H

#include <QCryptographicHash>
#include <QDirIterator>
#include <QFileInfo>
#include <QObject>
#include <QThread>
#include <QString>
#include <QDebug>
#include <QList>
#include <QDir>
#include <QMap>

#include <vector>
#include <map>

/**
 * @brief The DuplicatFinder class - Класс реализующий поиск файлов дубликатов
 */
class DuplicatFinder : public QObject {
    Q_OBJECT
public:

    /**
     * @brief DuplicatFinder
     * @param parent
     */
    explicit DuplicatFinder(QObject *parent = nullptr);

signals:

    /**
     * @brief equalFiles
     */
    void equalFiles(const QPair<QFileInfo, QFileInfo>);

public slots:

    /**
     * @brief checkDuplicates - Функция запускает процесс проверки файлов
     */
    void checkDuplicates();

    /**
     * @brief changeCheckDir1 - Устанавливает папку для поиска в исходном каталоге
     * @param aDir
     */
    void changeCheckDir1(const QString& a_Dir);

    /**
     * @brief setCheckDir2 - Устанавливает папку для поиска в целевом каталоге
     * @param aDir
     */
    void changeCheckDir2(const QString& a_Dir);

    /**
     * @brief ignoreFileSizeLess - Устанавливает порог размера файлов которые не будут учитываться
     * @param a_size
     */
    void ignoreFileSizeLess(int a_size);

    /**
     * @brief chancheHashAlgorithm
     * @param a_hashAlgoName
     */
    void chancheHashAlgorithm(const QString& a_hashAlgoName);

    /**
     * @brief getFileListOnDirectory - Пробегает по указанной директории и по поддиректориям записывая путь и размер файла
     * @param a_directoryPath
     * @param a_result - В данный параметр будет записываться результат работы функции
     */
    void getFileListOnDirectory(const QString& a_directoryPath, QVector<QFileInfo>& a_result);

private:

    /**
     * @brief isEqualsFiles
     * @param a_file1
     * @param a_file2
     * @param a_hashAlgo
     * @return
     */
    bool isEqualsFiles(const QString& a_file1, const QString &a_file2);

    /**
     * @brief getHashFile
     * @param a_filePath
     * @return
     */
    QByteArray getHashFile(const QString& a_filePath);

    // Папки для проверки
    QString m_Dir1, m_Dir2;
    int m_ignoreFilesLess;
    QCryptographicHash::Algorithm m_hashAlgo;
    const long BLOCK_SIZE = 8192;
};

#endif // DUPLICATFINDER_H
