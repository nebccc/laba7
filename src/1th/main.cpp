#include <iostream>
#include <vector>

using namespace std;

// Рекурсивная функция для размещения предметов в контейнерах
bool bagger(int number_of_containers, double container_height, int container_capacity, int number_of_items, int k, vector<int>& used_containers, vector<int>& items) {
    if (number_of_items == 0) {
        return true;
    }

    int item_height = items[items.size() - number_of_items]; // Высота текущего предмета

    for (int i = 0; i < number_of_containers; ++i) {
        if (container_height >= item_height && used_containers[i] < container_capacity) {
            // Предмет помещается в контейнер
            used_containers[i]++;
            cout << "Предмет высотой " << item_height << " помещается в контейнер " << i + 1 << endl;

            // Рекурсивно пытаемся разместить следующие предметы
            if (bagger(number_of_containers, container_height, container_capacity, number_of_items - 1, k, used_containers, items)) {
                return true;
            }

            // Если не удалось разместить следующие предметы, откатываем изменения
            used_containers[i]--;
            cout << "Предмет высотой " << item_height << " не может быть размещен в контейнере " << i + 1 << endl;
        }
    }

    // Если не удалось разместить текущий предмет ни в одном контейнере, возвращаем false
    cout << "Предмет высотой " << item_height << " не может быть размещен ни в одном контейнере" << endl;
    return false;
}

int main() {
    int N, H, C, M;
    cout << "Введите количество контейнеров N, их высоту H, вместимость C и количество предметов M: ";
    cin >> N >> H >> C >> M;

    vector<int> used_containers(N, 0); // Инициализируем массив использованных контейнеров
    vector<int> items(M); // Инициализируем вектор предметов

    cout << "Введите высоты предметов: ";
    for (int i = 0; i < M; ++i) {
        cin >> items[i];
    }

    // Запускаем функцию размещения предметов
    if (bagger(N, H, C, M, 0, used_containers, items)) {
        cout << "Предметы успешно размещены в контейнерах." << endl;
    } else {
        cout << "Не удалось разместить все предметы в контейнерах." << endl;
    }

    return 0;
}