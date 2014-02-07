/*Created by KASHYAP PATEL
FINAL PROJECT FOR PROGRAMMING FINANCE
Submission Date:12/06/2013*/
#ifndef finalproject_kashyap_h
#define finalproject_kashyap_h

#include<yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif
#include"mex.h" 
#include"matrix.h"
#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<engine.h>
#include<vector>
#include"ll_stock_kashyap.h"
#pragma warning(disable: 4996)

using namespace std;

class Account
{
	friend class LinkedList;
public:
	Account(){}
	static double current_balance;
	virtual unsigned short get_instruction();
	virtual void do_instruction(unsigned short,LinkedList*);
	void update_current_balance();
	void read_current_balance_at_start();
};

class StockAccount :public Account
{
	friend class LinkedList;
	friend class Node;
public:
	StockAccount()
	{
		no_of_shares = 0;
	}
	unsigned short no_of_shares; //To help parse stock_list.dat
	virtual unsigned short get_instruction();
	virtual void do_instruction(unsigned short, LinkedList*);
	float get_price(string);  //Will Check if the symbol user entered is in the dat file passed as argument or not and if found will return it's price
	unsigned long get_total_transaction(); //give total stocks value
	Node* search_same_stock(string, LinkedList*);  //Will check if there is a previous entry for the same stock and will return pointer to that node
	void update_stock_transaction(bool, string, float, unsigned long, LinkedList*);
	void update_stock_list(LinkedList*);  //Will update 'stock_transaction_history.dat' after every transaction
	double total_stocks_value(LinkedList*); //Gives the total value of the stock portfolio in real time
	double update_linkedlist_at_start(LinkedList*, bool);  //Will create linkedlist depending on previous transactions everytime program restarts
	void get_graph(); //plots graph in matlab
};

class BankAccount :public Account
{
public:
	virtual unsigned short get_instruction();
	virtual void do_instruction(unsigned short,LinkedList*);
	void update_bank_history(bool,double);
};
#endif