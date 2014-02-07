/*Created by KASHYAP PATEL
FINAL PROJECT FOR PROGRAMMING FINANCE
Submission Date:12/06/2013*/
#include"finalproject_kashyap.h"
#include"ll_stock_kashyap.h"

float StockAccount::get_price(string symbol)
{
	srand(time(NULL));
	int random; //For randomness in file selection
	random = rand() % 100 + 1;
	ifstream fin;
	if (random % 2)
	{
		fin.open("Result1.dat", ios::binary);
	}
	else
	{
		fin.open("Result2.dat", ios::binary);
	}
	if (fin.fail())	//For chcking if file is properly linked with the obj or not
	{
		cerr << "Error Opening File" << endl;
		exit(1);
	}
	string name, date; //Symbol obtained from file
	float price; //Store th price of desired stock from file
	while (fin)	//Till the the file ends
	{
		getline(fin, name, '\t');
		fin >> price; //Obtain price
		getline(fin, date, '\n');
		if (name == symbol)	//If match is founD
		{
			fin.close();
			return price;	//Will return TRUE if element is found
		}
	}
	fin.close();
	return 0;			//Will return FALSE if element is not found 
}

unsigned long StockAccount::get_total_transaction()
{
	ifstream fin;
	fin.open("stock_transaction_history.dat", ios::in | ios::binary);
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
		return 0;
	}
	else
	{
		fin.seekg(0, ios::beg);//put the 'cursor' back at the beginning of the file
		unsigned long count = 0;
		while (fin)
		{
			string event_string, symbol, trash, time_info;
			unsigned long no_of_shares;
			float price;
			double total, curr_bal, curr_portfolio_val;
			getline(fin, event_string, '\t');//Gets all the info from file
			if (event_string == "") //If event string is empty, break
			{
				break;
			}
			getline(fin, symbol, '\t'); //Parsing
			fin >> no_of_shares;
			fin >> price;
			fin >> total;
			fin >> curr_bal;
			fin >> curr_portfolio_val;
			getline(fin, time_info, '\n');
			getline(fin, trash);
			count++;
		}
		fin.close();
		return count;
	}
}

Node* StockAccount::search_same_stock(string symbol, LinkedList* ll_ptr)
{
	unsigned short noofshares_dummy = no_of_shares; //Will go through the existing linked list to check if same share is there or not
	Node* temp = ll_ptr->head;
	while (noofshares_dummy) //noofshare_dummy is for going through all the share nodes(For all future reference too)
	{
		if (symbol == temp->name_share) //If share is found, return pointer to that node
		{
			return temp;
		}
		temp = temp->next;
		noofshares_dummy--;
	}
	return NULL; //if not found return NULL
}

void StockAccount::update_stock_list(LinkedList* ll_ptr)  //Will re-write the file
{
	ofstream fout; //ofstream object fout associated with 'stock_transaction_hisory.dat'
	fout.open("stock_list.dat",ios::out|ios::binary);
	if (fout.fail())	//For chcking if file is properly linked with the obj or not
	{
		cerr << "Error Opening File" << endl;
		exit(1);
	}
	fout << no_of_shares << " is total number of different shares you have.\n";
	unsigned short noofshare_dummy = no_of_shares;
	//fout << current_balance << " is the current balance.\n";
	Node* temp;	 //Temp to traverse through the linkedlist
	temp = ll_ptr->head;
	while (noofshare_dummy)
	{
		float price = (temp->total_value) / (temp->no_share); //Will evaluate the price of one share
		string print_event;
		fout << temp->name_share << "\t" << temp->no_share << "\t" << price << "\t" << temp->total_value << "\n"; //Prints the node details
		temp = temp->next;
		noofshare_dummy--;
	}
	fout.close(); //Closing and de-associating
}

