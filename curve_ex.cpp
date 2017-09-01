#include <iostream>
#include <cmath>
#include <cstdlib>
#include "plotin/Plot.h"

using namespace std;

double* array_gen(double a, double b, int length);
double sigmoid(double x);
void recalc(double **y, int length);

int main(){
	Plot p1(23, Plot::BID_CURVE); // New plot of type = Scatter and id = 23
	
	double * new_range = new double[4]; // Visualization range array
	new_range[0] = -10; new_range[1] = 10; new_range[2] = 0; new_range[3] = 1; // Quick values assigment
	p1.setRange(new_range); // Linking the range to the plot object
	//-------------------------
	p1.setCurveFun("1/(1 + 2.71828**-x)"); // set curve function as sigmoid function
	p1.setLegendText("sigmoid curve"); // Adding Legend
	p1.setLegendPos(4, 0.5); // Setting legend position
	p1.setGrid(true);
	p1.setGridTickness(3);
	p1.setColor("red"); // Setting color as hexadecimal
	p1.printInfo(); // Printing info in terminal

	p1.genPlot(); // Plotting
	return 0;
}