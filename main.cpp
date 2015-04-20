/* Copyright 2014 ToxaKniotee */
#include <iostream>
#include <string>
#include <limits>

using std::string;
using std::cout;
using std::endl;

template <class T>
void printMatrix(T *m, int WIDTH, int HEIGTH) {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGTH; j++)
            cout << m[i * WIDTH + j] << " ";
        cout << endl;
    }
}

string chainMatrix(int *p, int num) {
    /* Creamos las variables a usar, tenemos una matriz en donde guardamos tan-
    ** to el número de operaciones en total así como cual es el orden de estas */
    int min, prev;
    int *matrix = new int[num * num];
    string tempPath;
    string *path = new string[num * num];

    /* Inicializamos la diagonal principal como 0, indicando que la multiplica-
    ** ción de una sola matriz es cero */
    for (int s = 0; s < num * num; s++)
        matrix[s] = 0;

    /* Llenamos la matriz con las letras y los espacios vacios */
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (i == j) {
                path[i * num + j] = static_cast<char>(65 + i);
            } else {
                path[i * num + j] = "";
            }
        }
    }

    /* Vamos llenando la matriz diagonal por diagonal */
    for (int c = 1; c < num; c++) {
        /* Fila */
        for (int i = 0; i < num - c; i++) {
            /* Establecemos el máximo número como el mínimo */
            min = std::numeric_limits<int>::max();

            /* Checamos el mínimo de las sumatorias posibles */
            for (int j = 0; j < c; j++) {
                /* Creamos el valor para no tener que hacer la operación despues
                ** en caso de que sea el nuevo valor mínimo */
                int val = matrix[i * num + j + i] + matrix[(i + j + 1) * num +
                    c + i] + p[i] * p[i + j + 1] * p[1 + c + i];

                /* Si es el mínimo entonces lo cambiamos y asignamos el string
                ** adecuado para el camino */
                if (min > val) {
                    min = val;
                    tempPath = "(" + path[i * num + j + i] + ")(" +
                        path[(i + j + 1) * num + c + i] + ")";
                }
            }

            /* Despues de escoger el minimo de todas las opciones lo guardamos
            ** en las matrices */
            matrix[i * num + (i + c)] = min;
            path[i * num + (i + c)] = tempPath;
        }
    }

    /* Regresamos el string donde representa el orden */
    return path[num - 1];
}

int main(int argc, char const *argv[]) {
    int matrices[] = { 2, 2, 3, 2, 4 };
    cout << chainMatrix(matrices, 4) << endl;

    system("PAUSE");
    return 0;
}
