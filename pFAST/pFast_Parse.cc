//	*******************************************************************************************
//	Description:
//		 PTRAC parser object/function file. (Update this as program evolves)
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
#include <fstream>
#include <string>
#include <vector>
#include "pFast_Parse.hh"
using namespace std;

// *************************************
// *** ptracParser *** class members ***
// *************************************

// ptracParser (***Constructor***)
ptracParser::ptracParser() {
	// ***Data initilization***
	// Bool
	isOpenP = false;
	isOpenG = false;
	isOpenA = false;
	// Dic
	keyDic[1] = "BUFFER";
	keyDic[2] = "CELL";
	keyDic[3] = "EVENT";
	keyDic[4] = "FILE";
	keyDic[5] = "FILTER";
	keyDic[6] = "MAX";
	keyDic[7] = "MENP";
	keyDic[8] = "NPS";
	keyDic[9] = "SURFACE";
	keyDic[10] = "TALLY";
	keyDic[11] = "TYPE";
	keyDic[12] = "VALUE";
	keyDic[13] = "WRITE";
	varDic[1] = "NPS";
	varDic[2] = "FIRST_EVENT_TYPE";
	varDic[3] = "NCL(3)";
	varDic[4] = "NSF(4)";
	varDic[5] = "JPTAL";
	varDic[6] = "TAL";
	varDic[7] = "Next_Event_Type";
	varDic[8] = "NODE";
	varDic[9] = "NSR";
	varDic[10] = "NXS";
	varDic[11] = "NTYN";
	varDic[12] = "NSF(12)";
	varDic[13] = "Angle";
	varDic[14] = "NTER";
	varDic[15] = "Branch#";
	varDic[16] = "IPT";
	varDic[17] = "NCL(17)";
	varDic[18] = "MAT";
	varDic[19] = "NCP";
	varDic[20] = "XXX";
	varDic[21] = "YYY";
	varDic[22] = "ZZZ";
	varDic[23] = "UUU";
	varDic[24] = "VVV";
	varDic[25] = "WWW";
	varDic[26] = "ERG";
	varDic[27] = "WGT";
	varDic[28] = "TME";
	eventDic[1000] = "SOURCE";
	eventDic[2000] = "BANK";
	eventDic[3000] = "SURFACE";
	eventDic[4000] = "COLLISION";
	eventDic[5000] = "TERMINATION";
	eventDic[9000] = "LAST_EVENT";
	EvntDic[1] = "src->1000";
	EvntDic[2] = "src->1000";
	EvntDic[3] = "bnk->2000";
	EvntDic[4] = "bnk->2000";
	EvntDic[5] = "sur->3000";
	EvntDic[6] = "sur->3000";
	EvntDic[7] = "col->4000";
	EvntDic[8] = "col->4000";
	EvntDic[9] = "ter->5000";
	EvntDic[10]= "ter->5000";
	MTDic[2] = "Elastic Scattering";
	MTDic[18] = "Fission";
	MTDic[19] = "1st Chance n-Fission";
	MTDic[20] = "2nd Chance n-Fission";
	MTDic[21] = "3rd Chance n-Fission";
	MTDic[51] = "n+Res. 1st Ex. State";
	MTDic[52] = "n+Res. 2nd Ex. State";
	MTDic[53] = "n+Res. 3rd Ex. State";
	MTDic[54] = "n+Res. 4th Ex. State";
	MTDic[55] = "n+Res. 5th Ex. State";
	MTDic[56] = "n+Res. 6th Ex. State";
	MTDic[57] = "n+Res. 7th Ex. State";
	MTDic[58] = "n+Res. 8th Ex. State";
	MTDic[59] = "n+Res. 9th Ex. State";
	MTDic[60] = "n+Res. 10th Ex. State";
	MTDic[61] = "n+Res. 11th Ex. State";
	MTDic[62] = "n+Res. 12th Ex. State";
	MTDic[63] = "n+Res. 13th Ex. State";
	MTDic[64] = "n+Res. 14th Ex. State";
	MTDic[65] = "n+Res. 15th Ex. State";
	MTDic[66] = "n+Res. 16th Ex. State";
	MTDic[67] = "n+Res. 17th Ex. State";
	MTDic[68] = "n+Res. 18th Ex. State";
	MTDic[69] = "n+Res. 19th Ex. State";
	MTDic[70] = "n+Res. 20th Ex. State";
	MTDic[71] = "n+Res. 21th Ex. State";
	MTDic[72] = "n+Res. 22th Ex. State";
	MTDic[73] = "n+Res. 23th Ex. State";
	MTDic[74] = "n+Res. 24th Ex. State";
	MTDic[75] = "n+Res. 25th Ex. State";
	MTDic[76] = "n+Res. 26th Ex. State";
	MTDic[77] = "n+Res. 27th Ex. State";
	MTDic[78] = "n+Res. 28th Ex. State";
	MTDic[79] = "n+Res. 29th Ex. State";
	MTDic[80] = "n+Res. 30th Ex. State";
	MTDic[81] = "n+Res. 31th Ex. State";
	MTDic[82] = "n+Res. 32th Ex. State";
	MTDic[83] = "n+Res. 33th Ex. State";
	MTDic[84] = "n+Res. 34th Ex. State";
	MTDic[85] = "n+Res. 35th Ex. State";
	MTDic[86] = "n+Res. 36th Ex. State";
	MTDic[87] = "n+Res. 37th Ex. State";
	MTDic[88] = "n+Res. 38th Ex. State";
	MTDic[89] = "n+Res. 39th Ex. State";
	MTDic[90] = "n+Res. 40th Ex. State";
	MTDic[91] = "n+Continuum";
	// Int
	pFlenInt = 0;
	nPKW = 0;
	nps_len = 0;
	src1_len = 0;
	src2_len = 0;
	bnk1_len = 0;
	bnk2_len = 0;
	sur1_len = 0;
	sur2_len = 0;
	col1_len = 0;
	col2_len = 0;
	ter1_len = 0;
	ter2_len = 0;
	srcInt = 1000;
	bnkInt = 2000;
	surInt = 3000;
	colInt = 4000;
	terInt = 5000;
	endInt = 9000;
	maxEvnt = 0;
}

