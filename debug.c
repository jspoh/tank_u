/**
 * @file debug.c
 * @author POH JING SENG (jingseng.poh)
 * @brief this file is used to look for memory leaks
 * 
 * @copyright Copyright Digipen 2023
 * 
 */


#include "cprocessing.h"
#include <stdio.h>

/*images*/
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

/*sound*/
extern CP_Sound gameMusic;
extern CP_Sound titleMusic;
extern CP_Sound tankFire;
extern CP_Sound winAudio;



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

  puts("\nSound memory leaks:\n");
  printf("gameMusic memory freed: %d\n", gameMusic == NULL);
  printf("titleMusic memory freed: %d\n", titleMusic == NULL);
  printf("tankFire memory freed: %d\n", tankFire == NULL);
  printf("winAudio memory freed: %d\n", winAudio == NULL);
}