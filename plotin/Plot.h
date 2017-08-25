#ifndef PLOT_H
#define PLOT_H

#include <iostream>

using namespace std;

class Plot{
	private:
		// Parametros generales:
		int plot_id; // Id del plot
		int plot_type; // Tipo del plot
		
		string plot_color; // Color del plot
		
		string legend_text; // Texto de leyenda
		double legend_x; // Posicion x de leyenda
		double legend_y; // Posicion y de leyenda

		double * range; // Rango de visualizacion del plot. [x=range[0]:range[1]][y=range[2]:range[3]]
		bool range_set;  // true: si hay rango especificado. false: por defecto

		bool grid_set; // true: cuadricula visible. false: cuadricula no visible
		int grid_tickness; // Grosor de la linea de cuadricula

		// Para plot_type = BID_SCATTER
		double * x_values; // Valores x
		double * y_values; // Valores y
		bool values_set; // true: se inicializaron valores para el scatter. false: sin inicializacion
		int num_values; // Cantidad de valores

		int plot_style; // Estilo de grafico

		bool animation_flag; // true: plot listo en contexto de animacion en tiempo real
		float delay; // delay en segundos entre frames de la animacion


		// Para plot_type = BID_CURVE
		string function;
		bool function_set;

		// Herramientas privadas
		static string genName(int t, string extension); // Generador de nombres indexables para los archivos usados
		// Metodos internos de ploteo
		static void addRange(ofstream * st, Plot* current_plot);
		static void addData(ofstream * st, Plot* current_plot, bool multiplot_flag);
		static void addCurve(ofstream * st, Plot* current_plot, bool multiplot_flag);
		static void addPreferences(ofstream * st, Plot* current_plot);
		void stopAnimFile();

	public:
		enum plot_types{ // Constantes mapeadas a los tipos de plot
			#include "Plotin_types.h"
			TOTAL
		};// Acceso estatico
		// Constructores
		Plot(int id, int type);
		Plot(const Plot& p);

		void printInfo(); // Imprime informacion de un objeto 'Plot'
		void setRange(double * range_arr); // Especifica range
		void setValues(double * X, double * Y, int length); // Especifica x_values e y_values
		void setCurveFun(string f);
		void setPlotStyle(int style); // Especifica plot_style
		void setLegendText(string text); // Especifica legend_text
		void setLegendPos(double x, double y); // Especifica legend_x y legend_y
		void setGrid(bool b); // Especifica grid_set
		void setGridTickness(int t); // Especifica grid_tickness
		void setColor(string hex); // Especifica plot_color
		void openAnimationContext(float s_delay);
		void closeAnimationContext();

		// Files de data
		void genScatterFile(); // Genera el archivo de datos X e Y para una dispersion

		// Ploteo
		void genPlot(); // Plotea un objeto
		static void genPlot(Plot * plots_array, int length); // Plotea un arreglo de objetos en un mismo entorno grafico
};
#endif