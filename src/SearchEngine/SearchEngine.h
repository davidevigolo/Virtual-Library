#pragma once
#include <SearchVisitor.h>

/**
    * @brief SearchEngine class
    * 
    * This class is responsible for searching items in the database.
    * It uses the SearchVisitor class to calculate the points for each item.
    * 
    *@function search
    *@param query - the query to search for
    *@param items - the items to search in
    *@return QVector<MediaItem*> - the items that match the query sorted on how well they match the query from the best match to the worst match
*/

class SearchEngine{
    SearchVisitor visitor;
private:
    void merge(QVector<MediaItem*>& items, QVector<short int>& points, int left, int mid, int right);
    void mergeSort(QVector<MediaItem*>& items, QVector<short int>& points, int left, int right);
public:
    SearchEngine() : visitor("") {};
    QVector<MediaItem*> search(const QString& query, const QVector<MediaItem*>& items);
};