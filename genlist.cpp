#include <fstream>
#include <iostream>
#include <boost/lexical_cast.hpp>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

using namespace std;

boost::mt19937 gen;

int rollDie(int range){
	boost::uniform_int<> dist(1, range);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(gen, dist);
	return die();
}

void help(){
	std::cout << "Usage: \n\tgenlist [# of lines] -o [filename]\n";
}

int main(int argc, char **argv){
	if(argc < 3){
		help();
	}

	int numLines;
	std::string oFileName;

	for(int i=1; i<argc; ++i){
		if( string( argv[i] ) == "-n" ){
			numLines = boost::lexical_cast<int>(argv[i+1]);
		}else if( string( argv[i] ) == "-o" ){
			oFileName = string( argv[i+1] );
		}
	}

	cout << "Outputting " << numLines << " lines to \"" << oFileName << "\"." << endl;
	ofstream oFile;
	oFile.open(oFileName.c_str());
	
	for(int i=0; i<numLines; i++){
		oFile << rollDie(1000) << "\n";
	}
	oFile.close();
	return 0;
}
