
## Language
Программа реализована на языке С++

## Code Style
Выдержан Google Code Style.

## Description

Реализует алгоритм K-means для заданного числа кластеров (K <= 1000). 
Работает в заданное число потоков (зависит от аппаратных ресурсов).
Выводит в файл центры полученных кластеров в отсортированном виде.
Управляется с cli.

## Usage

`klusters.exe -i "input_file.txt" -o "output_file.txt" -c 5 -t 2`

Read points from input_file.txt, execute kmeans algorithm for 5 
clusters, using 2 threads, and write result to output_file.txt

## Input format

Предполагаемый формат читаемого файла:

0.934 0.123 -0.434
10.0 1.0 -1.0
0.0 0.0 0.0
1 2 3
1000 2000 3000

