#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "Plot.h"

using namespace std;

Plot::Plot(int id, int type){
	plot_id = id;
	plot_type = type;
	plot_color = "#000000";
	legend_text = "";
	range = new double[4];
	range_set = false;
	values_set = false;
	num_values = 0;
	plot_style = 1;
	grid_set = false;
	grid_tickness = 0.5;

	function_set = false;

	animation_flag = false;
	delay = 0;
}

Plot::Plot(const Plot& p){
	plot_id = p.plot_id;
	plot_type = p.plot_type;
	plot_color = p.plot_color;
	legend_text = p.legend_text;
	legend_x = p.legend_x;
	legend_y = p.legend_y;
	range = p.range;
	range_set = p.range_set;
	grid_set = p.grid_set;
	grid_tickness = p.grid_tickness;
	x_values = p.x_values;
	y_values = p.y_values;
	values_set = p.values_set;
	num_values = p.num_values;
	plot_style = p.plot_style;
	function = p.function;
	function_set = p.function_set;
	animation_flag = p.animation_flag;
	delay = p.delay;
}

void Plot::printInfo(){
	cout << "*************************" << endl;
	cout << "********PLOT INFO********" << endl;
	cout << "*************************" << endl;
	cout << "- Plot id: " << plot_id << endl;
	cout << "- Plot type: " << plot_type << endl;
	cout << "- Plot color: " << plot_color << endl;
	cout << "- Legend: " << legend_text << endl;
	cout << "- Legend Pos: (" << legend_x << "," << legend_y << ")" << endl;
	cout << "- Range set: " << range_set << endl;
	if(range_set)
		cout << "- Range: [" << range[0] << ":" << range[1] << "][" << range[2] << ":" << range[3] << "]" << endl;
	cout << "- Values set: " << values_set << endl;
	if(values_set){	
		cout << "- x: ";
		for(int i = 0; i < num_values; i++){
			cout << x_values[i];
			if(i != num_values - 1){
				cout << ",";
			}
			if(i > 10){
				cout << "...";
				break;
			}
		}
		cout << endl;

		cout << "- y: ";
		for(int i = 0; i < num_values; i++){
			cout << y_values[i];
			if(i != num_values - 1){
				cout << ",";
			}
			if(i > 10){
				cout << "...";
				break;
			}
		}
		cout << endl;
	}
		cout << "- Values: " << num_values << endl;
		cout << "- Style: " << plot_style << endl;
		cout << "- Grid set: " << grid_set << endl;
		cout << "- Grid tickness: " << grid_tickness << endl;
		cout << "- Animation flag: " << animation_flag << endl;
		if(animation_flag){
			cout << "- Animation delay: " << delay << endl;
		}
}

void Plot::setRange(double * range_arr){
	range = range_arr;
	range_set = true;
}

void Plot::setValues(double * X, double * Y, int length){
	if(plot_type == BID_SCATTER){
		x_values = X;
		y_values = Y;
		num_values = length;
		values_set = true;
	} else {
		cout << "(plot|id:" << plot_id << ") WARNING: Values set to a non-BID_SCATTER plot" << endl;
	}
}

void Plot::setCurveFun(string f){
	function = f;
	function_set = true;
}

void Plot::setPlotStyle(int style){
	plot_style = style;
}

void Plot::setLegendText(string text){
	legend_text = text;
}

void Plot::setLegendPos(double x, double y){
	legend_x = x;
	legend_y = y;
}

void Plot::setGrid(bool b){
	grid_set = b;
}

void Plot::setGridTickness(int t){
	grid_tickness = t;
}

void Plot::setColor(string name_or_hex){
	plot_color = name_or_hex;
}

void Plot::openAnimationContext(float s_delay){
	delay = s_delay;
	animation_flag = true;
}

void Plot::closeAnimationContext(){
	if(animation_flag){
		system("pkill gnuplot");
		stopAnimFile();
		animation_flag = false;
	} else {
		cout << "(plot|id:" << plot_id << ") ERROR: Animation context already closed (Successfull call of 'openAnimationContext()' needed)" << endl;
	}
}

void Plot::genScatterFile(){
	if(plot_type == BID_SCATTER){
		ofstream sf_stream(genName(plot_id, ".dat").c_str());
		for(int i = 0; i < num_values; i++){
			sf_stream << x_values[i] << " " << y_values[i] << endl;
		}
		sf_stream.close();
	} else {
		cout << "(plot|id:" << plot_id << ") ERROR: Cannot generate file. Plot type not BID_SCATTER" << endl;
	}
}

