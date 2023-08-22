#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<cstdio>
#include<fstream>

using namespace std;

string ClientsFileName = "Clients.txt";
fstream MyFile;


enum enMainMenu
{
	ShowClientList = 1,
	AddNewClient = 2,
	DeleteClient = 3,
	UpdateClientInfo = 4,
	FindClient = 5,
	Transactions = 6,
	Exit = 7
};

enum enTransactions
{
	eDeposit = 1,
	eWithdraw = 2,
	eTotalBalance = 3,
	eMainMenu = 4
};

enum enClient{ AccountNumber, PinCode, Name, PhoneNumber, Balance};

struct stClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string PhoneNumber;
	double Balance;
	bool DeleteMark = false;
};

short ReadNumberInRange(string Message, short from, short to)
{
	int num;

	do
	{
		cout << Message;
		cin >> num;

		if (num < from || num > to)
		{
			cout << "Invalid Choice, ";
		}

	} while (num >= from ||num <= to);

	return num;
}

string ReadString(string Message)
{
	string txt;

	cout << Message;
	getline(cin>>ws, txt);

	return txt;
}

bool YesNoQues(string Message)
{
	char Answer;

	cout << Message;
	cin >> Answer;

	return tolower(Answer) == 'y';
}

string Equals(short NumOfEquals)
{
	string txt = "";
	for (short i = 0; i < NumOfEquals; i++)
	{
		txt += "=";
	}

	return txt;
}

string Underscores(short NumOfUnderscores)
{
	string txt = "";
	for (short i = 0; i < NumOfUnderscores; i++)
	{
		txt += "_";
	}

	return txt;
}

string Hyphens(short NumOfHyphens)
{
	string txt = "";
	for (short i = 0; i < NumOfHyphens; i++)
	{
		txt += "-";
	}

	return txt;
}

void PrintMainMenuScreen()
{
	system("cls");
	string EqualLine = Equals(45);
	cout << EqualLine << "\n"
		<< "\t\tMain Menu Screen\n"
		<< EqualLine << "\n";

	cout << "\t[1] ShowClientList.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions\n";
	cout << "\t[7] Exit.\n";

	cout << EqualLine << endl;

}

void PrintActionScreen(enMainMenu ActionType)
{
	string Line = Hyphens(36);

	if (ActionType != ShowClientList)
	{
		cout << "\n" << Line << "\n";
	}

	switch (ActionType)
	{
	case ShowClientList:
		cout << "\n";
		break;
	case AddNewClient:
		cout << "\tAdd New Client Screen\n";
		break;
	case DeleteClient:
		cout << "\tDelete Client Screen\n";
		break;
	case UpdateClientInfo:
		cout << "\tUpdate Client info Screen\n";
		break;
	case FindClient:
		cout << "\tFind Client Screen\n";
		break;
	case Exit:
		cout << "\tProgram Ends Here :-)\n";
		break;
	}

	if (ActionType != ShowClientList)
	{
		cout << Line << "\n";
	}
	
}

enMainMenu ChooseAction()
{
	enMainMenu ActionType;
	short ActionNum;

	cout << "Choose what do you want to do: [1 to 7]: ";
	cin >> ActionNum;

	ActionType = enMainMenu(ActionNum);

	return ActionType;
}

vector <string> SplitString(string txt, string delim = "#//#")
{
	vector <string> vSplitedTxt;
	string sWord;
	short delpos = 0;

	do
	{
		delpos = txt.find(delim);
		sWord = txt.substr(0, delpos);

		if (sWord != "")
		{
			vSplitedTxt.push_back(sWord);
		}

		txt.erase(0, delpos + delim.length());

	} while (delpos != std::string::npos);

	return vSplitedTxt;
}

string JoinString(vector <string> &vSplitedString, string delim = "#//#")
{
	string txt = "";

	for (string &sWord : vSplitedString)
	{
		if (sWord != vSplitedString.back())
		{
			txt = txt + sWord + delim;
		}
		else
		{
			txt += sWord;
		}
	}

	return txt;
}

stClient ConvertLineToRecord(string Line, string Seperator = "#//#")
{
	vector <string> vSplitedLine = SplitString(Line, Seperator);
	stClient Client;

	Client.AccountNumber = vSplitedLine[AccountNumber];
	Client.PinCode = vSplitedLine[PinCode];
	Client.Name = vSplitedLine[Name];
	Client.PhoneNumber = vSplitedLine[PhoneNumber];
	Client.Balance = stod(vSplitedLine[Balance]);

	return Client;
}

string ConvertRecordToLine(stClient C, string Seperator = "#//#")
{
	string Line = "";

	Line = Line + C.AccountNumber + Seperator;
	Line = Line + C.PinCode + Seperator;
	Line = Line + C.Name + Seperator;
	Line = Line + C.PhoneNumber + Seperator;
	Line += to_string(C.Balance);

	return Line;
}

vector <stClient> LoadClientsFromFileToVector(string FileName)
{
	vector <stClient> vClients;
	stClient C;

	MyFile.open(ClientsFileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;

		while (getline(MyFile, Line))
		{
			C = ConvertLineToRecord(Line);
			vClients.push_back(C);
		}
		
		MyFile.close();
	}

	return vClients;
}