// EVNT constructor
EVNT::EVNT() {
	// ***Data Init***
}

// readP
void ptracParser::readP() {
	if ( isOpenP ) {
		int kw_i = 1;					// keyword::counter
		int kw_j = 1;					// keyword::position counter
		const int keyMaxInt = 10;		// keyword::num of items per line
		float keyInt[keyMaxInt];
		const int varMaxInt = 20;		// var::num of items per line
		int varInt[varMaxInt];
		int varSum = 0;
		string tmpStr;
		int tmpInt;
		// Rem: pFlenInt is length of PTRAC file
		//while ( getline( pIn, tmpStr ) ) {
		//	pFlenInt++;
		//}
		//cout << "PTRAC file has " << pFlenInt << " lines." << endl;
		//gOut << "PTRAC file has " << pFlenInt << " lines." << endl;
		//pIn.clear();
		//pIn.seekg( 0, ios_base::beg ); // Reset file Ptr to beg
		pIn >> tmpInt;
        if ( tmpInt != -1) {
			cout << "WARNING: Is this a PTRAC file?" << endl;
		}
		for (int i=0; i<3; i++) {
			getline( pIn, tmpStr ); // Move to line #3
		}
		pFtitle = tmpStr;
		cout << "PTRAC file title: " << pFtitle << endl;
		gOut << "PTRAC file title: " << pFtitle << endl;
		// *** Read Keywords
		cout << "Processing KEYWORDS:" << endl;
		gOut << "Processing KEYWORDS:" << endl;
		// start with 1st line ( *line #4* in PTRAC file)
		for (int ii=0; ii<keyMaxInt; ii++) {
			pIn >> keyInt[ii];
			if ( ii==0 ) {
				nPKW = keyInt[0];
				cout << "Number of PTRAC keywords: " << nPKW << endl;
				gOut << "Number of PTRAC keywords: " << nPKW << endl;
			}
		}
		while ( 1 ) {
			print_keyDic( kw_i );
			kw_i++;
			if ( keyInt[kw_j] != 0 ) {
				if ( keyInt[kw_j] > 1 ) {
					cout << "WARNING: Extend Code!" << endl;
					gOut << "WARNING: Extend Code!" << endl;
				}
				kw_j++;
				if ( kw_j > 9 ) {
					for ( int ii=0; ii<keyMaxInt; ii++) {
						pIn >> keyInt[ii];
						kw_j=0;
					}
				}
				cout << keyInt[kw_j] << endl;
				gOut << keyInt[kw_j] << endl;
			}
			else {
				cout << "EMPTY" << endl;
				gOut << "EMPTY" << endl;
			}
			kw_j++;
			if ( kw_j > 9 ) {
				for ( int ii=0; ii<keyMaxInt; ii++) {
					pIn >> keyInt[ii];
					kw_j=0;
				}
			}
			if ( kw_i > nPKW ) break;
		}
		// *** Read Variable Numbers
		for ( int ii=0; ii < varMaxInt; ii++ ) {
			pIn >> varInt[ii];
			if ( ii < 11 ) {			// Rem: N12,13 are special
				varSum+=varInt[ii];		// and N14-20 are not used
			}
		}
		const int varTSum = varSum;
		int varTInt[varTSum];	// var::keys (Type)
		for ( int ii=0; ii < varSum; ii++) {
			pIn >> varTInt[ii];
		}
		if ( varInt[12] == 4 ) {
			cout << "Note: PTRAC file has real*4 output" << endl;
			gOut << "Note: PTRAC file has real*4 output" << endl;
		}
		else {
			cout << "Note: PTRAC file has real*8 output" << endl;
			gOut << "Note: PTRAC file has real*8 output" << endl;
		}
		nps_len = varInt[0];
		src1_len = varInt[1];
		src2_len = varInt[2];
		bnk1_len = varInt[3];
		bnk2_len = varInt[4];
		sur1_len = varInt[5];
		sur2_len = varInt[6];
		col1_len = varInt[7];
		col2_len = varInt[8];
		ter1_len = varInt[9];
		ter2_len = varInt[10];
		cout << "Total number of variables in event lines: " << varSum << endl;
		gOut << "Total number of variables in event lines: " << varSum << endl;
		cout << "Number of variables on the NPS line: " << varInt[0] << endl;
		gOut << "Number of variables on the NPS line: " << varInt[0] << endl;
		for ( int ii=0; ii < varInt[0]; ii++) {
			print_varDic( varTInt[ii] );
			if ( varTInt[ii] == 1 ) {
				npsPosInt = ii; // set NPS position
			}
			if ( varTInt[ii] == 2 ) {
				npsETypePosInt = ii; // set First_Event_Type position
			}
			cout << " ";
			gOut << " ";
		}
		cout << endl;
		gOut << endl;
		tmpInt=nps_len;
		for ( int iii=1; iii<6; iii++ ) {
			cout << endl;
			cout << "Number of variables on the 1st event line for " << EvntDic[2*iii-1] << ": " << varInt[2*iii-1] << endl;
			gOut << "Number of variables on the 1st event line for " << EvntDic[2*iii-1] << ": " << varInt[2*iii-1] << endl;
			for ( int ii=tmpInt; ii < varInt[2*iii-1]+tmpInt; ii++) {
				print_varDic( varTInt[ii] );
				if ( iii == 1 ) {
					if ( varTInt[ii] == 7 ) {
						nextETypePosInt = ii-tmpInt; // based on source position (assumed same for rest!)
					}
					if ( varTInt[ii] == 8 ) {
						srcMPosInt = ii-tmpInt; // set NODE (multiplicity) position for source event (assumed same for rest!)
                        colMPosInt = srcMPosInt;
					}
				}
                if ( iii == 2 ) {
                    if ( varTInt[ii] == 10 ) {
						bnkNXSPosInt = ii-tmpInt;       // NXS
					}
                    if ( varTInt[ii] == 19 ) {
						bnkCPosInt = ii-tmpInt;         // NCP
					}
                    if ( varTInt[ii] == 11 ) {
						bnkRPosInt = ii-tmpInt;         // NTYN
					}
				}
                if ( iii == 3 ) {
                    if ( varTInt[ii] == 17 ) {
						surCELLPosInt = ii-tmpInt;      // CELL
					}
				}
                if ( iii == 4 ) {
					if ( varTInt[ii] == 10 ) {
						colNXSPosInt = ii-tmpInt;       // NXS
					}
                    if ( varTInt[ii] == 11 ) {
						colRPosInt = ii-tmpInt;         // NTYN
					}
                    if ( varTInt[ii] == 19 ) {
						colCPosInt = ii-tmpInt;         // NCP
					}
                    if ( varTInt[ii] == 17 ) {
						colCELLPosInt = ii-tmpInt;      // CELL
					}
				}
				cout << " ";
				gOut << " ";
			}
			cout << endl;
			gOut << endl;
			tmpInt+=varInt[2*iii-1];
			cout << endl;
			cout << "Number of variables on the 2nd event line for " << EvntDic[2*iii] << ": " << varInt[2*iii] << endl;
			gOut << "Number of variables on the 2nd event line for " << EvntDic[2*iii] << ": " << varInt[2*iii] << endl;
			for ( int ii=tmpInt; ii < varInt[2*iii]+tmpInt; ii++) {
				print_varDic( varTInt[ii] );
				if ( iii == 1 ) {
					if ( varTInt[ii] == 26 ) {
						srcEPosInt = ii-tmpInt; // set ERG position for source event
					}
					if ( varTInt[ii] == 28 ) {
						srcTPosInt = ii-tmpInt; // set TME position for source event
					}
					if ( varTInt[ii] == 20 ) {
						srcXPosInt = ii-tmpInt; // set X position for source event
					}
					if ( varTInt[ii] == 21 ) {
						srcYPosInt = ii-tmpInt; // set Y position for source event
					}
					if ( varTInt[ii] == 22 ) {
						srcZPosInt = ii-tmpInt; // set Z position for source event
					}
				}
				if ( iii == 2 ) {
					if ( varTInt[ii] == 26 ) {
						bnkEPosInt = ii-tmpInt; // set ERG position for bank event
					}
					if ( varTInt[ii] == 28 ) {
						bnkTPosInt = ii-tmpInt; // set TME position for bank event
					}
					if ( varTInt[ii] == 20 ) {
						bnkXPosInt = ii-tmpInt; // set X position for bank event
					}
					if ( varTInt[ii] == 21 ) {
						bnkYPosInt = ii-tmpInt; // set Y position for bank event
					}
					if ( varTInt[ii] == 22 ) {
						bnkZPosInt = ii-tmpInt; // set Z position for bank event
					}
				}
                if ( iii == 3 ) {
					if ( varTInt[ii] == 26 ) {
						surEPosInt = ii-tmpInt; // set ERG position for surf event
					}
                }
                if ( iii == 4 ) {
                    if ( varTInt[ii] == 26 ) {
						colEPosInt = ii-tmpInt; // set ERG position
					}
					if ( varTInt[ii] == 28 ) {
						colTPosInt = ii-tmpInt; // set TME position
					}
					if ( varTInt[ii] == 20 ) {
						colXPosInt = ii-tmpInt; // set X position
					}
					if ( varTInt[ii] == 21 ) {
						colYPosInt = ii-tmpInt; // set Y position
					}
					if ( varTInt[ii] == 22 ) {
						colZPosInt = ii-tmpInt; // set Z position
					}
				}
				if ( iii == 5 ) {
					if ( varTInt[ii] == 20 ) {
						terXPosInt = ii-tmpInt; // set X position for term event
					}
					if ( varTInt[ii] == 21 ) {
						terYPosInt = ii-tmpInt; // set Y position for term event
					}
					if ( varTInt[ii] == 22 ) {
						terZPosInt = ii-tmpInt; // set Z position for term event
					}
				}
				cout << " ";
				gOut << " ";
			}
			cout << endl;
			gOut << endl;
			tmpInt+=varInt[2*iii];	
		}
		// ***Start Event Parsing
		// get 1st line of event data
		cout << endl << "Begin reading event data:" << endl << endl;
		gOut << endl << "Begin reading event data:" << endl << endl;
		
		// Event loop variables
		// 1st line vars (general)
		int lpMax1=0;
		// 2nd line vars (general)
		int lpMax2=0;
		int npsInt[nps_len];
		int lpCntInt=0;
        
		//int zeroCntInt=0;   // number of non-events
        cout << "NPS" << "\t" << "CELL" << "\t" << "TIME" 
             << "\t" << "delT" << "\t" << "Energy" << endl;
        aOut << "NPS" << "\t" << "CELL" << "\t" << "TIME" 
             << "\t" << "delT" << "\t" << "Energy"
             << "\t" << "DetCount" << "\t" << "ZAID"
             << "\t" << "Collision" << endl;
		// ***Start Event Loop
		while ( !pIn.eof() ) {
			// ***** //
            // Now put in flight time and energy in detector!
            // Will need to update simulation!!
            delE = 0.0;             // in MeV
            delT = 0.0;             // in shake (10ns)
            float oldE = 0.0;
            float lightOut = 0.0;
            float firstT = 0.0;
            float lastT = 0.0;
            float winT = 1.0;       // Time window for energy deposition (shake)
            int   cell = 0;         // Interaction Cell
            int   cell1 = 140;      // Detector CELLs (redo this with a vector!)
            int   cell2 = 150;
            int   cell3 = 160;
            int   cell4 = 170;
            int   cell5 = 180;
            int   matCell = 110;
            int   nps = 0;
            int   zaid = 0;
            bool  scatOn = true;
            int   colType = 0;
            int   atm = 0;
            int detCnt=0;
			//EVNT newEvnt;
			for ( int ii=0; ii < nps_len; ii++) {
				pIn >> npsInt[ii];
			}
			if ( pIn.eof() ) {
				cout << "EOF encounter ... begin probe!" << endl << endl;
                gOut << "EOF encounter ... begin probe!" << endl << endl;
				break;
			}
            nps = npsInt[npsPosInt];
			maxEvnt = nps;
			//if ( nps != ( lpCntInt+1 ) ) {
			//	int tmp = 0;
			//	tmp = nps - Ntrack[lpCntInt-1].nps - 1;
			//	//cout << "***Source Event: No Event" << endl;
			//	//cout << "NPS: " << lpCntInt+1 << endl << endl;
			//	zeroCntInt+=tmp;    // number of non-events
			//}
			//newEvnt.nps = npsInt[npsPosInt];
            //cout << "NPS: " << newEvnt.nps << endl;
			//newEvnt.eType = npsInt[npsETypePosInt];
            //cout << "NPS: " << nps << endl;
			eTypeInt = npsInt[npsETypePosInt];
			eTypeSet( eTypeInt, lpMax1, lpMax2 );
            node = 0;
            nodeOld = 0;
			// ***Body of Event Loop
			while ( 1 ) {
                nextPair( lpMax1, lpMax2 );     // load lpV1,lpV2
                eTypeIntOld = eTypeInt;
                eTypeInt = lpV1[nextETypePosInt];
                nodeOld = node;
                node = lpV1[colMPosInt];
                // NEUTRONS served here
                //if ( eTypeIntOld == srcInt ) {
                    //cout << "Source neutron: " << endl;
                    //newInfo( newEvnt );
                    //}
                if ( eTypeIntOld == terInt ) {     // Rem: terInt = 5000
                    //cout << "End of this neutron." << endl;
                    //cout << "Final delE: " << delE << endl;
                    if ( lightOut >= 0.07 ) {
                        detCnt++;
                        cout << nps << "\t" << cell << "\t" << firstT <<
                        "\t" << lastT << "\t" << lightOut << endl;
                        aOut << nps << "\t" << cell << "\t" << firstT <<
                        "\t" << lastT << "\t" << lightOut
                             << "\t" << detCnt << "\t" << zaid << 
                        "\t" << colType << endl;
                    }
                    delE = 0.0;
                    //cout << "Final delT: " << delT << endl;
                    delT = 0.0;
                    oldE = 0.0;
                    lightOut = 0.0;
                    cell = 0;
                    zaid = 0;
                    colType = 0;
                    }
                if ( scatOn && eTypeIntOld==colInt && lpV1[colRPosInt]==2 && lpV1[colCELLPosInt]==matCell ) {
                    zaid = lpV1[colNXSPosInt];
                    colType = 2;
                }
                if ( eTypeIntOld==colInt && lpV1[colRPosInt]!=2 ) { //We assume this will not happen
                                                                    //in a detector ... dangerous?
                    //if ( node != nodeOld ) {
                        //cout << "New neutron:" << endl;
                        //newInfo( newEvnt );
                        if ( lightOut >= 0.07 ) {
                            detCnt++;
                            cout << nps << "\t" << cell << "\t" << firstT <<
                            "\t" << lastT << "\t" << lightOut << endl;
                            aOut << nps << "\t" << cell << "\t" << firstT <<
                            "\t" << lastT << "\t" << lightOut
                                 << "\t" << detCnt << "\t" << zaid 
                                 << "\t" << colType << endl;
                        }
                        //cout << "Final delE: " << delE << endl;
                        delE = 0.0;
                        //cout << "Final delT: " << delT << endl;
                        delT = 0.0;
                        oldE = 0.0;
                        firstT = 0.0;
                        lastT = 0.0;
                        lightOut = 0.0;
                        cell = 0;
                        zaid = lpV1[colNXSPosInt];
                        colType = lpV1[colRPosInt];
                        scatOn = false;
                    //}
                    //else {
                        //cout << "Warning: NODE value did not change: " << nps << endl;
                        //cout << "Node: " << node << " NodeOld: " << nodeOld << endl;
                    //}
                }
                if ( eTypeIntOld==(bnkInt+7) ) {
                    //cout << "New neutron:" << endl;
                    //newInfo( newEvnt );
                    if ( lightOut >= 0.07 ) {
                        detCnt++;
                        cout << nps << "\t" << cell << "\t" << firstT <<
                        "\t" << lastT << "\t" << lightOut << endl;
                        aOut << nps << "\t" << cell << "\t" << firstT <<
                        "\t" << lastT << "\t" << lightOut
                             << "\t" << detCnt << "\t" << zaid 
                             << "\t" << colType << endl;
                    }
                    //cout << "Final delE: " << delE << endl;
                    delE = 0.0;
                    //cout << "Final delT: " << delT << endl;
                    delT = 0.0;
                    oldE = 0.0;
                    firstT = 0.0;
                    lastT = 0.0;
                    lightOut = 0.0;
                    cell = 0;
                    zaid = lpV1[colNXSPosInt];
                    colType = lpV1[colRPosInt];
                    scatOn = false;
                }
                // update oldE
                if ( (eTypeIntOld==surInt) && ( (lpV1[surCELLPosInt]==cell1) ||
                                                (lpV1[surCELLPosInt]==cell2) ||
                                                (lpV1[surCELLPosInt]==cell3) ||
                                                (lpV1[surCELLPosInt]==cell4) ||
                                                (lpV1[surCELLPosInt]==cell5) ) ) {
                    oldE = lpV2[surEPosInt];
                }
                // Let's look for E-dep (scatters)
                if ( (eTypeIntOld==colInt) && (lpV1[colRPosInt]==2) && 
                                              ( (lpV1[colCELLPosInt]==cell1) ||
                                                (lpV1[colCELLPosInt]==cell2) ||
                                                (lpV1[colCELLPosInt]==cell3) ||
                                                (lpV1[colCELLPosInt]==cell4) ||
                                                (lpV1[colCELLPosInt]==cell5) ) ) {
                    delE = oldE - lpV2[colEPosInt];
                    oldE = lpV2[colEPosInt];
                    if ( firstT == 0 ) {
                        firstT = lpV2[colTPosInt];
                    }
                    delT = lpV2[colTPosInt] - firstT;
                    if ( delT < winT ) {
                        lastT = delT;
                        atm = lpV1[colNXSPosInt];
                        if ( (atm==1001) || (atm==6000) ) {
                            //cout << "delE: " << delE << endl;
                            lightOut += nLightOut( atm, delE );
                        }
                        if ( cell == 0 ) {
                            cell = lpV1[colCELLPosInt];
                        }
                    }
                }
                // Done with this event?
				if ( eTypeInt == endInt ) {     // Rem: endInt = 9000
					//cout << "Event END!" << endl;
                    lpV1.clear();
                    lpV2.clear();
                    delE = 0.0;
                    delT = 0.0;
                    lastT = 0.0;
                    firstT = 0.0;
                    oldE = 0.0;
                    lightOut = 0.0;
                    cell = 0;
                    zaid = 0;
                    colType = 0;
                    break;
				}
				eTypeSet( eTypeInt, lpMax1, lpMax2 );
                // Clear data vectors
				lpV1.clear();
				lpV2.clear();
			}
			//Ntrack.push_back( newEvnt );
			lpCntInt+=1;
			// ***** //
		}
		//cout << "Number of NULL events: " << zeroCntInt << endl;
		//gOut << "Number of NULL events: " << zeroCntInt << endl;
		cout << "Number of Events: " << maxEvnt << endl;
        gOut << "Number of Events: " << maxEvnt << endl;
	}
	else {
		cout << "ERROR: PTRAC file not open?" << endl;
        gOut << "ERROR: PTRAC file not open?" << endl;
	}
}

