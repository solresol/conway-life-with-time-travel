#include <stdio.h>
#include <stdlib.h>

#include "tlife-engine.h"
  /* But actually link with tlife3-engine.h */

int main (int argc, char * argv[]) {
  SEASON_GRID season1;
  SEASON_GRID season2;
  SEASON_GRID season3;

  for(season1=0;season1<=totally_full_grid;season1++) {
    for(season3=0;season3<=totally_full_grid;season3++) {
    season2 = make_consistent_season(season1,season3);
    printf("%d,%d,%d\n",(int) season1, (int) season2, (int) season3); }
  }
  return 0;
}
