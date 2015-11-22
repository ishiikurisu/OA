#ifndef BTNODE_H
#define BTNODE_H
#include <vector>

template <class T> class BTreeNode
{
	int next_node;
	int numkeys;
	int recaddress;
	int minkeys;
	int maxkeys;
	int maxbkeys;
	bool singleton;
	std::vector<int> rec_addresses;
	std::vector<T> keys;
	void clear();
	int find(T, int, int);
	friend class BTree<T>;
public:
	BTreeNode(int, bool);
	~BTreeNode() {};
	enum state = {
		failure = -1,
		overflow,
		sucess
	};
	int insert(T, int);
	int remove(T, int);
	int search(T, int);
	std::string print();
	int largest_key();
	int split(BTreeNode<T>*);
	int merge(BTreeNode<T>*);
	int update_key(T, T, int);
};

/********************
* PRIVATE FUNCTIONS *
********************/

template <class T> void BTreeNode<T>::clear()
{
	rec_addresses.clear();
	keys.clear();
}

template <class T> int BTreeNode<T>::find(T key, int rec, int exact)
{
	int i = 0;

	for (i = 0; i < numkeys; ++i)
	{
		if (keys[i] < key)
			continue;
		if (keys[i] == key)
		{
			if (rec < 0)
				return i;
			else if (rec == recAddrs[i])
				return i;
			else
				return state.failure;
		}

		if (!exact)
			return i;
		return state.failure;
	}
	if (exact == 1)
		return state.failure;
	else
		return numkeys-1;
}

/*******************
* PUBLIC FUNCTIONS *
*******************/
template <class T> BTreeNode<T>::BTreeNode(int maxkeys, bool unique)
{
	singleton = unique;
	if (maxkeys <= 0)
	{
		this->maxkeys = 0;
		return;
	}

	this->maxkeys = maxkeys;
	maxbkeys = maxkeys;
	numkeys = 0;
}

template <class T> int BTreeNode<T>::insert(T key, int recaddr)
{
	int i;
	int index = find(key);

	if ((singleton && index >= 0) || (numkeys == maxkeys))
		return state.overflow;

	for (i = numkeys-1; i >= 0; --i)
	{
		if (key > keys[i])
			break;
		keys[i+1] = keys[i];
		rec_addresses[i+1] = rec_addresses[i];
	}

	keys[i+1] = key;
	rec_addresses[i+1] = recaddr;
	++numkeys;
	return state.sucess;
}

template <class T> int BTreeNode<T>::remove(T key, int rec)
{
	int index = find(key, rec), i;
	if (index < 0)

		return state.failure;

	for (i = index; i < numkeys; ++i)
	{
		keys[i] = keys[i+1];
		rec_addresses[i] = rec_addresses[i+1];
	}

	--numkeys;
	return state.sucess;
}

template <class T> int BTreeNode<T>::search(T key, int rec)
{
	int index = find(key, rec, 1);
	return (index < 0)? index : rec_addresses[index];
}

template <class T> std::string BTreeNode<T>::print()
{
	std::string out;
	int i;

	out += "Node:\n";
	for (i = 0; i < numkeys; ++i)
	{
		out += "- key: " + i + " = " + keys[i] + " @ " + rec_addresses[i] + std::endl;
	}

	return out;
}

template <class T> T BTreeNode<T>::largest_key()
{
	if (numkeys > 0)
		return keys[numkeys-1];
	else
		return NULL;
}

#endif /* end of include guard: BTNODE_H */
