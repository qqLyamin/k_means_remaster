# K-Means Clustering Program

**Programming Language:** The software solution is developed using the robust and efficient C++ programming language, ensuring high-speed execution and effective memory management.

**Coding Standards:** The codebase strictly adheres to Google's C++ Style Guide, promoting consistency, readability, and maintainability across the entire project.

## Description
This application brings to life the renowned K-means clustering algorithm. Given a user-defined number of clusters (with the constraint K <= 1000), the software effectively segregates a dataset into distinctive groups, maximizing intra-cluster similarity and inter-cluster variation.

The execution is designed to be multi-threaded, thereby leveraging concurrent processing capabilities. The number of threads is user-defined, allowing you to align execution with available hardware resources. 

Upon completion, the software exports the cluster centroids into a designated output file. These centroids are written in a sorted format, aiding quick analysis and further processing. The application interface is command-line driven, enabling easy integration and automation in data analysis pipelines.

## Usage
Here's an illustrative example demonstrating how to use the command-line interface:
```sh
klusters.exe -i "input_file.txt" -o "output_file.txt" -c 5 -t 2
```
In this scenario, the application reads data points from 'input_file.txt', executes the K-means algorithm to form 5 clusters using 2 processing threads, and records the results into 'output_file.txt'.

## Input Format
The data points for clustering should be formatted as follows in the input file:
```sh
0.934 0.123 -0.434 10.0 1.0 -1.0 0.0 0.0 0.0 1 2 3 1000 2000 3000
```
This compact and simple format ensures that the application can process a large volume of data efficiently.
