#include "duplicatfinder.h"

DuplicatFinder::DuplicatFinder(QObject *parent) : QObject(parent) {
    qDebug() << " [M] DuplicatFinder::DuplicatFinder";
    m_ignoreFilesLess = 5;
    m_hashAlgo = QCryptographicHash::Md5;
}

void DuplicatFinder::checkDuplicates() {
    qDebug() << " [S] DuplicatFinder::checkDuplicates";

    if (m_Dir1.isEmpty() || m_Dir2.isEmpty()) {
        qDebug() << " [S] DuplicatFinder::checkDuplicates - no path to source or target directory";
        return;
    }

    const int RESERVE_FILE_COUNT = 1000;
    const bool IS_SINGLE_FOLDER = m_Dir1 == m_Dir2;

    QVector<QFileInfo> l_FilesSource, l_FilesTarget;
    l_FilesSource.reserve(RESERVE_FILE_COUNT);
    l_FilesTarget.reserve(RESERVE_FILE_COUNT);

    getFileListOnDirectory(m_Dir1, l_FilesSource);
    if (!IS_SINGLE_FOLDER) {
        getFileListOnDirectory(m_Dir2, l_FilesTarget);
    }

    QVector<QFileInfo>& l_targetAlias = IS_SINGLE_FOLDER ? l_FilesSource : l_FilesTarget;

    QVector<QPair<QFileInfo, QFileInfo>> compareCandidats;
    compareCandidats.reserve(RESERVE_FILE_COUNT);

    for (auto s_it = l_FilesSource.begin(); s_it != l_FilesSource.end(); s_it++) {
        for (auto t_it = l_targetAlias.begin(); t_it != l_targetAlias.end(); t_it++) {

            if (s_it->size() == t_it->size()) {
                if (IS_SINGLE_FOLDER && s_it->filePath() == t_it->filePath())
                    continue;

                compareCandidats.append(qMakePair(*s_it, *t_it));
            }
        }
    }

    QVector<QPair<QFileInfo, QFileInfo>> l_equalFiles;
    QByteArray l_hash1, l_hash2;
    for (auto it = compareCandidats.begin(); it != compareCandidats.end(); it++) {
        l_hash1 = getHashFile(it->first.filePath());
        l_hash2 = getHashFile(it->second.filePath());

        if (l_hash1 == l_hash2) {
            l_equalFiles.append(*it);
            qDebug() << QString(" |-- Candidats: %1 <== ==> %2").arg(it->first.filePath()).arg(it->second.filePath());
        }
    }

}

void DuplicatFinder::changeCheckDir1(const QString &a_Dir) {
    qDebug() << " [S] DuplicatFinder::setCheckDir1";
    m_Dir1 = a_Dir;
}

void DuplicatFinder::changeCheckDir2(const QString &a_Dir) {
    qDebug() << " [S] DuplicatFinder::setCheckDir2";
    m_Dir2 = a_Dir;
}

void DuplicatFinder::ignoreFileSizeLess(int a_size) {
    qDebug() << " [S] DuplicatFinder::ignoreFileSizeLess to " << a_size;
    m_ignoreFilesLess = a_size * 1024; // Передаются kB а здесь указывается в байтах
}

void DuplicatFinder::chancheHashAlgorithm(const QString &a_hashAlgoName) {
    qDebug() << " [S] DuplicatFinder::chancheHashAlgorithm to " << a_hashAlgoName;

    if (a_hashAlgoName == "MD5") {
        m_hashAlgo = QCryptographicHash::Md5;
    } else if (a_hashAlgoName == "SHA256") {
        m_hashAlgo = QCryptographicHash::Sha256;
    }
}

void DuplicatFinder::getFileListOnDirectory(const QString &a_directoryPath, QVector<QFileInfo> &a_result) {
    qDebug() << " [M] DuplicatFinder::getFileListOnDirectory";
    QDirIterator l_iter(a_directoryPath, QStringList(),  QDir::Files, QDirIterator::Subdirectories);
    QFileInfo l_fInfo;

    while (l_iter.hasNext()) {
        l_fInfo.setFile(l_iter.next());

        if (l_fInfo.size() <= m_ignoreFilesLess)
            continue;

        a_result.append(l_fInfo);
    }
}

bool DuplicatFinder::isEqualsFiles(const QString &a_file1, const QString &a_file2) { // TODO: А нужен ли он теперь?
    qDebug() << " [S] DuplicatFinder::isEqualsFiles";
    QCryptographicHash l_hash(m_hashAlgo);

    QByteArray l_hash1 = getHashFile(a_file1);
    QByteArray l_hash2 = getHashFile(a_file2);

    if (l_hash1 == l_hash2) {
        return true;
    }

    return false;
}

QByteArray DuplicatFinder::getHashFile(const QString &a_filePath) {
    qDebug() << " [M] DuplicatFinder::getHashFile " << a_filePath;
    QCryptographicHash l_hash(m_hashAlgo);

    QFile l_file(a_filePath);
    l_file.open(QFile::ReadOnly);

    while (!l_file.atEnd()){
        l_hash.addData(l_file.read(BLOCK_SIZE));
    }

    return l_hash.result();
}












