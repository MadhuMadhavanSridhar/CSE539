#include "Mode.h"
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

//private


unsigned char Mode::addition(unsigned char p1, unsigned char p2) {
    return p1 ^ p2;
}

vector<unsigned char> Mode::addCoef(vector<unsigned char> coef1, vector<unsigned char> coef2){
    vector<unsigned char> result;
    for (int i = 0; i < 4; i++){
        result.push_back(addition(coef1[i], coef2[i])); //Most significant NOT first, based on index #, this is different
    }
    return result;
}

vector<vector<vector<unsigned char>>> Mode::PaddingMethod (vector<vector<vector<unsigned char>>> inputBlocks){
    int l = inputBlocks.size();
    int z = inputBlocks[l-1].size();
    int z2 = inputBlocks[l-1][z-1].size();
    int j=0;
    int paddedentries=0;
    int paddedvectors=0;
    vector<unsigned char> indicator = {0x00,0x00,0x00,0x00};
    vector<vector<unsigned char>> padindicator;
    unsigned char res;
    unsigned char res2;
    while(z2<4){
        cout << "\n";
        cout << z << "Adjusting column entries";
        inputBlocks[l-1][z-1].push_back(0x00);
        z2++;
        paddedentries++;
    }
    
    while(!(z%4==0)){
        cout << "\n";
        cout << "Adjusting block length";
        inputBlocks[l-1].push_back(indicator);
        z++;
        paddedvectors++;
    }
    res=decToHexa1(paddedentries);
    res2=decToHexa1(paddedvectors);
    for(int i=0;i<3;i++){
        padindicator.push_back(indicator);
    }
    padindicator.push_back({0x00,0x00,res,res2});
    inputBlocks.push_back(padindicator);
    
    //viewState(inputBlocks[l-1]);
    //viewState(inputBlocks[l]);

    return inputBlocks;
}

 vector<vector<vector<unsigned char>>> Mode::InvPaddingMethod (vector<vector<vector<unsigned char>>> plainText, unsigned char m,unsigned char n){
    plainText.pop_back();
    int l = plainText.size();
    cout << l;
    int z1 = HexTodec(n);
    cout << z1;
     cout << "hell frmo";
    for(int i=0;i<z1;i++){
        plainText[l-1].pop_back();
    }
    int z2 = HexTodec(m);
    cout << z2;
    cout << "hell to";
    for(int i=0;i<z2;i++){
        plainText[l-1][3-n].pop_back();
    }
    
    // for(int j=0,j<(3-n),j++){
        // for(int k=0;k<(3-m);k++){
        //     cout << plainText[l-1][3-n][k];
        // }
    //}
    
    //viewPlain(plainText[l-1]);
    
    return plainText;
 }

unsigned char Mode::decToHexa1(int n)
{
    switch (n) {
  case 0:
    cout << "\n";
    cout << "0x00";
    cout << "\n";
    return 0x00;
  case 1:
    cout << "\n";
    cout << "0x01";
    cout << "\n";
    return 0x01;
  case 2:
    cout << "\n";
    cout << "0x02";
    cout << "\n";
    return 0x02;
  case 3:
    cout << "\n";
    cout << "0x03";
    cout << "\n";
    return 0x03;
    }
}

int Mode::HexTodec(unsigned char n)
{
    switch (n) {
  case 0x00:
    cout << "\n";
    return 0;
  case 0x01:
    cout << "\n";
    return 1;
  case 0x02:
    cout << "\n";
    return 2;
  case 0x03:
    cout << "\n";
    return 3;
    }
}

string Mode::decToHexa(int n)
{
    char hexaDeciNum[100];
    int i = 0;
    string str1;
    while (n != 0) {
        int temp = 0;
        temp = n % 16;
        if (temp < 10) {
            hexaDeciNum[i] = temp + 48;
            i++;
        }
        else {
            hexaDeciNum[i] = temp + 55;
            i++;
        }
 
        n = n / 16;
    }
    for (int j = i - 1; j >= 0; j--){
        std::stringstream ss;
        ss << hexaDeciNum[j];
        std::string out_string = ss.str();
        str1 = str1 + out_string;
    }
    return str1;
}

string Mode::generateIV(){
    char output[2];
    int counter=0;
    string m = "";
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator (seed); 
    unsigned long long res;
    unsigned long long y = 7654321;
    string n;
    char arr1[36]={'9','8','7','6','5','4','3','2','1','0','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    while(counter<16){
    res = generator();
    int temp = res/y;
    int arb = arr1[temp % 36];
    n = decToHexa(arb);
    //cout << n << endl;
    n[0]=tolower(n[0]);
    n[1]=tolower(n[1]);
    m = m + n;
    n = "";
    counter++;
    }

    return m;
}



vector<vector<unsigned char>> Mode::convertBlockToCFB(vector<vector<vector<unsigned char>>> blIn){
	vector<vector<unsigned char>> output;
	vector<unsigned char> mid;
	unsigned char tempChar;
	for(int i = 0; i < blIn.size(); i++){
		for (int j = 0; j < blIn[i].size(); j++){
			for(int k = 0; k< blIn[i][j].size(); k++){
				tempChar = blIn[i][j][k];
				mid.push_back(tempChar);

			}
		}
		output.push_back(mid);
		mid.clear();
	}

	return output;

}
vector<vector<vector<unsigned char>>> Mode::convertCFBBlockTo(vector<vector<unsigned char>> CFBIn){
	vector<vector<vector<unsigned char>>> output;
	vector<vector<unsigned char>> mid2;
	vector<unsigned char> mid;
	unsigned char tempChar;

	for(int i = 0; i < CFBIn.size(); i++){
		for(int j = 0; j < CFBIn[i].size(); j++){
			tempChar = CFBIn[i][j];
			mid.push_back(tempChar);

			if(mid.size()==4){
				mid2.push_back(mid);
				mid.clear();
			}
			
		}
		output.push_back(mid2);
		mid2.clear();

	}
	return output;

}

