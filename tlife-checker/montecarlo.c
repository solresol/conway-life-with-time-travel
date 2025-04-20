#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "tlife-engine.h"

int main (int argc, char* argv[]) {
  struct timeval t;
  int tried_pairs = 0;
  int ok_pairs = 0;
  const SEASON_GRID totally_full_grid = (1 << 25) - 1;
  SEASON_GRID season1;
  SEASON_GRID season2;
  SEASON_GRID season3;
  gettimeofday(&t,NULL);
  srand(((t.tv_sec % 1000) * 1000000) + t.tv_usec);
    /* probably good enough random for me */
  tried_pairs = 0;
  while (1) {
    if (tried_pairs % 100 == 0) {
	printf("%d/%d consistent\n",ok_pairs,tried_pairs);
    }
    tried_pairs++;
    season1 = random_season();
    season2 = random_season();
    for(season3=0;season3<=totally_full_grid;season3++) {
      if (current_season_is_consistent(season1,season2,season3)) {
	ok_pairs++;
	printf("%d/%d consistent\n",ok_pairs,tried_pairs);
	break;
      }
    }
  }
}
