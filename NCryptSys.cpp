// Byron Zaragoza
// September 23, 2013
// CSE-40567
// Encryption System
// ------------------

#include <algorithm>
#include <bitset>
#include <fstream>
#include <math.h>
#include <sstream>
#include <string>

using namespace std;

// READ FILE CONTENTS
// ------------------
string readFile( const char* fileName ){
	ifstream file;
	string fileText;
	string lineText;

	file.open( fileName );
	while ( !file.eof() ){
		getline( file, lineText );
		fileText.append( lineText );
	}
	file.close();

	return fileText;
}

// PREPROCESSING
// -------------
void preprocessing( string &inputString ){
	inputString.erase( ::remove_if( inputString.begin(), inputString.end(), ::isspace ), inputString.end() );
	inputString.erase( ::remove_if( inputString.begin(), inputString.end(), static_cast<int(*)(int)>(&ispunct) ), inputString.end() );
}

// SUBSTITUTION
// ------------
string substitution( string &inputString, string inputKey ){
	string outputString;
	for( int i = 0, j = 0; i < inputString.length(); ++i ){
		char c = inputString[i];

		if ( c >= 'a' && c <= 'z' )
			c += 'A' - 'a';
		else if ( c < 'A' || c > 'Z' )
			continue;

		outputString += ( c + inputKey[j] - 2*'A') % 26 + 'A';
		j = (j + 1) % inputKey.length();
	}

	return outputString;
}

// PADDING
// -------
void padding( string &inputString ){
	while ( inputString.length() % 16 != 0 )
		inputString.append( "A" );
}

// SHIFT ROWS
// ----------
void shiftRows( string &inputString ){
	char temp, temp2;
	for ( int block = 0; block < inputString.length() / 16; ++block )
		for ( int row = 1; row < 4; ++row ){
			int startIndex = block*16 + row*4;

			if ( row == 1 ){
				temp = inputString[startIndex];
				inputString[startIndex] = inputString[startIndex+1];
				inputString[startIndex+1] = inputString[startIndex+2];
				inputString[startIndex+2] = inputString[startIndex+3];
				inputString[startIndex+3] = temp;
			} else if ( row == 2 ){
				temp = inputString[startIndex+1];
				temp2 = inputString[startIndex+2];
				inputString[startIndex+1] = inputString[startIndex+3];
				inputString[startIndex+2] = inputString[startIndex];
				inputString[startIndex+3] = temp;
				inputString[startIndex] = temp2;
			} else if ( row == 3 ){
				temp = inputString[startIndex+3];
				inputString[startIndex+3] = inputString[startIndex+2];
				inputString[startIndex+2] = inputString[startIndex+1];
				inputString[startIndex+1] = inputString[startIndex];
				inputString[startIndex] = temp;
			}
		}
}

// PARITY BIT
// ----------
string parityBit( string &inputString ){
	string outputString;

	int baseTen, numOnes;
	stringstream hexVal;
	for ( int index = 0; index < inputString.length(); ++index ){
		baseTen = inputString[index];
		numOnes = 0;

		while ( baseTen > 0 ){
			if ( baseTen % 2 != 0 )
				numOnes++;
			baseTen /= 2;
		}

		if ( numOnes % 2 == 0 )
			baseTen = inputString[index];
		else
			baseTen = inputString[index] + 128;

		hexVal << hex << baseTen;
	}

	outputString.append( hexVal.str() );
	return outputString;
}

// MULTIPLY 8-BIT BINARY WITH 2 OR 3 **** INCOMPLETE ****
// ------------------------------------------------------
string RGFMul( string hexVal, int y ){
	string outputString;
	int decVal = (int)strtol( hexVal.c_str(), NULL, 16 );

	// FIGURE OUT HOW TO SHIFT-LEFT AND CONVERT BETWEEN DATA-VALUES	

	// PUT OUTPUT INTO OUTPUTSTRING
	return outputString;
}

// MIX COLUMNS **** INCOMPLETE ****
// --------------------------------
string mixColumns( string &inputString ){
	string outputString;
	stringstream hexVal;
	for ( int block = 0; block < inputString.length() / 32; ++block ){
		// FOR EACH COLUMN, APPLY RGF FORUMLA		
	} 

	// CONTINUE ADDING CORRECT VALUES TO HEX STRING STREAM AND
	// APPEND TO OUTPUTSTRING.
	return outputString;
}

// MAIN FUNCTION
// -------------
int main ( int argc, const char* argv[] ){
	ofstream outputFile("output.txt");
	string inputString = readFile( argv[1] );
	string inputKey = readFile( argv[2] );

	// PREPROCESSING
	// -------------
	preprocessing( inputString );
	outputFile << "Preprocessing:" << endl;
	outputFile << inputString << endl << endl; 

	// SUBSTITUTION
	// ------------
	inputString = substitution( inputString, inputKey );
	outputFile << "Substitution:" << endl;
	outputFile << inputString << endl << endl; 

	// PADDING
	// -------
	padding( inputString );
	outputFile << "Padding:" << endl;
	for ( int i = 0; i < inputString.length(); i+=4 ){
		if ( i != 0 && i%16 == 0 )
			outputFile << endl;	
		outputFile << inputString[i] << " "
			   << inputString[i+1] << " "
			   << inputString[i+2] << " "
			   << inputString[i+3] << endl; 
	}
	outputFile << endl;	

	// SHIFT ROWS
	// ----------
	shiftRows( inputString );
	outputFile << "ShiftRows:" << endl;
	for ( int i = 0; i < inputString.length(); i+=4 ){
		if ( i != 0 && i%16 == 0 )
			outputFile << endl;	
		outputFile << inputString[i] << " "
			   << inputString[i+1] << " "
			   << inputString[i+2] << " "
			   << inputString[i+3] << endl; 
	}
	outputFile << endl;	

	// PARITY BIT
	// ----------
	inputString = parityBit( inputString );
	outputFile << "Parity:" << endl;
	for ( int i = 0; i < inputString.length(); i+=8 ){
		if ( i != 0 && i%32 == 0 )
			outputFile << endl;	
		outputFile << inputString[i] << inputString[i+1] << " "
			   << inputString[i+2] << inputString[i+3] << " "
			   << inputString[i+4] << inputString[i+5] << " "
			   << inputString[i+6] << inputString[i+7] << " " << endl; 
	}
	outputFile << endl;

	// MIX COLUMNS **** INCOMPLETE ****
	// --------------------------------
//	inputString = mixColumns( inputString );
//	outputFile << "MixColumns:" << endl;
//	outputFile << inputString << endl; 

}