vector<string> Mode::convertBlockToVectString(vector<vector<vector<unsigned char>>> blIn){
	string strOut = "";
	string tempString = "";
	stringstream ss;
	unsigned int tempChar;
	vector<string> output;

	for (int i = 0; i < blIn.size();i++){
		for(int j = 0; j < blIn[i].size(); j++){
			for(int k = 0; k < blIn[i][j].size(); k++){
				tempChar = blIn[i][j][k];
				ss << hex << tempChar;
				ss >> tempString;
				strOut += tempString;
				ss.str("");
            	ss.clear();
			}
		}

		output.push_back(strOut);
		strOut = "";
	}
	return output;

}

string Mode::convertBlockToString(vector<vector<vector<unsigned char>>> blIn){
	string output = "";
	string tempString = "";
	stringstream ss;
	unsigned int tempChar;

	for (int i = 0; i < blIn.size();i++){
		for(int j = 0; j < blIn[i].size(); j++){
			for(int k = 0; k < blIn[i][j].size(); k++){
				tempChar = blIn[i][j][k];
				ss << hex << tempChar;
				ss >> tempString;
				output += tempString;
				ss.str("");
            	ss.clear();
			}
		}
	}
	return output;

}


vector<vector<vector<unsigned char>>> Mode::convertStrToBlock(string strIn){
	string validChars = "0123456789abcdef";
    vector<vector<unsigned char>> outputVector;
    vector<unsigned char> columnVec;
    string tempHex = "zz"; // should only be 2 letters long
    unsigned int tempChar; // this is weird but it must be int instead of char for stringstream
    std::stringstream ss;
    vector<vector<vector<unsigned char>>> blockVect;

	//validate
	try{
		for(int i = 0; i < strIn.size(); i++){
		    
		    if(validChars.find(strIn[i]) == -1){
		        throw 11;
		    }
		    
		    else {
		        if(i % 2 == 0){
		            tempHex[0] = strIn[i];
		            //cout << tempHex[0] << endl;

		            if(i == (strIn.size()-1)){//PROBlEM?
		            	tempHex[1] = 0b0;

		            	ss << tempHex;
		            	ss >> hex >> tempChar;
		            	//cout << hex << tempChar << endl;
		            	columnVec.push_back(tempChar);
		            	ss.str("");
		            	ss.clear(); //ss will not be reset by "<< tempHex"

		            	//this neceessiarily will be the last one
		                outputVector.push_back(columnVec);
		                columnVec.clear();
		                blockVect.push_back(outputVector);
		            	outputVector.clear();

		            }
		        }
		        
		        else {
		            tempHex[1] = strIn[i]; 
		            //cout << tempHex << endl;
		            
		            ss << tempHex;
		            ss >> hex >> tempChar;
		            //cout << hex << tempChar << endl;
		            columnVec.push_back(tempChar);
		            ss.str("");
		            ss.clear(); //ss will not be reset by "<< tempHex"
		            
		            if(columnVec.size() == 4 || i == strIn.size()-1){ //4 is how many items in a column max, but if at the end it needs to push
		                outputVector.push_back(columnVec);
		                columnVec.clear();
		            }

		            if(outputVector.size() == 4){
		            	blockVect.push_back(outputVector);
		            	outputVector.clear();
		            }
		        }
		    }
		    
		}

		return blockVect;

	} catch (int num){
	    cout << "Something is wrong" << num << endl;

	}

}


vector<vector<vector<unsigned char>>> Mode::convertStrBlockToBlock(vector<string> strIn){ // inputs and validates CFB ONLY IN THIS WAY
	strIn[0] = validateStringCut(strIn[0]);
	int charCount= ceil(s/4);

	string validChars = "0123456789abcdef";
    vector<vector<unsigned char>> outputVector;
    vector<unsigned char> columnVec;
    string tempHex = "zz"; // should only be 2 letters long
    unsigned int tempChar; // this is weird but it must be int instead of char for stringstream
    std::stringstream ss;
    vector<vector<vector<unsigned char>>> blockVect;

	//validate
	try{

		for (int j = 0; j <strIn.size();j++){
			strIn[j] = validateStringCut(strIn[j]); // validate and cut off 0x
			//cout << strIn[j].size()<< endl;

			if (strIn[j].size() > charCount or (strIn[j].size() != charCount and strIn.size()-1 != j)){
				throw 10; // they are different sizes going in except for end - invalid
			}


			for(int i = 0; i < strIn[j].size(); i++){

			    if(validChars.find(strIn[j][i]) == -1){
			        throw 12;
			    }
			    
			    else {
			        if(i % 2 == 0){
			            tempHex[0] = strIn[j][i];
			            //cout << tempHex[0] << endl;

			            if(i == (strIn.size()-1)){//PROBlEM?
			            	tempHex[1] = 0b0;

			            	ss << tempHex;
			            	ss >> hex >> tempChar;
			            	//cout << hex << tempChar << endl;
			            	columnVec.push_back(tempChar);
			            	ss.str("");
			            	ss.clear(); //ss will not be reset by "<< tempHex"

			            	//this neceessiarily will be the last one
			                outputVector.push_back(columnVec);
			                columnVec.clear();
			            }
			        }
			        
			        else {
			            tempHex[1] = strIn[j][i]; 
			            //cout << tempHex << endl;
			            
			            ss << tempHex;
			            ss >> hex >> tempChar;
			            //cout << hex << tempChar << endl;
			            columnVec.push_back(tempChar);
			            ss.str("");
			            ss.clear(); //ss will not be reset by "<< tempHex"
			            
			            if(columnVec.size() == 4 || i == strIn[j].size()-1){ //4 is how many items in a column max, but if at the end it needs to push
			                outputVector.push_back(columnVec);
			                columnVec.clear();
			            }
			        }
			    }
			    
			}
			blockVect.push_back(outputVector);
			outputVector.clear();
		}

		return blockVect;

	} catch (int num){
        cout << "Something is wrong" << num << endl;
	}

}

