/* File name: fitness.c
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

double comp_distance(const PIXEL *A, const PIXEL *B, int image_size){
	double distance = 0;

	for (int i = 0; i < image_size; i++ ){
		distance += (A[i].r - B[i].r)*(A[i].r - B[i].r) + (A[i].g - B[i].g)*(A[i].g - B[i].g) + (A[i].b - B[i].b)*(A[i].b - B[i].b);
	}

	distance = sqrt(distance);

	return distance;
}

void comp_fitness_population(const PIXEL *image, Individual *individual, int population_size){
	for (int popIndex = 0; popIndex < population_size; popIndex ++){
		individual[popIndex].fitness = comp_distance(image, individual[popIndex].image.data, individual[popIndex].image.width*individual[popIndex].image.height);
	}
}
