/*Created by KASHYAP PATEL
FINAL PROJECT FOR PROGRAMMING FINANCE
Submission Date:12/06/2013*/
#include"finalproject_kashyap.h"

void BankAccount::update_bank_history(bool event_bool, double money)
{
	fstream fout;
	fout.open("bank_transaction_history.dat", ios::binary | ios::app | ios::out);
	if (fout.fail())	//For chcking if file is properly linked with the obj or not
	{
		cerr << "Error Opening File" << endl;
		exit(1);
	}
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	
	string event_print;
	if (event_bool) //==TRUE i.e BUY transaction
	{
		event_print = "DEPOSIT\t";
	}
	else
	{
		event_print = "WTHDRAW\t";
	}
	fout.seekg(0, ios::end); // put the "cursor" at the end of the file
	fout << event_print << "\t" << money << "\t" << rawtime << "\n"; //Prints the transaction details*/
	fout.close();
}

unsigned short BankAccount::get_instruction()
{
	unsigned bank_op;
	cout << endl << "Bank Account" << endl;
	cout << endl << "1. View account balance";
	cout << endl << "2. Deposit money";
	cout << endl << "3. Withdraw money";
	cout << endl << "4. Print out history";
	cout << endl << "5. Return to previous menu";
	cout << endl << "Option:";
	cin >> bank_op;
	return bank_op;
}

void BankAccount::do_instruction(unsigned short bank_op,LinkedList* ll_ptr)
{
	switch (bank_op)
	{
	case 1:  //View Balance
	{
				 cout << endl << "Your current balance is " << current_balance << endl;
				 break;
	}
	case 2:  //Deposit
	{
				 double amount;  //For deposit
				 cout << endl << "Enter the amount you want to deposit :";
				 cin >> amount;
				 current_balance += amount;
				 update_current_balance();
				 cout << endl << "Deposit Successful" << endl;
				 update_bank_history(true, amount);
				 break;
	}
	case 3:
	{
			  double amount; //For withdrawal
			  cout << endl << "Enter the amount you want to withdraw :";
			  cin >> amount;
			  if (amount <= current_balance)
			  {
				  current_balance -= amount;
				  update_current_balance();
				  cout << endl << "Withdrawal Successful" << endl;
				  update_bank_history(false, amount);
			  }
			  else
			  {
				  cout << endl << "You don't have enough money to withdraw this much sum of money" << endl;
				  cout << "Your current balance is $" << current_balance << endl;
			  }
			  break;
	}
	case 4:
	{
			  ifstream fin;
			  fin.open("bank_transaction_history.dat", ios::in | ios::binary);
			  if (fin.fail())	//For chcking if file is properly linked with the obj or not
			  {
				  cerr << "Error Opening File" << endl;
				  exit(1);
			  }
			  int length;
			  fin.seekg(0, ios::end); // put the "cursor" at the end of the file
			  length = fin.tellg(); // find the position of the cursor
			  if (length == 0) //If starting for forst time
			  {
				  cout << endl << "No Transactions Made";
				  fin.close();
			  }
			  else
			  {
				  fin.seekg(0, ios::beg);//put the 'cursor' back at the beginning of the file
				  while (fin)
				  {
					  string event_string, trash, time_info;
					  double money;
					  getline(fin, event_string, '\t');//Gets all the info from file
					  if (event_string == "") //If event string is empty, break
					  {
						  break;
					  }
					  time_t rawtime; //for time info
					  struct tm * timeinfo;
					  char buffer[80];
					  fin >> money;
					  fin >> rawtime;
					  timeinfo = localtime(&rawtime);
					  strftime(buffer, 80, "%c", timeinfo);
					  getline(fin, trash, '\n');
					  cout << event_string << "\t" << money << "\t" << buffer << "\n"; //Prints out the details on screen
				  }
				  fin.close();
			  }
			  break;
	}
	case 5:
	{
			  break;
	}
	default:
	{
			   cout << endl << "Invalid Choice" << endl;
			   break;
	}
	}
}