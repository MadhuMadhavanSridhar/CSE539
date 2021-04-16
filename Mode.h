#include "State.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <bitset>         // std::bitset
#include <vector>
#include <math.h>       /* pow */
#include <algorithm>
#include <iterator>
#include <sstream>
using namespace std;

class Mode{
private:

	vector<vector<vector<unsigned char>>> block;
	vector<string> strBlock;
	vector<vector<unsigned char>> IV;
	vector<vector<unsigned char>> CFBblock;
	vector<vector<unsigned char>> counter;

	unsigned char State::addition(unsigned char p1, unsigned char p2);
	vector<unsigned char> State::addCoef(vector<unsigned char> coef1, vector<unsigned char> coef2);

	vector<vector<vector<unsigned char>>> PaddingMethod (vector<vector<vector<unsigned char>>> inputBlocks);
	vector<vector<vector<unsigned char>>> InvPaddingMethod (vector<vector<vector<unsigned char>>> plainText, unsigned char m,unsigned char n);

	unsigned char decToHexa(int n);
	int HexTodec(unsigned char n);
	string generateIV();

	void convertBlockToCFB();
	void convertCFBBlockTo();
	void convertBlockToVectString();
	vector<vector<unsigned char>> insertIV(string hexInput);
	string State::validateStringCut(string hexString);




public:
	Mode();
	Mode(vector<vector<vector<unsigned char>>> input);
	Mode(vector<string> strInput);

	void regenerateIV();
	void ECBmodeEncrypt (vector<vector<unsigned char>> key);
	void ECBmodeDecrypt (vector<vector<unsigned char>> key);
	void CBCmodeEncrypt (vector<vector<unsigned char>> key);
	void CBCmodeDecrypt (vector<vector<unsigned char>> key);
	void CFBmodeEncrypt (double s, vector<vector<unsigned char>> plainText, vector<vector<unsigned char>> key);
	void CFBmodeDecrypt (double s, vector<vector<unsigned char>> cipherText, vector<vector<unsigned char>> key);
	void OFBmodeEncrypt (vector<vector<vector<unsigned char>>> plainText, vector<vector<unsigned char>> key);
	void OFBmodeDecrypt (vector<vector<vector<unsigned char>>> cipherText, vector<vector<unsigned char>> key);
	void CTRmodeEncrypt (vector<vector<unsigned char>> counter1, vector<vector<unsigned char>> key);
	void CTRmodeDecrypt (vector<vector<unsigned char>> counter1, vector<vector<unsigned char>> key);
    
    vector<vector<vector<unsigned char>>> getBlock();
    void setBlock();
    vector<vector<unsigned char>> getIV();
    vector<string> getCutUpBlock();
    void viewCutBlocks();





}