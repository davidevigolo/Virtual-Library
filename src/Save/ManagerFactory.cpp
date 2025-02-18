#include <ManagerFactory.h>
#include <XmlManager.h>
#include <JsonManager.h>
#include <QFileInfo>

ManagerFactory::ManagerFactory(QString filePath) : filePath(filePath){}
FileManager* ManagerFactory::create(){
    QString t = QFileInfo(filePath).suffix();
    if(t == QString("xml")) return new XmlManager(filePath);
    else if(t == QString("json")) return new JsonManager(filePath);
    else return nullptr;
}