#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <regex>
#include "ghostCrypt.cpp"

using namespace std;

const int KEY_LENGTH = 15;

string loadKeyFromFile();
int loadPasswordFile(vector<string>&, vector<string>&, vector<string>&);
void savePrompt(vector<string>, vector<string>, vector<string>, string);


int main()
{
	ghostCrypt crypt;
	vector<string> f1;
	vector<string> f2;
	vector<string> f3;
	cout << "GhostWord Password Manager" << endl;
	
	ifstream check("ghostword.txt");
	if(!check)
	{
		ofstream createFile("ghostword.txt");
		cout << "No password file detected, blank file 'ghostword.txt' created" << endl;
	}
	check.close();
	
	int menuSelection;
	
	string key = "";
	
	while(true)
	{
		cout << endl << "Main Menu" << endl << endl;
		cout << "1.  Load password file" << endl;
		cout << "2.  View Help" << endl;
		cout << "3.  Generate new key file" << endl;
		cout << "0.  Exit" << endl;
		cin >> menuSelection;
		if(menuSelection == 1)
		{
			//FILE SUBMENU
			key = loadKeyFromFile();
			while(true)
			{
				if(key == "00000000")
				{
					break;
				}
				//LOAD FILE
				int status = loadPasswordFile(f1, f2, f3);
				if(status == 1)
				{
					break;
				}
				string hold1;
				string hold2;
				string hold3;
				for(int i = 0; i < f1.size(); i++)
				{
					hold1 = f1[i];
					hold2 = f2[i];
					hold3 = f3[i];
					f1[i] = crypt.decrypt(hold1, key);
					f2[i] = crypt.decrypt(hold2, key);
					f3[i] = crypt.decrypt(hold3, key);
				}
				//LOAD FILE -end
				//SORT VECTORS
				int sortArray[f1.size()];
				vector<string> f1Clone = f1;
				sort(f1Clone.begin(), f1Clone.end());
				for(int i = 0; i < f1.size(); i++)
				{
					for(int j = 0; j < f1.size(); j++)
					{
						if(f1Clone[i] == f1[j])
						{
							sortArray[i] = j;
						}
					}
				}
				
				cout << endl << "File Options" << endl << endl;
				cout << "1.  View All Passwords" << endl;
				cout << "2.  Search For A Title" << endl;
				cout << "3.  Edit Password Entries" << endl;
				cout << "4.  Add New Password Entry" << endl;
				cout << "5.  Generate New Key For This Password File" << endl;
				cout << "0.  Cancel" << endl;
				cin >> menuSelection;
				
				if(menuSelection == 1)
				{
					cout << "Title\tEmail/Username\tPassword" << endl << endl;
					for(int i = 0; i < f1.size(); i++)
					{
						cout << f1[sortArray[i]] << '\t' << f2[sortArray[i]] << '\t' << f3[sortArray[i]] << endl;
					}
				}
				if(menuSelection == 2)
				{
					cout << "Enter title of entry to find: ";
					string titleChoice;
					cin >> titleChoice;
					int editIndex = -1;
					string searchCrit = "(" + titleChoice + ")(.*)";
					regex r(searchCrit, regex_constants::icase);
					for(int i = 0; i < f1.size(); i++)
					{
						if(regex_match(f1[i], r))
						{
							editIndex = i;
							break;
						}
					}
					bool run = false;
					if(editIndex != -1)
					{
						cout << "Entry Found" << endl;
						cout << endl << f1[editIndex] << '\t' << f2[editIndex] << '\t' << f3[editIndex] << endl << endl;
						run = true;
					}
					else
					{
						cout << "Entry with title '" << titleChoice << "' not found" << endl;
					}
				}
				if(menuSelection == 3)
				{
					cout << "Enter title of entry to edit: ";
					string titleChoice;
					cin >> titleChoice;
					int editIndex = -1;
					string searchCrit = "(" + titleChoice + ")(.*)";
					regex r(searchCrit, regex_constants::icase);
					for(int i = 0; i < f1.size(); i++)
					{
						if(regex_match(f1[i], r))
						{
							editIndex = i;
							break;
						}
					}
					bool run = false;
					if(editIndex != -1)
					{
						cout << "Entry Found" << endl;
						cout << endl << f1[editIndex] << '\t' << f2[editIndex] << '\t' << f3[editIndex] << endl << endl;
						run = true;
					}
					else
					{
						cout << "Entry with title '" << titleChoice << "' not found" << endl;
					}
					while(run)
					{
						int editChoice;
						cout << "Options" << endl;
						cout << "1.  Edit Title" << endl;
						cout << "2.  Edit Email/Username" << endl;
						cout << "3.  Edit Password" << endl;
						cout << "7.  Delete Entry" << endl;
						cout << "0.  Cancel" << endl;
						cin >> editChoice;
						if(editChoice == 1)
						{
							string newTitle;
							cout << "Enter New Title" << endl;
							cout << "Title:  ";
							cin >> newTitle;
							f1[editIndex] = newTitle;
							savePrompt(f1, f2, f3, key);
							run = false;
						}
						if(editChoice == 2)
						{
							string newUsername;
							cout << "Enter New Email/Username" << endl;
							cout << "Email/Username:  ";
							cin >> newUsername;
							f2[editIndex] = newUsername;
							savePrompt(f1, f2, f3, key);
							run = false;
						}
						if(editChoice == 3)
						{
							string newPass;
							
							cout << "(Enter 'gen' to automatically generate password)" << endl;
							cout << "Enter New Password:  ";
							cin >> newPass;
							if(newPass == "gen")
							{
								cout << "Length of automatically generated password:  ";
								int lengthChoice;
								cin >> lengthChoice;
								newPass = crypt.generatePass(lengthChoice);
							}
							f3[editIndex] = newPass;
							cout << "New Password:  " << newPass << endl;
							savePrompt(f1, f2, f3, key);
							run = false;
						}
						if(editChoice == 7)
						{
							cout << "Entry will be deleted" << endl;
							f1[editIndex].erase();
							f2[editIndex].erase();
							f3[editIndex].erase();
							savePrompt(f1, f2, f3, key);
							run = false;
						}
						if(editChoice == 0)
						{
							run = false;
						}
					}
				}
				if(menuSelection == 4)
				{
					string addInput;
					cout << "Title:  ";
					cin >> addInput;
					f1.push_back(addInput);
					cout << "Username:  ";
					cin >> addInput;
					f2.push_back(addInput);
					cout << "(Enter 'gen' to automatically generate password)" << endl;
					cout << "Password:  ";
					cin >> addInput;
					if(addInput == "gen")
					{
						cout << "Length of automatically generated password:  ";
						int lengthChoice;
						cin >> lengthChoice;
						addInput = crypt.generatePass(lengthChoice);
					}
					f3.push_back(addInput);
					cout << "New Password:  " << addInput << endl;
					cout << "New entry created" << endl;
					savePrompt(f1, f2, f3, key);
				}
				if(menuSelection == 5)
				{
					cout << "This new key file will be created in the same directory as this .exe application.  The key file must be moved to the root directory of a drive (such as flash drive) to use it with GhostWord" << endl;
					cout << "OLD KEYFILE WILL NOT WORK WITH THIS PASSWORD FILE IF NEW KEY FILE IS CREATED" << endl << endl;
					cout << "Create new key file? y/n" << endl;
					char decision;
					cin >> decision;
					if(decision == 'y')
					{
						ofstream newKeyFile("key.txt");
						key = crypt.generateKey(KEY_LENGTH);
						newKeyFile << key;
						cout << "'key.txt' created in working directory" << endl;
						cout << "Move file to root of drive and reload password file to reaccess passwords" << endl;
						ofstream newpassfile("ghostword.txt");
						for(int i = 0; i < f1.size(); i++)
						{
							newpassfile << crypt.encrypt(f1[i], key) << '\t' << crypt.encrypt(f2[i], key) << '\t' << crypt.encrypt(f3[i], key) << '\t';
						}
						newpassfile.close();
						break;
					}
					else
					{
						cout << "No key file created" << endl;
					}
				}
				if(menuSelection == 0)
				{
					break;
				}
			}
		}
		else if(menuSelection == 2)
		{
			cout << "--Key File" << endl << endl;
			cout << "Key file must be located in root directory of drive" << endl << endl;
			cout << "You will be prompted to enter the drive letter (case insensitive) of where your key file is located" << endl << endl;
			cout << "Before making any changes, be sure to view all passwords to be sure key file was correct.  Making changes with wrong key will corrupt password entries" << endl << endl;
			cout << "--Password File" << endl << endl;
			cout << "Password file will ba automatically created in directory of this .exe if it does not exist" << endl << endl;
			cout << "Backups of this file can be made, but in order for it to be read by this .exe , it must be in the same directory with this .exe and named 'ghostword.txt'" << endl << endl;
			cout << "If passwords were saved with a key file, do not use another key file to edit the passwords of that file" << endl << endl;
			cout << "--Finding And Editing Entries" << endl << endl;
			cout << "When being asked title of entry to find or edit, it is not case sensitive (it is a regex search '(<input>)(.*)'" << endl << endl;
		}
		else if(menuSelection == 3)
		{
			cout << "This new key file will be created in the same directory as this .exe application.  The key file must be moved to the root directory of a drive (such as flash drive) to use it with GhostWord" << endl << endl;
			cout << "Create new key file? y/n" << endl;
			char decision;
			cin >> decision;
			if(decision == 'y')
			{
				ofstream newKeyFile("key.txt");
				newKeyFile << crypt.generateKey(KEY_LENGTH);
				cout << "'key.txt' created in working directory" << endl;
			}
			else
			{
				cout << "No key file created" << endl;
			}
		}
		else if(menuSelection == 0)
		{
			cout << "Exiting" << endl;
			break;
		}
		else
		{
			
		}
	}
	
	return 0;
}

