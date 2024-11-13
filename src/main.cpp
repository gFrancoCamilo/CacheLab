#include "cache.h"
#include "common.h"
#include <iostream>
#include <string>

int main(int args, char **argv)
{
    registerPolicy(CacheSimulation::Policy::LRU);
    if (args > 1){
        std::string policy = argv[1];
	if (policy == "LRU"){
            registerPolicy(CacheSimulation::Policy::LRU);
	} else if (policy == "Random"){
            registerPolicy(CacheSimulation::Policy::Random);
	} else if (policy == "Tree-LRU"){
            registerPolicy(CacheSimulation::Policy::TreeLRU);
	} else {
            fprintf(stderr, "Option not available\n");
	    exit(1);
	}
    }
    initCache();
    matrix_mult_args ma;
    convolution_args ca;
    // tomato: add an argument to specify your replacement policy
    initMatrixMultiplicationWithDimensions(256, ma);
    initConvolutionWithDimensions(256, ca);
    baseConvolution(ca.dim, ca.src, ca.ker, ca.dst);
    copyBaseDst(ca);
    std::cout << "Base Convolution Stats:" << std::endl;
    printStats();
    std::cout << "=======================" << std::endl;
    resetCacheStats();
    convolution(ca.dim, ca.src, ca.ker, ca.dst);
    checkBuffers(ca);
    std::cout << "Your Convolution Stats:" << std::endl;
    printStats();
    std::cout << "=======================" << std::endl;
    resetCacheStats();
    baseMatrixMultiplication(ma.dim, ma.src, ma.src2, ma.dst);
    copyBaseDst(ma);
    std::cout << "Base Matrix Multiplication Stats:" << std::endl;
    printStats();
    std::cout << "=================================" << std::endl;
    resetCacheStats();
    matrixMultiplication(ma.dim, ma.src, ma.src2, ma.dst);
    checkBuffers(ma);
    std::cout << "Your Matrix Multiplication Stats:" << std::endl;
    printStats();
    std::cout << "=================================" << std::endl;
    resetCacheStats();
}
