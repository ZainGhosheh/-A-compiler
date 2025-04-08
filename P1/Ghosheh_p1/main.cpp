#include <fstream>
#include <string.h>
#include "errors.hpp"
#include "scanner.hpp"

using namespace std;
using namespace a_lang;

static void usageAndDie(){
	std::cerr << "Usage: ac <infile> <options>\n"
	<< " [-t <tokensFile>]: Output tokens to <tokensFile>\n"
	<< "\n"
	;
	std::cout << std::flush;
	std::cerr << std::flush;
	exit(1);
}

static void writeTokenStream(const char * inPath, const char * outPath){
	std::ifstream inStream(inPath);
	if (!inStream.good()){
		std::string msg = "Bad input stream";
		msg += inPath;
		throw new a_lang::InternalError(msg.c_str());
	}
	if (outPath == nullptr){
		std::string msg = "No tokens output file given";
		throw new a_lang::InternalError(msg.c_str());
	}

	a_lang::Scanner scanner(&inStream);
	if (strcmp(outPath, "--") == 0){
		scanner.outputTokens(std::cout);
	} else {
		std::ofstream outStream(outPath);
		if (!outStream.good()){
			std::string msg = "Bad output file ";
			msg += outPath;
			throw new InternalError(msg.c_str());
		}
		scanner.outputTokens(outStream);
	}
}




int
main( const int argc, const char **argv )
{
	if (argc <= 1){ usageAndDie(); }
	std::ifstream * input = new std::ifstream(argv[1]);
	if (input == nullptr){ usageAndDie(); }
	if (!input->good()){
		std::cerr << "Bad path " << argv[1] << std::endl;
		usageAndDie();
	}

	const char * inFile = nullptr;
	const char * tokensFile = nullptr;
	bool useful = false;

	int i = 1;
	for (int i = 1 ; i < argc ; i++){
		if (argv[i][0] == '-'){
			if (argv[i][1] == 't'){
				i++;
				tokensFile = argv[i];
				useful = true;
			} else {
				std::cerr << "Unrecognized argument: ";
				std::cerr << argv[i] << std::endl;
				usageAndDie();
			}
		} else {
			if (inFile == NULL){
				inFile = argv[i];
			} else {
				std::cerr << "Only 1 input file allowed";
				std::cerr << argv[i] << std::endl;
				usageAndDie();
			}
		}
	}
	if (inFile == NULL){
		usageAndDie();
	}
	if (!useful){
		std::cerr << "Hey, you didn't tell the compiler to do anything!\n";
		usageAndDie();
	}

	try {
		if (tokensFile != nullptr){
			writeTokenStream(inFile, tokensFile);
		}
	} catch (a_lang::ToDoError * e){
		std::cerr << "ToDoError: " << e->msg() << std::endl;
		return 1;
	} catch (a_lang::InternalError * e){
		std::cerr << "InternalError: " << e->msg() << std::endl;
		return 1;
	}
	return 0;
}