void StockAccount::update_stock_transaction(bool buy_or_sell,string name,float price_per_share,unsigned long no_of_shares,LinkedList* ll_ptr) //Modifies
{
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	//timeinfo = localtime(&rawtime);
	fstream fout;
	fout.open("stock_transaction_history.dat", ios::binary | ios::app | ios::out);
	string event_print;
	if (buy_or_sell) //==TRUE i.e BUY transaction
	{
		event_print = "BUY\t";
	}
	else
	{
		event_print = "SELL\t";
	}
	fout.seekg(0, ios::end); // put the "cursor" at the end of the file
	fout << event_print << name << "\t" << no_of_shares << "\t" << price_per_share << "\t" << (no_of_shares*price_per_share) << "\t" << current_balance << "\t" << total_stocks_value(ll_ptr) << "\t" << rawtime << "\n"; //Prints the transaction details
}

double StockAccount::total_stocks_value(LinkedList* ll_ptr)
{
	Node* temp = ll_ptr->head;  //Same as in the function 'get_price
	unsigned short noofshare_dummy = no_of_shares;
	if (!noofshare_dummy) //If no of share=0
	{
		std::cout << endl << endl << "No trasactions made" << endl;
	}
	double total_stock_value = 0;  //Will hold the total_stock value
	while (noofshare_dummy)
	{
		//Obtains the value from LINKEDLIST
		float price = get_price(temp->name_share);
		total_stock_value += (temp->no_share*price);
		temp = temp->next;
		noofshare_dummy--;
	}
	return total_stock_value;
}

double StockAccount::update_linkedlist_at_start(LinkedList* ll_ptr,bool check) //Update linkedlist when program is run first time or coming from main menu again
{
	ifstream fin;
	fin.open("stock_list.dat",ios::binary);
	int length;
	fin.seekg(0, ios::end); // put the "cursor" at the end of the file
	length = fin.tellg(); // find the position of the cursor
	if (length == 0)
	{
		fin.close();
	}
	else
	{
		fin.seekg(0, ios::beg); //put the cursor back at beginning
		string trash; //For garbage values which are not needed
		unsigned short num;
		fin >> num; //NO of diff. shares
		no_of_shares = num;
		getline(fin, trash, '\n');
		while (num)
		{
			string name;  //Vars for parsing as per the name
			long no;
			float price;
			double total_value;
			getline(fin, name, '\t');
			fin >> no;  //Getting all the values from file
			fin >> price;
			fin >> total_value;
			getline(fin, trash, '\n');
			num--;  //decrement num for proper loop functionality
			if (!check) 
			{
				/*check is static bool, 
				so when program starts it's false,
				any other time when coming from main menu is true,
				so Linkedlist is already present, and it won't be tampered with*/
				Node* new_node = new Node(name, no, price);
				ll_ptr->insert_share_sorted(&(ll_ptr->head), new_node);
			}
		}
		fin.close();
		return current_balance;
	}
}

