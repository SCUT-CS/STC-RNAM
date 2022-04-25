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
	if (root != nullptr)
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
  * @param treeIterator it */
void Tree::LevelOrder(vector<char>& res, treeIterator it)
{
	res.push_back(getConfirm(it));
	treeIterator nwIt{ it }, neIt{ it };
	if (nwIt.toNeChild())
	{
		LevelOrder(res, nwIt);
	}
	if (neIt.toNeChild())
	{
		LevelOrder(res, neIt);
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
void Tree::addchild(treeIterator it,Direction dir)
{
	if (*it == nullptr)
	{
		return;
	}
	if (dir == Direction::nw)
	{
		if (it->nwchild != nullptr) //防止内存泄漏
		{
			delete it->nwchild;
		}
		it->nwchild = new treeNode;
		InitialNode(it->nwchild);
		it->nwchild->parent = *it;
	}
	else if (dir == Direction::ne)
	{
		if (it->nechild != nullptr)
		{
			delete it->nechild;
		}
		it->nechild = new treeNode;
		InitialNode(it->nechild);
		it->nechild->parent = *it;
	}
}

/** Set confirm
  * @author CuiYuxin
  * @param treeIterator it
  * @param uchar c */
void Tree::setConfirm(treeIterator it, uchar c)
{
	if (*it != nullptr)
	{
		it->confirm = c;
	}
}

/** Get confirm
  * @author CuiYuxin
  * @param treeIterator it */
uchar Tree::getConfirm(treeIterator it)
{
	if (it.p!=nullptr)
	{
		return (*it)->confirm;
	}
}

/** Set child confirm
  * @author CuiYuxin
  * @param treeIterator it
  * @param uchar c
  * @param Direction dir */
void Tree::setChildConfirm(treeIterator it, uchar c, Direction dir)
{
	if (*it == nullptr)
	{
		return;
	}
	if (dir == Direction::nw)
	{
		it.toNwChild();
		if (*it == nullptr)
		{
			return;
		}
		it->confirm = c;
	}
	else if (dir == Direction::ne)
	{
		it.toNeChild();
		if (*it == nullptr)
		{
			return;
		}
		it->confirm = c;
	}
}

/** Delete child node
  * @author CuiYuxin
  * @param treeIterator it
  * @param Direction dir */
void Tree::deleteChildNode(treeIterator it, Direction dir)
{
	if (*it == nullptr)
	{
		return;
	}
	if (dir == Direction::nw)
	{
		auto temp = it.getNwChild();
		if (*temp == nullptr)
		{
			return;
		}
		delete (*temp);
		it.p->nwchild = nullptr;
	}
	else if (dir == Direction::ne)
	{
		auto temp = it.getNeChild();
		if (*temp == nullptr)
		{
			return;
		}
		delete (*temp);
		it.p->nechild = nullptr;
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
	if (p != nullptr&& p->nwchild!=nullptr)
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
	if (p != nullptr&& p->nechild!=nullptr)
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
	if (p != nullptr&& p->parent!=nullptr)
	{
		p = p->parent;
		return true;
	}	
	return false;
}

/** Return the iterator point to the NwChild
  * @author CuiYuxin
  * @return treeIterator */
treeIterator treeIterator::getNwChild() const
{
	treeIterator temp = *this;
	if (temp.toNwChild()) 
	{
		return temp;
	}
	return treeIterator(nullptr);
}

/** Return the iterator point to the NwChild
  * @author CuiYuxin
  * @return treeIterator */
treeIterator treeIterator::getNeChild() const
{
	treeIterator temp = *this;
	if(temp.toNeChild())
	{
		return temp;
	}
	return treeIterator(nullptr);
}

/** Return the iterator point to the NwChild
  * @author CuiYuxin
  * @return treeIterator */
treeIterator treeIterator::getParent() const
{
	treeIterator temp = *this;
	if(temp.toParent())
	{
		return temp;
	}
	return treeIterator(nullptr);
}
