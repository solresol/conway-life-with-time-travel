#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "tlife-engine.h"

int main (int argc, char* argv[]) {
  struct timeval t;
  const SEASON_GRID totally_full_grid = (1 << 25) - 1;
  SEASON_GRID season1;
  SEASON_GRID season2;
  SEASON_GRID season3;
  SEASON_GRID season4;
  gettimeofday(&t,NULL);
  srand(((t.tv_sec % 1000) * 1000000) + t.tv_usec);
    /* probably good enough random for me */
  season1 = random_season();
  season4 = random_season();
  for(season3=0;season3<=totally_full_grid;season3++) {
      /* if (season3 % 256 == 0) { printf("%d\r",season3); } */
    season2 = make_consistent_season(season1,season3);
    if (current_season_is_consistent(season2,season3,season4)) {
      display_four_seasons(season1,season2,season3,season4);
     }
  }
}
