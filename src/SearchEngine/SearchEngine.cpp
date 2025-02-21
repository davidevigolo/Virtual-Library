#include <SearchEngine.h>
#include <iostream>
#include <Settings.h>

QVector<MediaItem*> SearchEngine::search(const QString& query, const QVector<MediaItem*>& items) {
    std::map<std::string, int> weights;
    for (const auto& pair : Settings::getSettings().weights.toStdMap()) {
        weights[pair.first.toStdString()] = pair.second;
    }
    visitor = SearchVisitor("", weights);
    QVector<MediaItem*> result = items;
    QVector<short int> points(items.size(), 1); //to store the search  points for each item instead of re-visit it every time i need a check

    for (auto word : query.split(" ")) {
        visitor.setQuery(word);
        for (int i = 0; i < items.size(); i++) {
            items[i]->accept(&visitor);
            points[i] *= visitor.getPoints();
        }
    }

    mergeSort(result, points, 0, items.size() - 1);

    bool isZero = true; 
    int i = result.size() - 1;

    while(isZero && i >= 0){
        if(points[i] == 0){
            result.pop_back();
            i--;
        } else {
            isZero = false;
        }
    }
    return result;
}

void SearchEngine::merge(QVector<MediaItem*>& items, QVector<short int>& points, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    QVector<MediaItem*> L(n1);
    QVector<MediaItem*> R(n2);
    QVector<short int> points_l(n1);
    QVector<short int> points_r(n2);

    for (int i = 0; i < n1; i++){
        L[i] = items[left + i];
        points_l[i] = points[left + i];
    }
    for (int j = 0; j < n2; j++){
        R[j] = items[mid + 1 + j];
        points_r[j] = points[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (points_l[i] >= points_r[j]) {
            items[k] = L[i];
            points[k] = points_l[i];
            i++;
        } else {
            items[k] = R[j];
            points[k] = points_r[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        items[k] = L[i];
        points[k] = points_l[i];
        i++;
        k++;
    }

    while (j < n2) {
        items[k] = R[j];
        points[k] = points_r[j];
        j++;
        k++;
    }
}

void SearchEngine::mergeSort(QVector<MediaItem*>& items, QVector<short int>& points, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(items, points, left, mid);
        mergeSort(items, points, mid + 1, right);

        merge(items, points, left, mid, right);
    }
}
