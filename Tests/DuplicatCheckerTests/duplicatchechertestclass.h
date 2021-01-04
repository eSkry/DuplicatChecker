#ifndef DUPLICATCHECHERTESTCLASS_H
#define DUPLICATCHECHERTESTCLASS_H

#include <QFileInfo>
#include <QObject>

#include "duplicatfinder.h"

class DuplicatChecherTestClass : public QObject {
    Q_OBJECT
public:
    explicit DuplicatChecherTestClass(QString a_dir1, QString a_dir2, int ignoreLess, QObject *parent = nullptr);
    ~DuplicatChecherTestClass();

    int getCountDuplicates();

public slots:
    void applyDuplicatPair(QPair<QFileInfo, QFileInfo>);

    void runTest();

private:
    int duplicatCounter;
    DuplicatFinder *m_df;
};

#endif // DUPLICATCHECHERTESTCLASS_H
