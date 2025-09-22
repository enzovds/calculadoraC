#include "calculadora_logica.h"

double somar(double a, double b) {
    return a + b;
}

double subtrair(double a, double b) {
    return a - b;
}

double multiplicar(double a, double b) {
    return a * b;
}

// Retorna um valor especial em caso de erro para a interface tratar
double dividir(double a, double b) {
    if (b == 0) {
        return -1; // Vamos usar -1 como um código de erro simples, a interface saberá o que fazer
    }
    return a / b;
}