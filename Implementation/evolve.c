/* File name: evolve.c
 * Author: Leon So
 * Date: 2017-11-28
 * MacID: sol4
 * Student No.: 400127468
 * Course: 2S03 - 2018
 */

#include "a4.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int compare (const void * a, const void * b) {
	Individual *individuala = (Individual *)a;
	Individual *individualb = (Individual *)b;
	return ( individuala->fitness - individualb -> fitness );
}

PPM_IMAGE * evolve_image ( const PPM_IMAGE * image , int num_generations , int population_size , double rate ){
	PPM_IMAGE * newImage = malloc(sizeof(PPM_IMAGE));
	newImage -> width = image -> width;
	newImage -> height = image -> height;
	newImage -> max_color = image -> max_color;
	PIXEL * pixels = (PIXEL*)malloc(newImage -> width*newImage -> height*sizeof(PIXEL));
	Individual * population = generate_population(population_size, newImage->width, newImage->height, newImage->max_color);
	comp_fitness_population(image->data, population, population_size);

	qsort (population, population_size, sizeof(Individual), compare);

	//Generating generation

    for (int gen = 1; gen <= num_generations; gen++){
    	crossover(population, population_size);
    	mutate_population(population, population_size, rate);
        comp_fitness_population(image -> data, population, population_size);
    	qsort (population, population_size, sizeof(Individual), compare);
    }

    //Copying fittest individual into pixel array for newImage
	for (int row = 0; row < image->height; row ++){
		for (int col = 0; col < image->width; col ++){
			pixels[row*image->width+col].r = population[0].image.data[row*image->width+col].r;
			pixels[row*image->width+col].b = population[0].image.data[row*image->width+col].b;
			pixels[row*image->width+col].g = population[0].image.data[row*image->width+col].g;
		}
	}

	newImage->data = pixels;

    for(int popIndex = population_size - 1; popIndex >= 0; popIndex--){
		free(population[popIndex].image.data);
    }

    free(population);
	return newImage;
}

void free_image (PPM_IMAGE *p ){
	free(p->data);
	free(p);
}
