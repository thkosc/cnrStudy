#include <functional>
#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <getopt.h>

#include "canvas/Persistency/Common/Assns.h"
#include "canvas/Utilities/InputTag.h"

#include "gallery/Event.h"

#include "lardataobj/RecoBase/Wire.h"
#include "lardataobj/RawData/RawDigit.h"


#include "TFile.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TMath.h"
#include "TH1.h"

int iev = -1;

// larsooft root file name
std::string fFileName;

// config faile name
std::string fConfigFileName;
std::fstream fConfig;

// label for art/larsoft objects
std::string fRawDigit;
std::string fRecobWire;

//art::InputTag pandoratrack_tag{str_pandoratrack};
//art::InputTag artTrackHit_tag{str_artTrackHit};
art::InputTag tagRawDigit;
art::InputTag tagRecobWire;


