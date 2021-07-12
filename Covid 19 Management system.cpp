#include <iostream>
#include <string>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <conio.h>
#include <windows.h>
int numOfBedAvailable;
using namespace std;

class ward
{
protected:
	int numOfBed;
	static int wardNum;
	bool bedAvailibility;
	string Assignedward;
public:
	ward(string x)
	{}
	ward()
	{
		int i;
		string temp[2];
		ifstream wardfile("ward.txt");
		if (wardfile.is_open())
		{
			while (wardfile.eof() == 0)
			{
				wardfile >> wardNum;
				for (i = 0; i < 2; i++)
				{
					wardfile >> temp[i];
				}
			}
			wardfile.close();
		}
		else
		{
			wardNum = 0;
		}
		char choice;
		cout << "\n\n\t\tENTER THE NUMBER OF BEDS: " << endl;
		cin >> numOfBed;
		numOfBedAvailable = numOfBed;
		wardNum++;
		bedAvailibility = 1;
		wardfiling();
	}
	ward(int x)
	{
		ofstream outFile("temp.txt");
		ifstream readFile("ward.txt");
		string search;
		string temp;
		string readout;
		int skipLines = 0;
		int i = 0; int k = 1;
		int tempbedavailable = 6;
		if (readFile)
		{
			while (readFile.eof() == 0)
			{
				for (i = 0; i < 2; i++)
				{
					readFile >> temp;
				}
				readFile >> tempbedavailable;
				k++;
				if (tempbedavailable != 0)
				{
					tempbedavailable--;
					break;
				}

			}
			i = 0;
			readFile.close();
			readFile.open("ward.txt", ios::in);
			while (readFile.eof() == 0)
			{
				if (i == (k - 2))
				{
					readFile >> Assignedward;
					break;
				}
				readFile >> temp;
				i++;
			}
			i = 0;
			readFile.close();
			readFile.open("ward.txt", ios::in);
			while (readFile.eof() == 0)
			{
				if (k == i)
				{
					readFile >> temp;
					outFile << endl << tempbedavailable;
				}
				else if (i == 0)
				{
					readFile >> temp;
					outFile << temp;
				}
				else
				{
					readFile >> temp;
					outFile << endl << temp;
				}
				i++;
			}
			outFile.close();
			readFile.close();
			remove("ward.txt");
			int g = rename("temp.txt", "ward.txt");
		}
		else
		{
			cout << "\n\n\t\tWARD FILE DOES NOT EXIST!\n" << endl;
		}
	}
	friend void wdeleterecord();
	friend void wdisplayrecord();
	friend void weditrecord();
	friend void waddrecord();
	void wdeletefile()
	{
		ifstream patientfile;
		patientfile.open("ward.txt", ios::in);
		if (patientfile)
		{
			while (1)
			{
				bool found = 0;
				string wardnumber;
				int tempbeds;
				int bedsavail;
				cout << "\n\n\t\tENTER THE WARD NUMBER YOU WANT TO DELETE: ";
				cin >> wardnumber;
				string readout;
				ifstream validation("ward.txt");
				while (getline(validation, readout))
				{
					if (readout == wardnumber)
					{
						found = 1;
					}
				}
				if (found == false)
				{
					system("CLS");
					cout << "\n\n\t\tWARD # " << wardnumber << " DOES NOT EIXTS!\n" << endl;
					break;
				}
				validation.close();
				int i, j;
				string y;
				string temp;
				ofstream tempfile("temp.txt");
				int k = 0;
				while (patientfile.eof() == 0)
				{
					patientfile >> y;
					if (y != wardnumber)
					{
						if (!patientfile.eof())
						{
							if (k == 0)
							{
								patientfile >> tempbeds >> bedsavail;
								tempfile << y << endl << tempbeds << endl << bedsavail;
							}
							else
							{
								patientfile >> tempbeds >> bedsavail;
								tempfile << endl << y << endl << tempbeds << endl << bedsavail;
							}
							k++;
						}
						else
						{
							break;
						}
					}
					else if (y == wardnumber)
					{
						for (i = 0; i < 2; i++)
						{
							patientfile >> temp;
						}
					}

				}
				patientfile.close();
				tempfile.close();
				remove("ward.txt");
				rename("temp.txt", "ward.txt");
				break;
			}
		}
	}
	void weditrecord()
	{
		ifstream readFile("ward.txt");
		if (readFile)
		{
			while (1)
			{
				bool found = 0;
				string search;
				ofstream outFile("temp.txt");
				ifstream validation("ward.txt");
				string readout;
				int tempbedavailable;
				int tempbeds;
				int skipLines = 0;
				string temp;
				int lines;
				int i = 0;
				cout << "\n\n\t\tENTER THE WARD NUMBER YOU WANT TO EDIT: ";
				cin >> search;
				while (getline(validation, readout))
				{
					if (readout == search)
					{
						found = 1;
					}
				}
				if (found == false)
				{
					system("CLS");
					cout << "\n\n\t\tWARD # " << search << " DOES NOT EIXTS!\n" << endl;
					break;
				}
				validation.close();
				cout << "\n\n\t\tENTER THE UPDATED BEDS AVAILABLE: ";
				cin >> tempbedavailable;
				cout << "\n\n\t\tENTER THE TOTAL NUMBER OF BEDS: ";
				cin >> tempbeds;
				while (getline(readFile, readout))
				{
					if (skipLines != 0)
					{
						skipLines--;
						continue;
					}
					else if (readout == search)
					{
						outFile << search << endl;
						outFile << tempbeds << endl;
						outFile << tempbedavailable;
						skipLines = 2;

					}
					else
					{
						outFile << endl << readout;
					}
				}
				outFile.close();
				readFile.close();
				remove("ward.txt");
				int g = rename("temp.txt", "ward.txt");
				break;
			}
		}
	}
	void display()
	{
		string answer;
		cout << "\n\n\t\tNUMBER OF BEDS: " << numOfBed << endl;
		cout << "\n\t\tWARD NUMBER: " << wardNum << endl;
		if (numOfBedAvailable == 0)
		{
			bedAvailibility = 0;
		}
		else
		{
			bedAvailibility = 1;
		}
		if (bedAvailibility == 1)
		{
			answer = "YES";
		}
		else if (bedAvailibility == 0)
		{
			answer = "NO";
		}
		cout << "BED AVAILIBILITY: " << answer << endl;
	}
	int getNumOfBed()
	{
		return numOfBed;
	}
	int getWardNum()
	{
		return wardNum;
	}
	bool getBedAvailibility()
	{
		return bedAvailibility;
	}
	void wardfiling()
	{
		char c='\0';
		ofstream wardfile;
		ifstream examplefile;
		examplefile.open("ward.txt", ios::in);
		examplefile >> c;
		if (c=='\0')
		{
			wardfile.open("ward.txt", ios::app);
			wardfile << wardNum << endl << numOfBed << endl << numOfBedAvailable;
		}
		else
		{
			wardfile.open("ward.txt", ios::app);
			wardfile <<endl << wardNum << endl << numOfBed << endl << numOfBedAvailable;
		}
		wardfile.close();
		examplefile.close();
	}
	void wardreadfile()
	{
		int choice; string tempwardnum; int tempBedsAvailable; int totalbeds;
		ifstream wardfile;
		wardfile.open("ward.txt");
		if (wardfile)
		{
			system("CLS");
			cout << "\n\n\t\tVIEW ALL WARD DETAILS\t\t[1]";
			cout << "\n\n\t\tVIEW A SINGLE WARD DETAIL\t[2]";
			cout << "\n\n\n\t\tYour Choice: ";
			cin >> choice;
			if (choice == 1)
			{
				int i = 0;
				while (wardfile.eof() == 0)
				{
					if (i == 0)
					{
						wardfile >> tempwardnum;
						cout << "\n\t\tWARD NUMBER: " << tempwardnum << endl;
					}
					if (i == 1)
					{
						wardfile >> totalbeds;
						cout << "\n\t\tTOTAL BEDS : " << totalbeds << endl;
					}
					if (i == 2)
					{
						wardfile >> tempBedsAvailable;
						cout << "\n\t\tBEDS AVAILABLE : " << tempBedsAvailable << endl << endl;
					}
					if (i == 3)
					{
						cout << endl;
						i = 0;
					}
					else
					{
						i++;
					}
				}
				wardfile.close();
			}
			if (choice == 2)
			{
				while (1)
				{
					bool found = 0;
					string answer; int i = 0;
					cout << "\n\n\t\tENTER THE WARD NUMBER YOU WANT DETAILS OF: ";
					cin >> answer;
					string readout;
					ifstream validation("ward.txt");
					while (getline(validation, readout))
					{
						if (readout == answer)
						{
							found = 1;
						}
					}
					if (found == false)
					{
						system("CLS");
						cout << "\n\n\t\tWARD # " << answer << " DOES NOT EIXTS!\n" << endl;
						break;
					}
					validation.close();
					while (wardfile.eof() == 0)
					{
						wardfile >> tempwardnum;
						if (tempwardnum == answer)
						{
							wardfile >> totalbeds >> tempBedsAvailable;
							cout << "\n\n\t\tWARD NUMBER : " << tempwardnum << endl;
							cout << "\n\t\tTOTAL BEDS : " << totalbeds << endl;
							cout << "\n\t\tBEDS AVAILABLE : " << tempBedsAvailable << endl;
							cout << endl;
							break;
						}
						else
						{
							for (i = 0; i < 2; i++)
							{
								wardfile >> tempwardnum;
							}
						}
					}
					wardfile.close();
					break;
				}
			}
		}
		else
		{
			system("CLS");
			cout << "\n\n\t\tWARD FILE DOES NOT EXIST!\n" << endl;
		}
	}
};
class bed :public ward
{
protected:
	int bedNum;
	string nurse;
public:
	bed() :ward('a')
	{

	}
	bed(int x) :ward(x)
	{
		cout << "\n\n\t\t\tASSIGNING A BED TO PATIENT";
		cout << "\n\n\t\tENTER THE BED NUMBER: ";
		cin >> bedNum;
		cout << "\n\t\tENTER THE NAME OF NURSE: ";
		cin >> nurse;
		bed b;
		bedfiling();
		numOfBedAvailable--;
	}
	void display()
	{
		cout << "BED NUMBER: " << bedNum << endl;
		cout << "NAME OF NURSE: " << nurse << endl;
	}
	void bedfiling()
	{
		int serialnum;
		ifstream serialfile;
		serialfile.open("serial.txt");
		if (serialfile.is_open())
		{
			serialfile >> serialnum;
			serialnum++;
			serialfile.close();
		}
		else
		{
			serialnum = 1;
		}
		ofstream bedfile;
		bedfile.open("bed.txt", ios::app);
		bedfile << serialnum << endl << bedNum << endl << Assignedward << endl << nurse << endl;
		bedfile.close();
	}
};
class Patient :public bed
{
protected:
	int serial;
	string firstName;
	string lastName;
	string NIC;
	bool critical;
	string contact;
	bool vaccinated;
public:
	Patient() :bed()
	{

	}
	Patient(int x) :bed(x) // Add Record
	{
		ifstream SerialNum1("Serial.txt");
		SerialNum1 >> serial;
		serial++;
		SerialNum1.close();
		ofstream SerialNum2("Serial.txt");
		SerialNum2 << serial;
		SerialNum2.close();
		cout << "\n\n\t\t\tPatient Information" << endl;
		cout << "\n\n\t\tAutomated Patient Serial Number: " << serial;
		cout << "\n\n\t\tFirst Name: "; cin >> firstName;
		cin.ignore();
		cout << "\n\t\tLast Name: "; cin >> lastName;
		cin.ignore();
		cout << "\n\t\tCNIC Number: "; cin >> NIC;
		while (1)
		{
			char crt;
			cout << "\n\t\tIs Patient in a critical condition?(Y/N) "; cin >> crt;
			if (crt == 'y' || crt == 'Y')
			{
				critical = true;
				break;
			}
			else if (crt == 'n' || crt == 'N')
			{
				critical = false;
				break;
			}
			else
			{
				cout << "\n\t\tInvalid Choice!" << endl;
			}
		}
		cout << "\n\t\tContact Number: "; cin >> contact;
		while (1)
		{
			char vcn;
			cout << "\n\t\tIs the Patient vaccinated(Y/N) ?"; cin >> vcn;
			if (vcn == 'y' || vcn == 'Y')
			{
				vaccinated = true;
				break;
			}
			else if (vcn == 'n' || vcn == 'N')
			{
				vaccinated = false;
				break;
			}
			else
			{
				cout << "\t\tInvalid Choice!" << endl;
			}
		}
	}
	Patient(int x, int y) // Edit Record
	{
		ifstream readFile("patient.txt");
		if (readFile)
		{
			while (1) // Validation Loop
			{
				bool found = 0;
				ofstream outFile("temp.txt");
				ifstream validation("patient.txt");
				string readout;
				string search, pfname, plname, pNIC, pcontact;
				bool pcritical, pvaccinated;
				unsigned int skipLines = 0;
				cout << "ENTER THE SERIAL NUMBER OF PATIENT YOU WANT TO EDIT THE RECORD OF: ";
				cin >> search;
				while (getline(validation, readout))
				{
					if (readout == search)
					{
						found = 1;
					}
				}
				if (found == false)
				{
					system("CLS");
					cout << "\n\n\t\tNO PATEINT OF SERIAL # " << search << " EIXTS!\n" << endl;
					break;
				}
				validation.close();
				system("CLS");
				cout << "\n\n\t\t\tEDIT MENU OF PATIENT # " << search << endl;
				cout << "\n\n\t\tEDIT FIRST NAME\t\t\t\t[1]" << endl;
				cout << "\n\t\tEDIT LAST NAME\t\t\t\t[2]" << endl;
				cout << "\n\t\tEDIT CNIC NUMBER\t\t\t[3]" << endl;
				cout << "\n\t\tEDIT CRITICAL CONDITION STATUS\t\t[4]" << endl;
				cout << "\n\t\tEDIT CONTACT NUMBER\t\t\t[5]" << endl;
				cout << "\n\t\tEDIT VACCINATION STATUS\t\t\t[6]" << endl;
				cout << "\n\t\tEDIT WHOLE RECORD\t\t\t[7]" << endl;
				cout << "\n\t\tGO BACK\t\t\t\t\t[8]" << endl;
				cout << "\n\n\t\tYour Choice: ";
				int choice;
				cin >> choice;

				switch (choice)
				{
				case 1:
				{
					system("CLS");
					cout << "\n\n\t\tENTER NEW FIRST NAME: ";
					cin >> pfname;
					while (getline(readFile, readout))
					{
						if (skipLines != 0)
						{
							skipLines--;
							continue;
						}
						else if (readout == search)
						{
							outFile << search << endl;
							outFile << pfname;
							skipLines = 1;
						}
						else
						{
							outFile << readout;
						}
						outFile << endl;
					}
					outFile.close();
					readFile.close();
					remove("patient.txt");
					int i = rename("temp.txt", "patient.txt");
					break;
				}
				case 2:
				{
					system("CLS");
					cout << "\n\n\t\tENTER NEW LAST NAME: ";
					cin >> plname;
					while (getline(readFile, readout))
					{
						if (skipLines != 0)
						{
							skipLines--;
							continue;
						}
						else if (readout == search)
						{
							outFile << search << endl;
							getline(readFile, readout);
							outFile << readout << endl;
							outFile << plname;
							skipLines = 1;
						}
						else
						{
							outFile << readout;
						}
						outFile << endl;
					}
					outFile.close();
					readFile.close();
					remove("patient.txt");
					int i = rename("temp.txt", "patient.txt");
					break;
				}
				case 3:
				{
					system("CLS");
					cout << "\n\n\t\tENTER NEW CNIC NUMBER: ";
					cin >> pNIC;
					while (getline(readFile, readout))
					{
						if (skipLines != 0)
						{
							skipLines--;
							continue;
						}
						else if (readout == search)
						{
							outFile << search << endl;
							for (int i = 0; i < 2; i++)
							{
								getline(readFile, readout);
								outFile << readout << endl;
							}
							outFile << pNIC;
							skipLines = 1;
						}
						else
						{
							outFile << readout;
						}
						outFile << endl;
					}
					outFile.close();
					readFile.close();
					remove("patient.txt");
					int i = rename("temp.txt", "patient.txt");
					break;
				}
				case 4:
				{
					system("CLS");
					while (1)
					{
						char crt;
						cout << "IS THE PATIENT IN CRITICAL CONDITION?(Y/N) "; cin >> crt;
						if (crt == 'y' || crt == 'Y')
						{
							pcritical = true;
							break;
						}
						else if (crt == 'n' || crt == 'N')
						{
							pcritical = false;
							break;
						}
						else
						{
							cout << "INVALID CHOICE!" << endl;
						}
					}
					while (getline(readFile, readout))
					{
						if (skipLines != 0)
						{
							skipLines--;
							continue;
						}
						else if (readout == search)
						{
							outFile << search << endl;
							for (int i = 0; i < 3; i++)
							{
								getline(readFile, readout);
								outFile << readout << endl;
							}
							outFile << pcritical;
							skipLines = 1;
						}
						else
						{
							outFile << readout;
						}
						outFile << endl;
					}
					outFile.close();
					readFile.close();
					remove("patient.txt");
					int i = rename("temp.txt", "patient.txt");
					break;
				}
				case 5:
				{
					system("CLS");
					cout << "\n\n\t\tENTER NEW CONTACT NUMBER: ";
					cin >> pcontact;
					while (getline(readFile, readout))
					{
						if (skipLines != 0)
						{
							skipLines--;
							continue;
						}
						else if (readout == search)
						{
							outFile << search << endl;
							for (int i = 0; i < 4; i++)
							{
								getline(readFile, readout);
								outFile << readout << endl;
							}
							outFile << pcontact;
							skipLines = 1;
						}
						else
						{
							outFile << readout;
						}
						outFile << endl;
					}
					outFile.close();
					readFile.close();
					remove("patient.txt");
					int i = rename("temp.txt", "patient.txt");
					break;
				}
				case 6:
				{
					system("CLS");
					while (1)
					{
						char crt;
						cout << "IS THE PATIENT COVID-19 VACCINATED?(Y/N) "; cin >> crt;
						if (crt == 'y' || crt == 'Y')
						{
							pvaccinated = true;
							break;
						}
						else if (crt == 'n' || crt == 'N')
						{
							pvaccinated = false;
							break;
						}
						else
						{
							cout << "INVALID CHOICE!" << endl;
						}
					}
					while (getline(readFile, readout))
					{
						if (skipLines != 0)
						{
							skipLines--;
							continue;
						}
						else if (readout == search)
						{
							outFile << search << endl;
							for (int i = 0; i < 5; i++)
							{
								getline(readFile, readout);
								outFile << readout << endl;
							}
							outFile << pvaccinated;
							skipLines = 1;
						}
						else
						{
							outFile << readout;
						}
						outFile << endl;
					}
					outFile.close();
					readFile.close();
					remove("patient.txt");
					int i = rename("temp.txt", "patient.txt");
					break;
				}
				case 7:
				{
					system("CLS");
					cout << "ENTER NEW FIRST NAME: ";
					cin >> pfname;
					cout << "ENTER NEW LAST NAME: ";
					cin >> plname;
					cout << "ENTER NEW CNIC:";
					cin >> pNIC;
					while (1)
					{
						char crt;
						cout << "IS THE PATIENT IN CRITICAL CONDITION?(Y/N) "; cin >> crt;
						if (crt == 'y' || crt == 'Y')
						{
							pcritical = true;
							break;
						}
						else if (crt == 'n' || crt == 'N')
						{
							pcritical = false;
							break;
						}
						else
						{
							cout << "INVALID CHOICE!" << endl;
						}
					}
					cout << "ENTER NEW CONTACT NUMBER: "; cin >> pcontact;
					while (1)
					{
						char vcn;
						cout << "IS THE PATIENT VACCINATED?(Y/N) "; cin >> vcn;
						if (vcn == 'y' || vcn == 'Y')
						{
							pvaccinated = true;
							break;
						}
						else if (vcn == 'n' || vcn == 'N')
						{
							pvaccinated = false;
							break;
						}
						else
						{
							cout << "INVALID CHOICE!" << endl;
						}
					}

					while (getline(readFile, readout))
					{
						if (skipLines != 0) {
							skipLines--;
							continue;
						}
						else if (readout == search)
						{
							outFile << search << endl;
							outFile << pfname << endl;
							outFile << plname << endl;
							outFile << pNIC << endl;
							outFile << pcritical << endl;
							outFile << pcontact << endl;
							outFile << pvaccinated;
							skipLines = 6;
						}
						else
						{
							outFile << readout;
						}
						outFile << endl;
					}
					outFile.close();
					readFile.close();
					remove("patient.txt");
					int i = rename("temp.txt", "patient.txt");
					break;
				}
				case 8:
				{
					readFile.close();
					outFile.close();
					remove("temp.txt");
					break;
				}
				default:
				{
					break;
				}
				}
				break;
			}
		}
		else
		{
			system("CLS");
			cout << "\n\n\t\tPATIENT FILE DOES NOT EXIST!\n" << endl;
		}
	}
	Patient(string a, string z) // View Record
	{
		{
			ifstream readFile("patient.txt");
			if (readFile)
			{
				while (1)
				{
					bool found = 0;
					int i;
					string readout;
					string temp[6];
					string pfname, plname, pNIC, pcontact;
					bool pvaccinated, pcritical;
					string tempSr;
					cout << "\nPLEASE ENTER THE SERIAL NUMBER OF THE PATIENT: ";
					cin >> tempSr;
					ifstream validation("patient.txt");
					while (getline(validation, readout))
					{
						if (readout == tempSr)
						{
							found = 1;
						}
					}
					if (found == false)
					{
						system("CLS");
						cout << "\n\n\t\tNO PATIENT OF SERIAL # " << tempSr << " EIXTS!\n" << endl;
						break;
					}
					validation.close();
					while (getline(readFile, readout))
					{
						readFile >> readout;
						if (readout == tempSr)
						{
							readFile >> pfname >> plname >> pNIC >> pcritical >> pcontact >> pvaccinated;
							cout << "\n\n\t\tSERIAL NUMBER: " << tempSr;
							cout << "\n\n\t\tFIRST NAME: " << pfname;
							cout << "\n\n\t\tLAST NAME: " << plname;
							cout << "\n\n\t\tCNIC # : " << pNIC;
							if (pcritical == 0)
							{
								cout << "\n\n\t\tIS THE PATIENT CRITICAL: NO";
							}
							else if (pcritical == 1)
							{
								cout << "\n\n\t\tIS THE PATIENT CRITICAL: YES" << endl;
							}
							cout << "\n\n\t\tCONTACT: " << pcontact;
							if (pvaccinated == 0)
							{
								cout << "\n\n\t\tIS THE PATIENT VACCINATED: NO" << endl;
							}
							else if (pvaccinated == 1)
							{
								cout << "\n\n\t\tIS THE PATIENT VACCINATED: YES" << endl;
							}
							break;
						}
						else
						{
							for (i = 0; i < 6; i++)
							{
								readFile >> temp[i];
							}
						}
					}
					break;
				}
			}
			else
			{
				system("CLS");
				cout << "\n\n\t\tPATIENT FILE DOES NOT EXIST!\n" << endl;
			}
		}
	}

