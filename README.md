Программа реализована на языке С++, выдержан Google Code Style,
читает файл input.txt, содержащий точки в формате :

0.934 0.123 -0.434
10.0 1.0 -1.0
0.0 0.0 0.0
1 2 3
1000 2000 3000

Реализует алгоритм K-means для заданного числа кластеров (K <= 1000), 
работающий в заданное число потоков (число потоков зависит от аппаратных ресурсов).

Желаемое количество центров кластеров - задается в 52 строке файла kmeans.cpp.

Выводит в файл output.txt центры полученных кластеров в отсортированном виде.

Так же в репоритории присутствует ряд текстовых файлов, которыми можно протестировать программу
имя входного файла можно поменять в файле kmeans.cpp - в строке 26.
