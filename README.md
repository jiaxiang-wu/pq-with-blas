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

| Query Size     |  128 x 1 | 128 x 50 |  960 x 1 | 960 x 50 |
|:---------------|---------:|---------:|---------:|---------:|
| PQ  (built-in) |    0.025 |    0.025 |    0.249 |    0.233 |
| PQ  (IntelMKL) |    0.015 |    0.004 |    0.048 |    0.017 |
| OPQ (built-in) |    0.043 |    0.041 |    1.191 |    1.201 |
| OPQ (IntelMKL) |    0.017 |    0.005 |    0.182 |    0.074 |
| CQ  (built-in) |    0.270 |    0.252 |    2.043 |    2.029 |
| CQ  (IntelMKL) |    0.050 |    0.019 |    0.306 |    0.131 |
| SCQ (built-in) |    0.049 |    0.048 |    0.273 |    0.270 |
| SCQ (IntelMKL) |    0.053 |    0.014 |    0.172 |    0.111 |
| TQ  (built-in) |    0.028 |    0.028 |    0.244 |    0.237 |
| TQ  (IntelMKL) |    0.015 |    0.004 |    0.054 |    0.020 |


## Analysis

