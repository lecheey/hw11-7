#include <iostream>
#include <fstream>
#include <cstdlib>

void write_arr(const std::string& filename, const int* arr, const int n){
	std::fstream fs;
	fs.open(filename, std::fstream::out);
	if(fs.is_open()){
//		fs << n << '\n';
		for(int i = 0; i < n; i++){
			fs << arr[i] << ' ';
		}
		fs << '\n';
		fs.close();
	}
}

int main(){
    std::string filename = "data.txt";

    /*
	srand(time(nullptr));
	int ll = 1000;
	int rr = 10000;
    const int size1 = ll + rand() % rr;
    */
    const int size = 500000;

	srand(time(nullptr));
	int lef_border = 100;
	int range_len = 1000;
	int* arr = new int[size];

	for(int i = 0; i < size; i++){
		arr[i] = lef_border + rand() % range_len;
	}

	write_arr(filename, arr, size);

	delete[] arr;
    return 0;
}
