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

| Feature Dim. | 128 | 128 | 960 | 960 |
|:-------------|----:|----:|----:|----:|
| Batch Size   |   1 |  50 |   1 |  50 |

<table class="table table-bordered table-striped table-condensed">
  <tr>
    <td>Feature Dim.</td>
    <td>128</td>
    <td>128</td>
    <td>960</td>
    <td>960</td>
  </tr>
  <tr>
    <td>Batch Size</td>
    <td>1</td>
    <td>50</td>
    <td>1</td>
    <td>50</td>
  </tr>
</table>

## Analysis