float ptracParser::nLightOut( int atm, float eN ) {
    float a=0.03495;
    float b=0.1424;
    float c=-0.036;
    float lo=0.0;
    if ( atm == 1001 ) {
        lo = (a*eN*eN) + (b*eN) + c;
    }
    if ( atm == 6000 ) {
        lo = 0.02;
    }
    return lo;
}

void ptracParser::newInfo( EVNT &newEvnt ) {
    newEvnt.sT.push_back( lpV2[colTPosInt] );
    //cout << "Birth Time: " << lpV2[colTPosInt] << endl;
    newEvnt.sE.push_back( lpV2[colEPosInt] );
    cout << "Birth Energy: " << lpV2[colEPosInt] << endl;
    newEvnt.sX.push_back( lpV2[colXPosInt] );
    //cout << "Birth X: " << lpV2[colXPosInt] << endl;
    newEvnt.sY.push_back( lpV2[colYPosInt] );
    newEvnt.sZ.push_back( lpV2[colZPosInt] );
}

void ptracParser::nextPair( int lpM1, int lpM2 ) {
    float lp1Int=0.0;
    float lp2Flt=0.0;
    for ( int ii=0; ii<lpM1; ii++) {  // load first line
        pIn >> lp1Int;
        //cout << "lp1Int: " << lp1Int << endl;
        lpV1.push_back( lp1Int );  // I am "coercing" this!
        //cout << lpV1.back() << endl;
    }
    for ( int ii=0; ii<lpM2; ii++) {  // load second line
        pIn >> lp2Flt;
        lpV2.push_back( lp2Flt );
    }
}


