type direction = NW | N | NE | W | O | E | SW | S | SE;;
type chrono = Past | Present | Future;;
type chronodirection = direction * chrono;;

type rulemask = chronodirection list * int * int;; 
(* first int is minimum number for the rule to fire, second int is maximum number *)

type livingness = Alive | Dead;;

type rule = rulemask * livingness;; 

type cell = Known of livingness | Unknown

type generation_grid = cell array array;;

type grid_moment = { past : generation_grid ;
                     present : generation_grid ;
                     future : generation_grid } ;;

type cell_calculator = grid_moment -> rule list -> (int * int) -> cell;;

let get_cell g (x,y) = g.(y).(x);;

let offset_direction d (x,y) = match d with
   NW -> (x-1,y+1)  | N -> (x,y+1) | NE -> (x+1,y+1)
 | W -> (x-1,y)     | O -> (x,y)   | E -> (x+1,y)
 | SW -> (x-1,y-1)  | S -> (x,y-1) | SE -> (x+1,y-1)

(* Variations for this:
   1. Instead of returning Unknown for out-of-bounds, raise an exception.
   2. Instead of returning Unknown for out-of-bounds, return a different value.
   3. Instead of returning Unknown for out-of-bounds, wrap around *)

let get_offset_cell gm (c,d) (x,y) =
  let which_grid = match c with
           Past -> gm.past
         | Present -> gm.present
         | Future -> gm.future
  and (x2,y2) = offset_direction d (x,y) 
  in if (x2 < 0 or y2 < 0) then Unknown else
  let height = Array.length which_grid
  in if y2 >= height then Unknown else
  let width = Array.length which_grid.(y2) 
  in if x2 >= width then Unknown else
    get_cell which_grid (x2,y2);;
  
let rec count_mask_matches (masklist) gm (x,y) = match masklist with 
     [] -> 0
   | cd :: tl -> 
      (match get_offset_cell gm cd (x,y) with Known Alive -> 1 | _ -> 0) +
        count_mask_matches tl gm (x,y)

let check_rulemask (masklist,min,max) gm (x,y) = 
 let c = count_mask_matches masklist gm (x,y) in
 if (c < min or c > max) then false else true;;

let h = "Hello world" in print_string h;;