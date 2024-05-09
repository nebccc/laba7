#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Функция для вычисления результата выражения
int evaluate(int a, int b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    return 0; // Этот код никогда не выполнится, но компилятор требует возвращать значение
}

// Рекурсивная функция для вычисления всех возможных результатов
void compute(string expression, int start, int end, unordered_map<string, vector<int>>& memo, vector<int>& results) {
    // Если результат уже вычислен, возвращаем его
    string key = expression.substr(start, end - start + 1);
    if (memo.count(key)) {
        results = memo[key];
        return;
    }

    // Если в выражении нет операторов, то это просто число
    if (start == end) {
        results.push_back(expression[start] - '0');
        return;
    }

    // Вычисляем результаты для всех возможных способов группировки
    for (int i = start; i <= end; ++i) {
        if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*') {
            string left = expression.substr(start, i - start);
            string right = expression.substr(i + 1, end - i);

            vector<int> left_results, right_results;
            compute(expression, start, i - 1, memo, left_results);
            compute(expression, i + 1, end, memo, right_results);

            // Комбинируем результаты с учетом оператора
            for (int l : left_results) {
                for (int r : right_results) {
                    results.push_back(evaluate(l, r, expression[i]));
                }
            }
        }
    }

    // Сохраняем результаты в memo для повторного использования
    memo[key] = results;
}

vector<int> diffWaysToCompute(string expression) {
    unordered_map<string, vector<int>> memo;
    vector<int> results;
    compute(expression, 0, expression.length() - 1, memo, results);
    return results;
}

int main() {
    string expression;
    cout << "Введите выражение: ";
    cin >> expression;

    vector<int> results = diffWaysToCompute(expression);

    cout << "Результаты вычислений: ";
    for (int result : results) {
        cout << result << " ";
    }
    cout << endl;

    return 0;
}