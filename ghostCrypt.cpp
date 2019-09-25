#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class ghostCrypt
{
	private:

		char signs[62];

	public:

		ghostCrypt();
		string encrypt(string, string);
		string decrypt(string, string);
		long long conv62to10(string);
		string conv10to62(long long);
		string generateKey(int);
		string generatePass(int);
};

	ghostCrypt::ghostCrypt()
	{
		signs[0] = '0';
		signs[1] = '1';
		signs[2] = '2';
		signs[3] = '3';
		signs[4] = '4';
		signs[5] = '5';
		signs[6] = '6';
		signs[7] = '7';
		signs[8] = '8';
		signs[9] = '9';
		signs[10] = 'a';
		signs[11] = 'b';
		signs[12] = 'c';
		signs[13] = 'd';
		signs[14] = 'e';
		signs[15] = 'f';
		signs[16] = 'g';
		signs[17] = 'h';
		signs[18] = 'i';
		signs[19] = 'j';
		signs[20] = 'k';
		signs[21] = 'l';
		signs[22] = 'm';
		signs[23] = 'n';
		signs[24] = 'o';
		signs[25] = 'p';
		signs[26] = 'q';
		signs[27] = 'r';
		signs[28] = 's';
		signs[29] = 't';
		signs[30] = 'u';
		signs[31] = 'v';
		signs[32] = 'w';
		signs[33] = 'x';
		signs[34] = 'y';
		signs[35] = 'z';
		signs[36] = 'A';
		signs[37] = 'B';
		signs[38] = 'C';
		signs[39] = 'D';
		signs[40] = 'E';
		signs[41] = 'F';
		signs[42] = 'G';
		signs[43] = 'H';
		signs[44] = 'I';
		signs[45] = 'J';
		signs[46] = 'K';
		signs[47] = 'L';
		signs[48] = 'M';
		signs[49] = 'N';
		signs[50] = 'O';
		signs[51] = 'P';
		signs[52] = 'Q';
		signs[53] = 'R';
		signs[54] = 'S';
		signs[55] = 'T';
		signs[56] = 'U';
		signs[57] = 'V';
		signs[58] = 'W';
		signs[59] = 'X';
		signs[60] = 'Y';
		signs[61] = 'Z';

		/* signs[0] = '4';
		signs[1] = '1';
		signs[2] = '2';
		signs[3] = '7';
		signs[4] = '0';
		signs[5] = '5';
		signs[6] = '6';
		signs[7] = '3';
		signs[8] = '8';
		signs[9] = '9';
		signs[10] = 'j';
		signs[11] = 'b';
		signs[12] = 'c';
		signs[13] = 'd';
		signs[14] = 'H';
		signs[15] = 'f';
		signs[16] = 'g';
		signs[17] = 'e';
		signs[18] = 'i';
		signs[19] = 'a';
		signs[20] = 'k';
		signs[21] = 'l';
		signs[22] = 'm';
		signs[23] = 'n';
		signs[24] = 'p';
		signs[25] = 'o';
		signs[26] = 'q';
		signs[27] = 'r';
		signs[28] = 's';
		signs[29] = 't';
		signs[30] = 'u';
		signs[31] = 'v';
		signs[32] = 'E';
		signs[33] = 'x';
		signs[34] = 'y';
		signs[35] = 'z';
		signs[36] = 'A';
		signs[37] = 'B';
		signs[38] = 'C';
		signs[39] = 'D';
		signs[40] = 'w';
		signs[41] = 'F';
		signs[42] = 'G';
		signs[43] = 'H';
		signs[44] = 'I';
		signs[45] = 'J';
		signs[46] = 'K';
		signs[47] = 'L';
		signs[48] = 'M';
		signs[49] = 'N';
		signs[50] = 'O';
		signs[51] = 'h';
		signs[52] = 'Q';
		signs[53] = 'R';
		signs[54] = 'S';
		signs[55] = 'Z';
		signs[56] = 'U';
		signs[57] = 'V';
		signs[58] = 'W';
		signs[59] = 'X';
		signs[60] = 'Y';
		signs[61] = 'T'; */

	}
	string ghostCrypt::encrypt(string str, string key)
	{
		string encryptedString = "";
		long long currAscii;
		//
		long long convKey = conv62to10(key);
		//

		string value = "";

		for(int i = 0 ; i < str.size(); i++)
		{
			currAscii = long(str[i]);
			currAscii *= 67;
			currAscii *= convKey;
			value += conv10to62(currAscii);
			value += ' ';
		}
		return value;
	}

	string ghostCrypt::decrypt(string str, string key)
	{
		string decryptedString = "";
		long long convKey = conv62to10(key);

		long long currAscii;
		string value = "";

		for(int i = 0; i < str.size(); i++)
		{
			value = "";
			while(str[i] != ' ')
			//for(int j = 0; j < 8; j++)
			{
				value += str[i];
				i++;
			}
			currAscii = conv62to10(value);
			currAscii /= convKey;
			currAscii /= 67;
			decryptedString += static_cast<char>(currAscii);

		}
		return decryptedString;
	}

	long long ghostCrypt::conv62to10(string input)
	{
		string longNum = input;
		long long total = 0;
		long long tempPower;
		long long find;
		long long product;
		for(int i = 0; i < input.size(); i++)
		{
			find = 0;
			while(signs[find] != input[input.size()-i-1])
			{
				find++;
			}
			tempPower = pow(62, i);
			product = tempPower * find;
			total+=product;
		}
		return total;
	}

	string ghostCrypt::conv10to62(long long input)
	{
		long long number = input;
		long long tempMod;
		string output = "";
		while(number != 0)
		{
			tempMod = number % 62;
			output = signs[tempMod] + output;
			number = number / 62;
		}
		return output;
	}
	
	string ghostCrypt::generateKey(int length)
	{
		srand(time(0));
		int rand();
		string strKey = "";
		char tempChar;
		int tempInt;
		char numbers[10] = {'0','1','2','3','4','5','6','7','8','9'};
		for(int i = 0; i < length; i++)
		{
			tempChar = numbers[rand() % 10];
			strKey += tempChar;
		}
		long long keyIn10 = stoll(strKey);
		string output = conv10to62(keyIn10);
		
		return output;
	}

	string ghostCrypt::generatePass(int length)
	{
		srand(time(0));
		int rand();
		string strKey = "";
		char tempChar;
		int tempInt;
		char symbols[69] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','!','@','$','%','&','_','-'};
		for(int i = 0; i < length; i++)
		{
			tempChar = symbols[rand() % 69];
			strKey += tempChar;
		}
		
		return strKey;
	}