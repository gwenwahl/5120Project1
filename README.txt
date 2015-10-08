Instructions for use:

	Either 1: Use the make shell script which will prompt for a data file and 
		  output all 5 algorithms or
	       2: clang++ main.cpp will compile the application, which can then be
		  used by ./a.out FILE_PATH AlGORITHM
	       3: Available options for ALGORITHM are as follows:
			
			quickSortLast
			quickSortFirst
			quickSortMiddle
			quickSortRandom
			heapSort
		4. This will output the number of lines in the data file, the number
	           of comparisons made, and the processing time of the algorithm in 
		   nanoseconds as a comma seperated list.
