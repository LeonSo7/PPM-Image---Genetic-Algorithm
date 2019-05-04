/* File name: mutate.c
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

void mutate(Individual * individual, double rate){
	int n = individual->image.width * individual->image.height;
	int numberOfPixels = (rate/100*n);
	int randIndex;

	for (int popIndex = 0 ; popIndex < numberOfPixels; popIndex++){
		randIndex = rand () % (n);
		individual->image.data[randIndex].r = rand () % (individual->image.max_color + 1);
		individual->image.data[randIndex].g = rand () % (individual->image.max_color + 1);
		individual->image.data[randIndex].b = rand () % (individual->image.max_color + 1);
	}
}

void mutate_population(Individual * individual, int population_size, double rate){
	for(int mutateIndex = population_size/4; mutateIndex < population_size; mutateIndex++){
		mutate(individual + mutateIndex, rate);
	}
}
