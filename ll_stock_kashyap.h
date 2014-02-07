/*Created by KASHYAP PATEL
FINAL PROJECT FOR PROGRAMMING FINANCE
Submission Date:12/06/2013*/
#ifndef ll_stock_kashyap_h
#define ll_stock_kashyap_h

#include<iostream>
#include<string>
#include"finalproject_kashyap.h"

using namespace std;

class Node
{
	friend class StockAccount;
	friend class LinkedList;
public:
	unsigned long no_share;	//No of Share
	double total_value; //=(Price of one share*No of Shares)
	string name_share;	//Symbol of Share
	Node* next;
	Node(string name, unsigned long no,double share_price)
	{
		name_share = name;
		no_share = no;
		total_value = share_price*no; 
		next = NULL;
	}
};

class LinkedList
{
	friend class Account;
	friend class StockAccount;
public:
	Node* head;
	LinkedList()
	{
		head = NULL;
	}
	void insert_share_sorted(Node**, Node*); //EXTRA CREDIT
	void delete_share(string);
};
#endif