#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "tlife-engine.h"

int main (int argc, char* argv[]) {
  const SEASON_GRID totally_full_grid = (1 << 25) - 1;
  SEASON_GRID season1 = -1;
  SEASON_GRID season2 = -1;
  SEASON_GRID season3;
  char *endptr;

  if (argc != 3) {
    fprintf(stderr,"Usage: %s gridint1 gridint2\n",argv[0]);
    exit(1);
  }
  season1 = (SEASON_GRID) strtol(argv[1],&endptr,10);
  if (*endptr != '\0') {
    fprintf(stderr,"Did not understand argument 1: %s\n",argv[1]);
    exit(1);
  }

  season3 = (SEASON_GRID) strtol(argv[2],&endptr,10);
  if (*endptr != '\0') {
    fprintf(stderr,"Did not understand argument 2: %s\n",argv[2]);
    exit(1);
  }

  season2 = make_consistent_season(season1,season3);
  printf("%d\n",(int) season2);
}
