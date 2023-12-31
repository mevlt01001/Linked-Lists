#include <iostream>

class Node
{
	public:

	int data;
	Node* pre_address;
	Node* next_address;
};

Node* head_address = nullptr;
Node* tail_address = nullptr;
int numb;
int counter;

void add_link(int node_data)
{
	Node* new_node = new Node();
	new_node->data = node_data;

	if(head_address == nullptr)
	{
		head_address = new_node;
		tail_address = new_node;
		new_node->next_address = nullptr;
		new_node->pre_address = nullptr;
	}
	else
	{
		tail_address->next_address = new_node;
		new_node->pre_address = tail_address;
		tail_address = new_node;
	}
}

void show_link()
{
	Node* shows = head_address;
	if (shows == nullptr)
	{
		std::cout << "(show_link)No link!\n";
	}
	while (shows != nullptr)
	{
		std::cout << "node("<<shows<<") :: data : "<<shows->data<<" | preAddress : "<<shows->pre_address<<" | nextAddress : "<<shows->next_address<<"\n";
		shows = shows->next_address;
	}
	std::cout << "---------------------------------------------------------------------------------------------------\n";
}

void del_link()
{
	Node* destroy = head_address;
	if(destroy == nullptr)
	{
		std::cout << "(del_link)No erasable link!\n";
	}
	while (destroy != nullptr)
	{
		Node* temp = destroy->next_address;
		delete destroy;
		destroy = temp;
	}
	head_address = nullptr;
	tail_address = nullptr;
}

void del_node(Node* that_node)
{
	Node* del_node = that_node;
	Node* pre_del_node = that_node->pre_address;
	if(that_node->next_address == nullptr) // if that node is last node;
	{
		pre_del_node->next_address = nullptr; 
		delete del_node;
	}
	else
	{
		Node* next_del_node = del_node->next_address;
		pre_del_node->next_address = next_del_node;
		next_del_node->pre_address = pre_del_node;
		delete del_node;
	}
}

void relocation(Node* that_point, Node* that_node)
{
	Node* point = that_point;
	Node* node = that_node;
	bool side_by_side = (point->next_address == node); // if its are side by side, this function do nothing.

	if (node->next_address == nullptr && side_by_side == false) // if that node is last node and, point and that node are not side by side;
	{
		Node* pre_node = node->pre_address;
		Node* point_next = point->next_address;

		pre_node->next_address = nullptr;
		point->next_address = node;
		node->next_address = point_next;
		point_next->pre_address = node;
		node->pre_address = point;
	}
	else if(node->next_address != nullptr && side_by_side == false)
	{
		Node* pre_node = node->pre_address;
		Node* next_node = node->next_address;
		Node* point_next = point->next_address;

		pre_node->next_address = next_node;
		next_node->pre_address = pre_node;
		point->next_address = node;
		node->next_address = point_next;
		point_next->pre_address = node;
		node->pre_address = point;
	}
}

void manipulation_link(int that_numb)
{
	Node* point = head_address;
	Node* traveler = point->next_address;
	numb = that_numb;
	counter = 1; // the value of this is 1 because the point already has a that value in point->data.

	while (point->next_address != nullptr)
	{
		if(traveler == nullptr)
		{
			point = point->next_address;
			traveler = point->next_address;
			counter = 1;
		}
		else if(traveler->data == point->data)
		{
			Node* address = traveler->next_address;
			if (counter < numb)
			{
				counter++;
				relocation(point, traveler);
				point = point->next_address;
				traveler = address;
			}
			else
			{
				del_node(traveler);
				traveler = address;
			}
		}
		else
		{
			traveler = traveler->next_address;
		}

	}
}

int main()
{
	int arr[] = { 1, 3, 4, 5, 2, 3, 5, 6, 1, 4, 5, 6, 6, 7, 4, 5 };
	for (int i : arr) add_link(i);
	show_link();
	manipulation_link(2);
	show_link();
	del_link();
	show_link();
	return 0;
}