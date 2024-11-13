
#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

void baseConvolution(int dim, int_cached_buffer &src, int_cached_buffer &ker, int_cached_buffer &dst)
{
    int i, j, k, l;

    for (i = 0; i < dim - 8 + 1; i++)
        for (j = 0; j < dim - 8 + 1; j++)
        {
            dst[j * dim + i] = 0;
            for (k = 0; k < 8; k++)
                for (l = 0; l < 8; l++)
                {
                    dst[j * dim + i] = dst[j * dim + i] + src[(j + l) * dim + (i + k)] * ker[l * dim + k];
                }
        }
}

void convolution(int dim, int_cached_buffer &src, int_cached_buffer &ker, int_cached_buffer &dst)
{
    // rule: offsets, indices and sizes can be integers but all the integers that are used as temporary
    // values are int_cache_dependent, you can have at most 8 of these otherwise initialize a buffer.
    int i, j, k, l;
    int_cache_dependent res;
    // example: you can initialize another buffer like this.
    int_cached_buffer kernValues;
    initBuffer(kernValues, 64);
    int block_size = 8;
    // tomato: optimize convolution for more cache hits.
    for (i = 0; i < dim - 8 + 1; i+= block_size)
	   for (j = 0; j < dim - 8 + 1; j+= block_size){
		  for (int ii = i; ii < std::min(i + block_size, dim - 8 + 1);  ii++)
			 for (int jj = j; jj < std::min(j + block_size, dim - 8 + 1); jj++){
				res = dst[jj * dim + ii] = 0;
			        for (k = 0; k < 8; k++)
					for (l = 0; l < 8; l++){
						 res+= src[(jj + l) * dim + (ii + k)] * ker[l * dim + k];
					}
				dst[jj * dim + ii] = res;
			 }
	   }

}

void baseMatrixMultiplication(int dim, int_cached_buffer &src, int_cached_buffer &src2, int_cached_buffer &dst)
{
    int i, j, k;

    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
        {
            dst[j * dim + i] = 0;
            for (k = 0; k < dim; k++)
                dst[j * dim + i] = dst[j * dim + i] + src[j * dim + k] * src2[i + k * dim];
        }
}

void matrixMultiplication(int dim, int_cached_buffer &src, int_cached_buffer &src2, int_cached_buffer &dst)
{
    int i, j, k;
    // rule: offsets, indices and sizes can be integers but all the integers that are used as temporary
    // values are int_cache_dependent, you can have at most 8 of these otherwise initialize a buffer.
    int size = dim * dim, offset = dim * (dim - 1), initIndex = dim >> 3;
    int_cache_dependent res;
    // tomato: optimize matrix multiplication for more cache hits.
    int block_size = 8;
    for (i = 0; i < dim; i+= block_size)
	   for (j = 0; j < dim; j+= block_size)
		  for (int ii = i; ii < std::min(i + block_size, dim);  ii++)
			 for (int jj = j; jj < std::min(j + block_size, dim); jj++){
				res = dst[jj * dim + ii] = 0;
     				for (k = 0; k < dim; k++){
					res += src[jj * dim + k] * src2[ii + k * dim];
				dst [jj * dim + ii] = res;
			 }
	   }


}
