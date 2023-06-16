#include "trabalho3.h"

int count = 0;

int contaVeiculos (Imagem3C* img, Imagem3C* bg, int contagem [N_TIPOS_DE_VEICULOS]) {
  Imagem3C* test;
  test = criaImagem3C(bg->largura, bg->altura);

  for (int i = 0; i < bg->altura; i++) {
    for (int j = 0; j < bg->largura; j++) {
      test->dados[0][i][j] = abs(bg->dados[0][i][j] - img->dados[0][i][j]) < 50 ? 0 : abs(bg->dados[0][i][j] - img->dados[0][i][j]);
      test->dados[1][i][j] = abs(bg->dados[1][i][j] - img->dados[1][i][j]) < 50 ? 0 : abs(bg->dados[1][i][j] - img->dados[1][i][j]);
      test->dados[2][i][j] = abs(bg->dados[2][i][j] - img->dados[2][i][j]) < 50 ? 0 : abs(bg->dados[2][i][j] - img->dados[2][i][j]);
    }
  }

  char fileName[20];
  sprintf(fileName, "test%d.bmp", count);

  salvaImagem3C(test, fileName);
  count++;
}
