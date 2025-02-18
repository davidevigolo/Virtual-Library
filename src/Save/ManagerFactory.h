#pragma once
#include <FileManager.h>
#include <QString>

class ManagerFactory
{
private:
    QString filePath;

public:
    ManagerFactory(QString filepath);
    FileManager *create();
};