void SaveClientsDataToFile(string FileName, vector <stClient> &vClients)
{
	string DataLine;

	MyFile.open(ClientsFileName, ios::out);

	if (MyFile.is_open())
	{
		for (stClient &Client : vClients)
		{
			if(Client.DeleteMark == false)
			{
				DataLine = ConvertRecordToLine(Client);
				MyFile << DataLine << endl;
			}
		}

		MyFile.close();
	}
}

void PrintClientsTable(vector <stClient> &vClients)
{
	if (vClients.size() == 0)
	{
		cout << "There is No Client To Show.\n";
	}
	else
	{
		for (stClient C : vClients)
		{
			cout << " | " << setw(15) << left << C.AccountNumber
				<< " | " << setw(15) << left << C.PinCode
				<< " | " << setw(45) << left << C.Name
				<< " | " << setw(15) << left << C.PhoneNumber
				<< " | " << setw(10) << left << C.Balance << "\n";
		}
	}
}

void PrintClientData(stClient Client)
{
	string Line = Hyphens(36);
	cout << "\nThe following are the client details:\n";

	cout << Line ;

	cout << "\nAccount Number : " << Client.AccountNumber
		<< "\nPin Code       : " << Client.PinCode
		<< "\nName           : " << Client.Name
		<< "\nPhone          : " << Client.PhoneNumber
		<< "\nAccount Balance: " << Client.Balance << endl;

	cout << Line << "\n";

}

bool IsAccNumExist(vector <stClient> &vClients, string AccNum)
{
	for (stClient &C : vClients)
	{
		if (C.AccountNumber == AccNum)
		{
			return true;
		}
	}
	return false;
}

string AccNumValidation(vector <stClient> &vClients, string &AccNum)
{
	while(IsAccNumExist(vClients, AccNum))
	{
		cout << "\nClient with [" << AccNum << "] already exists, Enter another Account Number: ";
		getline(cin >> ws, AccNum);
	}

	return AccNum;
}

string ChkAccNumExistance(vector <stClient>& vClients, string& AccNum)
{
	while (!IsAccNumExist(vClients, AccNum))
	{
		cout << "\nClient with [" << AccNum << "] does not exists.\n\nPlease enter another Account Number: ";
		getline(cin >> ws, AccNum);
	}

	return AccNum;
}

stClient ReadClient(vector <stClient> &vClients)
{
	stClient C;

	cout << "Enter Account Number: ";
	getline(cin >> ws, C.AccountNumber);
	AccNumValidation(vClients, C.AccountNumber);

	cout << "Enter PinCode: ";
	getline(cin, C.PinCode);

	cout << "Enter Full Name: ";
	getline(cin, C.Name);

	cout << "Enter Phone Number: ";
	getline(cin, C.PhoneNumber);

	cout << "Enter AccountBalance: ";
	cin >> C.Balance;

	return C;
}

void AddClient(vector <stClient>& vClients)
{
	stClient NewClient;
	NewClient = ReadClient(vClients);
	vClients.push_back(NewClient);
}

stClient ChangeClientInfo(string AccountNum)
{
	stClient C;

	C.AccountNumber = AccountNum;

	cout << "Enter PinCode: ";
	getline(cin >> ws, C.PinCode);

	cout << "Enter Full Name: ";
	getline(cin, C.Name);

	cout << "Enter Phone Number: ";
	getline(cin, C.PhoneNumber);

	cout << "Enter AccountBalance: ";
	cin >> C.Balance;

	return C;
}

void MarkClientToDelete(vector <stClient>& vClients, string AccNum)
{
	for (stClient &C : vClients)
	{
		if (C.AccountNumber == AccNum)
		{
			C.DeleteMark = true;
		}
	}
}

bool FindClientByAccNum(vector <stClient>& vClients, string AccNum, stClient &ClientFound)
{
	for (stClient &C : vClients)
	{
		if (C.AccountNumber == AccNum)
		{
			ClientFound = C;
			return true;
		}
	}
	return false;
}

