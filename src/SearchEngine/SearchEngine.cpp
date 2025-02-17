#include <SearchEngine.h>

QVector<MediaItem*> SearchEngine::search(const QString& query, const QVector<MediaItem*>& items) {
    visitor = SearchVisitor(query);
    QVector<MediaItem*> result = items;
    mergeSort(result,0,items.size()-1);
    int i = result.size()-1;
    while(result[i] == 0){
        result.pop_back();
        i--;
    }
    return result;
}

void SearchEngine::merge(QVector<MediaItem*>& items, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    QVector<MediaItem*> L(n1);
    QVector<MediaItem*> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = items[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = items[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        L[i]->accept(&visitor);
        int points_l = visitor.getPoints();
        R[j]->accept(&visitor);
        int points_r = visitor.getPoints();
        if (points_l >= points_r) {
            items[k] = L[i];
            i++;
        } else {
            items[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        items[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        items[k] = R[j];
        j++;
        k++;
    }
}

void SearchEngine::mergeSort(QVector<MediaItem*>& items, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(items, left, mid);
        mergeSort(items, mid + 1, right);

        merge(items, left, mid, right);
    }
}