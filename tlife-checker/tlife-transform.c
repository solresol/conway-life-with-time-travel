#include <stdio.h>
#include <stdlib.h>
#include "tlife-engine.h"

int main (int argc, char* argv[]) {
  SEASON_GRID sg;
  char *endptr;
  if (argc != 3) {
    fprintf(stderr,"Usage: %s operation gridint\n",argv[0]);
    exit(1);
  }
  sg = (SEASON_GRID) strtol(argv[2],&endptr,10);
  if (*endptr != '\0') {
    fprintf(stderr,"Did not understand argument 2: %s\n",argv[1]);
    exit(1);
  }

  if (strcasecmp(argv[1],"rotate") == 0) {
    printf("%d\n",(int) (rotate_season_clockwise(sg)));
    exit(0);
  }

  if (strcasecmp(argv[1],"vertical-flip") == 0) {
    printf("%d\n",(int) (flip_season_vertical(sg)));
    exit(0);
  }

  if (strcasecmp(argv[1],"horizontal-flip") == 0) {
    printf("%d\n",(int) (flip_season_horizontal(sg)));
    exit(0);
  }

  fprintf(stderr,"Operation %s not understood, should be one of rotate, vertical-flip or horizontal-flip.",argv[1]);
  exit(1);
}
