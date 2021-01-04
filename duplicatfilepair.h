#ifndef DUPLICATFILEPAIR_H
#define DUPLICATFILEPAIR_H

#include <QString>

/**
 * @brief The DuplicatFilePair struct
 * @details Информация о паре дубликатов
 */
struct DuplicatFilePair {
    QString m_filePathSource, m_filePathTarget;
    QByteArray m_sourceHash, m_targetHash;
    qint64 m_sourceSize, m_targetSize;
};

#endif // DUPLICATFILEPAIR_H
