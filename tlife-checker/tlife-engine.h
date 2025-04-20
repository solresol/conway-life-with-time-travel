#ifndef TLIFE_ENGINE_H
#define TLIFE_ENGINE_H


extern const int min_temporal_neighbours_to_survive;
extern const int max_temporal_neighbours_to_survive;
extern const int grid_size;
extern const int number_of_cells;
extern const int totally_full_grid;

typedef int SEASON_GRID;
typedef short GRID_POSITION;



int is_alive(const SEASON_GRID sg,const GRID_POSITION gp);
SEASON_GRID set_cell(const SEASON_GRID sg,const GRID_POSITION gp,int state);

int neighbour_count(const SEASON_GRID sg, const GRID_POSITION gp);

SEASON_GRID make_consistent_season(const SEASON_GRID last_season,
				   const SEASON_GRID next_season);


int current_season_is_consistent(const SEASON_GRID last_season,
				 const SEASON_GRID current_season,
				 const SEASON_GRID next_season);

char display_cell(const SEASON_GRID sg,const GRID_POSITION gp);

void display_row(FILE *outstream, const SEASON_GRID sg,const int row);

SEASON_GRID random_season(void);

void display_four_seasons(const SEASON_GRID season1,
			  const SEASON_GRID season2,
			  const SEASON_GRID season3,
			  const SEASON_GRID season4);


SEASON_GRID rotate_season_clockwise(const SEASON_GRID);
SEASON_GRID flip_season_vertical(const SEASON_GRID);
SEASON_GRID flip_season_horizontal(const SEASON_GRID);

#endif