vector<vector<unsigned char>> Mode::convertStringtoVect(string hexInput){
	//should look something like: 6bc1bee22e409f96e93d7e117393172a 
    //128/4 = 32 char
    string validChars = "0123456789abcdef";
    vector<vector<unsigned char>> outputVector;
    vector<unsigned char> columnVec;
    string tempHex = "zz"; // should only be 2 letters long
    unsigned int tempChar; // this is weird but it must be int instead of char for stringstream
    std::stringstream ss;
    
    //Validate input first
    try {

    	hexInput = validateStringCut(hexInput);
        
        for(int i = 0; i < hexInput.size(); i++){
            
            if(validChars.find(hexInput[i]) == -1){
                throw 1;
            }
            
            else {
                if(i % 2 == 0){
                    tempHex[0] = hexInput[i];
                    //cout << tempHex[0] << endl;

                    if(i == (hexInput.size()-1)){//PROBlEM?
                    	tempHex[1] = 0b0;

                    	ss << tempHex;
                    	ss >> hex >> tempChar;
                    	//cout << hex << tempChar << endl;
                    	columnVec.push_back(tempChar);
                    	ss.str("");
                    	ss.clear(); //ss will not be reset by "<< tempHex"

                    	//this neceessiarily will be the last one
                        outputVector.push_back(columnVec);
                        columnVec.clear();
                    }
                }
                
                else {
                    tempHex[1] = hexInput[i]; 
                    //cout << tempHex << endl;
                    
                    ss << tempHex;
                    ss >> hex >> tempChar;
                    //cout << hex << tempChar << endl;
                    columnVec.push_back(tempChar);
                    ss.str("");
                    ss.clear(); //ss will not be reset by "<< tempHex"
                    
                    if(columnVec.size() == 4 || i == hexInput.size()-1){ //4 is how many items in a column max, but if at the end it needs to push
                        outputVector.push_back(columnVec);
                        columnVec.clear();
                    }
                }
            }
            
        }
        
        return outputVector;
        
    } catch (int num) {
        cout << "Invalid Input For the state" << num << endl;
    }
}

string Mode::validateStringCut(string hexString){
	string cutString = "";
	char firstIn = hexString[0];
	char secIn = hexString[1];
	try {

    	if(hexString.size() > 34){
            throw 3; //too big
        } 

    	if(firstIn == '0' && secIn == 'x'){
    		for (int i = 2; i < hexString.size() ; i++){
    			cutString += hexString[i];
    		}
    		hexString = cutString;
    	}
    	

    	if(hexString.size() > 32){
    		throw 3; //too big
    	}

    	return hexString;

    } catch (int num) {
        cout << "Invalid Input For the state" << num << endl;
    }
}

//public
Mode::Mode(){//fill with nothing I guess? don't use this.
	IV = convertStringtoVect(generateIV());
	counter1 = convertStringtoVect(generateIV());
	s = 128;
	strInput = "";

}

Mode::Mode(vector<string> strBl){ // CFB CANNOT GO IN THIS WAY unless all s = 128
	s = 128;
	IV = convertStringtoVect(generateIV());
	cout << "This is ok 1" << endl; 
	counter1 = convertStringtoVect(generateIV());
	cout << "This is ok 2" << endl; 
	block = convertStrBlockToBlock(strBl); // validates
	cout << "This is ok 3" << endl; 
	strBlock = strBl;
	cout << "This is ok 4" << endl; 
	strInput = convertBlockToString(block);
	cout << "This is ok 5" << endl; 
}

Mode::Mode(vector<string> strBl, double sBit){//need to put in CFB input this way mainly
	s = sBit;
	IV = convertStringtoVect(generateIV());
	counter1 = convertStringtoVect(generateIV());
	block = convertStrBlockToBlock(strBl); // validates
	strBlock = strBl;
	strInput = convertBlockToString(block);
}

Mode::Mode(string strIn){ // CFB CANNOT GO IN THIS WAY unless all s = 128
	s = 128;
	IV = convertStringtoVect(generateIV());
	counter1 = convertStringtoVect(generateIV());
	block = convertStrToBlock(strIn); // validates
	strInput = strIn;
	strBlock = convertBlockToVectString(block);
}

void Mode::ECBmodeEncrypt (vector<vector<unsigned char>> key){
    vector<vector<vector<unsigned char>>> outputBlocks;
    vector<vector<unsigned char>> outCipher;
    int l = block.size();
    int z = block[l-1].size();
    int z2 = block[l-1][z-1].size();
    cout << block[l-1][z-1].size();
    cout << "\n";
    if(!(z%4==0) or z2<4){
        block = PaddingMethod(block);
    }
    cout << "\n";
    for(int i = 0; i<block.size(); i++){
    	AESState myState = AESState(block[i]);

        myState.Cipher(key);
        
        outputBlocks.push_back(myState.getCurrentStateVect());
        
    }
    
    block = outputBlocks;
    strBlock = convertBlockToVectString(block);
    strInput = convertBlockToString(block);

}

