#include "Tree.h"

/** Initialize Tree
  * @author CuiYuxin */
Tree::Tree()
{
	root = new treeNode; //建立根结点
	InitialNode(root);
}

/** Delete Tree
  * @author CuiYuxin */
Tree::~Tree()
{
	if (root!=nullptr)
	{
		deleteTree(root);
	}
}

/** Initialize the node
  * @author CuiYuxin 
  * @param treeNode*& node */
void Tree::InitialNode(treeNode*& node)
{
	node->parent = nullptr;
	node->nwchild = nullptr;
	node->nechild = nullptr;
	node->confirm = '0';
}

/** Level traverse the tree
  * @author CuiYuxin
  * @param vector<char>& res
  * @param treeNode*& root */
void Tree::LevelOrder(vector<char>& res, treeNode* root)
{
	res.push_back(root->confirm);
	if (root->nwchild != nullptr)
	{
		LevelOrder(res, root->nwchild);
	}
	if (root->nechild != nullptr)
	{
		LevelOrder(res, root->nechild);
	}
}

/** Delete Tree
  * @author CuiYuxin
  * @param treeNode* root */
void Tree::deleteTree(treeNode* root)
{
	treeNode* right = root->nechild;
	treeNode* left = root->nwchild;
	delete root;
	if (right!=nullptr)
	{
		deleteTree(right);
	}
	if (left!=nullptr)
	{
		deleteTree(left);
	}
}

/** Return the root
  * @author CuiYuxin
  * @return treeNode* root */
treeNode* Tree::getRoot()
{
	return root;
}

/** Insert a child
  * @author CuiYuxin
  * @param treeIterator it
  * @param Direction dir */
void Tree::addchild(treeIterator it, Direction dir)
{
	if (dir == Direction::nw)
	{
		it->nwchild = new treeNode;
		InitialNode(it->nwchild);
		it->nwchild->parent = *it;
	}
	else if (dir == Direction::ne)
	{
		it->nechild = new treeNode;
		InitialNode(it->nechild);
		it->nechild->parent = *it;
	}
}

///** Insert the node
//  * @author CuiYuxin
//  * @param treeNode*& root */
//void Tree::InsertNode(treeNode*& root)
//{
//	root->nwchild = new treeNode; 
//	InitialNode(root->nwchild); 
//	root->nwchild->parent = root;
//	root->nechild = new treeNode; 
//	InitialNode(root->nechild); 
//	root->nechild->parent = root;
//}

/** Return the treeNode address
  * @author CuiYuxin
  * @return treeNode* p */
treeNode* treeIterator::operator->()
{
	return p;
}

/** Return the treeNode address
  * @author CuiYuxin
  * @return treeNode* p */
treeNode* treeIterator::operator*()
{
	return p;
}

/** Move the iterator to the nwchild, return if the move is successful
  * @author CuiYuxin
  * @return bool */
bool treeIterator::toNwChild()
{
	if (p != nullptr)
	{
		p = p->nwchild;
		return true;
	}
	return false;
}

/** Move the iterator to the nechild, return if the move is successful
  * @author CuiYuxin
  * @return bool */
bool treeIterator::toNeChild()
{
	if (p != nullptr)
	{
		p = p->nechild;
		return true;
	}
	return false;
}

/** Move the iterator to the parent, return if the move is successful
  * @author CuiYuxin
  * @return bool */
bool treeIterator::toParent()
{
	if (p != nullptr)
	{
		p = p->parent;
		return true;
	}	
	return false;
}
