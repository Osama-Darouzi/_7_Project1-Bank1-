#include "Functions.h";

void ShowMainMenu_TS();

void TransactionScreen_TS(vector <stClient>&);

void ShowClientsScreen(vector <stClient> &vClients)
{
	system("cls");
	vClients = LoadClientsFromFileToVector(ClientsFileName);
	string Line = Underscores(112);

	PrintActionScreen(ShowClientList);

	cout << "\t\t\t\t\tClient List (" << vClients.size() << ") Client(s)\n";
	cout << Line << "\n\n";

	cout << " | " << setw(15) << left << "Account Number"
		<< " | " << setw(15) << left << "Pin Code"
		<< " | " << setw(45) << left << "Client Name"
		<< " | " << setw(15) << left << "Phone Number"
		<< " | " << setw(10) << left << "Balance";

	cout << "\n" << Line << "\n\n";

	PrintClientsTable(vClients);

	cout << "\n" << Line << "\n\n" << endl;
}

void AddNewClientsScreen(vector <stClient> &vClients) 
{
	do
	{
		system("cls");
		PrintActionScreen(AddNewClient);

		cout << "Adding New Client...:\n\n";

		AddClient(vClients);

		SaveClientsDataToFile(ClientsFileName, vClients);

		cout << "\nClient Added Successfully, ";

	} while (YesNoQues("Do you want to add another new client ? Y/N: "));
}

void DeleteClientScreen(vector <stClient> &vClients)
{
	system("cls");
	PrintActionScreen(DeleteClient);

	string AccNum = ReadString("\nPlease enter Account Number: ");
	
	DeleteClientByAccNum(vClients, AccNum);
	
}

void UpdateClientScreen(vector <stClient>& vClients)
{
	system("cls");
	PrintActionScreen(UpdateClientInfo);

	string AccNum = ReadString("\nPlease enter Account Number: ");

	UpdateClientByAccNum(vClients, AccNum);
}

void FindClientScreen(vector <stClient>& vClients)
{
	system("cls");
	PrintActionScreen(FindClient);

	string AccNum = ReadString("\nPlease enter Account Number: ");
	stClient FoundClient;

	if (FindClientByAccNum(vClients, AccNum, FoundClient))
	{
		PrintClientData(FoundClient);
	}
}

void TransactionScreen(vector <stClient>& vClients)
{
	enTransactions ActionType;

	do
	{
		system("cls");
		PrintTransactionsScreen();
		ActionType = Choose_TrnsA_Action();

		switch (ActionType)
		{
		case eDeposit:
			system("cls");
			WithdrawOrDeposit_Screen(vClients, ActionType);
			break;
		case eWithdraw:
			system("cls");
			WithdrawOrDeposit_Screen(vClients, ActionType);
			break;
		case eTotalBalance:
			system("cls");
			TotalBalancesScreen(vClients);
			break;
		case eMainMenu:
			system("cls");
			break;
		}

		if (ActionType != eMainMenu)
		{
			cout << "\n\nPress any key to go back to Transaction Menu...";
			system("pause>0");
		}

	} while (ActionType != eMainMenu);
}

void ExitScreen()
{
	system("cls");
	PrintActionScreen(Exit);
}

void ChooseWhatToDo(vector <stClient>& vClients, enMainMenu ActionType)
{
	switch (ActionType)
	{
	case ShowClientList:
		ShowClientsScreen(vClients);
		break;
	case AddNewClient:
		AddNewClientsScreen(vClients);
		break;
	case DeleteClient:
		DeleteClientScreen(vClients);
		break;
	case UpdateClientInfo:
		UpdateClientScreen(vClients);
		break;
	case FindClient:
		FindClientScreen(vClients);
		break;
	case Transactions:
		TransactionScreen(vClients);
		break;
	case Exit:
		ExitScreen();
		break;
	}
}

void ShowMainMenu(vector <stClient>& vClients)
{
	enMainMenu ActionType;

	do
	{
		PrintMainMenuScreen();
		ActionType = ChooseAction();

		ChooseWhatToDo(vClients, ActionType);

		if (ActionType != Exit && ActionType != Transactions)
		{		
			cout << "\n\nPress any key to go back to Main Menu...";
			system("pause>0");
		}

	} while (ActionType != Exit);
}

void GoBackToMainMenu()
{
	cout << "\n\nPress any key to go back to Main Menu...";
	system("pause>0");
	ShowMainMenu_TS();
}

void GoBackToTransactionScreen(vector <stClient>& vClients)
{
	cout << "\n\nPress any key to go back to Transactions Screen...";
	system("pause>0");
	TransactionScreen_TS(vClients);
}

void TransactionScreen_TS(vector <stClient>& vClients)
{
	enTransactions ActionType;

	{
		system("cls");
		PrintTransactionsScreen();
		ActionType = Choose_TrnsA_Action();

		switch (ActionType)
		{
		case eDeposit:
			system("cls");
			WithdrawOrDeposit_Screen(vClients, ActionType);
			GoBackToTransactionScreen(vClients);
			break;
		case eWithdraw:
			system("cls");
			WithdrawOrDeposit_Screen(vClients, ActionType);
			GoBackToTransactionScreen(vClients);
			break;
		case eTotalBalance:
			system("cls");
			TotalBalancesScreen(vClients);
			GoBackToTransactionScreen(vClients);
			break;
		case eMainMenu:
			//ShowMainMenu_TS();
			break;
		}

	}
	
}

void ChooseWhatToDo_TS(vector <stClient>& vClients, enMainMenu ActionType)
{
	switch (ActionType)
	{
	case ShowClientList:
		ShowClientsScreen(vClients);
		GoBackToMainMenu();
		break;
	case AddNewClient:
		AddNewClientsScreen(vClients);
		GoBackToMainMenu();
		break;
	case DeleteClient:
		DeleteClientScreen(vClients);
		GoBackToMainMenu();
		break;
	case UpdateClientInfo:
		UpdateClientScreen(vClients);
		GoBackToMainMenu();
		break;
	case FindClient:
		FindClientScreen(vClients);
		GoBackToMainMenu();
		break;
	case Transactions:
		TransactionScreen(vClients);
		ShowMainMenu_TS();
		break;
	case Exit:
		ExitScreen();
		break;
	}
}

void ShowMainMenu_TS()
{
	vector <stClient> vClients = LoadClientsFromFileToVector(ClientsFileName);
	enMainMenu ActionType;

	PrintMainMenuScreen();
	ActionType = ChooseAction();

	ChooseWhatToDo_TS(vClients, ActionType);

}

int main()
{
	
	
	ShowMainMenu_TS();

	system("pause>0");
	return 0;
}