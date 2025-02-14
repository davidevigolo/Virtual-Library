#pragma once
#include <XmlManager.h>

class XmlManagerTest{
public:
    static void testSaveAndLoadMediaItems();
    static std::vector<MediaItem*> generateXmlSampleFile(XmlManager& xmlManager);
};