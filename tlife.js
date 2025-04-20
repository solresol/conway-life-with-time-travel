var square_size = 9;
var min_temporal_neighbours_to_live = 5;
var max_temporal_neighbours_to_live = 6;
var years = 5;


function populate_tables() {
    var year;
    var rownum;
    var column;
    var row;
    for(year=1;year<=years;year++) {
	var tbody = document.getElementById("YEAR"+year);
	for(rownum=1;rownum<=square_size;rownum++) {
	    row = document.createElement("TR");
	    for(column=1;column<=square_size;column++) {
		var cell = document.createElement("TD");
		var inp = document.createElement("INPUT");
		inp['type'] = "checkbox";
		inp.onclick = redraw;
		inp.id = year + "-" + column + "," + rownum;
		if (year==2 && (column==1 || column==square_size || rownum==1 || rownum==square_size)) {
		    inp.disabled = true;
		}
		cell.appendChild(inp);
		cell.onmouseover = show_count_mouseover(rownum,column,year); 
		row.appendChild(cell);
	    }
	    tbody.appendChild(row);
	}
    }
}

function show_count_mouseover(rownum,column,year) {
    return function () { show_count(rownum,column,year); }
}

function show_count(rownum,column,year) {
    var cell_info = document.getElementById("CellInfo");
    var neighbour_count;
    if (year == 1) { neighbour_count = year_neighbour_count(rownum,column,2); }
    else if (year == years) { neighbour_count = year_neighbour_count(rownum,column,years-1); }
    else {
	neighbour_count = year_neighbour_count(rownum,column,year-1) +
	    year_neighbour_count(rownum,column,year+1);
    }
    if (neighbour_count != 1) { 
	cell_info.innerText = "Year: " + year + " (" + column + "," + rownum + ") has " + 
	    neighbour_count + " neighbours visible";
    } else {
	cell_info.innerText = "Year: " + year + " (" + column + "," + rownum + ") has 1 neighbour visible";
    }
}

function year_neighbour_count(rownum,column,year) {
    var count = 0;
    if (column > 1) {
	if (rownum > 1) {
	    neighbour = document.getElementById(year + "-" + (column-1) + "," + (rownum-1));
	    if (neighbour == null) { alert("A: Can't get all neighbours for " + column + "," + rownum);}
	    if (neighbour.checked) { count ++; }
	}
	
	neighbour = document.getElementById(year + "-" + (column-1) + "," + (rownum));
	if (neighbour == null) { alert("B: Can't get all neighbours for " + column + "," + rownum);}
	if (neighbour.checked) { count ++; }

	if (rownum < square_size) {
	    neighbour = document.getElementById(year + "-" + (column-1) + "," + (rownum+1));
	    if (neighbour == null) { alert("C: Can't get all neighbours for " + column + "," + rownum);}
	    if (neighbour.checked) { count ++; }
	}
    }

    if (rownum > 1) {
	neighbour = document.getElementById(year + "-" + (column) + "," + (rownum-1));
	if (neighbour == null) { alert("D: Can't get all neighbours for " + column + "," + rownum);}
	if (neighbour.checked) { count ++; }
    }

    if (rownum < square_size) {
	neighbour = document.getElementById(year + "-" + (column) + "," + (rownum+1));
	if (neighbour == null) { alert("E: Can't get all neighbours for " + column + "," + rownum + " in year " + year);}
	if (neighbour.checked) { count ++; }
    }

    if (column < square_size) {
	if (rownum > 1) {
	    neighbour = document.getElementById(year + "-" + (column+1) + "," + (rownum-1));
	    if (neighbour == null) { alert("F: Can't get all neighbours for " + column + "," + rownum);}
	    if (neighbour.checked) { count ++; }
	}
	neighbour = document.getElementById(year + "-" + (column+1) + "," + (rownum));
	if (neighbour == null) { alert("G: Can't get all neighbours for " + column + "," + rownum);}
	if (neighbour.checked) { count ++; }

	if (rownum < square_size) {
	    neighbour = document.getElementById(year + "-" + (column+1) + "," + (rownum+1));
	    if (neighbour == null) { alert("H: Can't get all neighbours for " + column + "," + rownum);}
	    if (neighbour.checked) { count ++; }
	}
    }
    return count;
}