void Plot::genPlot(){
	if(plot_type == BID_SCATTER){
		if(values_set){
			string current_file = genName(plot_id, ".gnp");
			ofstream plot_stream(current_file.c_str());
			plot_stream << "plot \\" << endl;
			if(range_set)
				addRange(&plot_stream, this);
			addData(&plot_stream, this, false);
			addPreferences(&plot_stream, this);
			plot_stream << "replot" << endl;

			if(animation_flag){
				plot_stream << "pause " << delay << endl;
				plot_stream << "reread" << endl;
			}
			plot_stream.close();

			string system_inst = "gnuplot -p '" + current_file + "'";
			if(animation_flag){
				system_inst += " &";
			} 
			system(system_inst.c_str());

		} else {
			cout << "(plot|id:" << plot_id << ") ERROR: Cannot plot. Scatter file not found (Successfull call of 'genScatter()' needed)" << endl;
		}
	}

	if(plot_type == BID_CURVE){
		if(function_set){
			string current_file = genName(plot_id, ".gnp");
			ofstream plot_stream(current_file.c_str());
			plot_stream << "plot \\" << endl;
			if(range_set)
				addRange(&plot_stream, this);
			addCurve(&plot_stream, this, false);
			addPreferences(&plot_stream, this);
			plot_stream << "replot" << endl;
			plot_stream.close();
			system(("gnuplot -p '" + current_file + "'").c_str());
		} else {
			cout << "(plot|id:" << plot_id << ") ERROR: Cannot plot. Function string not set (Successfull call of 'setCurveFun()' needed)" << endl;
		}
	}
}

void Plot::genPlot(Plot * plots_array, int length){
	Plot * plot_ptr = plots_array;
	string file_name = genName(plots_array[0].plot_id, "_multi.gnp");
	ofstream plot_stream(file_name.c_str());
	bool control_flag = true;
	plot_stream << "plot \\" << endl;
	if(plot_ptr->range_set)
		addRange(&plot_stream, plot_ptr);
	for(int i = 0; i < length; i++){
		if(plot_ptr->plot_type == BID_SCATTER){
			if(plot_ptr->values_set){
				if(i == length - 1){
					control_flag = false;
				}
				addData(&plot_stream, plot_ptr, control_flag);
			} else {
				cout << "(plot|id:" << plot_ptr->plot_id << ") ERROR: Cannot plot. Scatter file not found (Successfull call of 'genScatter()' needed)" << endl;
			}
		}
		if(plot_ptr->plot_type == BID_CURVE){
			if(plot_ptr -> function_set){
				if(i == length - 1){
					control_flag = false;
				}
				addCurve(&plot_stream, plot_ptr, control_flag);
			} else {
				cout << "(plot|id:" << plot_ptr->plot_id << ") ERROR: Cannot plot. Function string not set (Successfull call of 'setCurveFun()' needed)" << endl;
			}
		}
		plot_ptr++;
	}
	addPreferences(&plot_stream, plot_ptr - 1);
	plot_stream << "replot" << endl;
	plot_stream.close();
	system(("gnuplot -p '" + file_name + "'").c_str());
}


string Plot::genName(int t, string extension) {
	string file_name = "PlotinData/plot_id_";
	stringstream ss;
	ss << t;
	string T = ss.str();
	file_name = file_name + T + extension;
	
	return file_name;
}

void Plot::addRange(ofstream * st, Plot* current_plot){
	*st << "[x = " << current_plot->range[0] << ":" << current_plot->range[1] << "][y = " << current_plot->range[2] << ":" << current_plot->range[3] << "] \\" << endl;
}

void Plot::addData(ofstream * st, Plot* current_plot, bool multiplot_flag){
	*st << "'" << genName(current_plot->plot_id, ".dat") << "' \\" << endl;
	*st << "\tpointtype " << current_plot->plot_style << " lc '" << current_plot->plot_color << "' \\" << endl;
	*st << "\ttitle '" << current_plot->legend_text  << "'";
	if(multiplot_flag)
		*st << ", \\";
	*st << endl;
}

void Plot::addCurve(ofstream * st, Plot* current_plot, bool multiplot_flag){
	*st << current_plot->function << " \\" << endl;
	*st << "\tlt " << current_plot->plot_style << " lc '" << current_plot->plot_color << "' \\" << endl;
	*st << "\ttitle '" << current_plot->legend_text << "'";
	if(multiplot_flag)
		*st << ", \\";
	*st << endl;
}

void Plot::addPreferences(ofstream * st, Plot* current_plot){
	if(current_plot->grid_set)
		*st << "set grid lw " << current_plot->grid_tickness << endl;
	*st << "set key at " << current_plot->legend_x << "," << current_plot->legend_y << endl;
}

void Plot::stopAnimFile(){
	string file_name = genName(plot_id, ".gnp");
	ifstream gnu_file(file_name.c_str());
	ofstream temp_file("PlotinData/temp.txt");
	
	string delete_this = "reread";
	
	string str;

	while(getline(gnu_file, str)){
		if(str != delete_this){
			temp_file << str << endl;
		}
	}

	gnu_file.close();
	temp_file.close();

	remove(file_name.c_str());
	rename("PlotinData/temp.txt", file_name.c_str());
}