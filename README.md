How to use:

	make

	./wordcount difctile [inputfile ...]

	You can find some test files in test directory

How it works:

	Wordcount count the number of occurrence of any word in the dictfile that
	appears in inputfiles, and count the total number of words in inputfiles.

	Words are delimited by white space.

	wordcount parse a dictionary file as follows:
		remove all leading whitespace and tabulation on each line
		ignore empty line
		ignore line starting by character '#'
		ignore line with multiple word
		a line with a single word defines a word to be counted in the input stream

	then parse an input file as follows:
		count each word in it
		count each occurence from dictfile

	and finally print result with following format:
		"[count]	[word]"

Limitations:

	Doesn't handle duplicate word in dictfile
	Slow search because of linked list

Improvement:

	Replace dictfile linked list by hash table
	Make tests
	Improve documentation