	Patient(string a, int z) // Delete Record
	{
		ifstream readFile("patient.txt");
		ifstream readFile1("bed.txt");
		string tempSr;
		if (readFile)
		{
			bool found = 0;
			while (1)
			{
				ofstream outFile("temp.txt");
				ifstream validation("patient.txt");
				string readout;
				cout << "\nPLEASE ENTER THE SERIAL NUMBER OF THE PATIENT: ";
				cin >> tempSr;
				while (getline(validation, readout))
				{
					if (readout == tempSr)
					{
						found = true;
					}
				}
				if (found != true)
				{
					system("CLS");
					cout << "\n\n\t\tNO PATEINT OF SERIAL # " << tempSr << " EIXTS!\n" << endl;
					break;
				}
				validation.close();
				unsigned int skipLines = 0;
				system("CLS");
				while (getline(readFile, readout))
				{
					if (skipLines != 0)
					{
						skipLines--;
						continue;
					}
					else if (readout == tempSr)
					{
						skipLines = 6;
					}
					else
					{
						outFile << readout;
					}
					outFile << endl;
				}
				cout << "\n\n\t\tRECORD OF # " << tempSr << " SUCCESSFULLY DELETED" << endl;
				outFile.close();
				readFile.close();
				remove("patient.txt");
				int i = rename("temp.txt", "patient.txt");
				break;
			}
			while(1)
			{
				ofstream outFile1("temp.txt");
				ifstream validation1("bed.txt");
				string readout1;
				while (getline(validation1, readout1))
				{
					if (readout1 == tempSr)
					{
						found = true;
					}
				}
				if (found != true)
				{
					break;
				}
				validation1.close();
				unsigned int skipLines1 = 0;
				system("CLS");
				while (getline(readFile1, readout1))
				{
					if (skipLines1 != 0)
					{
						skipLines1--;
						continue;
					}
					else if (readout1 == tempSr)
					{
						skipLines1 = 3;
					}
					else
					{
						outFile1 << readout1;
					}
					outFile1 << endl;
				}
				outFile1.close();
				readFile1.close();
				remove("bed.txt");
				int i = rename("temp.txt", "bed.txt");
				break;
			}
		}
		else
		{
			system("CLS");
			cout << "\n\n\t\tPATIENT FILE DOES NOT EXIST!\n" << endl;
		}
	}
	void patientFiling()
	{
		ofstream patientfile;
		patientfile.open("patient.txt", ios::app);
		patientfile << endl << serial << endl << firstName << endl << lastName << endl << NIC << endl << critical << endl << contact << endl << vaccinated;
		patientfile.close();
	}
	friend void pAddRecord();
	friend void pViewRecord();
	friend void pEditRecord();
	friend void pDeleteRecord();
};

