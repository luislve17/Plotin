#include <iostream>
#include <cmath>
#include <cstdlib>
#include "plotin/Plot.h"
#define EULER 2.71828

using namespace std;

double* array_gen(double a, double b, int length);
double sigmoid(double x);
void recalc(double **y, int length);

int main(){
	Plot p1(23, Plot::BID_SCATTER);
	
	double * new_range = new double[4];
	new_range[0] = -10; new_range[1] = 10; new_range[2] = 0; new_range[3] = 1;
	p1.setRange(new_range);
	//-------------------------
	double *x = array_gen(-10, 10, 50);
	double *y1 = new double[50];
	
	for(int i = 0; i < 50; i++){
		y1[i] = sigmoid(x[i]);
	}
	//-------------------------
	p1.setValues(x, y1, 50);
	p1.setPlotStyle(13);
	p1.setLegendText("sigmoid");
	p1.setLegendPos(0, 0.5);
	p1.setColor("blue");
	p1.genScatterFile();
	p1.printInfo();
	p1.openAnimationContext(0.25);
	p1.printInfo();
	p1.genPlot();
	for(int frame = 1; frame <= 20; frame++){
		recalc(&y1, 50);
		p1.setValues(x, y1, 50);
		p1.genScatterFile();
		system("sleep 0.25");
	}
	
	p1.closeAnimationContext();
	delete y1;
	delete x;
	return 0;
}

double* array_gen(double a, double b, int length){
	double interval = (b - a)/(double)(length - 1);
	double * array = new double[length];
	for(int i = 0; i < length; i++){
		array[i] = a + i*interval;
	}
	return (array);
}

double sigmoid(double x){
	return(1/(1+pow(EULER, -x)));
}

void recalc(double **y, int length){
	for(int i = 0; i < length; i++){
		(*y)[i] -= 0.01;
	}
}