//	*******************************************************************************************
//	Description:
//		C++ PTRAC parser header file. (Update this as program evolves)
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

#ifndef PTRAC_PARSE_HH
#define PTRAC_PARSE_HH

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class FISSEVNT {	// really creative name
public: 
	// constructor
	FISSEVNT();
	// function
	// int
    int ncp;
    vector< int > dep;      // event depth
	// float
    vector< float > sX;     // start X
    vector< float > sY;     // start Y
    vector< float > sZ;     // start Z
	vector< float > sT;     // start Time
	vector< float > sE;     // start Energy
	//vector< float > sW;   // start weight
private:
	// float
	// int
};

class EVNT {	// really creative & inventive name
public: 
	// constructor
	EVNT();
	// function
	// int
	int nps;
	int eType;
	// float
    vector< float > sX;     // start X
    vector< float > sY;     // start Y
    vector< float > sZ;     // start Z
	vector< float > sE;     // start Energy
	vector< float > sT;     // start Time
    vector< float > dE;     // energy deposited in cell
    vector< int > cell;     // cell (det) where energy deposited
    // friend
    // friend class FISSEVNT;
    // vector< FISSEVNT > fE;
private:
	// float
	// int
};

class ptracParser {
 public:
	// constructor
	ptracParser();
	// function
	void openP( const char *infile );
	void openG( const char *outfile );
    void openA( const char *outfile );
	void readP();
	void closeP();
	void closeG();
    void closeA();
	void print_pFileLine( const int lnum );
	void print_pFLine( const int lnum );
	void print_keyDic( const int ikey );
	void print_varDic( const int ivar );
	void print_eventDic( const int ievent );
	void eTypeSet( int, int&, int& );
    void nextPair( int, int );
    void newInfo( EVNT & );
    float nLightOut( int, float );
	// bool
	bool isOpenP;
	bool isOpenG;
	bool isOpenA;
	// int
    int rtrnCntr;
	int pFlenInt;
    int eTypeInt;
    int eTypeIntOld;
    int node;
    int nodeOld;
    float delE;
    float delT;
    vector< int > lpV1;
    vector< float > lpV2;
	int nps_len;
	int src1_len;
	int src2_len;
	int bnk1_len;
	int bnk2_len;
	int sur1_len;
	int sur2_len;
	int col1_len;
	int col2_len;
	int ter1_len;
	int ter2_len;
	int srcInt;
	int bnkInt;
	int surInt;
	int colInt;
	int terInt;
	int endInt;
	int maxEvnt;                // for (-2) events (non-fission neutrons)
    int xnEvntNode;
	int npsPosInt;				// position of NPS entry on NPS line
	int srcEPosInt;				// position of Energy on source line (first -- not banked)
    int colEPosInt;
	int bnkEPosInt;
    int surEPosInt;
    int colNXSPosInt;
    int bnkNXSPosInt;
    int colCELLPosInt;
    int surCELLPosInt;
    int colRPosInt;             // reaction (NTYN) position
    int bnkRPosInt;             // reaction (NTYN) position
    int colCPosInt;             // # of collisions (NCP) position
    int bnkCPosInt;             // # of collisions (NCP) position
	int srcTPosInt;				// position of Time on source line (first -- not banked)
	int bnkTPosInt;
    int colTPosInt;
	int srcXPosInt;
	int bnkXPosInt;
    int colXPosInt;
	int terXPosInt;
	int srcYPosInt;
	int bnkYPosInt;
    int colYPosInt;
	int terYPosInt;
	int srcZPosInt;
	int bnkZPosInt;
    int colZPosInt;
	int terZPosInt;
	int srcMPosInt;				// position of Node (multiplicity) on source line (first -- not banked)
    int colMPosInt;				// position of Node (multiplicity) on collision line (first -- not banked)
	int npsETypePosInt;			// position of First_Event_Type on NPS line
	int nextETypePosInt;
	// float
	float nPKW; // number of PTRAC keywords

 private:
	 // streams
	 ifstream pIn;		// PTRAC file ( input )
	 ofstream gOut;	// General info from PTRAC file ( output )
	 ofstream aOut;	// ASCI file for plotting PTRAC data ( output )
	 // vector
	 //vector< vector< float > > pFvec;
	 // string
	 string pFtitle;
	 // function
	 //void strip( const vector< string > *someVec );
	 // Dic
	 typedef map< int, string > Dic; // like a dictionary in Python
	 Dic keyDic;
	 Dic varDic;
	 Dic eventDic;
     Dic EvntDic;	
	 Dic MTDic;		// ENDF MT #s
	 // friend
	 friend class EVNT;
	 vector< EVNT > Ntrack;
};


#endif
