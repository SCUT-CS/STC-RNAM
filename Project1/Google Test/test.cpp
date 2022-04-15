#include "pch.h"
#include "../Project1/Tree.h"
#include "../Project1/Tree.cpp"
namespace test 
{
	/** Test tree create and add node
	  * @author CuiYuxin */
	TEST(TestTree, TestCase1) {
		Tree t;
		EXPECT_NE(t.getRoot(), nullptr);
		treeIterator it(t.getRoot());
		Tree::addchild(it, nw);
		Tree::addchild(it, ne);
	}
	/** Test treeIterator create and move
      * @author CuiYuxin */
	TEST(TestTree, TestCase2) {
		Tree t;
		EXPECT_NE(t.getRoot(), nullptr);
		treeIterator it(t.getRoot());
		EXPECT_NE(*it, nullptr);
		Tree::addchild(it, nw);
		Tree::addchild(it, ne);		
		EXPECT_TRUE(it.toNwChild());
		EXPECT_TRUE(it.toNeChild());
		EXPECT_FALSE(it.toParent());
		EXPECT_EQ(*it, nullptr);
		treeIterator p(t);
		EXPECT_NE(*p, nullptr);
		EXPECT_NE(*p, *it);
	}
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}