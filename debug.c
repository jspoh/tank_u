#include "cprocessing.h"
#include <stdio.h>

extern CP_Image dropboxImg;
extern CP_Image gameBg;
extern CP_Image rapidFire;
extern CP_Image bigBullet;
extern CP_Image shotGun;
extern CP_Image menuBg;
extern CP_Image logo;

extern CP_Image winnerImage[2];
extern CP_Image treeImgs[2];
extern CP_Image creditsImgs[2];
extern CP_Image helpImgs[2];


void checkMem(void) {
  puts("\nImage memory leaks:\n");
  printf("dropboxImg memory freed: %d\n", dropboxImg == NULL);
  printf("gameBg memory freed: %d\n", gameBg == NULL);
  printf("rapidFire memory freed: %d\n", rapidFire == NULL);
  printf("bigBullet memory freed: %d\n", bigBullet == NULL);
  printf("shotGun memory freed: %d\n", shotGun == NULL);
  printf("menuBg memory freed: %d\n", menuBg == NULL);
  printf("logo memory freed: %d\n", logo == NULL);
  
  for (int i=0; i<2; i++) {
    printf("winnerImage[%d] memory freed: %d\n", i, winnerImage[i] == NULL);
  }

  for (int i=0; i<2; i++) {
    printf("treeImgs[%d] memory freed: %d\n", i, treeImgs[i] == NULL);
  }

  for (int i=0; i<2; i++) {
    printf("creditsImgs[%d] memory freed: %d\n", i, creditsImgs[i] == NULL);
  }

  for (int i=0; i<2; i++) {
    printf("helpImgs[%d] memory freed: %d\n", i, helpImgs[i] == NULL);
  }
}