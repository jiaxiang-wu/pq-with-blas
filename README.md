# Introduction

This project compares the run-time speed of the look-up table pre-computation 
  procedure in Product Quantization and its several variants. Intel's MKL 
  library (BLAS & SparseBLAS) is used for acceleration; a built-in 
  implementation of matrix multipliation is also included for comparison.

We compare the following PQ-like methods:

+ PQ (Product Quantization).
+ OPQ (Optimized Product Quantization).
+ CQ (Composite Quantization).
+ SCQ (Sparse Composite Quantization).
+ TQ (Tree Quantization).

Another two PQ-like methods, CKM (Cartesian K-means) and AQ (Additive 
  Quantization), are not included, since their pre-computation procedure is the 
  same as OPQ and CQ, respectively.

MKL library provides acceleration for matrix multiplication operations (both 
  dense and sparse matrices). PQ, OPQ, and CQ can be accelerated by MKL's BLAS 
  routine, and SCQ can be sped-up be MKL's SparseBLAS routine. TQ is a little 
  bit special. Due to its structured sparsity, MKL's BLAS routine can still be 
  adopted for better speed-up (compared against SparseBLAS).

# Experiments

## Settings

We report the pre-computation time (in millisecond) of each query (average over 
  10k queries). Two input settings are evaluated, "single query" and "multiple 
  queries" (50 queries in a batch). The time consumption is measured on a 
  workstation, equiped with Intel Xeon E5-2640 CPU @ 2.50GHz (single-threaded).

## Results

| Method | Time Complexity |       128 x 1 |      128 x 50 |       960 x 1 |      960 x 50 |
|:-------|----------------:|--------------:|--------------:|--------------:|--------------:|
| PQ     |           D * K | 0.024 / 0.015 | 0.025 / 0.004 | 0.247 / 0.048 | 0.232 / 0.018 |
| OPQ    |   D * D + D * K | 0.044 / 0.017 | 0.040 / 0.005 | 1.177 / 0.178 | 1.190 / 0.075 |
| CQ     |       D * M * K | 0.271 / 0.050 | 0.252 / 0.018 | 2.004 / 0.306 | 1.992 / 0.130 |
| SCQ    |           D * K | 0.050 / 0.053 | 0.048 / 0.014 | 0.272 / 0.171 | 0.270 / 0.112 |
| TQ     |       2 * D * K | 0.058 / 0.020 | 0.056 / 0.006 | 0.489 / 0.094 | 0.488 / 0.037 |

Note: for query size X x Y, X is the number of feature dimensions, and Y is the 
  number of queries in each input batch. The first time is for the built-in 
  implementation, and the second time is for the MKL-based implementation. We 
  choose SCQ's sparsity so that its complexity is the same as that of PQ.

# Analysis

+ MKL's BLAS routine is much more powerful than the built-in implementation, and
  its advantage grows as the input batch size increases.
+ MKL's SparseBLAS routine is also slightly better than the built-in version, 
  but less efficient than the BLAS routine (comparing PQ and SCQ).
+ TQ is more efficient than SCQ due to its structured sparsity.