class doctor :public Patient
{
public:
	doctor()
	{

	}
	void viewallpatients()
	{
		ifstream patientfile;
		patientfile.open("patient.txt", ios::in);
		if (patientfile)
		{
			int choice;
			string pfname, plname, pNIC, pcontact, pserial;
			bool pvaccinated, pcritical;
			system("CLS");
			if (patientfile.is_open())
			{
				int i = 0;
				while (patientfile.eof() == 0)
				{
					if (i == 0)
					{
						patientfile >> pserial;
						cout << "\n\n\t\tPATIENT SERIAL NUMBER : " << pserial << endl;
					}
					if (i == 1)
					{
						patientfile >> pfname;
						cout << "\n\t\tPATIENT NAME : " << pfname << endl;
					}
					if (i == 2)
					{
						patientfile >> plname;
						cout << "\n\t\tPATIENT LAST NAME : " << plname << endl;
					}
					if (i == 3)
					{
						patientfile >> pNIC;
						cout << "\n\t\tPATIENT NIC : " << pNIC << endl;
					}
					if (i == 4)
					{
						patientfile >> pcritical;
						if (pcritical == 1)
							cout << "\n\t\tCRITICAL STATUS : Yes" << endl;
						else
							cout << "\n\t\tCRITICAL STATUS : NO" << endl;
					}
					if (i == 5)
					{
						patientfile >> pcontact;
						cout << "\n\t\tPATIENT CONTACT NUMBER : " << pcontact << endl;
					}
					if (i == 6)
					{
						patientfile >> pvaccinated;
						if (pvaccinated == 1)
							cout << "\n\t\tVACCINATED : YES" << endl;
						if (pvaccinated == 0)
							cout << "\n\t\tVACCINATED : NO" << endl;
					}
					if (i == 7)
					{
						cout << endl;
						i = 0;
					}
					else
					{
						i++;
					}
				}
				system("pause");
			}
			else
			{
				cout << "Error in opening file";
			}
			patientfile.close();
		}
		else
		{
			system("CLS");
			cout << "\n\n\t\tPATIENT FILE DOES NOT EXIST!\n" << endl;
			system("pause");
		}
	}
	void vaccinatepatients()
	{
		while (1)
		{
			bool found = 0;
			ofstream outFile("temp.txt");
			ifstream validation("patient.txt");
			string readout;
			string search;
			bool pcritical, pvaccinated;
			unsigned int skipLines = 0;
			system("CLS");
			cout << "\n\n\t\tENTER THE SERIAL NUMBER OF THE PATIENT YOU WOULD LIKE TO VACCINATED : ";
			cin >> search;
			while (getline(validation, readout))
			{
				if (readout == search)
				{
					found = 1;
				}
			}
			if (found == false)
			{
				system("CLS");
				cout << "\n\n\t\tNO PATEINT OF SERIAL # " << search << " EIXTS!\n" << endl;
				system("pause");
				break;
			}
			validation.close();
			ifstream readFile("patient.txt");
			while (getline(readFile, readout))
			{
				if (skipLines != 0)
				{
					skipLines--;
					continue;
				}
				else if (readout == search)
				{
					outFile << search << endl;
					for (int i = 0; i < 5; i++)
					{
						getline(readFile, readout);
						outFile << readout << endl;
					}
					getline(readFile, readout);
					if (readout == "0")
					{
						outFile << true;
						skipLines = 1;
						system("CLS");
						cout << "\n\n\t\tPATIENT OF SERIAL # " << search << " SUCCESSFULLY VACCINATED" << endl;
						system("pause");
					}
					if (readout == "1")
					{
						system("CLS");
						cout << "\n\n\t\tPATIENT ALREADY VACCINATED!\n" << endl;
						system("pause");
						outFile << readout << endl;
						skipLines = 1;
					}
				}
				else
				{
					outFile << readout;
				}
				outFile << endl;

			}
			outFile.close();
			readFile.close();
			remove("patient.txt");
			int i = rename("temp.txt", "patient.txt");
			break;
		}
	}
	void criticalpatients()
	{
		ifstream bedfile("bed.txt");
		ifstream patientfile("patient.txt");
		ofstream tempfile("temp.txt");
		if (bedfile && patientfile)
		{
			int criticCount = 0;
			string tempo;
			string tempcr;
			getline(patientfile, tempo);
			int i = 0;
			string tempSr,
				tempfname,
				templname,
				tempvac;
			while (getline(patientfile, tempo))
			{
				if (i == 0)
				{
					tempSr = tempo;
					i++;
				}
				else if (i == 1)
				{
					tempfname = tempo;
					i++;
				}
				else if (i == 2)
				{
					templname = tempo;
					i++;
				}
				else if (i == 3)
					i++;
				else if (i == 4)
				{
					tempcr = tempo;
					i++;
				}
				else if (i == 5)
					i++;
				else if (i == 6)
				{
					tempvac = tempo;
					i++;
				}
				if (i == 7)
				{
					if (tempcr == "1")
					{
						criticCount++;
						tempfile << tempSr << endl;
						tempfile << tempfname << endl;
						tempfile << templname << endl;
						tempfile << tempvac << endl;
					}
					i = 0;
				}
			}
			tempfile.close();
			system("CLS");
			cout << "\n\n\t\tTHESE PATIENTS ARE IN CRITICAL CONDITION AND REQUIRE IMMEDIATE ASSISTANCE:\n";
			ifstream tempfile1("temp.txt");
			string temp, tsr, tfname, tlname, tvac;
			i = 0;
			while (getline(tempfile1, temp))
			{
				if (i == 0)
				{
					tsr = temp;
					i++;
				}
				else if (i == 1)
				{
					tfname = temp;
					i++;
				}
				else if (i == 2)
				{
					tlname = temp;
					i++;
				}
				else if (i == 3)
				{
					tvac = temp;
					i++;
				}
				if (i == 4)
				{
					cout << "\n\n\t\tS. # " << tsr;
					cout << "\n\n\t\tFIRST NAME: " << tfname;
					cout << "\n\n\t\tLAST NAME: " << tlname;
					if (tvac == "0")
					{
						cout << "\n\n\t\tVACCINATED: NO" << endl;
					}
					else if (tvac == "1")
					{
						cout << "\n\n\t\tVACCINATED: YES" << endl;
					}
					i = 0;
				}
			}
			tempfile1.close();
			system("pause");
		}
		else
		{
			system("CLS");
			cout << "\n\n\t\tBED FILE DOES NOT EXIST!\n" << endl;
		}
	}
};
int ward::wardNum = 0;
void dviewcriticalpatient()
{
	doctor d;
	d.criticalpatients();
}
void dviewpatients()
{
	doctor d;
	d.viewallpatients();
}
void dvaccinatepatient()
{
	doctor d;
	d.vaccinatepatients();
}
void wdeleterecord()
{
	system("CLS");
	ward w3("a");
	w3.wdeletefile();
}
void wdisplayrecord()
{
	system("CLS");
	ward w3("a");
	w3.wardreadfile();
}
void weditrecord()
{
	system("CLS");
	ward w1("a");
	w1.weditrecord();

}
void waddrecord()
{
	system("CLS");
	ward w;
}
void pAddRecord()
{
	system("CLS");
	Patient p(10);
	p.patientFiling();
}
void pEditRecord()
{
	system("CLS");
	Patient p(10, 20);
}
void pViewRecord()
{
	system("CLS");
	Patient p("x", "a");
}
void pDeleteRecord()
{
	system("CLS");
	Patient p("x", 0);
}
class MainMenu
{
public:
	int choice;
	MainMenu()
	{
		Sleep(50);
		cout << "\n\n\n\n";
		Sleep(50);
		cout << "\t\t\t_________________________________________________________________" << endl;	Sleep(50);
		cout << "\t\t\t|                        WELCOME TO                              |" << endl;	Sleep(50);
		cout << "\t\t\t|             COVID-19 HOSPITAL MANAGEMENT SYSTEM                |" << endl;	Sleep(50);
		cout << "\t\t\t|            ======================================              |" << endl;	Sleep(50);
		cout << "\t\t\t|                      DEVELOPED BY:                             |" << endl;	Sleep(50);
		cout << "\t\t\t|                  ABDULLAH NAEEM 20K-0496                       |" << endl;	Sleep(50);
		cout << "\t\t\t|                   YAHYA NAVEED 20K-1050                        |" << endl;	Sleep(50);
		cout << "\t\t\t|                    ARHAM AFZAL 20K-0329                        |" << endl;	Sleep(50);
		cout << "\t\t\t|________________________________________________________________|" << endl;	Sleep(50);
		cout << "\n\n\n\n";
		system("pause");
		system("CLS");
		int j = 0;
		while (j == 0)
		{
			cout << "\n\n\t\t*************************************\n";
			cout << "\n\t\t\t\tMAIN MENU\n";
			cout << "\n\t\t*************************************\n";
			cout << "\n\t\tSELECT USER:";
			cout << "\n\n\n\t\tRECEPTIONIST\t\t[1]";
			cout << "\n\n\t\tCARETAKER\t\t[2]";
			cout << "\n\n\t\tDOCTOR\t\t\t[3]";
			cout << "\n\n\t\tEXIT\t\t\t[4]";
			cout << "\n\n\n\t\tYour Choice: ";
			cin >> choice;
			switch (choice)
			{
				case 1:
					while (1)
					{
						int choice;
						system("CLS");
						cout << "\n\n\t\t\tRECEPTIONIST MENU:";
						cout << "\n\n\t\tADD A PATIENT RECORD\t\t[1]";
						cout << "\n\n\t\tEDIT A PAITENT RECORD\t\t[2]";
						cout << "\n\n\t\tVIEW A PATIENT RECORD\t\t[3]";
						cout << "\n\n\t\tDELETE A PATIENT RECORD\t\t[4]";
						cout << "\n\n\t\tRETURN TO MENU\t\t\t[5]";
						cout << "\n\n\n\t\tYour Choice: ";
						cin >> choice;
						switch (choice)
						{
						case 1:
							pAddRecord();
							cout << "\n\n\t\tRECORD HAS BEEN ADDED SUCCESSFULLY!" << endl;
							system("pause");
							break;
						case 2:
							pEditRecord();
							system("pause");
							break;
						case 3:
						{
							pViewRecord();
							system("pause");
							break;
						}
						case 4:
						{
							pDeleteRecord();
							system("pause");
							break;
						}
						case 5:
							cout << "\nEXITING RECEPTIONIST MODE" << endl;
							system("pause");
							break;
						default:
							cout << "\nINVALID CHOICE!" << endl;
							system("pause");
							break;
						}
						system("CLS");
						if (choice == 5)
						{
							break;
						}
					}
					break;
				case 2:
				{
					int i = 0;
					while (i == 0)
					{
						int choice2;
						system("CLS");
						cout << "\n\n\t\t\tCARETAKER MENU" << endl;
						cout << "\n\n\t\tADD WARD DETAILS\t[1]";
						cout << "\n\n\t\tEDIT WARD DETAILS\t[2]";
						cout << "\n\n\t\tVIEW WARD DETAILS\t[3]";
						cout << "\n\n\t\tDELETE WARD DETAILS\t[4]";
						cout << "\n\n\t\tRETURN TO MENU\t\t[5]\n";
						cout << "\n\n\t\tENTER CHOICE: ";
						cin >> choice2;
						switch (choice2)
						{
						case 1:
							waddrecord();
							system("pause");
							break;
						case 2:
							weditrecord();
							system("pause");
							break;
						case 3:
							wdisplayrecord();
							system("pause");
							break;
						case 4:
							wdeleterecord();
							system("pause");
							break;
						case 5:
							cout << "\nEXITING CARETAKER MODE";
							i = 1;
							break;
						default:
							cout << "\n\t\tINVALID CHOICE!\n" << endl;
							system("pause");
							break;
						}
					}
					break;
				}
				case 3:
					while (1)
					{
						int choice2;
						system("CLS");
						cout << "\n\n\t\t\tDOCTOR MENU" << endl;
						cout << "\n\n\t\tVIEW ALL CURRENT PATIENTS\t[1]" << endl;
						cout << "\n\t\tVACCINATE A PATIENT\t\t[2]";
						cout << "\n\n\t\tVIEW CRITICAL PATIENTS\t\t[3]";
						cout << "\n\n\t\tGO BACK TO MAIN MENU\t\t[4]";
						cout << "\n\n\n\t\tYour Choice: ";
						cin >> choice2;
						switch (choice2)
						{
						case 1:
							dviewpatients();
							break;
						case 2:
							dvaccinatepatient();
							break;
						case 3:
							dviewcriticalpatient();
							break;
						case 4:
							cout << "\n\nEXITING DOCTOR MODE";
							cout << "\n\nPRESS ANY KEW TO GO BACK";
							system("pause");
							break;
						default:
							cout << "\nINVALID CHOICE PLEASE SELECT AGAIN!";
							system("pause");
							break;
						}
						if (choice2 == 4)
						{
							break;
						}
					}
					break;
				case 4:
				{
					j = 1;
					system("pause");
					break;
				}
				default:
				{
					cout << "\n\n\t\tINVALID SELECTION!" << endl;
					system("pause");
					break;
				}
			}	system("CLS");
		}
	}
};
int main()
{
	system("color A");
	MainMenu obj;
	return 0;
};
