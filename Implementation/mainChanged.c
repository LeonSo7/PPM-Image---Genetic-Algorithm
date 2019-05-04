#include "a4.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char **argv){
   //Process input parameters
  if (argc!=6)
    {
      printf("Usage ./evolve in_file out_file num_gen p_size rate\n");
      return 1;
    }

  const char *input_file = argv[1];
  const char *output_file = argv[2];

  int num_generations = atoi(argv[3]);
  int population_size = atoi(argv[4]);

  double mutation_rate = atof(argv[5]);
  // Read image.
  PPM_IMAGE *goal = read_ppm(input_file);
  printf("\nFile %s:\n %d %d, max color %d\n",
		  input_file, goal->width, goal->height, goal->max_color);
  // Compute image
  PPM_IMAGE *new_image = evolve_image(goal, num_generations, population_size, mutation_rate);

  // Write image
  write_ppm(output_file, new_image);
//  // Free memory
//  free_image(goal);
//  free_image(new_image);

  return (0);
}

// int main(){
//	int size;
//	int tempB, tempG, tempH, tempMax, tempR, tempW;
//	PPM_IMAGE * imageFile;
//	FILE * f = fopen("mcmaster.ppm", "r"); //Pointer for reading file
//
//	//Store width and height
//	fseek(f, 2, SEEK_SET);
//	fscanf(f, "%d %d", &tempW, &tempH);
//	printf("%d %d", tempW, tempH);
//
//	imageFile -> width = tempW;
//	imageFile -> height = tempH;
//	printf("%d", imageFile->width);
//
//	//Store max value for color
//	fscanf(f, "%d", &tempMax);
//	imageFile -> max_color = tempMax;
//
//	printf("%d\n", tempMax);
//
//	size = tempW * tempH;
//
//	PIXEL pixel [size];
//	for (int col = 0; col < tempW; col ++){
//		for (int row = 0; row < tempH; row ++){
//			fscanf(f, "%d ", &tempR);
//			pixel[col*size+row].r = tempR;
//
//			fscanf(f, "%d ", &tempB);
//			pixel[col*size+row].b = tempB;
//
//			fscanf(f, "%d", &tempG);
//			pixel[col*size+row].g = tempG;
//
//		}
//	}
//
//	imageFile -> data = pixel;
//
//
//	fclose(f); //Closing file
//
//	return 0;
//}
