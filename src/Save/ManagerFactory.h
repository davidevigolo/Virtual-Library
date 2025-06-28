#pragma once
#include <FileManager.h>
#include <QString>


/**
 * @brief Factory class for creating FileManager objects whit a given file path
 * 
 */
class ManagerFactory
{
private:
    QString filePath;

public:
    ManagerFactory(QString filepath);
    FileManager *create();
};