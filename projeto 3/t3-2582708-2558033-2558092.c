#include "trabalho3.h"
#include <math.h>

#define NUM_FAIXAS 8
#define TOLERANCIA 35
#define ALTURA_MINIMA 3
#define COMPRIMENTO_MINIMO 45
#define COMPRIMENTO_MOTO 72
#define COMPRIMENTO_MEDIO 122
#define COMPRIMENTO_LONGO 302
#define SATURACAO_MINIMA 50

void classificaVeiculo(int comprimento, int contagem[N_TIPOS_DE_VEICULOS]) {
  if (comprimento <= COMPRIMENTO_MOTO)
    contagem[0]++;
  else if (comprimento <= COMPRIMENTO_MEDIO)
    contagem[1]++;
  else if (comprimento <= COMPRIMENTO_LONGO)
    contagem[2]++;
  else
    contagem[3]++;
}

float calcularSaturacao(int r, int g, int b) {
  float max = fmax(r, fmax(g, b));
  float min = fmin(r, fmin(g, b));

  if (max == 0)
    return 0;

  float delta = max - min;
  float saturation = delta / max;

  return saturation;
}

void removeFundo(Imagem3C* img, Imagem3C* bg) {
  int i, j;

  for (i = 0; i < bg->altura; i++) {
    for (j = 0; j < bg->largura; j++) {
      int r_img = img->dados[0][i][j];
      int g_img = img->dados[1][i][j];
      int b_img = img->dados[2][i][j];

      int r_bg = bg->dados[0][i][j];
      int g_bg = bg->dados[1][i][j];
      int b_bg = bg->dados[2][i][j];

      float saturation = calcularSaturacao(r_img, g_img, b_img);

      if (abs(r_img - r_bg) <= TOLERANCIA &&
          abs(g_img - g_bg) <= TOLERANCIA &&
          abs(b_img - b_bg) <= TOLERANCIA &&
          saturation >= SATURACAO_MINIMA) {
        img->dados[0][i][j] = 0;
        img->dados[1][i][j] = 0;
        img->dados[2][i][j] = 0;
      }
    }
  }
}

void verificaVeiculosFaixa(Imagem3C* img, int contagem[N_TIPOS_DE_VEICULOS], int* total_veiculos) {
  int comprimento = 0, contagem_pixels;
  int i, j, k, faixa, max_faixa;

  faixa = img->altura / NUM_FAIXAS;
  max_faixa = faixa;

  for (i = 0; max_faixa < img->altura; i += faixa, max_faixa += faixa) {
    for (j = 0; j < img->largura; j++) {
      contagem_pixels = 0;

      for (k = i; k < max_faixa && contagem_pixels < ALTURA_MINIMA; k++) {
        if (img->dados[0][k][j] || img->dados[1][k][j] || img->dados[2][k][j])
          contagem_pixels++;
      }

      if (contagem_pixels == ALTURA_MINIMA)
        comprimento++;
      else {
        if (comprimento > COMPRIMENTO_MINIMO) {
          *total_veiculos += 1;
          classificaVeiculo(comprimento, contagem);
        }
        comprimento = 0;
      }
    }
  }
}

int contaVeiculos(Imagem3C* img, Imagem3C* bg, int contagem[N_TIPOS_DE_VEICULOS]) {
  int total_veiculos = 0, i;

  for (i = 0; i < N_TIPOS_DE_VEICULOS; i++)
    contagem[i] = 0;

  removeFundo(img, bg);
  verificaVeiculosFaixa(img, contagem, &total_veiculos);

  return total_veiculos;
}
