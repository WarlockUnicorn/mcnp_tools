//	*******************************************************************************************
//	Description:
//		C++ PTRAC parser. (Update this as program evolves)
//
//	Use: 
//		>PTRAC_Parse.exe <flags>
//		Flags:
//			-p <ptrac file>: replace <?> with ptrac file name, e.g. ptrac
//			-g <output file>: replace <?> with output file name for general information, 
//				e.g. out.text
//			-a <output file>: replace <?> with an output file name for track information, 
//				e.g. out.asci
//
//	Environment:
//		This software and related is being purposefully designed to NOT be system dependent.
//
//	Community:
//		This software is being created with the low and medium energy nuclear physics and 
//		nuclear engineering communities in mind. It is hoped that this software will be used
//		and developed by both academic and applied nuclear science researchers.
//
//	Author:
//		Ryan Clement	( Original Author )
//		E-mail:
//
//	Copyright Information: (as applicable ... stay tuned)
//		April, 2011	
//	*******************************************************************************************

#include <iostream>
#include <iomanip>
#include <string>
#include "pFast_Parse.hh"
using namespace std;

int main( int argc, char * const argv[] )
{
  // Execution line parameters
  cout << "Parsing execution line parameters:" << endl;
  cout << setw(25) << "# of Arguments: " << argc << endl;
  cout << setw(25) << "Executable: " << argv[0] << endl;
  //char* iFileP  = "";	   // ptrac input file
  string iFileP;
  bool  iYesP   = false;   // file given?
  string oFileG;
  bool  oYesG   = false;   // file given?
  string oFileA;
  bool  oYesA   = false;   // file given?
  for ( int i=1; i<argc-1; i+=2 )
  {
	  if ( string( argv[i] ) == "--p" )
	  {
		  iYesP  = true;
		  iFileP = argv[i+1];
		  cout << setw(25) << "PTRAC File: " << iFileP << endl;
		  continue;
	  }
	  else if ( string(argv[i]) == "--g" )
      {
	      oYesG  = true;
		  oFileG = argv[i+1];
		  cout << setw(25) << "Basic Output File: " << oFileG << endl;
		  continue;
	  }
	  else if ( string(argv[i]) == "--a" )
	  {
		  oYesA  = true;
		  oFileA = argv[i+1];
		  cout << setw(25) << "Track Output File: " << oFileA << endl;
		  continue;
	  }
  } // End for-loop
    

  // Create PTRAC file reader and output writers
  ptracParser	*pPar	= new ptracParser();

  if ( iYesP && oYesG && oYesA) {
	pPar->openP( iFileP.c_str() );
	pPar->openG( oFileG.c_str() );
    pPar->openA( oFileA.c_str() );
	pPar->readP();
  }
  
  // Close Files
  if ( pPar->isOpenP ) {
	pPar->closeP();
    pPar->closeG();
    pPar->closeA();
  }

  return 0;
  
} //	End Main Program
  //	*******************************************************************************************
