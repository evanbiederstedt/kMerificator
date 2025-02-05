//============================================================================
// Name        : kMerificator.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : 
//============================================================================

#include <iostream>
#include <vector>
#include <assert.h>

#include "Utilities.h"
#include "Validator.h"

using namespace std;

void errEx(std::string message);

int main(int argc, char *argv[]) {

	std::vector<string> arguments (argv + 1, argv + argc + !argc);

	int cortex_height = 26;
	int cortex_width = 140;
	int kMer_size = 31;
	int threads = 40;
	int maximumHaplotypePairs = 200;
	
	bool onlyPASS = false;

	std::string vcfFile;
	std::string referenceGenome;
	std::string deBruijnGraph;
	std::string outputDirectory;
	std::string regions;
	
	for(unsigned int i = 0; i < arguments.size(); i++)
	{
		if(arguments.at(i) == "--vcf")
		{
			vcfFile = arguments.at(i+1);
		}

		if(arguments.at(i) == "--referenceGenome")
		{
			referenceGenome = arguments.at(i+1);
		}

		if(arguments.at(i) == "--deBruijnGraph")
		{
			deBruijnGraph = arguments.at(i+1);
		}

		if(arguments.at(i) == "--outputDirectory")
		{
			outputDirectory = arguments.at(i+1);
		}


		if(arguments.at(i) == "--cortex_height")
		{
			cortex_height = Utilities::StrtoI(arguments.at(i+1));
		}

		if(arguments.at(i) == "--cortex_width")
		{
			cortex_width = Utilities::StrtoI(arguments.at(i+1));
		}

		if(arguments.at(i) == "--k")
		{
			kMer_size = Utilities::StrtoI(arguments.at(i+1));
		}

		if(arguments.at(i) == "--threads")
		{
			threads = Utilities::StrtoI(arguments.at(i+1));
		}

		if(arguments.at(i) == "--onlyPASS")
		{
			onlyPASS = Utilities::StrtoI(arguments.at(i+1));
		}
		
		if(arguments.at(i) == "--maximumHaplotypePairs")
		{
			maximumHaplotypePairs = Utilities::StrtoI(arguments.at(i+1));
		}
		
		if(arguments.at(i) == "--regions")
		{
			regions = arguments.at(i+1);
		}		
	}

	if(vcfFile.length() == 0)
	{
		errEx("Please provide parameter --vcf");
	}
	if(referenceGenome.length() == 0)
	{
		errEx("Please provide parameter --referenceGenome");
	}
	if(deBruijnGraph.length() == 0)
	{
		errEx("Please provide parameter --deBruijnGraph (Cortex 1-colour binary)");
	}
	if(outputDirectory.length() == 0)
	{
		errEx("Please provide parameter --outputDirectory");
	}

	if(! Utilities::fileExists(vcfFile))
	{
		errEx("--vcf specifies a non-existing file.");
	}
	if(! Utilities::fileExists(referenceGenome))
	{
		errEx("--referenceGenome specifies a non-existing file.");
	}
	if(! Utilities::fileExists(deBruijnGraph))
	{
		errEx("--deBruijnGraph specifies a non-existing file.");
	}
	if(! Utilities::directoryExists(outputDirectory))
	{
		Utilities::makeDir(outputDirectory);
	}
	assert(Utilities::directoryExists(outputDirectory));

	if(kMer_size == 31)
	{
		validateCompleteVCF<1, 31>(vcfFile, referenceGenome, deBruijnGraph, cortex_height, cortex_width, maximumHaplotypePairs, outputDirectory, threads, onlyPASS, regions);
	}
	else
	{
		errEx("Unsupported kMer size - use a different value for --k.");
	}

	return 0;
}

void errEx(std::string message)
{
	std::cerr << message << "\n" << std::flush;
	exit(1);
}
