/* File name: population.c
 * Author: Leon So
 * Date: 2017-11-28
 * MacID: sol4
 * Student No.: 400127468
 * Course: 2S03 - 2018
 */

#include "a4.h"
#include <stdio.h>
#include <stdlib.h>

PIXEL *generate_random_image(int width, int height, int max_color){
	int size = width * height;
	PIXEL * randImage;
	randImage = (PIXEL *) malloc(size*sizeof(PIXEL));

	//Generate random rbg values and array of pixels
	for (int row = 0; row < height; row ++){
		for (int col = 0; col < width; col ++){
			randImage[row*width+col].r = rand() % (max_color + 1);
			 randImage[row*width+col].g = rand() % (max_color + 1);
			 randImage[row*width+col].b = rand() % (max_color + 1);
		}
	}
	return randImage;
}

Individual *generate_population(int population_size, int width, int height, int max_color){

	Individual * population;
	population = (Individual *) malloc(population_size*sizeof(Individual));

	for (int popIndex = 0; popIndex < population_size; popIndex++){
		population[popIndex].image.width = width;
		population[popIndex].image.height = height;
		population[popIndex].image.max_color = max_color;
		population[popIndex].image.data = generate_random_image(width, height, max_color);
	}


	return population;

}