// eTypeSet function
// set event type lengths
void ptracParser::eTypeSet( int n, int &lpMax1, int &lpMax2 ) {
    //cout << "Event Type: " << n << endl;
	if ( n==srcInt ) {
		lpMax1 = src1_len;
		lpMax2 = src2_len;
	}
	else if ( n<0 || ( n>=bnkInt && n<=( bnkInt+26 ) ) ) {
		lpMax1 = bnk1_len;
		lpMax2 = bnk2_len;
	}
	else if ( n==surInt ) {
		lpMax1 = sur1_len;
		lpMax2 = sur2_len;
	}
	else if ( n==colInt ) {
		lpMax1 = col1_len;
		lpMax2 = col2_len;
	}
	else if ( n==terInt ) {
		lpMax1 = ter1_len;
		lpMax2 = ter2_len;
	}
	else {
		cout << "Warning: Unknown Event Type!" << endl;
		cout << "n: " << n << endl;
		gOut << "Warning: Unknown Event Type!" << endl;
        abort();
	}
}

// closeP
void ptracParser::closeP() {
  if ( isOpenP ) {
	  pIn.close();
	  isOpenP = false;
  }
  else {
	  cout << "ptracParser::close" << endl; 
	  cout << "No file is currently open." << endl;
  }
}

