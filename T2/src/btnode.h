#ifndef BTNODE_H
#define BTNODE_H

template <class keyType> class BTreeNode
{
	int nextNode;
	int recAddress;
	int minKeys;
	int maxKeys;
	int maxBKeys;
	int init();
	void clear();
	friend class BTree<keyType>;
public:
	BTreeNode(int, int);
	~BTreeNode();
	enum states;
	int sucess
};

#endif /* end of include guard: BTNODE_H */
