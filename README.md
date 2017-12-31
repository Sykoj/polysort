# polysort

Compilation:
requires C++14

Usage:
polysort [options] [column type and index...]
options (not required):
	-i [filename]    Name of input file. (implicit standard input)
	-o [filename]    Name of output file. (implicit standard output)
	-s[char]         Character symbol as column separator, implicit ' '
column type and index (required):
	atleast one argument in format [char][column index]
	char is specifing type of column, available {N - int, S - string}
	column indexing starts from 1