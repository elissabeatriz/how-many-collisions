/**************************************************************/

/**                                                          **/

/**  Elissa Beatriz da Silva Martins NUSP 11284248           **/

/**  Exercicio-Programa 2                                    **/

/**  Professor: Guilherme Mota                               **/

/**  Turma: 03                                               **/

/**                                                          **/

/**************************************************************/


#include <stdio.h>
#include <math.h>
#define L 0.1


void read_data(double *x0, double *x1, double *x2, double *x3,
double *v0, double *v1, double *v2, double *v3,
double *m0, double *m1, double *m2, double *m3,
double *T_max);


double t(double x, double xx, double v, double vv);

double min(double a, double b, double c, int *i);

double adv(double *x, double v, double t);

void resolve(double *v, double *vv, double m, double mm);

void print_data(long c1, long c2, long c3,
double x0, double x1, double x2, double x3,
double v0, double v1, double v2, double v3,
double d0, double d1, double d2, double d3);


double t_e;

/*as variaveis globais colisoes1, colisoes2, colisoes3 serao usadas para armazenar as colisoes, uma vez
  que na funcao prototipo as colisoes sao do tipo long, que so armazena ate 2 bi. e nas entradas
  input10 e wall10 as massas eram muito maiores do que o tipo long consegue armazenar, o que prejudicou
  a saida final. por isso, decidi usar essas variaveis do tipo double*/

double colisoes1, colisoes2, colisoes3;

int main()
{
    double x0, x1, x2, x3, v0, v1, v2, v3,
        m0, m1, m2, m3, T, T_max,
        d0, d1, d2, d3;

    d0 = 0.0;
    d1 = 0.0;
    d2 = 0.0;
    d3 = 0.0;

    colisoes1 = 0;
    colisoes2 = 0;
    colisoes3 = 0;

    T = 0.0;
    read_data(&x0, &x1, &x2,&x3, &v0, &v1, &v2, &v3, &m0, &m1, &m2, &m3, &T_max);

    while(T < T_max){
        double t01, t12, t23;
        int indice_e;

        t01 = t(x0, x1, v0, v1);
        t12 = t(x1, x2, v1, v2);
        t23 = t(x2, x3, v2, v3);
        t_e = min(t01, t12, t23, &indice_e);


        if (t_e + T > T_max) {
            double t_restante = T_max - T;
            d0 += adv(&x0, v0, t_restante);
            d1 += adv(&x1, v1, t_restante);
            d2 += adv(&x2, v2, t_restante);
            d3 += adv(&x3, v3, t_restante);
            break;
        }

        T += t_e;

        d0 += adv(&x0, v0, t_e);
        d1 += adv(&x1, v1, t_e);
        d2 += adv(&x2, v2, t_e);
        d3 += adv(&x3, v3, t_e);

        if (t01 == t_e) {
            resolve(&v0, &v1, m0, m1);
            colisoes1++;
        }
        if (t12 == t_e) {
            resolve(&v1, &v2, m1, m2);
            colisoes2++;
        }
        if (t23 == t_e) {
            resolve(&v2, &v3, m2, m3);
            colisoes3++;
        }
    }
    print_data(0, 0, 0, x0, x1, x2, x3, v0, v1, v2, v3, d0, d1, d2, d3);

    return 0;
}

void read_data(double *x0, double *x1, double *x2, double *x3,
double *v0, double *v1, double *v2, double *v3,
double *m0, double *m1, double *m2, double *m3,
double *T_max){

    scanf("%lf %lf %lf", x0, v0, m0);
    scanf("%lf %lf %lf", x1, v1, m1);
    scanf("%lf %lf %lf", x2, v2, m2);
    scanf("%lf %lf %lf", x3, v3, m3);
    scanf("%lf", T_max);
}

double t(double x, double xx, double v, double vv){
double distancia, v_relativa;
double delta_t;

distancia = (xx - x) - L;
v_relativa = v - vv;
delta_t = distancia / v_relativa;

    if(v_relativa > 0)
        return delta_t;
    else
        return HUGE_VAL;
}



double min(double a, double b, double c, int *i){
    double m = 1.0;

    if(a <= b && a <= c){
        m = a;
        *i = 1;
        if(a == b || a == c)
            return m;
    }

    else if (b <= a && b <= c){
        m = b;
        *i = 2;
        if(b == c)
            return m;
    }

    else if (c < a && c < b){
        m = c;
        *i = 3;
    }
    return m;
}

double adv(double *x, double v, double t){
    double s;
    s = v * t;
    *x = *x + s;
    return fabs(s);
}

void resolve(double *v, double *vv, double m, double mm){
    double A, parte_1, parte_2;

    parte_1 = m * (*v);
    parte_2 = mm * (*vv);
    A = (2 * (parte_1 + parte_2)) / (m + mm);
    *v = A - (*v);
    *vv = A - (*vv);
}

void print_data(long c1, long c2, long c3,
double x0, double x1, double x2, double x3,
double v0, double v1, double v2, double v3,
double d0, double d1, double d2, double d3){

/*long so armazena ate 2 bi. Por isso, a impressao das colisoes sao do tipo double
 para que as saidas, cujas entradas contenham massas maiores que 2 bi, nao sejam
 discrepantes. o input10 e wall10 sao exemplos de casos em que usar long prejudicaria
 a saida das colisoes. so deixei long no prototipo porque as funcoes eram obrigatorias*/

    double total_colisoes, direita_colisoes;

    total_colisoes = colisoes1 + colisoes2 + colisoes3;
    direita_colisoes = colisoes2 + colisoes3;

    printf("Numero total de colisoes por bloco: %.0lf %.0lf %.0lf\n", colisoes1, colisoes2, colisoes3);
    printf("Numero total de colisoes: %.0lf\n", total_colisoes);
    printf("Colisoes dos dois blocos a direita: %.0lf\n", direita_colisoes);
    printf("x0 = % 10.6lf v0 = % 10.6lf d0 = % 10.6lf\n", x0, v0, d0);
    printf("x1 = % 10.6lf v1 = % 10.6lf d1 = % 10.6lf\n", x1, v1, d1);
    printf("x2 = % 10.6lf v2 = % 10.6lf d2 = % 10.6lf\n", x2, v2, d2);
    printf("x3 = % 10.6lf v3 = % 10.6lf d3 = % 10.6lf\n", x3, v3, d3);

    if (t_e == HUGE_VAL){
        printf("Nao ha mais colisoes\n");
    }
    else {
        printf("Ha colisoes remanescentes\n");
    }
}

