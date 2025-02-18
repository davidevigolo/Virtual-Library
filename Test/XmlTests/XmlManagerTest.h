#pragma once
#include <XmlManager.h>

class XmlManagerTest{
public:
    static void testSaveAndLoadMediaItems();
    static QVector<MediaItem*> generateXmlSampleFile(XmlManager& xmlManager);
};