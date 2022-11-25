#include "cnrStudy.h"

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Removes 'useless characters' = ':' and spaces from input string.
void RemoveUselessCharacters(std::string& _str)
{
_str.erase(0, _str.find_first_of(":")+1);
while (_str.find(" ")!=_str.npos){int c = _str.find(" "); _str.erase(c, 1);}
return;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// try to open config txt file, throws exception if can't be found
void OpenConfigFile()
{
fConfig.open(fConfigFileName.c_str());
if (!fConfig.is_open()) throw std::runtime_error( std::string("Couldn't open config file with name ") + fConfigFileName);
return;
}


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Init art::InputTags from strings read in config file
void InitLabelNames()
{
std::string line;
while (std::getline(fConfig, line))
	{
	if (line.find("rawdigit")!=line.npos)
		{
		RemoveUselessCharacters(line); 
		fRawDigit = line;
		tagRawDigit = art::InputTag{fRawDigit};
		}
	if (line.find("recobwire")!=line.npos) 
		{
		RemoveUselessCharacters(line); 
		fRecobWire = line; // useless step, should be removed
		tagRecobWire =art::InputTag{fRecobWire};
		}
	}

//std::cout << "rawdigits label = " << fRawDigit << std::endl;
//std::cout << "recobwires label = " << fRecobWire << std::endl;

return;
}


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

void PrintHelp()
{
std::cout << "Help : \n";
std::cout << std::endl;
return;
}



////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

bool GetInputOptions(int argc, char **argv)
{
char cc;

// define a structure for long options
struct option long_option[] =
{
	{"longopt", no_argument, NULL, '0'},
	{NULL, 0, NULL, 0}
};

bool isC = false;
bool isF = false;
bool isHelp = false;

//while ( ( cc=getopt(argc, argv, "f:n:o:v:h")) != -1 )
while ( (cc = getopt_long(argc, argv, "c:f:h0", long_option, 0)) != -1)
{
switch(cc)
	{
	case 'c':
	    fConfigFileName = optarg;
	    isC = true;
	    break;
	case 'f':
	    fFileName = optarg;
	    isF = true;
	    break;
	case 'h':
	    PrintHelp();
	    isHelp = true;
	    break;
	case '0':
	    break;
	} // end switch
} // end while
if (!isC) std::runtime_error("Error : can't run program without option -c specified");
if (!isF) std::runtime_error("Error : can't run program without option -f specified");
return isHelp;
} // END FUNC



/////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
//auto start = std::chrono::system_clock::now();

// read input arguments
try{
	bool isHelp = GetInputOptions(argc, argv);
	if (isHelp) return 0; // leave program if help is printed
} catch (const char* errmsg) {std::cout << errmsg << std::endl;}

  try{
     OpenConfigFile();
}  catch(const char* errmsg){std::cout << errmsg << std::endl;}

  // init labels
  InitLabelNames();

  // Create a vector of length 1, containing the given larsoft reco filename.
  std::vector<std::string> filenames(1, fFileName);

  int evcounter = -1;
  // Loop over events
  for (gallery::Event ev(filenames); !ev.atEnd(); ev.next()) 
  	{
	evcounter++;
	// I might want to look into just one event
	if (iev>=0 && evcounter!=iev ) continue;

	auto const& mRawDigits 	= *ev.getValidHandle< std::vector<raw::RawDigit> >(tagRawDigit);
	auto const& mWires 	= *ev.getValidHandle< std::vector<recob::Wire> >(tagRecobWire);

	std::cout << "sizes = " << mRawDigits.size() << "\t" << mWires.size() << std::endl;

	} // end loop over events






/*
auto end = std::chrono::system_clock::now();
std::chrono::duration<double> elapsed_seconds = end-start;
std::cout << "File analyzed in " << elapsed_seconds.count() << "s" << std::endl;
*/

return 0;
}