void Mode::ECBmodeDecrypt (vector<vector<unsigned char>> key){
    vector<vector<vector<unsigned char>>> plainText;
    vector<vector<unsigned char>> tempBlock;
    vector<vector<unsigned char>> outInvCipher;
    
    //plainText.push_back(tempBlock);
    
    for(int i = 0; i<block.size(); i++){
    	AESState myState = AESState(block[i]);
        
        myState.invCipher(key);
        
        plainText.push_back(myState.getCurrentStateVect());
        
    }
    int l = plainText.size();
    
    for(int i=0;i<4;i++){
        if(plainText[l-1][i][0]==0x00 and plainText[l-1][i][1]==0x00 and plainText[l-1][i][2]==0x00 and plainText[l-1][i][3]==0x00)
        continue;
        else if(i==3 and plainText[l-1][i][0]==0x00 and plainText[l-1][i][1]==0x00){
            cout << plainText[l-1][i][3];
            block = InvPaddingMethod(plainText,plainText[l-1][i][2],plainText[l-1][i][3]);
        }
        else{
            block = plainText;
        }
    }

    strBlock = convertBlockToVectString(block);
    strInput = convertBlockToString(block);

}


void Mode::CBCmodeEncrypt (vector<vector<unsigned char>> key){
    // ssuming that we've transformed the IV into a similar sized "state"
    //the input text would also be transformed to a vector of states. So it can go one by one as many times as needed.
    vector<vector<unsigned char>> tempBlock;
    vector<vector<vector<unsigned char>>> outputBlocks;
    
    int l = block.size();
    int z = block[l-1].size();
    int z2 = block[l-1][z-1].size();
    cout << block[l-1][z-1].size();
    cout << "\n";
    if(!(z%4==0) or z2<4){
        block = PaddingMethod(block);
    }
    cout << "\n";
    
    for(int i = 0; i < IV.size(); i++){
        tempBlock.push_back(addCoef(IV[i],block[0][i]));
    }
    AESState myState = AESState(tempBlock);
    myState.Cipher(key);
    
    outputBlocks.push_back(myState.getCurrentStateVect());
    
    for(int i = 1; i<block.size(); i++){
        tempBlock.clear();
        
        for(int j = 0; j < IV.size(); j++){ 
            tempBlock.push_back(addCoef(myState.getCurrentStateVect()[j],block[i][j]));
        }
        
        myState.setCurrentStateVect(tempBlock);
        myState.Cipher(key);
        
        outputBlocks.push_back(myState.getCurrentStateVect());
        
    }
    
    block = outputBlocks;
    strBlock = convertBlockToVectString(block);
    strInput = convertBlockToString(block);

}

void Mode::CBCmodeDecrypt (vector<vector<unsigned char>> key){
    // ssuming that we've transformed the IV into a similar sized "state"
    //the input text would also be transformed to a vector of states. So it can go one by one as many times as needed.
    vector<vector<unsigned char>> tempBlock;
    vector<vector<vector<unsigned char>>> plainText;

    AESState myState = AESState(block[0]);
    myState.invCipher(key);
    
    vector<vector<unsigned char>> outInvCipher = myState.getCurrentStateVect();
   
    for(int i = 0; i < IV.size(); i++){
        tempBlock.push_back(addCoef(IV[i], outInvCipher[i]));
    }
    
    plainText.push_back(tempBlock);
    
    for(int i = 1; i<block.size(); i++){
        tempBlock.clear();

        myState.setCurrentStateVect(block[i]);
        myState.invCipher(key);
        
        outInvCipher = myState.getCurrentStateVect();
        
        for(int j = 0; j < IV.size(); j++){
            tempBlock.push_back(addCoef(outInvCipher[j], block[i-1][j]));
        }
        
        plainText.push_back(tempBlock);
        
    }
    
    int l = plainText.size();
    
    for(int i=0;i<4;i++){
        if(plainText[l-1][i][0]==0x00 and plainText[l-1][i][1]==0x00 and plainText[l-1][i][2]==0x00 and plainText[l-1][i][3]==0x00)
        continue;
        else if(i==3 and plainText[l-1][i][0]==0x00 and plainText[l-1][i][1]==0x00){
            cout << plainText[l-1][i][3];
            block = InvPaddingMethod(plainText,plainText[l-1][i][2],plainText[l-1][i][3]);
        }
        else{
            block = plainText; // ????
        }
    }

    strBlock = convertBlockToVectString(block);
    strInput = convertBlockToString(block);
    
}

