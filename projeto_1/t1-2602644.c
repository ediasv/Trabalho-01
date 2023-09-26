/*============================================================================*/
/* ICSF13 - 2023-2 - TRABALHO 1                                               */
/*----------------------------------------------------------------------------*/
/* Eduardo Vinicius Dias                                                      */
/*============================================================================*/

#include "trabalho1.h"

/*============================================================================*/
/* Funções do trabalho. */

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
    return 0;
}

/*============================================================================*/
