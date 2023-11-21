#include <iostream>

class costumer
{
	static int max_costumer_capacity;
	static int current_size;
	static int costumer_id;
public:
	int id;
	int age;
	bool priority;
	costumer* next = nullptr;

	costumer(int _age)
	{
		costumer_id++;
		id = costumer_id;
		age = _age;
		priority = (_age >= 65);
		current_size++;
		std::cout << "ENQUEUE_FUNCTION : id=" << this->id << " age=" << this->age << " priority(" << this->priority << ")(capacity=" << costumer::get_size() << "/" << costumer::get_capacity() << ")\n";
	}
	~costumer()
	{
		current_size--;
		std::cout << "DEQUEUE_FUNCTION : id=" << this->id << " age=" << this->age << " priority(" << this->priority << ")(capacity=" << costumer::get_size() << "/" << costumer::get_capacity() << ")\n";
	}
	static int get_capacity()
	{
		return max_costumer_capacity;
	}
	static int get_size()
	{
		return current_size;
	}
	static void set_capacity(int _capacity)
	{
		max_costumer_capacity = _capacity;
	}
};

int costumer::max_costumer_capacity = 20;
int costumer::current_size = 0;
int costumer::costumer_id = 0;

costumer* head_address = nullptr;
costumer* tail_address = nullptr;
costumer* privileged_head_address = nullptr;
costumer* privileged_tail_address = nullptr;

bool isEmpty()
{
	return costumer::get_size() == 0;
}
bool isFull()
{
	return costumer::get_size() == costumer::get_capacity();
}

void enqueue(int _age) // Adding to queue
{
	if (isFull())
	{
		std::cout << "ENQUEUE_FUNCTION : Full capacity(" << costumer::get_size() << "/" << costumer::get_capacity() << ")\n";
		return;
	}
	costumer* person = new costumer(_age);

	if (person->priority) // if this person is privileged person
	{
		if (privileged_head_address == nullptr)
		{
			privileged_head_address = person;
			privileged_tail_address = person;
		}
		else
		{
			privileged_tail_address->next = person;
			privileged_tail_address = person;
			if (head_address != nullptr)
			{
				privileged_tail_address->next = head_address;
			}
			else
			{
				privileged_tail_address->next = nullptr;
			}
		}
	}
	else // if this person is non-privileged person.
	{
		if (head_address == nullptr)
		{
			head_address = person;
			tail_address = person;
		}
		else
		{
			tail_address->next = person;
			tail_address = person;
			person->next = nullptr;
		}
	}
}

void dequeue()
{
	if (isEmpty())
	{
		std::cout << "No costumer!\n";
		return;
	}
	costumer* delete_person;
	costumer* next_person;

	if (privileged_head_address != nullptr)
	{
		delete_person = privileged_head_address;

		if (privileged_head_address == privileged_tail_address)
		{
			delete delete_person;
			privileged_head_address = nullptr;
			privileged_tail_address = nullptr;
		}
		else
		{
			next_person = privileged_head_address->next;
			delete delete_person;
			privileged_head_address = next_person;
		}

	}
	else
	{
		delete_person = head_address;
		if (head_address == tail_address)
		{
			delete delete_person;
			head_address = nullptr;
			tail_address = nullptr;
		}
		else
		{
			next_person = head_address->next;
			delete delete_person;
			head_address = next_person;
		}
	}
}

void show_queue()
{
	costumer* traveler = privileged_head_address;
	if (privileged_head_address == nullptr)
	{
		traveler = head_address;
	}

	while (traveler != nullptr)
	{
		std::cout << "SHOW_QUEUE_FUNCTION : id=" << traveler->id << " age=" << traveler->age << " priority(" << traveler->priority << ")\n";
		traveler = traveler->next;
	}
}

int main()
{
	int ages[] = { 22,34,56,46,27,89,90,72,23,54,32,67,45,86,78,68,78,29 };
	for (int age : ages)
	{
		enqueue(age);
	}
	show_queue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	show_queue();
	return 0;
}