//THIS IS ODD AF
void Mode::CFBmodeEncrypt (vector<vector<unsigned char>> key){
    //plainText can be any number of bits from 1 - 128. This presents some challenges. The inner vector represents those 
    //1-128 bit values in 8 bit unsigned characters, most significant bit as the first unsigned char in the leftmost place,
    //just as in a state. Only this is a 1-dimentional vector and not a 2D vector for concatination/simplification of code purposes. The 2D comes in 
    //with multiple plainTexts like 1, 2, 3 as represented in the diagram
    
    //count s-bits
    //TODO this function and s

	//
	//padding is done manually inside this 

    CFBblock = convertBlockToCFB(block);

    vector<vector<unsigned char>> tempBlock;
    vector<vector<unsigned char>> outputBlockCipher;
    vector<vector<unsigned char>> cipherTextBlock;
    vector<unsigned char> cipherText;
    int remainderInt = (int)s % 8;
    unsigned char tempChar;
    unsigned char tempChar2;


    /*int fullChar = s/8;
	unsigned char n; //number of extra char empty on last. (padding is done within the unsigned char already neccessarily)
    
	string lastString = strBlock[strBlock.size()-1];
	if(remainderInt == 0){
		n = fullChar - lastString.size();
	} else {
		n = fullChar + 1 - lastString.size();
	}
	cout << hex << n << endl;
    if(n != 0){
	    for(int i = 0; i< n; i++){
		    CFBblock[CFBblock.size()-1].push_back(0x00);
	    }
	    
	    vector<unsigned char> paddingVect;
	    for(int i = 0; i < ceil(s/8); i++){
		    if(i != ceil(s/8)-1){
		    	paddingVect.push_back(0x00);
		    } else {
		    	paddingVect.push_back(n);
		    }
		
	    }
	    CFBblock.push_back(paddingVect);
    }*/

    //cout << "Here1"<< endl;
    //cout << ceil(s/8) << endl;
    
    for(int i = 0; i < IV.size(); i++){
        tempBlock.push_back(IV[i]);
    }
    //viewState(IV);

    AESState myState = AESState(tempBlock);
    myState.Cipher(key);
    
    outputBlockCipher = myState.getCurrentStateVect();
    //viewState(outputBlockCipher);
    
    for(int i = 0; i < ceil(s/8); i++){ // ceil might not work here, guess we will find out - it didn't changed to double.
        if(remainderInt != 0 && i == ceil(s/8)-1){
            //note the 8-remainderInt zeros on the end are NOT part of this, they are least significant, but I am limited
            tempChar = outputBlockCipher[i/4][i%4];
            //cout << hex << (int)tempChar << endl;
            tempChar = tempChar >> (8-remainderInt);
            //cout << hex << (int)tempChar << endl;
            tempChar2 = CFBblock[0][i];
            //cout << hex << (int)tempChar2 << endl;
            tempChar2 = tempChar2;
            //cout << hex << (int)tempChar2 << endl;
            tempChar ^= tempChar2;
            //cout << hex << (int)tempChar << endl;
            //tempChar = tempChar << (8-remainderInt);
            //cout << hex << (int)tempChar << endl;
            cipherText.push_back(tempChar);
        }else{
            tempChar = CFBblock[0][i] ^ outputBlockCipher[i/4][i%4];
            cipherText.push_back(CFBblock[0][i] ^ outputBlockCipher[i/4][i%4]);
            //cout << hex << (int)(plainText[0][i] ^ outputBlockCipher[i/Nk][i%Nb]) << endl;
        }
        //cout << "tempChar: ";
        //cout << hex << (int)tempChar << endl; // for 1 this maybe 8 digits long
    }
    //cout << "Here2"<< endl;
    
    
    cipherTextBlock.push_back(cipherText);
    cipherText.clear();
    
    for(int i = 1; i < CFBblock.size(); i++){
        tempBlock.clear();
        //IV shift left s bits
        bitset<128> IVbits;
        bitset<128> cipherTextBits; // won't always have 128, just a space holder
        bitset<128> tempIVholdBits;
        //cout << "Here3"<< endl;
        //viewState(IV);
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                //will always be 128 bits
                tempIVholdBits = IV[j][k];
                //cout << "tempIVholdBits" << tempIVholdBits << endl;
                IVbits |= (tempIVholdBits << (((3-j)*32)+((3-k)*8)));
                //cout << "IVbits " << IVbits << endl;
            }
        }
        //cout << "IVbits Orignial" << IVbits << endl;
        IVbits = IVbits << s; // If s == 128, IV bits are zeroed.
        //cout << "IVbits shift s" << IVbits << endl;
        //cout << "IVbits shift" << IVbits << endl;
        //concat with cipherTextBlock
        //cout << "Here4"<< endl;
        for(int j = 0; j < ceil(s/8); j++){
            if(remainderInt != 0 && j == ceil(s/8)-1){
                //note the 8-remainderInt zeros on the end are NOT part of this, they are least significant, but I am limited
                //cout << "Here6"<< endl;
                //cout << "i: " << i << "j: " << j << endl;
                //cout << "cipherTextBlock[i-1][j]:" << hex << (int)cipherTextBlock[i-1][j] << endl; // PROBLEM RIGHT HERE
                //cipherTextBits |= (cipherTextBlock[i-1][j] >> (8-remainderInt));
                cipherTextBits |= (cipherTextBlock[i-1][j]);
            }else{
                //cout << "cipherTextBlock[i-1][j]:" << hex << (int)cipherTextBlock[i-1][j] << endl;
                tempIVholdBits = cipherTextBlock[i-1][j];
                cipherTextBits |= (tempIVholdBits << ((((int)s/8)-j-1)*8+remainderInt));
                //cout << "((((int)s/8)-j-1)*8+remainderInt): " << dec << ((((int)s/8)-j-1)*8+remainderInt) << endl;
                //cout << "(cipherTextBlock[i-1][j] << ((((int)s/8)-j-1)*8+remainderInt)): " << hex << (tempIVholdBits << ((((int)s/8)-j-1)*8+remainderInt)) << endl;
            }   
        }
        
        IVbits |= cipherTextBits;
        //cout << "IVbits OR" << IVbits << endl;
        bitset<128> tempMask = 0b11111111;
        bitset<128> loadBits;
        
        //cout << "Here5"<< endl;
        //back to vector<unsigned char> form
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                //cout << "j" << j << " k" << k << endl;
                //will always be 128 bits // takes care of anything not 8 divisible
                loadBits = ((IVbits >> (((3-j)*32)+((3-k)*8))) & tempMask);
                //cout << "IVbits" << IVbits << endl;
                //cout << "loadBits" << loadBits <<endl;
                
                unsigned char loadChar = 00000000;
                for(int z = 0; z < 8; z++){
                    //cout << "loadBits[z]" << loadBits[z] <<endl;
                    loadChar |= loadBits[z] << z;
                    //cout << "loadChar"; 
                    //cout << hex << loadChar <<endl;
                    
                }
                IV[j][k] = loadChar;
                //IV[j][k] = (IVbits >> (((3-j)*32)+((3-k)*8))) & 0b11111111;
            }
        }
        //cout << "inputblock: " << endl;
        //viewState(IV);
        
        for(int j = 0; j < IV.size(); j++){
            tempBlock.push_back(IV[j]);
        }
        
        myState.setCurrentStateVect(tempBlock);
        myState.Cipher(key);


        outputBlockCipher = myState.getCurrentStateVect();
        //cout << "outputblock: " << endl;
        //viewState(outputBlockCipher);
        
        for(int j = 0; j < ceil(s/8); j++){ // ceil might not work here, guess we will find out
            if(remainderInt != 0 && j == ceil(s/8)-1){
                //note the 8-remainderInt zeros on the end are NOT part of this, they are least significant, but I am limited
                tempChar = outputBlockCipher[j/4][j%4];
                //cout << "tempChar:" << hex << (int)tempChar << endl;
                tempChar = tempChar >> (8-remainderInt);
                //cout << "tempChar:" << hex << (int)tempChar << endl;
                tempChar2 = CFBblock[i][j];
                //cout << "tempChar2:" << hex << (int)tempChar2 << endl;
                tempChar2 = tempChar2; // originally thought shifting was necessary, but maybe not? this is bc the 1 isn't in the most significant bit but already shifted
                //cout << "tempChar2:" << hex << (int)tempChar2 << endl;
                tempChar ^= tempChar2;
                //cout << "tempChar:" << hex << (int)tempChar << endl;
                //tempChar = tempChar << (8-remainderInt);
                //cout << "tempChar:" << hex << (int)tempChar << endl;
                cipherText.push_back(tempChar);
                
                //cipherText.push_back((outputBlockCipher[j/Nk][j%Nb] >> (8-remainderInt)) ^ (plainText[i][j] >> (8-remainderInt))) <<(8-remainderInt)
            }else{
                tempChar = CFBblock[i][j] ^ outputBlockCipher[j/4][j%4];
                cipherText.push_back(CFBblock[i][j] ^ outputBlockCipher[j/4][j%4]);
            }
            
            //cout << "tempChar: ";
            //cout << hex << (int)tempChar << endl; // for 1 this maybe 8 digits long
        }
        
        cipherTextBlock.push_back(cipherText);
        cipherText.clear();
    }
    

    CFBblock =  cipherTextBlock;
    block = convertCFBBlockTo(CFBblock);
    strBlock = convertBlockToVectString(block);
    strInput = convertBlockToString(block);
}

