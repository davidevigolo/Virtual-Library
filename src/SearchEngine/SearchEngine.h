#pragma once
#include <SearchVisitor.h>

class SearchEngine{
    SearchVisitor visitor;
private:
    void merge(QVector<MediaItem*>& items, int left, int mid, int right);
    void mergeSort(QVector<MediaItem*>& items, int left, int right);
public:
    SearchEngine() : visitor("") {};
    QVector<MediaItem*> search(const QString& query, const QVector<MediaItem*>& items);
};