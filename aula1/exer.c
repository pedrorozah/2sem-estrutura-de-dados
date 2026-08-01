#include <stdio.h>

// protótipos
float soma(float x, float y);

float dividir(float x, float y);

float subtrair(float x, float y);

float multiplicar(float x, float y);

float calcular_operacao(float x, float y, char op);

int main()
{

    float a, b, resultado;
    char op;

    printf("Digite o primeiro número: ");
    scanf("%f", &a);

    printf("Digite o segundo número: ");
    scanf("%f", &b);

    printf("Digite a operação: /, *, + ou -:");
    scanf(" %c", &op);

    resultado = calcular_operacao(a, b, op);

    printf("\nResultado: %.2f", resultado);

    return 0;
}

float soma(float x, float y)
{
    return x + y;
}

float dividir(float x, float y)
{
    return x / y;
}

float subtrair(float x, float y)
{
    return x - y;
}

float multiplicar(float x, float y)
{
    return x * y;
}

float calcular_operacao(float x, float y, char op)
{
    switch (op)
    {
    case '/':
        return dividir(x, y);
        break;

    case '*':
        return multiplicar(x, y);
        break;
    case '-':
        return subtrair(x, y);
        break;
    case '+':
        return soma(x, y);
        break;

    default:
        printf("Caractere inválido.");
        break;
    }
    return 0;
}
