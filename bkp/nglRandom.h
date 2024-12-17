#pragma once
#include <ctime>
#include <iostream>

bool nglRandom();
int nglRandom(int min, int max);
double nglRandom(double min, double max);

//небольшая перегрузочка тут
bool nglRandom(){
	srand(time(NULL) + rand());
	bool min = false;
	bool max = true;
	bool n = min + rand()%(max - min + 1);
	return n;
}

int nglRandom(int min, int max){
	srand(time(NULL) + rand());
	int n = min + rand()%(max - min + 1);
	return n;
}

double nglRandom(double min, double max){
	srand(time(NULL) + rand());
	double n = (double)rand()/(double) RAND_MAX*(max-min)+min;
	return n;
}
