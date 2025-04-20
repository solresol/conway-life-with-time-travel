#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "tlife-engine.h"

int main (int argc, char* argv[]) {
  const SEASON_GRID totally_full_grid = (1 << 25) - 1;
  SEASON_GRID season1 = -1;
  SEASON_GRID season2;
  char *endptr;
  if (argc != 2) {
    fprintf(stderr,"Usage: %s gridint1 gridint2\n",argv[0]);
    exit(1);
  }
  season1 = (SEASON_GRID) strtol(argv[1],&endptr,10);
  if (*endptr != '\0') {
    fprintf(stderr,"Did not understand argument 1: %s\n",argv[1]);
    exit(1);
  }

  for(season2=0;season2<=totally_full_grid;season2++) {
    if (current_season_is_consistent(season1,season2,season1) &&
	current_season_is_consistent(season2,season1,season2)) {
      printf("%d\n",(int) season2);
     }
  }
}
