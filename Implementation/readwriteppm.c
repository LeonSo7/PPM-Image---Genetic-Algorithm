/* File name: readwriteppm.c
 * Author: Leon So
 * Date: 2017-11-28
 * MacID: sol4
 * Student No.: 400127468
 * Course: 2S03 - 2018
 */

#include "a4.h"
#include <stdio.h>
#include <stdlib.h>

PPM_IMAGE *read_ppm(const char *file_name){

	int size;
	int tempB, tempG, tempH, tempMax, tempR, tempW;
	PPM_IMAGE * imageFile = malloc(sizeof(PPM_IMAGE));
	FILE * fRead = fopen(file_name, "r"); //Open file for reading

	//Store width and height
	fseek(fRead, 2, SEEK_SET);
	if (fscanf(fRead, "%d %d", &tempW, &tempH) == 2){

		imageFile -> width = tempW;
		imageFile -> height = tempH;

		//Store max value for color
		if (fscanf(fRead, "%d", &tempMax) == 1){
			imageFile -> max_color = tempMax;
		}

		//Storing pixels into array
		size = tempW * tempH;

		PIXEL * pixel = (PIXEL *) malloc(size*sizeof(PIXEL));

		for (int row = 0; row < tempH; row ++){
			for (int col = 0; col < tempW; col ++){
				if (fscanf(fRead, "%d", &tempR) == 1){
					 pixel[row*tempW+col].r = tempR;
				}

				if (fscanf(fRead, "%d", &tempG) == 1){
					pixel[row*tempW+col].g = tempG;
				}

				if (fscanf(fRead, "%d", &tempB) == 1){;
					pixel[row*tempW+col].b = tempB;
				}
			}
		}

		imageFile -> data = pixel;

	}

	fclose(fRead); //Closing file

	return imageFile;
}


void write_ppm(const char *file_name, const PPM_IMAGE *image){

	int tempB, tempG, tempH, tempMax, tempR, tempW;

	FILE * fWrite = fopen(file_name, "w"); //Open file for writing

	tempW = image -> width;
	tempH = image  -> height;
	tempMax = image  -> max_color;


	//Write PPM image data to outfile
	fprintf(fWrite, "P3\n%d %d\n%d\n", tempW, tempH, tempMax);

	for (int row = 0; row < tempH; row ++){
		for (int col = 0; col < tempW; col ++){
			tempR = ((image->data)[row*tempW+col]).r ;
			fprintf(fWrite, "%d ", tempR);

			tempG = ((image->data)[row*tempW+col]).g ;
			fprintf(fWrite, "%d ", tempG);

			tempB = ((image->data)[row*tempW+col]).b ;
			fprintf(fWrite, "%d ", tempB);
		}

		fprintf(fWrite, "\n");

	}

	fclose(fWrite); //Closing file

}
