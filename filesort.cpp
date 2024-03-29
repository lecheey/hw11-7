#include <iostream>
#include <fstream>
#include <cstdlib>
#include "qsort.h"

std::string file1 = "data.txt"; // сырые данные
std::string file2 = "datasorted.txt"; // после сортировки

std::string temp1 = "temp1.txt"; // временный файл 1
std::string temp2 = "temp2.txt"; // временный файл 2

int countLen(const std::string& filename){ // подсчет количества элементов в файле 
	std::cout << "counting length... " << std::endl;
	std::fstream fs;
	fs.open(filename, std::fstream::in);
	int n = 0, m = 0;
	while (!fs.eof()){
		fs >> m;
		n++;
	}
	n -= 1;
//	std::cout << n << std::endl;
	fs.close();
	return n;
}

void readFile(const std::string& filename, int*& arr, int& n){ // чтение файла	
	std::cout << "reading file... " << std::endl;
	std::fstream fs;
	fs.open(filename, std::fstream::in);
	n = countLen(filename); 
	if(fs.is_open()){
		arr = new int[n];
		for (int i = 0; i < n; i++){
			fs >> arr[i];
		}
		fs.close();
	}
}

void writeFile(const std::string& filename, const int* arr, const int n){ // запись в файл
	std::cout << "writing..." << std::endl;
	std::fstream temp;
	temp.open(filename, std::fstream::out);
	if(temp.is_open()){
		temp << n << '\n';
		for(int i = 0; i < n; i++){
			temp << arr[i] << ' ';
		}	
		temp << '\n';
		temp.close();
	}
}

void splitFile(const std::string& filename, int* arr, int& n){ // разделение главного файла на два
	std::cout << "splitting file... " << std::endl;
	std::fstream fs;
	fs.open(filename, std::fstream::in);
	if(fs.is_open()){
		int len = n / 2;
		int l = 0;
		int r = len;
		while(l < n){
			int* t = new int[len];
			if(l == 0 && r == len){
				for(int i = 0; i < len; i++){
					t[i] = arr[l];
					l++;
//					std::cout << t[i] << ' ';
				}
				std::cout << '\n';
				writeFile(temp1, t, len);
			}
			if(l == len && r == len*2){
				for(int i = 0; i < len; i++){
					t[i] = arr[l];
					l++;
//					std::cout << t[i] << ' ';
				}
				std::cout << '\n';
				writeFile(temp2, t, len);
			}
			std::cout << '\n';
			r += len;
			delete[] t;
		}
		fs.close();
	}
}

void mergeFiles(int* arr_total, int* arr1, int* arr2, int n1, int n2){ // объединения файлов с сортировкой
    std::cout << "merging files..." << std::endl;
    int k = 0, i = 1, j = 1;

    while (i < n1 && j < n2) {
       if (arr1[i] <= arr2[j]) {
           arr_total[k] = arr1[i];
           i++;
       }
       else {
           arr_total[k] = arr2[j];
           j++;
       }
       k++;
   }

   while (i < n1) {
       arr_total[k] = arr1[i];
       i++;
       k++;
   }

   while (j < n2) {
       arr_total[k] = arr2[j];
       j++;
       k++;
   }
}

int main(){
	int* arr = nullptr; // массив под исходный файл
	int n = 0, n1 = 0, n2 = 0;
	readFile(file1, arr, n);
	splitFile(file1, arr, n);

	int* arr1 = nullptr; // массив чдля части 1
	readFile(temp1, arr1, n1);
    std::cout << "sorting data..." << std::endl;
//	timSort(arr1, n1);
	quickSort(arr1, 0, n1);
	
	int* arr2 = nullptr; // массив для части 2
	readFile(temp2, arr2, n2);
    std::cout << "sorting data..." << std::endl;
//	timSort(arr2, n2);
	quickSort(arr2, 0, n2);

	std::cout << '\n';
	int n_total = n1 + n2;
	int* arr_total = new int[n_total]; // массив вод сортированные данные
	mergeFiles(arr_total, arr1, arr2, n1, n2);
	std::cout << '\n';

	writeFile(file2, arr_total, n_total); // создание готового файла
	std::cout << file2 << " is ready!\n";

	delete[] arr;
	delete[] arr1;
	delete[] arr2;
	delete[] arr_total;
	return 0;
}