void Mode::CFBmodeDecrypt (vector<vector<unsigned char>> key){
    //plainText can be any number of bits from 1 - 128. This presents some challenges. The inner vector represents those 
    //1-128 bit values in 8 bit unsigned characters, most significant bit as the first unsigned char in the leftmost place,
    //just as in a state. Only this is a 1-dimentional vector and not a 2D vector for concatination/simplification of code purposes. The 2D comes in 
    //with multiple plainTexts like 1, 2, 3 as represented in the diagram
    vector<vector<unsigned char>> tempBlock;
    vector<vector<unsigned char>> outputBlockCipher;
    vector<vector<unsigned char>> plainTextBlock;
    vector<unsigned char> plainText;
    int remainderInt = (int)s % 8;
    unsigned char tempChar;
    unsigned char tempChar2;
    //cout << "Here1"<< endl;
    //cout << ceil(s/8) << endl;
    
    for(int i = 0; i < IV.size(); i++){
        tempBlock.push_back(IV[i]);
    }
    //viewState(IV);
    AESState myState = AESState(tempBlock);
    myState.Cipher(key);
    
    
    outputBlockCipher = myState.getCurrentStateVect();
    
    //viewState(outputBlockCipher);
    
    for(int i = 0; i < ceil(s/8); i++){ // ceil might not work here, guess we will find out - it didn't changed to double.
        if(remainderInt != 0 && i == ceil(s/8)-1){
            //note the 8-remainderInt zeros on the end are NOT part of this, they are least significant, but I am limited
            tempChar = outputBlockCipher[i/4][i%4];
            //cout << hex << (int)tempChar << endl;
            tempChar = tempChar >> (8-remainderInt);
            //cout << hex << (int)tempChar << endl;
            tempChar2 = CFBblock[0][i];
            //cout << hex << (int)tempChar2 << endl;
            tempChar2 = tempChar2;
            //cout << hex << (int)tempChar2 << endl;
            tempChar ^= tempChar2;
            //cout << hex << (int)tempChar << endl;
            //tempChar = tempChar << (8-remainderInt);
            //cout << hex << (int)tempChar << endl;
            plainText.push_back(tempChar);
        }else{
            tempChar = CFBblock[0][i] ^ outputBlockCipher[i/4][i%4];
            plainText.push_back(CFBblock[0][i] ^ outputBlockCipher[i/4][i%4]);
            //cout << hex << (int)(plainText[0][i] ^ outputBlockCipher[i/Nk][i%Nb]) << endl;
        }
        //cout << "tempChar: ";
        //cout << hex << (int)tempChar << endl; // for 1 this maybe 8 digits long
    }
    //cout << "Here2"<< endl;
    
    
    plainTextBlock.push_back(plainText);
    plainText.clear();
    
    for(int i = 1; i < CFBblock.size(); i++){
        tempBlock.clear();
        //IV shift left s bits
        bitset<128> IVbits;
        bitset<128> cipherTextBits; // won't always have 128, just a space holder
        bitset<128> tempIVholdBits;
        //cout << "Here3"<< endl;
        //viewState(IV);
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                //will always be 128 bits
                tempIVholdBits = IV[j][k];
                //cout << "tempIVholdBits" << tempIVholdBits << endl;
                IVbits |= (tempIVholdBits << (((3-j)*32)+((3-k)*8)));
                //cout << "IVbits " << IVbits << endl;
            }
        }
        //cout << "IVbits Orignial" << IVbits << endl;
        IVbits = IVbits << s; // If s == 128, IV bits are zeroed.
        //cout << "IVbits shift s" << IVbits << endl;
        //cout << "IVbits shift" << IVbits << endl;
        //concat with cipherTextBlock
        //cout << "Here4"<< endl;
        for(int j = 0; j < ceil(s/8); j++){
            if(remainderInt != 0 && j == ceil(s/8)-1){
                //note the 8-remainderInt zeros on the end are NOT part of this, they are least significant, but I am limited
                //cout << "Here6"<< endl;
                //cout << "i: " << i << "j: " << j << endl;
                //cout << "cipherTextBlock[i-1][j]:" << hex << (int)cipherTextBlock[i-1][j] << endl; // PROBLEM RIGHT HERE
                //cipherTextBits |= (cipherText[i-1][j] >> (8-remainderInt));
                cipherTextBits |= (CFBblock[i-1][j]);
            }else{
                //cout << "cipherTextBlock[i-1][j]:" << hex << (int)cipherTextBlock[i-1][j] << endl;
                tempIVholdBits = CFBblock[i-1][j];
                cipherTextBits |= (tempIVholdBits << ((((int)s/8)-j-1)*8+remainderInt));
                //cout << "((((int)s/8)-j-1)*8+remainderInt): " << dec << ((((int)s/8)-j-1)*8+remainderInt) << endl;
                //cout << "(cipherTextBlock[i-1][j] << ((((int)s/8)-j-1)*8+remainderInt)): " << hex << (tempIVholdBits << ((((int)s/8)-j-1)*8+remainderInt)) << endl;
            }   
        }
        
        IVbits |= cipherTextBits;
        //cout << "IVbits OR" << IVbits << endl;
        bitset<128> tempMask = 0b11111111;
        bitset<128> loadBits;
        
        //cout << "Here5"<< endl;
        //back to vector<unsigned char> form
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                //cout << "j" << j << " k" << k << endl;
                //will always be 128 bits // takes care of anything not 8 divisible
                loadBits = ((IVbits >> (((3-j)*32)+((3-k)*8))) & tempMask);
                //cout << "IVbits" << IVbits << endl;
                //cout << "loadBits" << loadBits <<endl;
                
                unsigned char loadChar = 00000000;
                for(int z = 0; z < 8; z++){
                    //cout << "loadBits[z]" << loadBits[z] <<endl;
                    loadChar |= loadBits[z] << z;
                    //cout << "loadChar"; 
                    //cout << hex << loadChar <<endl;
                    
                }
                IV[j][k] = loadChar;
                //IV[j][k] = (IVbits >> (((3-j)*32)+((3-k)*8))) & 0b11111111;
            }
        }
        //cout << "inputblock: " << endl;
        //viewState(IV);
        
        for(int j = 0; j < IV.size(); j++){
            tempBlock.push_back(IV[j]);
        }

        myState.setCurrentStateVect(tempBlock);
        myState.Cipher(key);

        
        outputBlockCipher = myState.getCurrentStateVect();
        //cout << "outputblock: " << endl;
        //viewState(outputBlockCipher);
        
        for(int j = 0; j < ceil(s/8); j++){ // ceil might not work here, guess we will find out
            if(remainderInt != 0 && j == ceil(s/8)-1){
                //note the 8-remainderInt zeros on the end are NOT part of this, they are least significant, but I am limited
                tempChar = outputBlockCipher[j/4][j%4];
                //cout << "tempChar:" << hex << (int)tempChar << endl;
                tempChar = tempChar >> (8-remainderInt);
                //cout << "tempChar:" << hex << (int)tempChar << endl;
                tempChar2 = CFBblock[i][j];
                //cout << "tempChar2:" << hex << (int)tempChar2 << endl;
                tempChar2 = tempChar2; // originally thought shifting was necessary, but maybe not? this is bc the 1 isn't in the most significant bit but already shifted
                //cout << "tempChar2:" << hex << (int)tempChar2 << endl;
                tempChar ^= tempChar2;
                //cout << "tempChar:" << hex << (int)tempChar << endl;
                //tempChar = tempChar << (8-remainderInt);
                //cout << "tempChar:" << hex << (int)tempChar << endl;
                plainText.push_back(tempChar);
                
                //cipherText.push_back((outputBlockCipher[j/Nk][j%Nb] >> (8-remainderInt)) ^ (plainText[i][j] >> (8-remainderInt))) <<(8-remainderInt)
            }else{
                tempChar = CFBblock[i][j] ^ outputBlockCipher[j/4][j%4];
                plainText.push_back(CFBblock[i][j] ^ outputBlockCipher[j/4][j%4]);
            }
            
            //cout << "tempChar: ";
            //cout << hex << (int)tempChar << endl; // for 1 this maybe 8 digits long
        }
        
        plainTextBlock.push_back(plainText);
        plainText.clear();
    }
    
    

  	CFBblock = plainTextBlock;

  	/*//invpadding
  	unsigned char n; //number of extra char empty on last. (padding is done within the unsigned char already neccessarily)

  	vector<unsigned char> paddedString = CFBblock[CFBblock.size()-1];
  	vector<unsigned char> lastOne = CFBblock[CFBblock.size()-2];

  	n = paddedString[paddedString.size()-1];
	
  	vector<vector<unsigned char>> newCFBBlock;
  	for(int i = 0; i<CFBblock.size()-2; i++){ // push all but last and padded 
  		newCFBBlock.push_back(CFBblock[i]);

  	}

  	vector<unsigned char> unpaddedVect;

  	for(int i = 0; i < newCFBBlock[0].size()-n; i++){
  		unpaddedVect.push_back(lastOne[i]);
  	}
  	newCFBBlock.push_back(unpaddedVect);

  	CFBblock = newCFBBlock;*/
  	block = convertCFBBlockTo(CFBblock);
  	strBlock = convertBlockToVectString(block);
    strInput = convertBlockToString(block);

}

