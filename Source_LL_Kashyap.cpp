/*Created by KASHYAP PATEL
FINAL PROJECT FOR PROGRAMMING FINANCE
Submission Date:12/06/2013*/
#include"ll_stock_kashyap.h"

void LinkedList::insert_share_sorted(Node** head_ref, Node* new_node) //SORTED INSERT
{
	Node** current_ref = head_ref; //current_ref is pointer to pointer head
	double check_new,check_old; //check_new is the total value of new node;check_old is total value of old node
	check_new = new_node->total_value; //Obtaining TOTAL_VALUE for sorting
	if (*current_ref != NULL)
	{ 
		check_old = (*current_ref)->total_value;  //Obtaining TOTAL_VALUE for sorting
		while ((*current_ref!=NULL) && (check_new<check_old)) //IF head is not empty or new node is lower than older one, move to next 
		{
			current_ref = &((*current_ref)->next);  //Incrementing Double pointer
			if (*current_ref != NULL)  //If LL is empty
			{
				check_old = (*current_ref)->total_value;
			}
		}
	}
	new_node->next = *current_ref;  //Found the match , add the node before the current_ref
	*current_ref = new_node;
}

void LinkedList::delete_share(string name)  //Sell share
{
	Node* temp;   //Two dummy pointers to traverse through the ll
	Node* trail = NULL;
	temp = head;
	while (temp != NULL)
	{
		if ((temp->name_share == name) && (temp == head)) //Special case when first node is to be deleted
		{
			trail = temp;
			head = head->next;
			temp = temp->next;
			delete trail;
		}
		else if (temp->name_share == name)  //Any node other than first is to be deleted
		{
			trail->next = temp->next;
			trail = temp;
			temp = temp->next;
			delete trail;
		}
		else  //if no match advance
		{
			trail = temp;
			temp = temp->next;
		}
	}
}