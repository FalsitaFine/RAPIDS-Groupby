//
//  cpuGroupby.h
//  RAPIDS
//
//  Created by Aaron on 11/27/18.
//  Copyright © 2018 Aaron Nightingale. All rights reserved.
//

#ifndef cpuGroupby_h
#define cpuGroupby_h

#include <iostream>

using namespace std;

class cpuGroupby {
public:
    // Custom Structures
    enum reductionType {rmin, rmax, rmean, rcount, rsum};
    
    //Variables
    int num_ops;
    int* output_keys;
    int* output_values;
    reductionType* ops;
    
    // ARBITRARY VERSION
    int* key_columns;
    int* value_columns;
    int num_key_columns;
    int num_value_columns;
    int num_key_rows;
    int num_value_rows;     //always the same as above...
    
    // Aaron's custom data types
    int numGroups;
    int* tempCol;   //Used for temporary storage of groupPtrs
    int* groupPtr;  //array of indicies of start of each group
    
    // Functions
    void fillRand(int distinctKeys, int distinctVals);
    void sort();
    void groupby();
    void getNumGroups();
    void doReductionOps();
    
    // Reduction Functions
    // To do: add sum function
    void rMax(int valIdx);
    void rMean(int valIdx);
    void rCount(int valIdx);
    void rMin(int valIdx);
    void rSum(int valIdx);
    
    void printResults();
    void allocResultArray();
    void freeResults();
    
    // ARBITRARY FUNCTIONS
    void printData();
    bool nextKeyBigger(int cRow);
    void swapAtRow(int cRow);
    void getGroupPtr();
    void writeOutputKeys();
    
    //Constructor / destructor functions
    cpuGroupby(int numKeys, int numValues, int numRows);
    ~cpuGroupby();  // To do - make sure arrays are freed
    
    // GPU Validation
    bool validGPUResult(int* GPUKeys, int* GPUValues, int GPUOutputRows);
};

// Model after this:
/*
 groupby( T* key_columns[], int num_key_columns, int num_key_rows,
 T* value_columns[], int num_value_columns, int num_value_rows,
 reduction_op ops[], int num_ops, T* output_keys[], T* output_values[]) {
 }
 */

#endif /* cpuGroupby_hpp */