void Mode::OFBmodeEncrypt (vector<vector<unsigned char>> key){
    vector<vector<unsigned char>> tempBlock;
    vector<vector<unsigned char>> outputBlockCipher;
    vector<vector<vector<unsigned char>>> cipherTextBlock;
    vector<vector<unsigned char>> cipherText;
    
    for(int i = 0; i < IV.size(); i++){
        tempBlock.push_back(IV[i]);
    }
    //viewState(tempBlock);
    //cout << "Hello1";
    AESState myState = AESState(tempBlock);
    myState.Cipher(key);

    
    outputBlockCipher = myState.getCurrentStateVect();
    //viewState(outputBlockCipher);
    cipherText.clear();
    
    for(int j = 0; j < IV.size(); j++){
        cipherText.push_back(addCoef(outputBlockCipher[j], block[0][j]));
    }
    
    //viewState(block[0]);
    //viewState(cipherText);
    cipherTextBlock.push_back(cipherText);
    //cout << "Hello1" << endl;
    //viewState(cipherTextBlock[0]);
    
    for(int i = 1; i < block.size(); i++){
        //cout << "Hello3" << endl;
        tempBlock.clear();
        
        tempBlock = outputBlockCipher;
        //cout << "Hello4" << endl;

        myState.setCurrentStateVect(tempBlock);
        myState.Cipher(key);
        outputBlockCipher = myState.getCurrentStateVect();
        //viewState(outputBlockCipher);
        
        cipherText.clear();
        for(int j = 0; j < IV.size(); j++){
            
            cipherText.push_back(addCoef(outputBlockCipher[j], block[i][j]));
        }
        cipherTextBlock.push_back(cipherText);
        //viewState(cipherTextBlock[i]);
    }

    block = cipherTextBlock;
    strBlock = convertBlockToVectString(block);
    strInput = convertBlockToString(block);
}
    
    
void Mode::OFBmodeDecrypt (vector<vector<unsigned char>> key){
    OFBmodeEncrypt(key);
}

