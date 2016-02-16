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

| Query Size     | Time Complexity | 128 x 1 | 128 x 50 |  960 x 1 | 960 x 50 |
|:---------------|----------------:|--------:|---------:|---------:|---------:|
| PQ  (built-in) |           D * K |   0.024 |    0.025 |    0.247 |    0.232 |
| PQ  (MKL)      |           D * K |   0.015 |    0.004 |    0.048 |    0.018 |
| OPQ (built-in) |   D * D + D * K |   0.044 |    0.040 |    1.177 |    1.190 |
| OPQ (MKL)      |   D * D + D * K |   0.017 |    0.005 |    0.178 |    0.075 |
| CQ  (built-in) |       D * M * K |   0.271 |    0.252 |    2.004 |    1.992 |
| CQ  (MKL)      |       D * M * K |   0.050 |    0.018 |    0.306 |    0.130 |
| SCQ (built-in) |           D * K |   0.050 |    0.048 |    0.272 |    0.270 |
| SCQ (MKL)      |           D * K |   0.053 |    0.014 |    0.171 |    0.112 |
| TQ  (built-in) |       2 * D * K |   0.058 |    0.056 |    0.489 |    0.488 |
| TQ  (MKL)      |       2 * D * K |   0.020 |    0.006 |    0.094 |    0.037 |

Note: for query size X x Y, X is the number of feature dimensions, and Y is the 
  number of queries in each input batch. We choose SCQ's sparsity so that its 
  complexity is the same as that of PQ.

## Analysis

+ MKL's BLAS routine is much more powerful than the built-in implementation, and
  its advantage grows as the input batch size increases.
+ MKL's SparseBLAS routine is also slightly better than the built-in version, 
  but less efficient than the BLAS routine (comparing PQ and SCQ).
+ TQ is more efficient than SCQ due to its structured sparsity.

