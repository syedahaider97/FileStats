# FileStats
Implementation of the 'wc' Linux command in C++

The above program will take filenames as arguments and count lines, words, and characters. 
The output will then be stored and displayed in the following format:
Lines words characters filename

If no filenames are given, the program will then default to standard input, and promt the user for text.

The program is also capable of handling optional flags that must be placed before the specified file name. 

Character Coutner:
-findchar=[a-zA-Z]
Will return the total number of occurances of a specified character after the file analysis.

Word Counter:
-findWord=[a-zA-Z]*
Will return the total number of occurances of a specified word after the file analysis.

If multiple file names are present, the program will also return a "totals" line, that will sum the data from every file.
