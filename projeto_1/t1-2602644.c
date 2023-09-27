/*============================================================================*/
/* ICSF13 - 2023-2 - TRABALHO 1                                               */
/*----------------------------------------------------------------------------*/
/* Eduardo Vinicius Dias                                                      */
/*============================================================================*/

#include"trabalho1.h"
#include<stdio.h>
#include<math.h>

// 2^(16)
#define DOIS_A_DEZESSEIS 65536

/*============================================================================*/
/* Funções do trabalho. */

int calculaInterseccao (int n_retangulos);
unsigned int encontraParMaisProximo (int n_retangulos);

/*============================================================================*/
/* Funções auxiliares. */


/*============================================================================*/

int calculaInterseccao (int n_retangulos)
{
    int i;

    // Quatro pares de coordenadas, referentes aos vértices de dois retângulos.
    int ret1XSE, ret1YSE, ret1XID, ret1YID, ret2XSE, ret2YSE, ret2XID, ret2YID;

    // Área de intersecção e flag para saber se há intersecção entre os retângulos.
    int area, tem_inters;

    // Coordenadas do "retângulo definitivo". Se houver intersecção, as coordenadas do 
    // retângulo da intersecção serão armazenadas nestas variáveis.
    ret1XSE = pegaXSE(0);
    ret1YSE = pegaYSE(0);
    ret1XID = pegaXID(0);
    ret1YID = pegaYID(0);

    tem_inters = 1;
    area = 0;

    // Para cada retângulo...
    for (i = 1; i<n_retangulos ; i++)
    {
        // Coordenadas do "retângulo de comparação".
        ret2XSE = pegaXSE(i);
        ret2YSE = pegaYSE(i);
        ret2XID = pegaXID(i);
        ret2YID = pegaYID(i);

        // Descobrir se NÃO tem intersecção. Caso não tenha, encerra o loop e a área permanece 0.
        if (ret1XSE >= ret2XID || ret2XSE >= ret1XID || ret1YID >= ret2YSE || ret2YID >= ret1YSE)
        {
            tem_inters = 0;
            break;
        }

        // "Montar" o retângulo da intersecção:
        // O retângulo da inters. recebe o maior X dos vértices superiores esquerdos,...
        if (ret1XSE < ret2XSE)
            ret1XSE = ret2XSE;
        
        // O menor Y dos vértices superiores esquerdos,...
        if (ret1YSE > ret2YSE)
            ret1YSE = ret2YSE;

        // O menor X dos vértices inferiores direitos,...
        if (ret1XID > ret2XID)
            ret1XID = ret2XID;

        // E o maior Y dos vértices inferiores direitos.
        if (ret1YID < ret2YID)
            ret1YID = ret2YID;
    }

    // Calcular a área se tiver intersecção.
    if (tem_inters)
        area = (ret1XID - ret1XSE) * (ret1YSE - ret1YID);
    
    // Retorna a área de intersecção.
    return area;
}

unsigned int encontraParMaisProximo (int n_retangulos)
{
    int i, j;

    // Quatro pares de coordenadas, referentes aos vértices de dois retângulos.
    int ret1XSE, ret1YSE, ret1XID, ret1YID, ret2XSE, ret2YSE, ret2XID, ret2YID;


    // Coordenadas dos centros dos retângulos
    double ponto1X, ponto1Y, ponto2X, ponto2Y;


    // Distância entre dois pontos e menor distância.
    double dist, menor_dist;


    // Valor que vai ser retornado pela função e índices de retangulos
    unsigned int combina_id, id1, id2;


    // Para toda combinação de dois pontos, calcular a distância.
    for (i=0 ; i<n_retangulos ; i++)
    {   
        // Centro do retangulo i.
        ponto1X = (pegaXID(i) + pegaXSE(i))/2.0;
        ponto1Y = (pegaYSE(i) + pegaYID(i))/2.0;


        // Calcula a distância entre o ponto i e os outros centros de retângulos.
        for (j=i+1 ; j<n_retangulos ; j++)
        {
            // Calculando as posições dos centros dos retângulos.
            ponto2X = (pegaXID(j) + pegaXSE(j))/2.0; 
            ponto2Y = (pegaYSE(j) + pegaYID(j))/2.0;


            // Calcula distancia entre os pontos
            dist = sqrt((ponto1X - ponto2X)*(ponto1X - ponto2X) + (ponto1Y - ponto2Y)*(ponto1Y - ponto2Y));


            // A primeira distância calculada "é a menor".
            if (i == 0 && j == 1)
            {
                menor_dist = dist;

                // Armazenar os índices dos retângulos com menor distância
                id1 = i;
                id2 = j;
            }
            else
            {
                // Se a distancia entre os retangulos for zero, não precisa comparar nenhuma outra distância.
                if (dist == 0)
                {
                    menor_dist = dist;
                    id1 = i;
                    id2 = j;
                    j = n_retangulos;
                    i = n_retangulos;
                }

                // Se a distância calculada for menor que menor_dist, atualiza a variável da menor distancia e dos
                // índices dos retangulos
                else if (dist < menor_dist)
                {
                    menor_dist = dist;
                    id1 = i;
                    id2 = j;
                }
            }
        }
    }

    // Operação para "jogar" o menor índice 16 bits para a esquerda, depois somar o maior índice.
    combina_id = (id1 << 16) + id2;

    return combina_id;
}

/*============================================================================*/
