

#include "a4.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	int width = 5; int height = 6; int max_color = 500; int population_size = 50;
	generate_population(population_size, width, height, max_color);
	PIXEL *image1 = generate_random_image(width, height, max_color);
	comp_fitness_population(image1, generate_population(population_size, width, height, max_color), population_size);
}

PIXEL *generate_random_image(int width, int height, int max_color){
	int size = width * height;
	PIXEL * randImage;
	randImage = (PIXEL *) malloc(size*sizeof(PIXEL));

	//Generate random rbg values and array of pixels
	for (int row = 0; row < height; row ++){
		for (int col = 0; col < width; col ++){
			randImage[row*width+col].r = rand() % (max_color + 1);
			 printf("%d ",  randImage[row*width+col].r);
			 randImage[row*width+col].g = rand() % (max_color + 1);
			 printf("%d ",  randImage[row*width+col].g);
			 randImage[row*width+col].b = rand() % (max_color + 1);
			 printf("%d ",  randImage[row*width+col].b);
		}
		printf("\nRow %d\n", row+1);
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

//	printf("------------------");
	int popIndex = 0;
//	for (int row = 0; row < height; row ++){
//		for (int col = 0; col < width; col ++){
//			printf("%d ",  population[popIndex].image.data[row*width+col].r);
//			printf("%d ",  population[popIndex].image.data[row*width+col].g);
//			printf("%d ",  population[popIndex].image.data[row*width+col].b);
//		}
//		printf("\n");

//	}

	int n = 0;
	//Individual * indiv = population + n;
//	Individual * indiv = &population[n];
	printf("Distance: %f",comp_distance(population[0].image.data, population[1].image.data, width*height));

	printf("====");
	printf("\n%d\n",(population+n)->image.max_color);
	mutate((population+n), 20);

	mutate_population(population, population_size, 20);

	return population;

}

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
		//printf("\nFitness:%f", individual[popIndex].fitness);
	}
}

void mutate(Individual * individual, double rate){
	int n = individual->image.width * individual->image.height;
	int numberOfPixels = (rate/100*n);
	int randIndex;
	for (int popIndex = 0 ; popIndex < numberOfPixels; popIndex++){
		randIndex = rand () % n + 1;
		individual->image.data[randIndex].r = rand () % individual->image.max_color + 1;
		printf("Randpix%d\n", individual->image.data[randIndex].r);
		individual->image.data[randIndex].g = rand () % individual->image.max_color + 1;
		individual->image.data[randIndex].b = rand () % individual->image.max_color + 1;
	}
	printf("\n");
}

void mutate_population(Individual * individual, int population_size, double rate){
	for(int mutateIndex = population_size/4; mutateIndex < population_size; mutateIndex++){
		mutate(individual + mutateIndex, rate);
	}
}

PPM_IMAGE * evolve_image ( const PPM_IMAGE * image , int num_generations , int population_size , double rate ){

	PPM_IMAGE * PPM_image = malloc(sizeof(PPM_image));
	Individual * population = generate_population(population_size, image->width, image->height, image->max_color);
	Individual * temp = malloc(sizeof(Individual));
	comp_fitness_population(image->data, population, population_size);

	//Sorting population of individuals based on fitness
    for (int i = 0; i < population_size; i++)
    {
        for (int j = i + 1; j < population_size; j++)
        {
            if ((population+i)->fitness > (population+j)->fitness)
            {

                temp =  (population+i);
                *(population+i) = *(population+j);
                *(population+j) = *temp;

            }
        }
    }

    printf("%f", population->fitness);
    printf("%f", (population+1)->fitness);
    printf("%f", (population+2)->fitness);
	return PPM_image;
}

