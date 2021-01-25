#pragma once



template<typename T>
struct List
{
	List<T>* next;
	T* val;

	List<T>()
	{
		next = nullptr;
		val = nullptr;
	}

	List<T>(T *newItem)
	{
		next = nullptr;
		val = newItem;
	}

	~List<T>()
	{
		next = nullptr;
	}
};


template<typename T>
List<T>* GetLastItemInList(List<T>* head)
{
	List<T>* current = head;
	while(current->next != nullptr)
	{
		current = current->next;
	}
	
	return current;
}

template<typename T>
List<T>* AddNewListItem(List<T> *head, T *Item)
{
	List<T>* newList = new List<T>(Item);
	if (head != nullptr)
	{
		GetLastItemInList(head)->next = newList;
	}
	else
	{
		return newList;
	}
	
	return head;
}


template<typename T>
List<T>* FindItemInList(List<T>* firstNode, T* Item)
{
	List<T>* current = firstNode;
	if(current == nullptr)
	{
		return nullptr;
	}

	if(current->val != Item)
	{
		current = FindItemInList(current->next, Item);
	}
	return current;
}

template<typename T>
List<T>* RemoveItemFromList(List<T>* head, T* Item)
{
	if (head == nullptr)
	{
		return nullptr;
	}
	List<T>* currentNode = head;
	if (currentNode->val != Item)
	{
		List<T>* previousNode = nullptr;
		while (currentNode->next != nullptr)
		{
			previousNode = currentNode;
			currentNode = currentNode->next;
			if (currentNode->val == Item)
			{
				List<T>* nextNode = currentNode->next;
				//delete currentNode->next->val;
				delete currentNode;
				previousNode->next = nextNode;
				return head;
			}
		}

		return head;
		
	}
	else
	{
		List<T>* nextNode = currentNode->next;
		
		currentNode = nextNode;
	}
	
	return currentNode;
}

template<typename T>
bool DeleteList(List<T>* head)
{
	if(head->next != nullptr)
	{
		DeleteList(head->next);
	}
	delete head->val;
	delete head;
	return true;
}

template<typename T>
List<T>* ReverseList(List<T>* head)
{
	List<T>* node = head;
	List<T>* nextNode = node->next;
	List<T>* PreviousNode = nullptr;

	while (nextNode != nullptr)
	{
		node->next = PreviousNode;
		PreviousNode = node;
		node = nextNode;
		nextNode = node->next;
	}

	return node;
}

template<typename T>
T* GetItemAtIndex(List<T>* head, int index)
{
	List<T>* currentNode = head;
	int i = 0;
	while (currentNode != nullptr)
	{
		if (index == i)
		{
			return currentNode->val;
		}

		currentNode = currentNode->next;
		i++;
	}

	return nullptr;
}