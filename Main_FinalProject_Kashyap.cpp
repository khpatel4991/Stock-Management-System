/*Created by KASHYAP PATEL
FINAL PROJECT FOR PROGRAMMING FINANCE
Submission Date:12/06/2013*/

#include"finalproject_kashyap.h"

int main()
{
	unsigned short loop;
	Account* ptr = new Account;
	ptr->read_current_balance_at_start();
	//ptr->current_balance = initial_balance; //Initial balance
	LinkedList* ll_ptr = new LinkedList; //For storing all the shares
	do
	{
		loop = ptr->get_instruction();
		ptr->do_instruction(loop,ll_ptr);
	} while (loop != 3);
}