void DeleteClientByAccNum(vector <stClient>& vClients, string AccNum)
{
	stClient FoundClient;	

	if (FindClientByAccNum(vClients, AccNum, FoundClient))
	{
		PrintClientData(FoundClient);

		if (YesNoQues("\n\nAre you sure you want to delete this client? Y/N:  "))
		{
			MarkClientToDelete(vClients, AccNum);
			SaveClientsDataToFile(ClientsFileName, vClients);

			vClients = LoadClientsFromFileToVector(ClientsFileName);

			cout << "\n\nClient Deleted Successfully!";
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccNum << ") is Not Found!";
	}
	
}

void UpdateClientByAccNum(vector <stClient>& vClients, string AccNum)
{
	stClient FoundClient;

	if (FindClientByAccNum(vClients, AccNum, FoundClient))
	{
		PrintClientData(FoundClient);

		if (YesNoQues("\n\nAre you sure you want to update this client? Y/N:  "))
		{
			cout << "\n\n";

			for (stClient &C : vClients)
			{
				if (C.AccountNumber == AccNum)
				{
					C = ChangeClientInfo(AccNum);
					break;
				}
			}

			SaveClientsDataToFile(ClientsFileName, vClients);

			cout << "\n\nClient Updated Successfully!";

		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccNum << ") is Not Found!";
	}

}

void PrintTransactionsScreen()
{
	string ELine = Equals(45);

	cout << ELine << "\n"
		<< "  \tTransactions Menu Screen\n"
		<< ELine << "\n";

	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balance.\n";
	cout << "\t[4] Main Menu.\n";

	cout << ELine << endl;
}

void Print_Trnsaction_ActionScreen(enTransactions ActionType)
{
	string Line = Hyphens(36);

	cout << "\n" << Line << "\n";

	switch (ActionType)
	{
	case eDeposit:
		cout << "\t   Deposit Screen";
		break;
	case eWithdraw:
		cout << "\t   Withdraw Screen";
		break;
	}

	cout << "\n" << Line << "\n";
}

enTransactions Choose_TrnsA_Action()
{
	enTransactions ActionType;
	short ActionNum;

	cout << "Choose what do you want to do: [1 to 4]: ";
	cin >> ActionNum;

	ActionType = enTransactions(ActionNum);

	return ActionType;
}

void DepositToBalanceByAccNum(vector <stClient>& vClients, string AccNum, double ModifyAmount)
{
	for (stClient &C : vClients)
	{
		if (C.AccountNumber == AccNum)
		{
			C.Balance += ModifyAmount;
			break;
		}
	}
}

void ShowNewBalance(vector <stClient>& vClients, string AccNum)
{
	for (stClient &C : vClients)
	{
		if (C.AccountNumber == AccNum)
		{
			cout << "New Balance = " << C.Balance;
			break;
		}
	}
}

void WithdrawValidation(vector <stClient>& vClients, string AccNum, double &WithdrawAmount)
{
	for (stClient &C : vClients)
	{
		if (C.AccountNumber == AccNum)
		{
			while (C.Balance < WithdrawAmount)
			{
				cout << "\nAmount Exceeds the balance, You can withdraw up to : " << C.Balance;
				cout << "\nPlease enter another amount: ";

				cin >> WithdrawAmount;
			}
			break;
		}
	}
}

void Deposit(vector <stClient>& vClients, string AccNum)
{
	double DepositAmount = 0;
	cout << "\nPlease enter deposit amount: ";
	cin >> DepositAmount;

	if (YesNoQues("\n\nAre you sure you want to perform this transaction? Y/N: "))
	{
		DepositToBalanceByAccNum(vClients, AccNum, DepositAmount);

		cout << "\nDone Successfully, ";
		ShowNewBalance(vClients, AccNum);
	}
}

void Withdraw(vector <stClient>& vClients, string AccNum)
{
	double WithdrawAmount = 0;
	cout << "\nPlease enter withdraw amount: ";
	cin >> WithdrawAmount;

	WithdrawValidation(vClients, AccNum, WithdrawAmount);

	if (YesNoQues("\n\nAre you sure you want to perform this transaction? Y/N: "))
	{
		DepositToBalanceByAccNum(vClients, AccNum, WithdrawAmount * -1);

		cout << "\nDone Successfully, ";
		ShowNewBalance(vClients, AccNum);
	}
}

void WithdrawOrDeposit_Screen(vector <stClient>& vClients, enTransactions ActionType)
{
	Print_Trnsaction_ActionScreen(ActionType);

	stClient FoundClient;
	string AccNum = ReadString("\nPlease enter Account Number: ");
	ChkAccNumExistance(vClients, AccNum);

	if (FindClientByAccNum(vClients, AccNum, FoundClient))
	{
		PrintClientData(FoundClient);

		double WithdrawOrDepositAmount;

		switch (ActionType)
		{
		case eDeposit:
			Deposit(vClients, AccNum);
			break;
		case eWithdraw:
			Withdraw(vClients, AccNum);
			break;
		}

		SaveClientsDataToFile(ClientsFileName, vClients);
	}
}

double CalculateTotalBalances(vector <stClient>& vClients)
{
	double TotalBalances = 0;
	for (stClient &C : vClients)
	{
		TotalBalances += C.Balance;
	}

	return TotalBalances;
}

void PrintClientBalanceLine(stClient Client)
{

	{
		cout << "| " << setw(16) << left << Client.AccountNumber
			<< "| " << setw(45) << left << Client.Name
			<< "| " << setw(40) << left << Client.Balance << "\n";
	}

}

void TotalBalancesScreen(vector <stClient>& vClients)
{
	string Line = Underscores(105);

	cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s)\n";
	cout << Line << "\n\n";

	double TotalBalances = 0;

	for (stClient &C : vClients)
	{
		PrintClientBalanceLine(C);
		TotalBalances += C.Balance;
	}

	cout << "\n" << Line << "\n";

	

	cout << "\n\t\t\t\t\t\tTotal Balances = " << TotalBalances;
}