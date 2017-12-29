#include "grid.hpp"
#include "polysort.hpp"
#include "polysort_exception.hpp"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void print_usage() {
	
	cout << "Usage: polysort [options] [column type and index...]" << endl;
	cout << "options (not required):" << endl;
	cout << "	-i [filename]	 Name of input file. (implicit standard input)" << endl;
	cout << "	-o [filename]	 Name of output file. (implicit standard output)" << endl;
	cout << "	-s[char]		 Character symbol as column separator, implicit ' '" << endl;
	cout << "column type and index (required):" << endl;
	cout << "	atleast one argument in format [char][column index]" << endl;
	cout << "	char is specifing type of column, available {N - int, S - string}" << endl;
	cout << "	column indexing is starts from 1" << endl;
}

/// @brief Parsing arguments from command line. Throws invalid_argument exception in case of incorrect arguments.
void parse_args(const int argc, char* argv[], fstream& in, fstream& out, char& sep, polysort::column_constraints& cols) {
	
	// checking duplicities of options
	bool has_input_parsed = false;
	bool has_output_parsed = false;
	bool has_seperator_parsed = false;

	size_t i = 1;
	while (i != argc) {
		
		 const string arg = argv[i];

		if (arg == "-i") {

			if (has_input_parsed) 
				throw invalid_argument("Can't use parameter '-i' more than once.");
			if (i + 1 == argc)
				throw invalid_argument("Parameter -i can't be last parameter, input filename must be provided.");
			
			in.open(argv[i+1], fstream::in);
			if (in.fail()) 
				throw invalid_argument("Input file doesn't exist or can't be opened for reading.");

			has_input_parsed = true;
			i += 2;
		}

		else if (arg == "-o") {

			if (has_output_parsed) 
				throw invalid_argument("Can't use parameter '-o' more than once.");
			if (i + 1 == argc) 
				throw invalid_argument("Parameter -o can't be last parameter, output filename must be provided.");

			out.open(argv[i + 1], fstream::out);
			if (out.fail())
				throw invalid_argument("Output file can't be opened for writing.");

			has_output_parsed = true;
			i += 2;
		}

		else if (arg.length() == 3 && arg[0] == '-' && arg[1] == 's') {
			
			if (has_seperator_parsed) {
				throw invalid_argument("Can't use argument '-s' more than once.");
			}

			sep = arg[2];
			has_seperator_parsed = true;
			++i;
		}

		else break;
	}

	if (argc == i) throw invalid_argument("Atleast one column specifier must be provided.");

	while (i != argc) {
			
		const string arg = argv[i];

		if (arg.length() < 2) throw invalid_argument("Bad format of column specifier.");
		char type_symbol = arg[0];

		size_t pos;
		int index;
		try {
			index = stoi(arg.substr(1), &pos);
		}
		catch (...) { throw invalid_argument("Bad format of column specifier."); }
		// arg.size() - 1 because parsing substring starting at index 1
		if (arg.size() - 1 != pos) throw invalid_argument("Bad format of column specifier.");
		// indexing from 1
		if (index <= 0) throw invalid_argument("Bad format of column specifier.");

		cols.push_back(pair<char, size_t>(type_symbol, index));
		i++;
	}
}

int main(const int argc, char* argv[]) {
	
	fstream input;
	fstream output;
	char delimiter = ' ';
	polysort::column_constraints column_constraints;

	try {
		parse_args(argc, argv, input, output, delimiter, column_constraints);
	}
	catch (const invalid_argument& invalid_arg) {

		cout << invalid_arg.what() << endl;
		print_usage();
		return 1;
	}

	polysort::grid grid(column_constraints, delimiter);
	
	try {
		input.is_open() ? grid.create(input) : grid.create(cin);
		grid.sort();
		output.is_open() ? grid.print(output) : grid.print(cout);
	}
	catch(const polysort_exception& polysort_exception) {
				
		cout << polysort_exception.what() << endl;
		return 1;
	}

	return 0;
}