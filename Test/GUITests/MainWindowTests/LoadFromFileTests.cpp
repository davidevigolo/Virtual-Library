#include "LoadFromFileTests.h"

void initLoadFromFileTest()
{
    XmlManagerTest::generateXmlSampleFile(); 
}

int LoadFromFileTest::testLoadFromFile()
{
        initLoadFromFileTest();

        JsonManager json = JsonManager("Test/test.json");
        QVector<MediaItem*> jread = json.readJson();

        XmlManager xml = XmlManager("Test/test.xml");
        QVector<MediaItem*> xread = xml.load();


        QMap<QString, QVector<MediaItem*>> jmap;

        LoadVisitor jloadVisitor = LoadVisitor(jmap);
        for(auto item : jread){
            item->accept(jloadVisitor);
        }

        QMap<QString, QVector<MediaItem*>> xmap;

        LoadVisitor xloadVisitor = LoadVisitor(xmap);
        for(auto item : xread){
            item->accept(xloadVisitor);
        }

        for(int i = 0; i < 5; i++){
            std::cout<<i<<"\n\n";
            for(auto item : jmap[i]){
                std::cout<<item->getName().toStdString()<<"\n";
            }
        } 

        for(int i = 0; i < 5; i++){
            std::cout<<i<<"\n\n";
            for(auto item : xmap[i]){
                std::cout<<item->getName().toStdString()<<"\n";
            }
        } 
        return 0;

}