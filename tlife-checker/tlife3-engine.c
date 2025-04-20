#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "tlife-engine.h"

const int min_temporal_neighbours_to_survive = 5;
const int max_temporal_neighbours_to_survive = 6;

  /* Change these three together */
const int grid_size = 3;
const int number_of_cells = 9;
const int totally_full_grid = 511;

  /* A 3x3 grid is encoded as bit positions in an int like this:
     2  3  4
     1  0  5
     8  7  6

     So 25 means
     .  X  X
     .  X  .
     .  .  .
*/

int is_alive(const SEASON_GRID sg,const GRID_POSITION gp) {
  return (sg >> gp) % 2;
}

SEASON_GRID set_cell(const SEASON_GRID sg,const GRID_POSITION gp,int state) {
   if (state) {  return (1 << gp) | sg; }
   return ( totally_full_grid - (1 << gp) ) & sg ;
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

  /*
     2  3  4
     1  0  5
     8  7  6
  */

int neighbour_count(const SEASON_GRID sg, const GRID_POSITION gp) {
  switch (gp) {
  case 0: return eight_neighbour_count(sg,1,2,3,4,5,6,7,8);
  case 1: return five_neighbour_count(sg,0,2,3,7,8);
  case 2: return three_neighbour_count(sg,0,1,3);
  case 3: return five_neighbour_count(sg,0,1,2,4,5);
  case 4: return three_neighbour_count(sg,0,3,5);
  case 5: return five_neighbour_count(sg,0,3,4,6,7);
  case 6: return three_neighbour_count(sg,0,5,7);
  case 7: return five_neighbour_count(sg,1,0,5,8,6);
  case 8: return three_neighbour_count(sg,1,0,7);
  }
  fprintf(stderr,"Asked to retrieve neighbour count of %d\n",gp);
  exit(3);
}

SEASON_GRID make_consistent_season(const SEASON_GRID last_season, const SEASON_GRID next_season) {
  SEASON_GRID current_season = 0;
  GRID_POSITION gp;
  int neighbours;
  for(gp=0;gp<9;gp++) {
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

  for(gp=0;gp<9;gp++) {
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
			  const GRID_POSITION gp3) {
  fprintf(outstream,"%c %c %c",
	  display_cell(sg,gp1),
	  display_cell(sg,gp2),
	  display_cell(sg,gp3)
	  );
}

  /*
      2  3  4
      1  0  5
      8  7  6
  */

void display_row(FILE *outstream, const SEASON_GRID sg,const int row) {
  switch (row) {
  case 0: display_cells(outstream,sg,2,3,4); return;
  case 1: display_cells(outstream,sg,1,0,5); return;
  case 2: display_cells(outstream,sg,8,7,6); return;
  }
  fprintf(stderr,"Asked to display row %d\n",row);
  exit(3);
}


SEASON_GRID random_season(void) {
  int i;
  SEASON_GRID answer = 0;
  for(i=0;i<9;i++) {
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
  for(i=0;i<3;i++) {
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

/*
     2  3  4           8  1  2
     1  0  5    ---->  7  0  3
     8  7  6           6  5  4
*/

SEASON_GRID rotate_season_clockwise(const SEASON_GRID s) {
  SEASON_GRID r = 0;
  r = set_cell(r,2,is_alive(s,8));
  r = set_cell(r,3,is_alive(s,1));
  r = set_cell(r,4,is_alive(s,2));
  r = set_cell(r,1,is_alive(s,7));
  r = set_cell(r,0,is_alive(s,0));
  r = set_cell(r,5,is_alive(s,3));
  r = set_cell(r,8,is_alive(s,6));
  r = set_cell(r,7,is_alive(s,5));
  r = set_cell(r,6,is_alive(s,4));
  return r;
}

SEASON_GRID flip_season_horizontal(const SEASON_GRID s) {
  SEASON_GRID r = 0;
  r = set_cell(r,2,is_alive(s,8));
  r = set_cell(r,3,is_alive(s,7));
  r = set_cell(r,4,is_alive(s,6));
  r = set_cell(r,1,is_alive(s,1));
  r = set_cell(r,0,is_alive(s,0));
  r = set_cell(r,5,is_alive(s,5));
  r = set_cell(r,8,is_alive(s,2));
  r = set_cell(r,7,is_alive(s,3));
  r = set_cell(r,6,is_alive(s,4));
  return r;
}

SEASON_GRID flip_season_vertical(const SEASON_GRID s) {
  SEASON_GRID r = 0;
  r = set_cell(r,2,is_alive(s,4));
  r = set_cell(r,3,is_alive(s,3));
  r = set_cell(r,4,is_alive(s,2));
  r = set_cell(r,1,is_alive(s,5));
  r = set_cell(r,0,is_alive(s,0));
  r = set_cell(r,5,is_alive(s,1));
  r = set_cell(r,8,is_alive(s,6));
  r = set_cell(r,7,is_alive(s,7));
  r = set_cell(r,6,is_alive(s,8));
  return r;
}


