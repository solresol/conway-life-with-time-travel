#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "tlife-engine.h"

const int min_temporal_neighbours_to_survive = 5;
const int max_temporal_neighbours_to_survive = 6;

  /* A 5x5 grid is encoded as bit positions in an int like this:
    12 13 14 15 16
    11  2  3  4 17
    10  1  0  5 18
    9   8  7  6 19
    24 23 22 21 20

     So 25 means
     .  .  .  .  .
     .  .  X  X  .
     .  .  X  .  .
     .  .  .  .  .
     .  .  .  .  .
*/

int is_alive(const SEASON_GRID sg,const GRID_POSITION gp) {
  return (sg >> gp) % 2;
}

static int eight_neighbour_count(const SEASON_GRID sg,
				 const GRID_POSITION gp1,
				 const GRID_POSITION gp2,
				 const GRID_POSITION gp3,
				 const GRID_POSITION gp4,
				 const GRID_POSITION gp5,
				 const GRID_POSITION gp6,
				 const GRID_POSITION gp7,
				 const GRID_POSITION gp8
			       ) {
  return is_alive(sg,gp1)  + is_alive(sg,gp2) + is_alive(sg,gp3)  + is_alive(sg,gp4)
    + is_alive(sg,gp5) + is_alive(sg,gp6)   + is_alive(sg,gp7) + is_alive(sg,gp8);
}

static int five_neighbour_count(const SEASON_GRID sg,
				const GRID_POSITION gp1,
				const GRID_POSITION gp2,
				const GRID_POSITION gp3,
				const GRID_POSITION gp4,
				const GRID_POSITION gp5
				) {
  return is_alive(sg,gp1)  + is_alive(sg,gp2) + is_alive(sg,gp3)  + is_alive(sg,gp4) + is_alive(sg,gp5);
}

static int three_neighbour_count(const SEASON_GRID sg,
				 const GRID_POSITION gp1,
				 const GRID_POSITION gp2,
				 const GRID_POSITION gp3
				) {
  return is_alive(sg,gp1)  + is_alive(sg,gp2) + is_alive(sg,gp3);
}


int neighbour_count(const SEASON_GRID sg, const GRID_POSITION gp) {
  switch (gp) {
  case 0: return eight_neighbour_count(sg,1,2,3,4,5,6,7,8);
  case 1: return eight_neighbour_count(sg,11,2,3,10,0,9,8,7);
  case 2: return eight_neighbour_count(sg,12,13,14,11,3,10,1,0);
  case 3: return eight_neighbour_count(sg,13,14,15,2,4,1,0,5);
  case 4: return eight_neighbour_count(sg,14,15,16,3,17,0,5,18);
  case 5: return eight_neighbour_count(sg,3,4,17,0,18,7,6,19);
  case 6: return eight_neighbour_count(sg,0,5,18,7,19,22,21,20);
  case 7: return eight_neighbour_count(sg,1,0,5,8,6,23,22,21);
  case 8: return eight_neighbour_count(sg,10,1,0,9,7,24,23,22);
  case 9: return five_neighbour_count(sg,10,1,8,23,24);
  case 10: return five_neighbour_count(sg,11,2,1,9,8);
  case 11: return five_neighbour_count(sg,12,13,2,10,1);
  case 12: return three_neighbour_count(sg,11,13,2);
  case 13: return five_neighbour_count(sg,12,14,11,2,3);
  case 14: return five_neighbour_count(sg,13,15,2,3,4);
  case 15: return five_neighbour_count(sg,14,16,3,4,17);
  case 16: return three_neighbour_count(sg,15,4,17);
  case 17: return five_neighbour_count(sg,15,16,4,5,18);
  case 18: return five_neighbour_count(sg,15,16,4,5,18);
  case 19: return five_neighbour_count(sg,5,18,6,21,20);
  case 20: return three_neighbour_count(sg,6,19,21);
  case 21: return five_neighbour_count(sg,7,6,19,22,20);
  case 22: return five_neighbour_count(sg,6,7,8,23,21);
  case 23: return five_neighbour_count(sg,9,8,7,24,22);
  case 24: return three_neighbour_count(sg,9,8,23);
  }
  fprintf(stderr,"Asked to retrieve neighbour count of %d\n",gp);
  exit(3);
}

