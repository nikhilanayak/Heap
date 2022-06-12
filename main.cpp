/*
 Implementation of the heap ADT in C++ by Nikhil Nayak
 Used primarily for objects like priority queues to find the largest/smallest element in a "Heap" of numbers


 June 11, 2022
 */

#include <iostream>
#include <cstring>
#include <time.h>
#include <fstream>
#include <math.h>


void heap(int* array, int& current){
// makes an array into the proper heap form

	int num = (int)floor((current-1)/2);
	if(array[current] > array[num]){
		int tmp = array[current];
		array[current] = array[num];
		array[num] = tmp;
		heap(array, num);
	}
}


void rearrange(int* array, int index) {
	// Written with help from nihal
	// rearranges the heap to keep its max element in place
	if (array[(index*2)+1] >= array[(index*2)+2] && array[index] < array[(index*2)+1]) {
		int tmp = array[(index*2)+1];
		array[(index*2)+1] = array[index];
		array[index] = tmp;
		rearrange(array, (index*2)+1);
	}
	else if (array[(index*2)+1] <= array[(index*2)+2] && array[index] < array[(index*2)+2]) {
		int tmp = array[(index*2)+2];
		array[(index*2)+2] = array[index];
		array[index] = tmp;
		rearrange(array, (index*2)+2);
	}
}



void print(int index, int* array, int depth, int size){
	// print the heap sideways using tabs
	if((index + 1) * 2 <= size && array[(index + 1) * 2]){
		print((index + 1) * 2, array, depth + 1, size);
	}
	for(int i = 0; i < depth; i++) std::cout << '\t';
	std::cout << array[index] << "\n";
	if(index * 2 + 1 <= size && array[index * 2 + 1]){
		print(index * 2 + 1, array, depth + 1, size);
	}
}

int main(int argc, char** argv){
	if(argc != 2){
		std::cout << "Run with numbers file: ";
		std::cout << argv[0] << " " << "[file.txt]\n";
		return -1;
	}


	
	srand(time(0)); // set random from time seed


	int* array = new int[100]; // heap
	int current = 0;

	memset(array, 100, sizeof(int));

	while(true){
		std::cout << "(U)pload, (A)dd, (P)rint, (R)emove, (Q)uit: ";
		char c[256];
		std::cin >> c;

		switch(c[0]){
			case 'U': { // upload numbers from argv[1] file
				std::cout << "How many numbers: ";
				int numnums;
				std::cin >> numnums;
				
				for(int i = 0; i < numnums; i++){
					char input[10];
					char tmp[10];
					int c = 1;
					int num;
					int random = rand() % 50 + 1;
					
					std::fstream file(argv[1]);
					while(file.getline(input, 10, ' ')){
						if(c == random){
							strcpy(tmp, input);
							c++;
						}
						c++;
					}

					num = atoi(tmp);
					array[current] = num;
					heap(array, current);
					current++;

				}


				break;
			}
			case 'A': { // Add numbers manually
				int num;
				std::cout << "What number: ";
				std::cin >> num;
				if(array[0] == 0){
					array[0] = num;
					current = 1;
				}
				else{
					array[current] = num;
					heap(array, current);
					current++;
				}
				break;
			}
			case 'P': { // print the current heap
				print(0, array, 0, current);
				break;
			}
			case 'R': { // remove all elements and print them out in order of removal
				int size = current;
				while(size != 0){
					std::cout << array[0] << ", ";
					array[0] = array[size - 1];
					array[size - 1] = 0;
					rearrange(array, 0);
					size--;
				}
				std::cout << "\n";
				break;
			}
			case 'Q': { // quit
				return 0;
			}


		}
	}
}
