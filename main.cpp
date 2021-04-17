#include "Mode.h"
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





    
int main()
{
   
    /*
    //Addition (4.1) test as expressed in the AES Publication
    unsigned char poly1 = 0b01010111;
    polyStringOut(poly1);
    unsigned char poly2 = 0b10000011;
    polyStringOut(poly2);
    
    unsigned char addAnswer = addition(poly1, poly2);
    std::bitset<8> binaryAddAnswer;
    for(int i = 7; i >= 0; i--){
        binaryAddAnswer[i] = ((addAnswer >> i) & 1);
    }
    polyStringOut(addAnswer);
    cout << binaryAddAnswer << endl;
    cout << "Should be: 11010100" << endl;
    
    //Multiplication (4.2) test as expressed in the AES Publication
    unsigned char multAnswer = multiply(poly1, poly2);
    std::bitset<8> binaryMultAnswer;
    for(int i = 7; i >= 0; i--){
        binaryMultAnswer[i] = ((multAnswer >> i) & 1);
    }
    polyStringOut(multAnswer);
    cout << binaryMultAnswer << endl;
    cout << "Should be: 11000001" << endl;
    */
    
    //MixColumns() test - will also be testing the modPro function
    //See Appendix B for first MixColumns before and after, before is previous at ShiftRows
    
    //I don't know the best way to assign space numbers I wrote a function above
    //vector<vector<unsigned char>> state = assignInput(0xd4,0xbf,0x5d,0x30,0xe0,0xb4,0x52,0xae,0xb8,0x41,0x11,0xf1,0x1e,0x27,0x98,0xe5);
    
    //vector<vector<unsigned char>> input = assignInput(0x95,0x65,0xfd,0xf3,0x90,0xfb,0xb1,0x92,0x89,0x67,0xa6,0x70,0xc3,0xc9,0x6e,0xff);
    
    
    /*viewState(input);
    
    vector<vector<unsigned char>> output = MixColumns(input);
    
    viewState(output);
    
    vector<vector<unsigned char>> reverse = invMixColumns(output);
    viewState(reverse);*/
    /*vector<vector<unsigned char>> state = assignInput(0x32, 0x43, 0xf6, 0xa8,0x88,0x5a,0x30,0x8d,0x31,0x31,0x98,0xa2,0xe0,0x37,0x07,0x34);
    vector<vector<unsigned char>>  input = assignInput(0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c);
    viewState(input);
    vector<vector<unsigned char>> output = AddRoundKey(state, 0, KeyExpansion(input));
    viewState(output);*/
    
    //Cipher testing
    
    /*vector<vector<unsigned char>> state = assignInput(0x32, 0x43, 0xf6, 0xa8,0x88,0x5a,0x30,0x8d,0x31,0x31,0x98,0xa2,0xe0,0x37,0x07,0x34);
    vector<vector<unsigned char>> input = assignInput(0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c);
    
    viewState(state);
    viewState(input);
    
    vector<vector<unsigned char>> output = Cipher(state,input);
    vector<vector<unsigned char>> invCipherOut = invCipher(output,input);
    viewState(invCipherOut);*/
    
    //MODE testing
    vector<vector<unsigned char>> key = {{0x2b, 0x7e, 0x15, 0x16}, {0x28, 0xae, 0xd2, 0xa6}, {0xab, 0xf7, 0x15, 0x88}, {0x09, 0xcf, 0x4f, 0x3c}};
    //vector<vector<unsigned char>> IV = assignInput(0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f);
    vector<vector<vector<unsigned char>>> plainText = {{{0x6b, 0xc1, 0xbe, 0xe2}, {0x2e, 0x40, 0x9f, 0x96}, {0xe9, 0x3d, 0x7e, 0x11}, {0x73, 0x93, 0x17, 0x2a}}, 
        {{0xae, 0x2d, 0x8a, 0x57}, {0x1e, 0x03, 0xac, 0x9c}, {0x9e, 0xb7, 0x6f, 0xac}, {0x45, 0xaf, 0x8e, 0x51}}, {{0x30, 0xc8, 0x1c, 0x46}, {0xa3, 0x5c, 0xe4, 0x11}, 
        {0xe5, 0xfb, 0xc1, 0x19}, {0x1a, 0x0a, 0x52, 0xef}}, {{0xf6, 0x9f, 0x24, 0x45}, {0xdf, 0x4f, 0x9b, 0x17}, {0xad, 0x2b, 0x41, 0x7b}, {0xe6, 0x6c, 0x37, 0x10}}};
    vector<vector<vector<unsigned char>>> plain = {{{0x6b, 0xc1, 0xbe, 0xe2}, {0x2e, 0x40, 0x9f, 0x96}, {0xe9, 0x3d, 0x7e, 0x11}, {0x73, 0x93, 0x17, 0x2a}}, 
        {{0xae, 0x2d, 0x8a, 0x57}, {0x1e, 0x03, 0xac, 0x9c}, {0x9e, 0xb7, 0x6f, 0xac}, {0x45, 0xaf, 0x8e, 0x51}}, {{0x30, 0xc8, 0x1c, 0x46}, {0xa3, 0x5c, 0xe4, 0x11}, 
        {0xe5, 0xfb, 0xc1, 0x19}, {0x1a, 0x0a, 0x52, 0xef}}, {{0xf6, 0x9f, 0x24, 0x45}, {0xdf, 0x4f, 0x9b, 0x17}}};
    
    vector<vector<unsigned char>> plainText1 = {{0b00}, {0b01}, {0b01}, {0b00}, {0b01}, {0b00}, {0b01}, {0b01}, {0b01}, {0b01}, {0b00}, {0b00}, {0b00}, {0b00}, {0b00}, {0b01}};
    vector<vector<unsigned char>> plainText2 = {{0x6b}, {0xc1}, {0xbe}, {0xe2}, {0x2e}, {0x40}, {0x9f}, {0x96}, {0xe9}, {0x3d}, {0x7e}, {0x11}, {0x73}, {0x93}, {0x17}, {0x2a}, {0xae}, {0x2d}}; 
    vector<vector<unsigned char>> plainText3 = {{0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a}, {0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c, 
    0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51}, {0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11, 0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef}, {0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17, 
    0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10}}; 
    
    vector<vector<vector<unsigned char>>> cipherText1 = {{{0x87, 0x4d, 0x61, 0x91}, {0xb6, 0x20, 0xe3, 0x26}, {0x1b, 0xef, 0x68, 0x64}, {0x99, 0x0d, 0xb6, 0xce}}, 
        {{0x98, 0x06, 0xf6, 0x6b}, {0x79, 0x70, 0xfd, 0xff}, {0x86, 0x17, 0x18, 0x7b}, {0xb9, 0xff, 0xfd, 0xff}}, {{0x5a, 0xe4, 0xdf, 0x3e}, {0xdb, 0xd5, 0xd3, 0x5e}, 
        {0x5b, 0x4f, 0x09, 0x02}, {0x0d, 0xb0, 0x3e, 0xab}}, {{0x1e, 0x03, 0x1d, 0xda}, {0x2f, 0xbe, 0x03, 0xd1}, {0x79, 0x21, 0x70, 0xa0}, {0xf3, 0x00, 0x9c, 0xee}}};
   
    /*vector<vector<vector<unsigned char>>> encrypt = CBCmodeEncrypt(plainText, IV, key);
    
    viewState(encrypt[0]);
    viewState(encrypt[1]);
    viewState(encrypt[2]);
    viewState(encrypt[3]);
    
    vector<vector<vector<unsigned char>>> decrypt = CBCmodeDecrypt(encrypt, IV, key);
    
    viewState(decrypt[0]);
    viewState(decrypt[1]);
    viewState(decrypt[2]);
    viewState(decrypt[3]);*/
    
    //CFB
    /*vector<vector<unsigned char>> encrypt1 = CFBmodeEncrypt(1, plainText1, IV, key);
    vector<vector<unsigned char>> decrypt1 = CFBmodeDecrypt(1, encrypt1, IV, key);
    
    vector<vector<unsigned char>> encrypt2 = CFBmodeEncrypt(8, plainText2, IV, key);
    vector<vector<unsigned char>> decrypt2 = CFBmodeDecrypt(8, encrypt2, IV, key);
    
    vector<vector<unsigned char>> encrypt3 = CFBmodeEncrypt(128, plainText3, IV, key);
    vector<vector<unsigned char>> decrypt3 = CFBmodeDecrypt(128, encrypt3, IV, key);*/
    
    //OFB 
    /*vector<vector<vector<unsigned char>>> encryptOFB = OFBmodeEncrypt(plainText, IV, key);
    
    viewState(encryptOFB[0]);
    viewState(encryptOFB[1]);
    viewState(encryptOFB[2]);
    viewState(encryptOFB[3]);
    
    vector<vector<vector<unsigned char>>> decryptOFB = OFBmodeDecrypt(encryptOFB, IV, key);
    
    viewState(decryptOFB[0]);
    viewState(decryptOFB[1]);
    viewState(decryptOFB[2]);
    viewState(decryptOFB[3]);*/
    
    
    //ECB with padding test
    
    
    vector<string> test = {"6bc1bee22e409f96e93d7e117393172a","ae2d8a571e03ac9c9eb76fac45af8e51", "30c81c46a35ce411e5fbc1191a0a52ef",
    "f69f2445df4f9b17ad2b417be66c3710"};
    vector<string> CFB128test = {"000102030405060708090a0b0c0d0e0f", "3b3fd92eb72dad20333449f8e83cfb4a", "c8a64537a0b3a93fcde3cdad9f1ce58b", 
    "26751f67a3cbb140b1808cf187a4f4df"};
    vector<string> OFBtest = {"000102030405060708090a0b0c0d0e0f","50fe67cc996d32b6da0937e99bafec60", "d9a4dada0892239f6b8b3d7680e15674", 
    "a78819583f0308e7a6bf36b1386abf23"};
    
    /*Mode myMode = Mode(test);
    myMode.ECBmodeEncrypt(key);
    
    myMode.printStringVect();

    myMode.ECBmodeDecrypt(key);

    myMode.printStringVect();*/
    
    /*Mode myMode2 = Mode(test);
    myMode2.CBCmodeEncrypt(key);
    
    myMode2.printStringVect();

    myMode2.CBCmodeDecrypt(key);

    myMode2.printStringVect();*/
    
    /*Mode myMode3 = Mode(CFB128test);
    myMode3.CFBmodeEncrypt(key);
    
    myMode3.printStringVect();

    myMode3.CFBmodeDecrypt(key);

    myMode3.printStringVect();*/
    
    /*Mode myMode4 = Mode(OFBtest);
    myMode4.OFBmodeEncrypt(key);
    
    myMode4.printStringVect();

    myMode4.OFBmodeDecrypt(key);

    myMode4.printStringVect();*/
    
    Mode myMode5 = Mode(test);
    myMode5.CTRmodeEncrypt(key);
    
    myMode5.printStringVect();

    myMode5.CTRmodeDecrypt(key);

    myMode5.printStringVect();
    
    
    // viewState(encrypt[0]);
    // viewState(encrypt[1]);
    // viewState(encrypt[2]);
    // viewState(encrypt[3]);
    // viewState(encrypt[4]);
    //vector<vector<vector<unsigned char>>> decrypt = ECBmodeDecrypt(encrypt, key);
    
    
    return 0;
}