SEASON_GRID make_consistent_season(const SEASON_GRID last_season, const SEASON_GRID next_season) {
  SEASON_GRID current_season = 0;
  GRID_POSITION gp;
  int neighbours;
  for(gp=0;gp<25;gp++) {
    neighbours = neighbour_count(last_season,gp) + neighbour_count(next_season,gp);
    if (neighbours >= min_temporal_neighbours_to_survive &&
	neighbours <= max_temporal_neighbours_to_survive) {
      current_season |= (1 << gp);
    }
  }
  return current_season;
}

int current_season_is_consistent(const SEASON_GRID last_season,
				 const SEASON_GRID current_season,
				 const SEASON_GRID next_season) {
  GRID_POSITION gp;
  int neighbours;
  int alive;

  for(gp=0;gp<25;gp++) {
    alive = is_alive(current_season,gp);
    neighbours = neighbour_count(last_season,gp) + neighbour_count(next_season,gp);
    if (neighbours >= min_temporal_neighbours_to_survive &&
	neighbours <= max_temporal_neighbours_to_survive) {
      if (!alive) { return 0; }
    } else {
      if (alive) { return 0; }
    }
  }
  return 1;
}


char display_cell(const SEASON_GRID sg,const GRID_POSITION gp) { return is_alive(sg,gp) ? 'X' : '.'; }
static void display_cells(FILE *outstream,
			  const SEASON_GRID sg,
			  const GRID_POSITION gp1,
			  const GRID_POSITION gp2,
			  const GRID_POSITION gp3,
			  const GRID_POSITION gp4,
			  const GRID_POSITION gp5) {
  fprintf(outstream,"%c %c %c %c %c",
	  display_cell(sg,gp1),
	  display_cell(sg,gp2),
	  display_cell(sg,gp3),
	  display_cell(sg,gp4),
	  display_cell(sg,gp5)
	  );
}

  /*
    12 13 14 15 16
    11  2  3  4 17
    10  1  0  5 18
    9   8  7  6 19
    24 23 22 21 20
  */

void display_row(FILE *outstream, const SEASON_GRID sg,const int row) {
  switch (row) {
  case 0: display_cells(outstream,sg,12,13,14,15,16); return;
  case 1: display_cells(outstream,sg,11,2,3,4,17); return;
  case 2: display_cells(outstream,sg,10,1,0,5,18); return;
  case 3: display_cells(outstream,sg,9,8,7,6,19); return;
  case 4: display_cells(outstream,sg,24,23,22,21,20); return;
  }
  fprintf(stderr,"Asked to display row %d\n",row);
  exit(3);
}


SEASON_GRID random_season(void) {
  int i;
  SEASON_GRID answer = 0;
  for(i=0;i<25;i++) {
      /* make it not too dense */
    if (rand() % 16 <= 5) { answer |= (1 << i); }
  }
  return answer;
}

void display_four_seasons(const SEASON_GRID season1,
			  const SEASON_GRID season2,
			  const SEASON_GRID season3,
			  const SEASON_GRID season4) {
  int i;
  for(i=0;i<5;i++) {
    display_row(stdout,season1,i);
    printf("   ");
    display_row(stdout,season2,i);
    printf("   ");
    display_row(stdout,season3,i);
    printf("   ");
    display_row(stdout,season4,i);
    printf("\n");
  }
  printf("%d, %d, %d, %d\n",
	 (int) season1,
	 (int) season2,
	 (int) season3,
	 (int) season4);

  printf("\n");
}

