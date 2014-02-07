/*Created by KASHYAP PATEL
FINAL PROJECT FOR PROGRAMMING FINANCE
Submission Date:12/06/2013*/
#include"finalproject_kashyap.h"

double Account::current_balance = 10000;

void Account::update_current_balance() //updates balance after transaction
{
	ofstream fout("current_balance.dat",ios::binary);
	fout << current_balance;
	fout.close();
}

void Account::read_current_balance_at_start() //updates current balance at start
{
	ifstream fin("current_balance.dat", ios::binary);
	fin >> current_balance;
	fin.close();
}

unsigned short Account::get_instruction()
{
	unsigned short op;		//Operation
	cout << "Please select an account to access:" << endl;
	cout << "1. Stock Portfolio Account" << endl;
	cout << "2. Bank Account" << endl;
	cout << "3. Exit" << endl;
	cout << "Option:";
	cin >> op;	//Select Option
	return op;
}

void Account::do_instruction(unsigned short op,LinkedList* ll_ptr)
{
	static bool var_stock = false;
	StockAccount* stock_ptr = new StockAccount; //Account Pointer pointing at StockAccount obj
	switch (op)		//According to input obtained from Account::get_instruction(), will perform appropriate operation
	{
	case 1: //Stock Account
		{
				stock_ptr->update_linkedlist_at_start(ll_ptr, var_stock);
				unsigned short stock_op;		//Operation for Stock Account
				do
				{
					stock_op = stock_ptr->get_instruction();	//Same logic as Base Class
					stock_ptr->do_instruction(stock_op,ll_ptr);
					var_stock = true;
				} while (stock_op != 7);		//Continue till '7' is pressed for going back
				break;
		}
	case 2:	//Bank Account
		{
				BankAccount* bank_ptr = new BankAccount; //Account Pointer pointing at BankAccount obj
				unsigned short bank_op;		//Operation for Bank Account
				do
				{
					bank_op = bank_ptr->get_instruction();
					bank_ptr->do_instruction(bank_op,ll_ptr);
				} while (bank_op != 5);	//Continue till '5' is pressed for going back
				break;
		}
	case 3:		//Exit
		{

					stock_ptr->get_graph(); //graph at end
					cout << endl << "Thanks for using this service. Your session is saved" << endl;
					break;
		}
	default:	//Invalid Entry
		{
					cout << endl << "Please enter proper input" << endl;
					break;
		}
	}
}