void StockAccount::get_graph()
{
#define max 999
	bool history = true;
	int i = 0;
	unsigned long nooftransaction_dummy = get_total_transaction();
	//vector<string> time_stamp;
	//vector<double> a;
	double money[max];
	double time_stamp[max];
	ifstream fin;
	fin.open("stock_transaction_history.dat", ios::in | ios::binary);
	if (fin.fail())	//For checking if file is properly linked with the obj or not
	{
		cerr << "Error Opening File" << endl;
		exit(1);
	}
	int length;
	fin.seekg(0, ios::end); // put the "cursor" at the end of the file
	length = fin.tellg(); // find the position of the cursor
	double curr_portfolio_val;
	if (length == 0) //If starting for forst time
	{
		cout << endl << "No Transactions Made. So your current balance is $" << current_balance;
		history = false;
		fin.close();
	}
	else
	{
		fin.seekg(0, ios::beg);//put the 'cursor' back at the beginning of the file
		unsigned long count = 0;
		while (fin)
		{
			string event_string, symbol, trash;
			unsigned long no_of_shares;
			float price;
			double temp_time, total, curr_bal;
			getline(fin, event_string, '\t');//Gets all the info from file
			if (event_string == "") //If event string is empty, break
			{
				break;
			}
			getline(fin, symbol, '\t'); //Parsing
			fin >> no_of_shares;
			fin >> price;
			fin >> total;
			fin >> curr_bal;
			fin >> curr_portfolio_val;
			fin >> temp_time;
			getline(fin, trash, '\n');
			temp_time = (temp_time / 86400) + 719529 - (5.5 / 24) + (0.5 / 24);
			time_stamp[i] = temp_time;
			money[i] = curr_bal + curr_portfolio_val;
			i++;
		}
		money[i] = current_balance + curr_portfolio_val; //For the value when graph function is called
		time_t rawtime; //Timeinfo
		struct tm * timeinfo;
		char buffer[80];
		time(&rawtime);
		double te = (double)rawtime; //converting rawtime into double
		double temp;
		temp = (te / 86400) + 719529 - (5.5 / 24) + (0.5 / 24); //converting into EST readable by MATLAB
		time_stamp[i] = double(temp);
		i++;
	}
	if (history != false)
	{
		Engine* ep = engOpen(NULL); //Start matlab
		if (ep == NULL)//check for error
		{
			cout << "Error: Not Found" << endl;
			exit(1);
		}
		mxArray* m_array = mxCreateDoubleMatrix(1, i, mxREAL); //two mx array for money and time
		mxArray* t_array = mxCreateDoubleMatrix(1, i, mxREAL);
		memmove((void*)mxGetPr(m_array), (void*)money, sizeof(double)*(i)); //move data from c++ array to mxarray
		memmove((void*)mxGetPr(t_array), (void*)time_stamp, sizeof(double)*(i));
		engPutVariable(ep, "amount", m_array);//alias name
		engPutVariable(ep, "time_ref", t_array);
		engEvalString(ep, "startDate = datenum(time_ref(1));"); //for xtick labels
		engEvalString(ep, "endDate = datenum(time_ref(numel(time_ref)));");
		engEvalString(ep, "xData = linspace(startDate,endDate,5);");
		engEvalString(ep, "plot(time_ref,amount),title('Your Money');"); //plot
		engEvalString(ep, "set(gca,'XTick',xData)"); //ticklabels
		engEvalString(ep, "datetick('x','mm/dd HH:MM:SS','keepticks')");
		engEvalString(ep, "ylim(auto);");
	}
}

unsigned short StockAccount::get_instruction()  
{
	unsigned short stock_op;
	std::cout << endl << "Stock Portfolio Account" << endl;
	std::cout << "Please select an option:" << endl;
	std::cout << "1. Display the price for a stock symbol" << endl;
	std::cout << "2. Display the current portfolio" << endl;
	std::cout << "3. Buy shares" << endl;
	std::cout << "4. Sell shares" << endl;
	std::cout << "5. View a graph for the portfolio value" << endl;
	std::cout << "6. View transaction history" << endl;
	std::cout << "7. Return to previous menu" << endl;
	std::cout << "Option:";
	std::cin >> stock_op;
	return stock_op;	// Returns the operation user wants to perform
}