void Mode::CTRmodeEncrypt (vector<vector<unsigned char>> key){
        vector<vector<vector<unsigned char>>> outputBlocks;
        vector<vector<vector<unsigned char>>> output;
        vector<vector<unsigned char>> outCipher;
        vector<vector<unsigned char>> tempBlock;
        vector<vector<unsigned char>> counterOn = counter1;
        int j=3;
        int k=3;
        int l;
        int m;
        for(int i = 0; i<4; i++){
        	AESState myState = AESState(counterOn);
        	myState.Cipher(key);

            outCipher = myState.getCurrentStateVect();
            outputBlocks.push_back(outCipher); 
        }
        
        if(counterOn[j][k]==0xff) {
            l=j;
            m=k;
            while(j>0 and counterOn[j][k]==0xff){
                while (k>=0 and counterOn[j][k]==0xff){
                    counterOn[j][k]=0x00;
                    if (k==0 and !counterOn[j-1][k]==0xff){
                        counterOn[j][k+3]++;
                        break;
                    }
                    if (counterOn[j][k-1]==0xff){
                        continue;
                    }
                    else{
                        counterOn[j][k-1]++;
                        break;
                    }
                    k--;
                }
                j--;
                k=3; 
            }
            j=l;
            k=m;
        }
        else{
            counterOn[3][3]++;
            }

        
        
        for(int j = 0; j < block.size(); j++){
            for(int i = 0; i < block.size(); i++){
                tempBlock.push_back(addCoef(block[j][i],outputBlocks[j][i]));
            }
            output.push_back(tempBlock);
            tempBlock.clear();
        }
        block = output;
        strBlock = convertBlockToVectString(block);
        strInput = convertBlockToString(block);
    }

void Mode::CTRmodeDecrypt (vector<vector<unsigned char>> key){
    vector<vector<vector<unsigned char>>> plainText;
    vector<vector<vector<unsigned char>>> outText;
    vector<vector<unsigned char>> tempBlock;
    vector<vector<unsigned char>> outInvCipher;
    vector<vector<unsigned char>> counterOn = counter1;

     int j=3;
     int k=3;
     int l;
     int m;
    
    //plainText.push_back(tempBlock);
    
    for(int i = 0; i<4; i++){
    	AESState myState = AESState(counterOn);
    	myState.Cipher(key);
        
        outInvCipher = myState.getCurrentStateVect();
        
        plainText.push_back(outInvCipher);

    }
    if(counterOn[j][k]==0xff) {
        l=j;
        m=k;
        while(j>0 and counterOn[j][k]==0xff){
            while (k>=0 and counterOn[j][k]==0xff){
                counterOn[j][k]=0x00;
                if (k==0 and !counterOn[j-1][k]==0xff){
                    counterOn[j][k+3]++;
                    break;
                }
                if (counterOn[j][k-1]==0xff){
                    continue;
                }
                else{
                    counterOn[j][k-1]++;
                    break;
                }
                k--;
            }
            j--;
            k=3; 
        }
        j=l;
        k=m;
    }
    else{
        counterOn[3][3]++;
    }
    
    for(int j = 0; j < block.size(); j++){
        for(int i = 0; i < block.size(); i++){
            tempBlock.push_back(addCoef(plainText[j][i],block[j][i]));
        }
        outText.push_back(tempBlock);
        tempBlock.clear();
    }
    
    block = outText;
    strBlock = convertBlockToVectString(block);
    strInput = convertBlockToString(block);
}

vector<vector<vector<unsigned char>>> Mode::getBlock(){
	return block;
}

vector<string> Mode::getStrBlock(){
	return strBlock;
}

string Mode::getString(){
	return strInput;
}

void Mode::printStringVect(){
	cout << "Print:" << endl;
	for(int i = 0; i < strBlock.size();i++ ){
		cout << strBlock[i] << endl;
	}
}







