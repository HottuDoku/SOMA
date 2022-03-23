#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* test1 check -
 * test2 check -
 * test3 check -
 * test4 check -
 * test5 check -
 * test6 check -
**/

// Print entire matrix
void printMatrix(int W, int H, int matrix_p[W][H]){
	for(int i = 0; i < W; i++){
    	for(int j = 0; j < H; j++){
    		printf("%3d" , matrix_p[i][j]);
    	}
    	printf("\n");
    }
}

// Print color count
void printColorsCount(int colors[256][2]){
	printf("%3d:%5d\n", colors[0][0], colors[0][1]);
	for(int i = 1; i < 256; i++){
		if(i == 0){

		}
    	if(colors[i][1] > 0){
    		printf("%3d:%5d\n", colors[i][0], colors[i][1]);
    	}
    }
    printf("_________\n");
}

void rectangle(int W, int H, int matrix[W][H], int colors[256][2], int y1, int x1, int y2, int x2, int color){
	for(int i = y1; i <= y2; i++){
		for(int j = x1; j <= x2; j++){

			// Skip out of bounds
			if(i >= W || j >= H || i < 0 || j < 0){
				break;
			}

			// Checking color
			for(int k = 0; k < 256; k++){
				if(matrix[i][j] == colors[k][0]){
					colors[k][1]--;
					break;
				}
			}

			// Color the pixel
			matrix[i][j] = color;
			colors[color][1]++;
		}
	}
}

void hollowTangle(int W, int H, int matrix[W][H], int colors[256][2], int y1, int x1, int y2, int x2, int line, int color){
	for(int l = 0; l < line; l++){
		for(int i = y1; i <= y2; i++){
			for(int j = x1; j <= x2; j++){

				// Skip out of bounds
				if(i >= W || j >= H || i < 0 || j < 0){
					continue;
				}

				// Paint the edges
				if(i == y1 || i == y2 || j == x1 || j == x2){
					for(int k = 0; k < 256; k++){
						if(matrix[i][j] == colors[k][0]){
							colors[k][1]--;
							break;
						}
					}
					matrix[i][j] = color;
					colors[color][1]++;
				}
			}
		}
		// Line width => go deeper towards the center
		y1++;
		x1++;
		y2--;
		x2--;
	}
}

int floodFill(int W, int H, int matrix[W][H], int colors[256][2], int y, int x, int color, int overwrite){
	// If the color is the same the color from the first call, paint the pixel
	if(matrix[y][x] == overwrite){
		for(int k = 0; k < 256; k++){
			if(matrix[y][x] == colors[k][0]){
				colors[k][1]--;
				break;
			}
		}
		matrix[y][x] = color;
		colors[color][1]++;
	}else{
		return 0;
	}

	// Out of bounds check + recursion for 4 way flood fill
	if(x - 1 < 0){
	}else{
	floodFill(W, H, matrix, colors, y, x-1, color, overwrite);
	}

	if(y - 1 < 0){	
	}else{
	floodFill(W, H, matrix, colors, y-1, x, color, overwrite);
	}

	if(x + 1 >= H){
	}else{
	floodFill(W, H, matrix, colors, y, x+1, color, overwrite);
	}

	if(y + 1 >= W){	
	}else{
	floodFill(W, H, matrix, colors, y+1, x, color, overwrite);
	}
	return 0;
}

// Returns color of desided pixel
int pixelColor(int W, int H, int matrix[W][H], int y, int x){
	int color = matrix[x][y];
	return color;
}

int main(){
    int x, y, colors[256][2];
    for(int i = 0; i < 256; i++){ // initialize array for colors
    	colors[i][0] = i;
    	colors[i][1] = 0;
    }

    char command;
    int cycle = 1;

    scanf("%d %d", &x, &y);

    // Initialize matrix
    int matrix[x][y];
    colors[0][1] = x * y;

    for(int i = 0; i < x; i++){
    	for(int j = 0; j < y; j++){
    		matrix[i][j] = 0;
    	}
    }

    scanf("%c", &command);

    while(cycle){
    	int arg[6] = {0};
    	switch(command){
    		case 'R':					//	   y1		x1		 y2		  x2	Color
    			scanf("%d %d %d %d %d", &arg[0], &arg[1], &arg[2], &arg[3], &arg[4]);
    			
       			if(arg[0] > arg[2]){
    				int tmp = arg[0];
    				arg[0] = arg[2];
    				arg[2] = tmp;
    			}

    			if(arg[1] > arg[3]){
    				int tmp = arg[1];
    				arg[1] = arg[3];
    				arg[3] = tmp;
    			}

    			rectangle(x, y, matrix, colors, arg[0], arg[1], arg[2], arg[3], arg[4]);
    			break;

    		case 'H': // Hollow Rectangle		Y1 		 X1 	  Y2	  X2	LineSize   Color
	    		scanf("%d %d %d %d %d %d", &arg[0], &arg[1], &arg[2], &arg[3], &arg[4], &arg[5]);
	    		if(arg[4] <= 0){
	    			break;
	    		}

	    		if(arg[0] > arg[2]){
	    			int tmp = arg[0];
	    			arg[0] = arg[2];
	    			arg[2] = tmp;
	    		}

	    		if(arg[1] > arg[3]){
	    			int tmp = arg[1];
	    			arg[1] = arg[3];
	    			arg[3] = tmp;
	    		}

	    		hollowTangle(x, y, matrix, colors, arg[0], arg[1], arg[2], arg[3], arg[4], arg[5]);
	    		break;

	    	case 'F': // Flood fill	  Y1	   X1	  Color
	    		scanf("%d %d %d", &arg[0], &arg[1], &arg[2]);
	    		int color = pixelColor(x, y, matrix, arg[0], arg[1]);
	    		floodFill(x, y, matrix, colors, arg[0], arg[1], arg[2], color);
	    		break;

	    	case 'E': // End
	    		//printMatrix(x, y, matrix); // Uncomment to print the matrix
	    		printColorsCount(colors);
	    		cycle = 0;
	    		return 0;
    	}
    	scanf("%c", &command);
    }
    return 0;
}