void StockAccount::do_instruction(unsigned short stock_op,LinkedList* ll_ptr)
{
	//static bool buy_or_sell;  //TRUE=BUY ; FALSE=SELL
	switch (stock_op)
	{
	case 1:		//Display price of a stock
	{
					float price;  //For Checking if entry was found or not
					string symbol;	//Symbol entered by user
					std::cout << endl << "Enter the Stock Symbol: ";
					std::cin >> symbol; //Gets the symbol entered by user
					price = get_price(symbol);
					if (price)	//Found and price is returned
					{
						std::cout << endl << "Company Symbol price per share" << endl;
						std::cout << symbol << "\t" << price << endl;	//Show the result to user
					}
					else //If no entry found price will be zero
					{
						std::cout << endl << "No such stock entry found" << endl;
					}
					break;
	}
	case 2: //Display the current Portfolio
	{
				Node* temp = ll_ptr->head;  //Same as in the function 'get_price
				unsigned short noofshare_dummy = no_of_shares;
				if (!noofshare_dummy) //If no of share=0
				{
					std::cout << endl << endl << "No trasactions made" << endl;
				}
				double total_stock_value = 0;
				while (noofshare_dummy)
				{
					//Prints the value from LINKEDLIST
					float price = get_price(temp->name_share);
					std::cout << temp->name_share << "\t" << temp->no_share << "\t" << price << "\t" << (temp->no_share*price) << endl;
					total_stock_value += (temp->no_share*price);
					temp = temp->next;
					noofshare_dummy--;
				}
				std::cout << endl << "Total Portfolio Value: $" << total_stock_value << endl;
				std::cout << "Bank Balance: $" << current_balance << endl;
				break;
	}
	case 3:  //Buy Shares
	{
				 string symbol;  //Symbol will contain the name of the share user wants to buy
				 float price;
				 std::cout << endl << "Enter the symbol of the share you want to buy: ";
				 std::cin >> symbol; //Get symbol of share
				 price = get_price(symbol); //Get it's price
				 if (price) //If stock found price will be non-zero hence true
				 {
					 //Found and further
					 if (current_balance > price) //Current bal less than price of one share
					 {
						 //Enough Balance and further
						 unsigned long no;  //For getting the no of shares users wants
						 std::cout << endl << "Enter the number of shares you want to buy: ";
						 std::cin >> no;
						 if (current_balance > (no*price))
						 {
							 //Balance enough to buy no of shares entered and further
							 float temp_price;
							 std::cout << endl << "Enter the maximum amount you'd pay for this share: $";
							 std::cin >> temp_price;
							 if (temp_price > price)// IF expected price of share is less than real price
							 {
								 //BUYS SHARES..All conditions met
								 bool transaction = true;
								 Node* old_share = search_same_stock(symbol, ll_ptr); //old_share will have no. of share previously present in the list
								 if (old_share == NULL)  //If no such share is found, add a node
								 {
									 Node* add_share = new Node(symbol, no, price);
									 ll_ptr->insert_share_sorted(&(ll_ptr->head), add_share); //Reference to head is sent so as we can modify the LL directly including the head
									 no_of_shares++;
								 }
								 else  //Old share found, Just increment no of shares
								 {
									 //old_share->total_value += (no*price);
									 //old_share->no_share += no;
									 unsigned long temp_no_share = old_share->no_share; //Retrieve no of share user previously had e.g user has 6 GOOG shares.so 6 is obtained
									 double temp_total = old_share->total_value;
									 float price_modified = (temp_total + no*price) / (temp_no_share + no); //Weighted Mean, so that new node created has the sum of previous share value and the added one
									 ll_ptr->delete_share(symbol); //Delete previous share e.g delete the share 6 previous share
									 Node* add_share = new Node(symbol, no + temp_no_share, price_modified); // Add Combined value share e.g add 6+new shares of GOOG user wants
									 ll_ptr->insert_share_sorted(&(ll_ptr->head), add_share);
									 //Deleting and creating the same node because I have to keep the linkedlist sorted
									 std::cout << endl << no << " shares added to the previously present stock" << endl;
								 }
								 //total_stock_value += (no*price); //Update curr bal and portfolio value
								 current_balance -= (no*price);
								 update_current_balance();
								 update_stock_list(ll_ptr);  //Will update the transaction history dat file
								 update_stock_transaction(true, symbol, price, no, ll_ptr);
								 std::cout << endl << "The following transaction is successful." << endl;
								 std::cout << "BUY\t" << symbol << "\t" << no << "\t$" << price << "\t$" << no*price << endl;
							 }
							 else
							 {
								 //Price of share is higher than user wanted it to buy at
								 std::cout << endl << "Sorry! The price of share is $" << price << " which is more than you wanted to pay!" << endl;
							 }
						 }
						 else //Current balance less than no of shares inteded for buying
						 {
							 std::cout << endl << "You don't have enough money to buy this many no. of shares!" << endl;
						 }
					 }
					 else
					 {
						 //Current Balance is too low to buy even one share
						 std::cout << endl << "Sorry!But your current balnce is too low to buy even a single " << symbol << " share." << endl;
					 }
				 }
				 else
				 {
					 //NO Task performed as entry is not found
					 std::cout << endl << "No such stock entry found" << endl;
				 }
				 break;
	}
	case 4: //Sell share
	{
				if (no_of_shares)  //Check if there are any share or not
				{
					string symbol;
					std::cout << "Enter the symbol of share you want to sell: ";
					cin >> symbol;
					Node* old_share;
					old_share = search_same_stock(symbol, ll_ptr);
					if (old_share != NULL) //Stock is in the portfolio
					{
						unsigned long no; //No of shares user wants to sell
						std::cout << endl << "How many shares do you want to sell? ";
						cin >> no;
						if (no <= old_share->no_share)//Check if no of shares user want to sell is equal to or less than he acquires 
						{
							float temp_price; //For storing the minimum price at which user want to sell the share
							std::cout << endl << "Enter the minimum amount you'd want to sell this share on? $";
							cin >> temp_price;
							float price = get_price(symbol); //Get the price of the share user wants to sell from result.dat
							if (temp_price < price)
							{
								//Sell Successful
								bool transaction = false;
								if (no < old_share->no_share) //Remove no no of shares
								{
									unsigned long temp_no_share = old_share->no_share; //Retrieve no of share user previously had e.g user has 6 GOOG shares.so 6 is obtained
									ll_ptr->delete_share(symbol); //Delete previous share e.g delete the share 6 previous share
									Node* add_share = new Node(symbol, temp_no_share - no, price); // Add Combined value share e.g add 6+new shares of GOOG user wants
									ll_ptr->insert_share_sorted(&(ll_ptr->head), add_share);
									//Deleting and creating the same node because I have to keep the linkedlist sorted
									std::cout << endl << no << " shares have been sold out of total you had" << endl;
								}
								else //sellshare=old_share->no_share .So delete the entire node
								{
									ll_ptr->delete_share(symbol);
									no_of_shares--;
									std::cout << endl << "All share of " << symbol << " have been sold." << endl;
								}
								//total_stock_value -= (no*price); //Update curr bal and portfolo value
								current_balance += (no*price);
								update_current_balance();
								update_stock_list(ll_ptr);  //Will update the transaction history dat file
								update_stock_transaction(false, symbol, price, no, ll_ptr);
								std::cout << endl << "The following transaction is successful" << endl;
								std::cout << "SELL\t" << symbol << "\t" << no << "\t$" << price << "\t$" << no*price << endl;
							}
							else //Minimum price user wants can't be obtained
							{
								std::cout << endl << "The current price of the share is less than the minimum price you want to sell your shares at!";
								std::cout << "The current price of the share is $" << price << endl;
							}
						}
						else //No of share that user want to sell is higher than he acquires
						{
							std::cout << endl << "No of shares you want to sell is higher than you acquire.";
							std::cout << "You have only " << old_share->no_share << " of " << old_share->name_share << "!" << endl;
						}
					}
					else //Stock not present in your portfolio
					{
						std::cout << endl << "The share you want to sell is not available in your Portfolio." << endl;
					}
				}
				else //Bad symbol
				{
					std::cout << endl << "No stock in the portfolio" << endl;
				}
				break;
	}
	case 5: //View Graph of the portfolio
	{
				get_graph(); //gets graph
				break;
	}
	case 6: //View transaction history
	{
				ifstream fin;
				fin.open("stock_transaction_history.dat", ios::in | ios::binary);
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
						time_t rawtime;
						struct tm * timeinfo;
						char buffer[80];
						string event_string, symbol, trash, time_info;
						unsigned long no_of_shares;
						float price;
						double total, curr_bal, curr_portfolio_val, time_ref;
						getline(fin, event_string, '\t');//Gets all the info from file
						if (event_string == "") //If event string is empty, break
						{
							break;
						}
						getline(fin, symbol, '\t'); //Parsing
						fin >> no_of_shares;
						fin >> price;
						fin >> total;
						fin >> curr_bal;
						fin >> curr_portfolio_val;
						fin >> rawtime;
						timeinfo = localtime(&rawtime);
						strftime(buffer, 80, "%c", timeinfo);
						getline(fin, trash,'\n');
						cout << event_string << "\t" << symbol << "\t" << no_of_shares << "\t" << price << "\t" << total << "\t" << buffer << "\n"; //Prints out the details on screen
					}
					fin.close();
				}
				break;
	}

	case 7:  //Previous Menu
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