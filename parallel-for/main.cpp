#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <iostream>
#include <chrono>
#include <thread>

#include "LongestUncrossedKnightsPath.h"
#include "FileExporter.h"

void get_args(int, char*[], uint8_t&, uint8_t&, uint16_t&);

void err_abort (const char*);

int main(int argc, char* argv[]) {
    
    uint8_t m = 0, n = 0, x = 0, y = 0; uint16_t t = 0;
    if(argc == (4+1) || argc == (6+1)){
        get_args(argc, argv, m, n, t);        
    }else{
        err_abort("Valid are: \nWith all start fields: -m 8 -n 8\nWith all start fields and limited threads: -m 8 -n 8 -t 1");
    }
    if((m < 4 || n < 4) &&  (m + n) < 8){
        err_abort("Calculation only works from boards with min size 3x5 or 4x4.");
    }
   
    auto start = std::chrono::system_clock::now();

    LongestUncrossedKnightsPath algorithmn(m, n);
    algorithmn.setThreadLimit(t);

    std::cout << "Running algorithmn over all fields on a " << (int) m << "x" << (int) n << " board with " << (int) (t > 0 ? t: std::thread::hardware_concurrency()) << " threads." << std::endl;
    algorithmn.run();

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

	FileExporter fileExporter;
	fileExporter.exportPath(algorithmn.longestPathBoard, 1);

    std::cout << "The calculation took " << elapsed_seconds.count() << " seconds." << std::endl;
}

void get_args(int argc, char *argv[], uint8_t &m, uint8_t &n, uint16_t& t) {
    for(int i=1; i<argc; i+=2) {
        if(strcmp(argv[i], "-m") == 0) {
            m = strtol(argv[i+1], NULL, 10);
        } else if(strcmp(argv[i], "-n") == 0) {
            n = strtol(argv[i+1], NULL, 10);
        } else if(strcmp(argv[i], "-t") == 0) {
            t = strtol(argv[i+1], NULL, 10);
        }
    }
}

void err_abort (const char *str){ 
	fprintf (stderr,"LongestUncrossedKnightsPath: %s\n", str); 
	fflush (stdout); 
	fflush (stderr); 
	exit (1); 
}
