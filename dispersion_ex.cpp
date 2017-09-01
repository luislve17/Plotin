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
	Plot p1(23, Plot::BID_SCATTER); // New plot of type = Scatter and id = 23
	
	double * new_range = new double[4]; // Visualization range array
	new_range[0] = -10; new_range[1] = 10; new_range[2] = 0; new_range[3] = 1; // Quick values assigment
	p1.setRange(new_range); // Linking the range to the plot object
	//-------------------------
	double *x = array_gen(-10, 10, 50); // Generating x values
	double *y1 = new double[50]; 
	// Genrating y values (y = sigmoid(x))
	for(int i = 0; i < 50; i++){
		y1[i] = sigmoid(x[i]);
	}

	
	p1.setValues(x, y1, 50); // Loading values to plot object
	p1.setPlotStyle(13); // Assigning the plot style (dot style in graph)
	p1.setLegendText("sigmoid"); // Adding Legend
	p1.setLegendPos(4, 0.5); // Setting legend position
	p1.setColor("blue"); // Setting dot color
	p1.genScatterFile(); // Generating .dat file with colummns x-y
	p1.printInfo(); // Printing info in terminal

	p1.genPlot(); // Plotting
	
	delete y1;
	delete x;
	return 0;
}

// array_gen: Generates a random array with elements in
// range [a,b]
double* array_gen(double a, double b, int length){
	double interval = (b - a)/(double)(length - 1);
	double * array = new double[length];
	for(int i = 0; i < length; i++){
		array[i] = a + i*interval;
	}
	return (array);
}

// sigmoid: Math function example
double sigmoid(double x){
	return(1/(1+pow(EULER, -x)));
}