#include "LoadFromFileTests.h"

void initLoadFromFileTest()
{
    //XmlManagerTest::generateXmlSampleFile(); 
}

int LoadFromFileTest::testLoadFromFile()
{
        initLoadFromFileTest();


        XmlManager xml = XmlManager("test.xml");
        QVector<MediaItem*> xread = xml.load();

        JsonManager json = JsonManager("test.json");
        QVector<MediaItem*> jread = json.load();

        


        QMap<QString, QVector<MediaItem*>> jmap;

        LoadVisitor jloadVisitor = LoadVisitor(jmap);
        for(auto item : jread){
            item->accept(&jloadVisitor);
        }

        QMap<QString, QVector<MediaItem*>> xmap = {{"Article",{}},{"Book",{}},{"Film",{}},{"Music",{}},{"Podcast",{}}};

        LoadVisitor xloadVisitor = LoadVisitor(xmap);
        for(auto item : xread){
            item->accept(&xloadVisitor);
        }

        for(auto key : jmap.keys()){
            std::cout<<key.toStdString()<<"\n\n";
            for(auto item : jmap.value(key)){
                std::cout<<item->getTitle()<<"\n";
            }
                std::cout<<"fine vector\n";
        } 

        for(auto key : xmap.keys()){
            std::cout<<key.toStdString()<<"\n\n";
            for(auto item : xmap.value(key)){
                std::cout<<item->getTitle()<<"\n";
            }
                std::cout<<"fine vector\n";
        } 
        return 0;

}