function redraw() {
    for(rownum=1;rownum<=square_size;rownum++) {
	for(column=1;column<=square_size;column++) {
	    me = document.getElementById("2-" + column + "," + rownum);
	    var neighbour_count = year_neighbour_count(rownum,column,1) + year_neighbour_count(rownum,column,3);
	    if (neighbour_count >= min_temporal_neighbours_to_live && 
		neighbour_count <= max_temporal_neighbours_to_live) {
		me.checked = true;
	    } else {
		me.checked = false;
	    }
	    // parent = me.parentNode;
	}
    }


    var tail_year;
    for(tail_year=3;tail_year<years;tail_year++) {
	for(rownum=1;rownum<=square_size;rownum++) {
	    for(column=1;column<=square_size;column++) {
		me = document.getElementById(tail_year + "-" + column + "," + rownum);
		var neighbour_count = year_neighbour_count(rownum,column,tail_year-1) + year_neighbour_count(rownum,column,tail_year + 1);
		var should_be_alive;
		if (neighbour_count >= min_temporal_neighbours_to_live && 
		    neighbour_count <= max_temporal_neighbours_to_live) {
		    should_be_alive = true;
		} else {
		    should_be_alive = false;
		}
		parent = me.parentNode;
		if (me.checked && should_be_alive) { parent.bgColor = "#ffffff";  }
		if (!me.checked && should_be_alive) { parent.bgColor = "#00ff00"; }
		if (me.checked && !should_be_alive) { 
		    if (neighbour_count < min_temporal_neighbours_to_live) { parent.bgColor = "#0000ff"; }
		    if (neighbour_count > max_temporal_neighbours_to_live) { parent.bgColor = "#ff0000"; }
		}
		if (!me.checked && !should_be_alive) { parent.bgColor = "#ffffff"; }
	    }
	}
    }
    recalc_summary_ints();
}



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

var relative_positions = [
    [0,0],   /* 0 */

    [-1,0],  /* 1 */
    [-1,-1],[0,-1],[1,-1],  /* 2,3,4 */
    [1,0],[1,1],   /* 5,6 */
    [0,1],[-1,1],  /* 7,8 */
    
    [-2,1],[-2,0],[-2,-1],[-2,-2],  /* 9,10,11,12 */
    [-1,-2],[0,-2],[1,-2],[2,-2],   /* 13,14,15,16 */
    [2,-1],[2,0],[2,1],[2,2],      /* 17,18,19,20 */
    [1,2],[0,2],[-1,2],[-2,2]      /* 21,22,23,24 */
    // I do need to add a few more here.
];


function recalc_summary_int(year) {
    var i;
    var x_offset;
    var y_offset;
    var x_centre = Math.floor(square_size / 2) + 1;
    var y_centre = Math.floor(square_size / 2) + 1;
    var x;
    var y;
    var answer_int = 0;
    var bit = 1;
    for(i=0;i<relative_positions.length;i++) {
	x_offset = relative_positions[i][0];
	y_offset = relative_positions[i][1];
	x = x_centre + x_offset;
	y = y_centre + y_offset;
	var cell = document.getElementById(year + "-" + x + "," + y);
	if (cell.checked) { answer_int += bit; }
	bit = bit * 2;
    }
    var intfield = document.getElementById("YEAR" + year + "INT");
    intfield.value = answer_int;
}

function recalc_summary_ints() {
    var i;
    for(i=1;i<=years;i++) { recalc_summary_int(i); }
}

function set_from_int(year) {
    var intfield = document.getElementById("YEAR" + year + "INT");
    var board_number = intfield.value;
    console.log("Working with board_number = " + board_number);
    var i;
    var x_offset;
    var y_offset;
    var x_centre = Math.floor(square_size / 2) + 1;
    var y_centre = Math.floor(square_size / 2) + 1;
    var x;
    var y;
    var answer_int = 0;
    var bit = 1;
    for(i=0;i<relative_positions.length;i++) {
	x_offset = relative_positions[i][0];
	y_offset = relative_positions[i][1];
	x = x_centre + x_offset;
	y = y_centre + y_offset;
	var cell = document.getElementById(year + "-" + x + "," + y);
	if ((board_number & bit) > 0) {
	    cell.checked = true;
	} else {
	    cell.checked = false;
	}
	bit = bit * 2;
    }
    redraw();
}