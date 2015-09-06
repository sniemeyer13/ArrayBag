//Sarah Niemeyer
//100027519
//Homework 2
//Matt Sainz

#include <vector>
#include <cstddef>

// Constructor; creates and initializes an empty Bag of "capacity" size
template <class ItemType>
ArrayBag<ItemType>::ArrayBag(int capacity): numberOfItems(0)
{
	itemArray = new ItemType[myCapacity];
}

// Copy constructor; creates and initializes Bag from another Bag
template <class ItemType>
ArrayBag<ItemType>::ArrayBag(const ArrayBag& anotherBag)
{
	//update numberOfItems to be anotherBag's numberOfItems
	numberOfItems = anotherBag.getCurrentSize();
	myCapacity = anotherBag.getCapacity();
	itemArray = new ItemType[myCapacity];
	//loop to copy each item from items to new_items
	for(int k = 0; k < numberOfItems; ++k)
		itemArray[k] = anotherBag.itemArray[k];
}

//destructor
template <class ItemType>
ArrayBag<ItemType>::~ArrayBag()
{
	delete [] itemArray;
	//this is the destructor (because of the ~) 
}

// Assignment operator
//this one modifies one bag and leaves its copy the same
template <class ItemType>
ArrayBag<ItemType>& ArrayBag<ItemType>::operator=(const ArrayBag<ItemType>& anotherBag)
{
	//**check if we're self assigning using the address at this; if we are,
	//return *this
	if(&anotherBag == this)
		return *this; 
	else
	{	
		//if we're not self assigning, delete our existing itmes array
		delete [] itemArray;
		//set myCapacity and numberOfItems
		numberOfItems = anotherBag.getCurrentSize();
		myCapacity = anotherBag.getCapacity();
		//make a new items array with the capacity of anotherBag
		itemArray = new ItemType[myCapacity];
		//copy the items over for anotherBag to the new items array
		for(int k = 0; k < numberOfItems; ++k)
			itemArray[k] = anotherBag.itemArray[k];
		//return the pointer
		//technicall could have called the copy constructor here.......
		return *this;
	}
}

// Return the number of Items being stored in the Bag
template <class ItemType>
int ArrayBag<ItemType>::getCurrentSize() const
{
	return numberOfItems;		
}

// Return the capacity of the bag (the maximum Items it can store) 
template <class ItemType>
int ArrayBag<ItemType>::getCapacity( ) const
{
	return myCapacity;
}

//Resizes the bag's capacity to newCapacity
//if the new size is larger, copy all bag contents
// we don't downsize a bag in HW2
template <class ItemType> 
void ArrayBag<ItemType>::resize(int newCapacity)
{
	if (newCapacity > myCapacity)
	{	
		ItemType* oldArray = itemArray;
		//store everything that was in itemArray and call it oldArray
		itemArray = new ItemType[newCapacity];
		//make a new array called itemArray (don't worry, we've already saved it)
		for(int index = 0; index < myCapacity; index++)
		//copy the old array into the new array
			itemArray[index] = oldArray[index];
			//delete the old array as to not leak memory
		delete [] oldArray;
		//double the capacity
		myCapacity = newCapacity;
	}
}

template <class ItemType>
bool ArrayBag<ItemType>::isEmpty() const
{
	return numberOfItems == 0;
}

template <class ItemType>
bool ArrayBag<ItemType>::isFull() const
{
	return numberOfItems == myCapacity;	
}

// Give the Bag a new Item to store
// If Bag is full, double capacity and add newItem
// Else, Bag must add this Item to its Item array and update its numberOfItems
// If Bag is full after this, return true; else return false
template <class ItemType>
bool ArrayBag<ItemType>::add(const ItemType& newItem)
{
	bool hasRoomToAdd = (numberOfItems < myCapacity);
	if(!hasRoomToAdd)
	{
		resize(myCapacity*2);
	}
	itemArray[numberOfItems] = newItem;
	numberOfItems++;
	return true;
}

// Make the Bag act like an empty Bag again
template <class ItemType>
void ArrayBag<ItemType>::clear()
{
	numberOfItems = 0; 
}

// Remove an Item from the bag
// If Item is not there, nothing changes and we return false
// Else, we fill in its spot in that Item array and count number of Items down
template <class ItemType>
bool ArrayBag<ItemType>::remove(const ItemType& anItem)
{
	bool found = false;
	int curIndex = 0;
	while(!found && (curIndex < numberOfItems))
	{
		if(anItem == itemArray[curIndex])
		{
			found = true;
			itemArray[curIndex] = itemArray[numberOfItems-1];
			numberOfItems--;
		}
		curIndex++;
	}
	return found;	
}

// Check if an Item is in the Bag
// Return true if it is in the Bag, and false if not
template <class ItemType>
bool ArrayBag<ItemType>::contains(const ItemType& anItem) const
{
	bool found = false;
	int curIndex = 0;
	while(!found && (curIndex < numberOfItems))
	{
		if(anItem == itemArray[curIndex])
		{
			found = true;
		}
		curIndex++;
	}
	return found;
}

// Check how many times an Item is in the Bag
// return 0 if it's not there; otherwise,
// return the number of times it occurs
template <class ItemType>
int ArrayBag<ItemType>::getFrequencyOf(const ItemType& anItem) const
{
	int frequency = 0;
	int curIndex = 0;
	while(curIndex < numberOfItems)
	{
		if (itemArray[curIndex] == anItem)
		{
			frequency++;
		}
		curIndex++;
	}
	return frequency;
}

// Make an output vector of Items from the bag (for checking)
template <class ItemType>
vector<ItemType> ArrayBag<ItemType>::toVector() const
{
	vector<ItemType> bagContents;
	cout << numberOfItems << endl;
	for(int i = 0; i < numberOfItems; i++)
		bagContents.push_back(itemArray[i]);
	return bagContents;				
}

//valgrind!!!!!!!!!!!!
