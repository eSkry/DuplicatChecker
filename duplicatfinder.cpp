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

    QDirIterator it1(m_Dir1, QStringList(),  QDir::Files, QDirIterator::Subdirectories);

    QFileInfo l_FileInfo;

    std::map<QString, qint64> l_FileList;
    while (it1.hasNext()) {
        l_FileInfo.setFile(it1.next());
        if (l_FileInfo.size() <= m_ignoreFilesLess)
            continue;
        l_FileList.insert(std::make_pair(l_FileInfo.filePath(), l_FileInfo.size()));
    }

    typedef QVector<QPair<QString, QString>> CandidatPairList;
    CandidatPairList l_checkCandidats;

    auto findAllByValue = [&l_FileList](qint64 a_findValue) {
        QVector<QString> temp;
        temp.reserve(100);

        for (auto it = l_FileList.begin(); it != l_FileList.end(); it++) {
            if (it->second == a_findValue) {
                temp.push_back(it->first);
            }
        }
        return temp;
    };

    QDirIterator targetIt(m_Dir2, QStringList(), QDir::Files, QDirIterator::Subdirectories);
    while (targetIt.hasNext()) {
        l_FileInfo.setFile(targetIt.next());
        qint64 l_FileSize = l_FileInfo.size();

        if (l_FileSize <= m_ignoreFilesLess)
            continue;

        auto tempCandidatPaths = findAllByValue(l_FileSize);
        for (auto it = tempCandidatPaths.begin(); it != tempCandidatPaths.end(); it++) {
            l_checkCandidats.append({l_FileInfo.filePath(), *it});
            qDebug() << QString(" |-- Candidats: %1 <== ==> %2").arg(l_FileInfo.filePath()).arg(*it);
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

bool DuplicatFinder::isEqualsFiles(const QString &a_file1, const QString &a_file2) {
    qDebug() << " [S] DuplicatFinder::isEqualsFiles";
    QCryptographicHash l_hash(m_hashAlgo);


    {
        QFile file(a_file1);
        file.open(QFile::ReadOnly);
    }

}