string loadKeyFromFile()
{
	char driveNumber;

	cout << "What drive letter is key file located?: ";
	cin >> driveNumber;
	driveNumber = toupper(driveNumber);
	string dn(1, driveNumber);
	string keyFile = ":\\key.txt";
	keyFile.insert(0, dn);
	cout << keyFile << endl;
	ifstream inKey(keyFile);
	//ifstream inKey("key.txt");

	if (!inKey)
	{
		cout << "File wasn't found on drive" << endl;
		return "00000000";
	}
	else
	{
		cout << "Key found" << endl;
		string key;
		inKey >> key;
		inKey.close();
		return key;
	}
}

int loadPasswordFile(vector<string> &f1, vector<string> &f2, vector<string> &f3)
{
	ifstream inFile("ghostword.txt");
	if (!inFile)
	{
		cout << "File wasn't found on drive" << endl;
		return 1;
	}
	else
	{
		f1.clear();
		f2.clear();
		f3.clear();
		//cout << endl << "Password file loaded" << endl;
		string temp;
		int pass = 0;
		while(getline(inFile, temp, '\t'))
		{
			if(pass == 0)
			{
				f1.push_back(temp);
				pass++;
			}
			else if(pass == 1)
			{
				f2.push_back(temp);
				pass++;
			}
			else if(pass == 2)
			{
				f3.push_back(temp);
				pass = 0;
			}	
		}
		return 0;
	}
}

void savePrompt(vector<string> f1, vector<string> f2, vector<string> f3, string key)
{
	ghostCrypt crypt;
	cout << "Save and write to file? y/n" << endl;
	char choice;
	cin >> choice;
	if(choice == 'y')
	{
		ofstream file("ghostword.txt");
		for(int i = 0; i < f1.size(); i++)
		{
			file << crypt.encrypt(f1[i], key) << '\t' << crypt.encrypt(f2[i], key) << '\t' << crypt.encrypt(f3[i], key) << '\t';
		}
		file.close();
	}
	else
	{
		
	}
}