// closeG
void ptracParser::closeG() {
	if ( isOpenG ) {
		gOut.close();
		isOpenG = false;
	}
	else {
		cout << "ptracParser::close" << endl;
		cout << "No file is currently open." << endl;
	}
}

// closeA
void ptracParser::closeA() {
	if ( isOpenA ) {
		aOut.close();
		isOpenA = false;
	}
	else {
		cout << "ptracParser::close" << endl;
		cout << "No file is currently open." << endl;
	}
}

// print_eventDic
void ptracParser::print_eventDic( const int ievent ) {
	cout << eventDic[ievent] << endl;
}

// print_keyDic
void ptracParser::print_keyDic( const int ikey ) {
	cout << "*** " << keyDic[ikey] << "::";
}

// print_varDic
void ptracParser::print_varDic( const int ivar ) {
	cout << varDic[ ivar ];
	gOut << varDic[ ivar ];
}

// openP
void ptracParser::openP(const char *infile) {
	if ( isOpenP ) closeP();
	pIn.open( infile );
	if ( pIn.good() ) {
	  isOpenP = true;
	}
	else {
	  cout << "ptracParser::openP" << endl;
      cout << "Unable to open input file:" << infile << endl;
	}
}

// openG
void ptracParser::openG( const char *outfile ) {
	if ( isOpenG ) closeG();
	gOut.open( outfile );
	if ( gOut.good() ) {
		isOpenG = true;
	}
	else {
		cout << "ptracParser::openG" << endl;
		cout << "Unable to open output file:" << outfile << endl;
	}
}

// openA
void ptracParser::openA( const char *outfile ) {
	if ( isOpenA ) closeA();
	aOut.open( outfile );
	if ( aOut.good() ) {
		isOpenA = true;
	}
	else {
		cout << "ptracParser::openA" << endl;
		cout << "Unable to open output file:" << outfile << endl;
	}
}


