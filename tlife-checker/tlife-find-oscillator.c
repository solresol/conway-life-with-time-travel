#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "tlife-engine.h"

int main (int argc, char* argv[]) {
  const SEASON_GRID totally_full_grid = (1 << 25) - 1;
  SEASON_GRID season1 = -1;
  SEASON_GRID season2;

  for(season1=0;season1<=totally_full_grid;season1++) {
    season2=make_consistent_season(season1,season1);
    if (current_season_is_consistent(season2,season1,season2)) {
	printf("%d %d\n",(int) season1,(int) season2);
    }
  }
}
