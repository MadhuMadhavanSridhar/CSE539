#ifndef Mode_H
#define Mode_H

#include "AESState.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <bitset>         // std::bitset
#include <vector>
#include <math.h>       /* pow */
#include <algorithm>
#include <iterator>
#include <sstream>
#include <chrono>
#include <random>
using namespace std;

class Mode{

private: 
	vector<vector<vector<unsigned char>>> block;
	string strInput;
	vector<string> strBlock;
	vector<vector<unsigned char>> IV;
	vector<vector<unsigned char>> CFBblock;
	vector<vector<unsigned char>> counter1;
	double s; //number of bits in a block, used to invalidate any bad inputs for non-CFB and also give s number of bits for CFB


	unsigned char addition(unsigned char p1, unsigned char p2);

	vector<unsigned char> addCoef(vector<unsigned char> coef1, vector<unsigned char> coef2);

	vector<vector<vector<unsigned char>>> PaddingMethod (vector<vector<vector<unsigned char>>> inputBlocks);

	vector<vector<vector<unsigned char>>> InvPaddingMethod (vector<vector<vector<unsigned char>>> plainText, unsigned char m,unsigned char n);

	unsigned char decToHexa1(int n);
	int HexTodec(unsigned char n);
	string decToHexa(int n);
	string generateIV();
	vector<vector<unsigned char>> convertBlockToCFB(vector<vector<vector<unsigned char>>> blIn);
	vector<vector<vector<unsigned char>>> convertCFBBlockTo(vector<vector<unsigned char>> CFBIn);
	vector<string> convertBlockToVectString(vector<vector<vector<unsigned char>>> blIn);
	string convertBlockToString(vector<vector<vector<unsigned char>>> blIn);
	vector<vector<vector<unsigned char>>> convertStrToBlock(string strIn);
	vector<vector<vector<unsigned char>>> convertStrBlockToBlock(vector<string> strIn);
	vector<vector<unsigned char>> convertStringtoVect(string hexInput);
	string validateStringCut(string hexString);



public:
	Mode();
	Mode(vector<string> strBl);
	Mode(vector<string> strBl, double sBit);
	Mode(string strIn);
	void ECBmodeEncrypt (vector<vector<unsigned char>> key);
	void ECBmodeDecrypt (vector<vector<unsigned char>> key);
	void CBCmodeEncrypt (vector<vector<unsigned char>> key);
	void CBCmodeDecrypt (vector<vector<unsigned char>> key);
	void CFBmodeEncrypt (vector<vector<unsigned char>> key);
	void CFBmodeDecrypt (vector<vector<unsigned char>> key);
	void OFBmodeEncrypt (vector<vector<unsigned char>> key);    
	void OFBmodeDecrypt (vector<vector<unsigned char>> key);
	void CTRmodeEncrypt (vector<vector<unsigned char>> key);
	void CTRmodeDecrypt (vector<vector<unsigned char>> key);
	vector<vector<vector<unsigned char>>> getBlock();
	vector<string> getStrBlock();
	string getString();
	void printStringVect();

};
#endif