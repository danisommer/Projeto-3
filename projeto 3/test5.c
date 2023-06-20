#include "trabalho3.h"
#include "imagem.h"

#define TAMMIN 40
#define MOTO 80
#define CARRO 120
#define LONGO 290
#define TRESHOLD 38

int fileCount = 0;

void verificaTamanho (int tamanho, int *contagem) {
  if (tamanho <= MOTO)
    contagem[0]++;
  else if (tamanho <= CARRO)
    contagem[1]++;
  else if (tamanho <= LONGO)
    contagem[2]++;
  else
    contagem[3]++;
}

int contaVeiculos (Imagem3C* img, Imagem3C* bg, int contagem [N_TIPOS_DE_VEICULOS]) {
  int res = 0;

  for (int i = 0; i < 4; i++)
    contagem[i] = 0;

  char fileName[20];
  sprintf(fileName, "test%d.bmp", fileCount);

  for (int i = 0; i < bg->altura; i++) {
    for (int j = 0; j < bg->largura; j++) {
      img->dados[0][i][j] = abs(bg->dados[0][i][j] - img->dados[0][i][j]) < TRESHOLD ? 0 : abs(bg->dados[0][i][j] - img->dados[0][i][j]);
      img->dados[1][i][j] = abs(bg->dados[1][i][j] - img->dados[1][i][j]) < TRESHOLD ? 0 : abs(bg->dados[0][i][j] - img->dados[0][i][j]);
      img->dados[2][i][j] = abs(bg->dados[2][i][j] - img->dados[2][i][j]) < TRESHOLD ? 0 : abs(bg->dados[0][i][j] - img->dados[0][i][j]);
    }
  }

  int length = 0, i, k, max = 185, count, aux = 0;

  for (i = 86, max; i < 680; i += 100, max += 100) {
    //printf("k: %d, max: %d\n", k, max);
    for (int j = 0; j < bg->largura; j++) {
      count = 0;
      for (k = i; k < max; k++) {
          if (img->dados[0][k][j] || img->dados[1][k][j] || img->dados[2][k][j]) {
            count++;
          }
      }

      if (count >= 3)
        length++;
      else {
        //if (length) printf("%d\n", length);
        if (length > TAMMIN) {
          res++;
          verificaTamanho(length, contagem);
        }
        length = 0;
      }
    }
  }

  salvaImagem3C(img, fileName);
  fileCount++;

  return res;
}

