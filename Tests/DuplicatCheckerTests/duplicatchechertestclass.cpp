#include "duplicatchechertestclass.h"

DuplicatChecherTestClass::DuplicatChecherTestClass(QString a_dir1, QString a_dir2, int ignoreLess, QObject *parent) : QObject(parent) {
    duplicatCounter = 0;
    m_df = new DuplicatFinder();

    m_df->changeCheckDir1(a_dir1);
    m_df->changeCheckDir2(a_dir2);
    m_df->ignoreFileSizeLess(ignoreLess);

    connect(m_df, &DuplicatFinder::equalFiles, this, &DuplicatChecherTestClass::applyDuplicatPair);
}

DuplicatChecherTestClass::~DuplicatChecherTestClass() {
    m_df->deleteLater();
    delete m_df;
}

int DuplicatChecherTestClass::getCountDuplicates() {
    return duplicatCounter;
}

void DuplicatChecherTestClass::applyDuplicatPair(QPair<QFileInfo, QFileInfo>) {
    duplicatCounter++;
}

void DuplicatChecherTestClass::runTest() {
    m_df->checkDuplicates();
}
