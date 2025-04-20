#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "tlife-engine.h"

int main (int argc, char* argv[]) {
  const SEASON_GRID totally_full_grid = (1 << 25) - 1;
  SEASON_GRID season1 = -1;
  SEASON_GRID season2 = -1;
  SEASON_GRID season3;
  int show_progress = getenv("TLIFE_CONTINUE_PROGRESS") != NULL;
  int need_newline = 0;
  int do_newlines = 1;
  char *endptr;

  if (!isatty(fileno(stderr))) { show_progress = 0; }
  else {
    if (!isatty(fileno(stdout))) { do_newlines = 0; }
  }

  if (argc != 3) {
    fprintf(stderr,"Usage: %s gridint1 gridint2\n",argv[0]);
    exit(1);
  }
  season1 = (SEASON_GRID) strtol(argv[1],&endptr,10);
  if (*endptr != '\0') {
    fprintf(stderr,"Did not understand argument 1: %s\n",argv[1]);
    exit(1);
  }

  season2 = (SEASON_GRID) strtol(argv[2],&endptr,10);
  if (*endptr != '\0') {
    fprintf(stderr,"Did not understand argument 2: %s\n",argv[2]);
    exit(1);
  }

  for(season3=0;season3<=totally_full_grid;season3++) {
    if (show_progress && ((int) season3 % 3000000) == 0) {
      fprintf(stderr,"%s%.1f\r",getenv("TLIFE_CONTINUE_PROGRESS"),
	      season3 / (float) totally_full_grid);
      need_newline = do_newlines ? 1 : 0;
    }
    if (current_season_is_consistent(season1,season2,season3)) {
      if (need_newline) { fprintf(stderr,"\n");  need_newline = 0; }
      printf("%d\n",(int) season3);
     }
  }
}
