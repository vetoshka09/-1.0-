/*Калькулятор 1.0 - 31.01*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
- Программа выполняет арифметические операции (+, -, *, /, %) над двумя вещественными числами
- Используйте std::vector для хранения истории вычислений (например, вектор строк, содержащих выражения и результаты).
- Реализуйте функцию для выполнения арифметических операций.
- Обработка некорректного ввода (например, ввод текста вместо числа).
- Вывод истории вычислений в отформатированном виде.
- Использовать функции для обработки отдельных операций.

Примечания:
1. Если в истории больше 5 уравнений, первое удаляется
2. Проверка на неправильный ввод: asd+7=ОШИБКА, 3/0=ОШИБКА, 0/0=ОШИБКА
3. Остановка ввода командами: 0, stop
*/

//Глоб. переменные
vector<string> history;
string uravn;
//Определение функций
void output(float, int);
void string_to_int(string);
int getNumber_outInfo(vector<string>&);

//Арифмитические функции
float Sum(float num1, float num2) {
    float otv = 0;
    otv = num1 + num2;
    return otv;
}
float Sud(float num1, float num2) {
    float otv = 0;
    otv = num1 - num2;
    return otv;
}
float Del(float num1, float num2) {
    float otv = 0;
    otv = num1 / num2;
    return otv;
}
float Mul(float num1, float num2) {
    float otv = 0;
    otv = num1 * num2;
    return otv;
}
float Percent(float num1, float num2) {
    float otv = 0;
    otv = num1 / 100 * num2;
    return otv;
}

//Разделение уравнения на сост., вызов ар.функций, вызов функции ответа
void string_to_int(string str) {
    int sos = 1; //для ошибок
    float num1 = 0, num2 = 0;
    float otvet = 0;
    char symbol = ' ';

    int temp = 0; // если 0 - записываю в num1, если 1 - записываю в num2
    for (int i = 0; i < uravn.size(); i++) {
        if (temp == 0 && str[i] >= 48 && str[i] < 58) {
            num1 = (num1 * 10) + (str[i] - 48);
        }
        else if (temp == 1 && str[i] >= 48 && str[i] < 58) {
            num2 = (num2 * 10) + (str[i] - 48);
        }
        else if (str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*' || str[i] == '%') {
            symbol = str[i];
            temp = 1;
        }
        else
            sos = 404;
    }
    //Проверка: деление на 0
    if (num2 == 0 && symbol == '/')
        sos = 404;

    switch (symbol)
    {
    case '+':
        otvet = Sum(num1, num2);
        break;
    case '-':
        otvet = Sud(num1, num2);
        break;
    case '/':
        otvet = Del(num1, num2);
        break;
    case '*':
        otvet = Mul(num1, num2);
        break;
    case '%':
        otvet = Percent(num1, num2);
        break;

    default:
        break;
    }

    output(otvet, sos);
}

//Вывод ответа
void output(float otv, int sos) {
    string str_otv1;
    //Нужно острингить ответ
    if (sos == 404) {
        history.push_back(uravn + "=" + "ОШИБКА");
    }
    else {
        str_otv1 = to_string(otv);
        history.push_back(uravn + "=" + str_otv1);
    }


    if (history.size() > 5) {
        history.erase(history.begin());
    }
    system("cls");
}

//Получение уравнения, вывод информации
int getNumber_outInfo(vector<string>& history) {
    cout << "\t[Калькулятор]" << endl;
    cout << "История" << endl;
    if (history.empty()) {
        cout << "    [Пусто]" << endl;
    }
    vector<string>::iterator iter_history; //итератор для вектора
    if (!history.empty()) {
        for (iter_history = history.begin(); iter_history != history.end() - 1; iter_history++) {
            cout << "    " << *iter_history << endl;
        }
        cout << "  =>" << *iter_history << endl; //Вывод последнего эл. вектора через итератор
    }

    cout << endl << ">> "; cin >> uravn;

    //Остановка
    if (uravn == "0") {
        return 0;
    }
    if (uravn == "stop") {
        return 0;
    }
    //Очистка истории
    if (uravn == "clear") {
        history.clear();
    }
    //Вызываем функцию распределения уравнения на числа
    string_to_int(uravn);
    return 1;
}


int main(){
    setlocale(LC_ALL, "rus");

    //Цикл остановки
    int stop = 1;
    while (stop != 0) {
        stop = getNumber_outInfo(history);
    }
    return 0;
}
