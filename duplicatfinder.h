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

#include "duplicatfilepair.h"

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

private:

    /**
     * @brief isEqualsFiles
     * @param a_file1
     * @param a_file2
     * @param a_hashAlgo
     * @return
     */
    bool isEqualsFiles(const QString& a_file1, const QString &a_file2);

    // Папки для проверки
    QString m_Dir1, m_Dir2;

    int m_ignoreFilesLess;

    QCryptographicHash::Algorithm m_hashAlgo;
};

#endif // DUPLICATFINDER_H
