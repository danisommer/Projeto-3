/*============================================================================*/
/* CSF13 - 2023-1 - TRABALHO 3                                                */
/*----------------------------------------------------------------------------*/
/* Daniel Zaki Sommer - 2582708                                               */
/* Henrique dos Santos Pagliarini  - 2558033                                  */
/* Matheus Dias - 2558092                                                     */
/*============================================================================*/
/** Arquivo de entrega para o 3o trabalho da disciplina CSF13 (Fundamentos de
 * Programa��o 1), 2023-1, Universidade Tecnol�gica Federal do Paran�. */
/*============================================================================*/

#include "trabalho3.h"
#include <math.h>

/*============================================================================*/

#define NUM_FAIXAS 8
#define TOLERANCIA 35
#define ALTURA_MINIMA 3

#define COMPRIMENTO_MINIMO 45
#define COMPRIMENTO_MOTO 72
#define COMPRIMENTO_MEDIO 122
#define COMPRIMENTO_LONGO 302

/*============================================================================*/
/** Classifica um ve�culo de acordo com seu comprimento.
 *
 * Par�metros: int comprimento: o comprimento do ve�culo a ser analisado.
 *             int contagem[N_TIPOS_DE_VEICULOS]: vetor para contagem dos tipos de ve�culos.
 *
 * Valor de Retorno: NENHUM (os dados s�o escritos no vetor) */

void classificaVeiculo(int comprimento, int contagem[N_TIPOS_DE_VEICULOS]) {
  if (comprimento <= COMPRIMENTO_MOTO)
    contagem[0]++;  // Incrementa a contagem de motos.
  else if (comprimento <= COMPRIMENTO_MEDIO)
    contagem[1]++;  // Incrementa a contagem de ve�culos m�dios.
  else if (comprimento <= COMPRIMENTO_LONGO)
    contagem[2]++;  // Incrementa a contagem de ve�culos longos.
  else
    contagem[3]++;  // Incrementa a contagem de ve�culos muito longos.
}

/*----------------------------------------------------------------------------*/
/** Remove o fundo da imagem comparando-a com uma imagem de fundo.
 *
 * Par�metros: Imagem3C* img: ponteiro para a imagem a ser modificada.
 *             Imagem3C* bg: ponteiro para a imagem de fundo a ser comparada.
 *
 * Valor de Retorno: NENHUM (os dados s�o modificados diretamente na imagem de entrada) */

void removeFundo(Imagem3C* img, Imagem3C* bg) {
  int i, j;

  for (i = 0; i < bg->altura; i++) {
    for (j = 0; j < bg->largura; j++) {
      // Compara a diferen�a absoluta dos canais de cor de cada pixel com a toler�ncia definida.
      if (abs(bg->dados[0][i][j] - img->dados[0][i][j]) <= TOLERANCIA &&
          abs(bg->dados[1][i][j] - img->dados[1][i][j]) <= TOLERANCIA &&
          abs(bg->dados[2][i][j] - img->dados[2][i][j]) <= TOLERANCIA) {
            // Define os canais de cor do pixel como zero para remov�-lo.
            img->dados[0][i][j] = 0;
            img->dados[1][i][j] = 0;
            img->dados[2][i][j] = 0;
      }
    }
  }
}

/*----------------------------------------------------------------------------*/
/** Verifica os ve�culos presentes em cada faixa da imagem.
 *
 * Par�metros: Imagem3C* img: ponteiro para a imagem a ser analisada.
 *             int contagem[N_TIPOS_DE_VEICULOS]: vetor para contagem dos tipos de ve�culos.
 *             int* total_veiculos: ponteiro para a vari�vel que armazenar� o total de ve�culos.
 *
 * Valor de Retorno: NENHUM (os dados s�o escritos nos vetores e vari�vel de sa�da) */

void verificaVeiculosFaixa(Imagem3C* img, int contagem[N_TIPOS_DE_VEICULOS], int* total_veiculos) {
  int comprimento = 0, contagem_pixels;
  int i, j, k, faixa, max_faixa;

  faixa = img->altura / NUM_FAIXAS;  // Calcula a altura de cada faixa.
  max_faixa = faixa;

  for (i = 0; max_faixa < img->altura; i += faixa, max_faixa += faixa) {
    for (j = 0; j < img->largura; j++) {
      contagem_pixels = 0;

      for (k = i; k < max_faixa && contagem_pixels < ALTURA_MINIMA; k++) {
        if (img->dados[0][k][j] || img->dados[1][k][j] || img->dados[2][k][j])
          contagem_pixels++;  // Conta a quantidade de pixels diferentes de preto na faixa.
      }

      if (contagem_pixels == ALTURA_MINIMA)
        comprimento++;  // Incrementa o comprimento do ve�culo.
      else {
        if (comprimento > COMPRIMENTO_MINIMO) {
          *total_veiculos += 1;  // Incrementa o total de ve�culos.
          classificaVeiculo(comprimento, contagem);
        }
        comprimento = 0;  // Reinicia o comprimento para o pr�ximo ve�culo.
      }

    }
  }
}

/*----------------------------------------------------------------------------*/
/** Conta e classifica os ve�culos presentes na imagem.
 *
 * Par�metros: Imagem3C* img: ponteiro para a imagem a ser analisada.
 *             Imagem3C* bg: ponteiro para a imagem de fundo a ser comparada.
 *             int contagem[N_TIPOS_DE_VEICULOS]: vetor para contagem dos tipos de ve�culos.
 *
 * Valor de Retorno: o n�mero total de ve�culos encontrados. */

int contaVeiculos(Imagem3C* img, Imagem3C* bg, int contagem[N_TIPOS_DE_VEICULOS]) {
  int total_veiculos = 0, i;

  for (i = 0; i < N_TIPOS_DE_VEICULOS; i++)
    contagem[i] = 0;

  removeFundo(img, bg);
  verificaVeiculosFaixa(img, contagem, &total_veiculos);

  return total_veiculos;
}

/*============================================================================*/
