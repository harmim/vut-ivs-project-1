//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
// $Date:       $2017-02-18
//============================================================================//

/**
 * @file black_box_tests.cpp
 * @author Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
 * 
 * @brief Implementace testu binarniho stromu.
 */


#include <stdlib.h>
#include <vector>
#include "gtest/gtest.h"
#include "red_black_tree.h"


namespace BlackBoxTesting
{

	using namespace ::testing;


	class TestingTree : public Test
	{

	public:
		int numberOfNodes = 13,
			nodes[13] = {7, 12, 8, 2, 4, 1, 22, 26, 9, 11, 6, 39, 42},
			numberOfLeafNodes = 14,
			leafNodeParents[8] = {1, 2, 6, 7, 9, 12, 26, 42};

	protected:
		BinaryTree tree;

	};


	class EmptyTree : public TestingTree
	{
	};


	class NonEmptyTree : public TestingTree
	{

	protected:

		void SetUp() override
		{
			for (int value : nodes) {
				tree.InsertNode(value);
			}
		}

	};


	TEST_F(EmptyTree, Insert)
	{
		/// vlozeni uzlu s hodnotou 1
		std::pair<bool, BinaryTree::Node_t *> pair1 = tree.InsertNode(1);
		BinaryTree::Node_t *node1 = pair1.second;
		ASSERT_TRUE(node1 != NULL);
		EXPECT_TRUE(pair1.first);

		// overeni stavu uzlu 1
		EXPECT_EQ(node1->key, 1);
		EXPECT_EQ(node1->color, BinaryTree::BLACK);
		EXPECT_FALSE(node1->IsLeaf());
		EXPECT_TRUE(node1->pParent == NULL);

		// overeni stavu leveho potomka uzlu 1
		BinaryTree::Node_t *left1 = node1->pLeft;
		ASSERT_TRUE(left1 != NULL);
		EXPECT_EQ(left1->color, BinaryTree::BLACK);
		EXPECT_TRUE(left1->IsLeaf());
		EXPECT_TRUE(left1->pLeft == NULL);
		EXPECT_TRUE(left1->pRight == NULL);
		EXPECT_TRUE(left1->pParent != NULL);
		EXPECT_EQ(left1->pParent->key, 1);

		// overeni stavu praveho potomka uzlu 1
		BinaryTree::Node_t *right1 = node1->pRight;
		ASSERT_TRUE(right1 != NULL);
		EXPECT_EQ(right1->color, BinaryTree::BLACK);
		EXPECT_TRUE(right1->IsLeaf());
		EXPECT_TRUE(right1->pLeft == NULL);
		EXPECT_TRUE(right1->pRight == NULL);
		EXPECT_TRUE(right1->pParent != NULL);
		EXPECT_EQ(right1->pParent->key, 1);


		/// vlozeni uzlu s hodnotou 2
		std::pair<bool, BinaryTree::Node_t *> pair2 = tree.InsertNode(2);
		BinaryTree::Node_t *node2 = pair2.second;
		ASSERT_TRUE(node2 != NULL);
		EXPECT_TRUE(pair2.first);

		// overeni stavu uzlu 2
		EXPECT_EQ(node2->key, 2);
		EXPECT_EQ(node2->color, BinaryTree::RED);
		EXPECT_FALSE(node2->IsLeaf());
		ASSERT_TRUE(node2->pParent != NULL);
		EXPECT_EQ(node2->pParent->key, 1);

		// overeni stavu leveho potomka uzlu 2
		BinaryTree::Node_t *left2 = node2->pLeft;
		ASSERT_TRUE(left2 != NULL);
		EXPECT_EQ(left2->color, BinaryTree::BLACK);
		EXPECT_TRUE(left2->IsLeaf());
		EXPECT_TRUE(left2->pLeft == NULL);
		EXPECT_TRUE(left2->pRight == NULL);
		EXPECT_TRUE(left2->pParent != NULL);
		EXPECT_EQ(left2->pParent->key, 2);

		// overeni stavu praveho potomka uzlu 2
		BinaryTree::Node_t *right2 = node2->pRight;
		ASSERT_TRUE(right2 != NULL);
		EXPECT_EQ(right2->color, BinaryTree::BLACK);
		EXPECT_TRUE(right2->IsLeaf());
		EXPECT_TRUE(right2->pLeft == NULL);
		EXPECT_TRUE(right2->pRight == NULL);
		EXPECT_TRUE(right2->pParent != NULL);
		EXPECT_EQ(right2->pParent->key, 2);


		/// overeni spravnosti praveho potomka uzlu 1 po vlozeni uzlu 2
		ASSERT_TRUE(node1->pRight != NULL);
		EXPECT_EQ(node1->pRight->key, 2);


		/// vlozeni existujciho uzlu
		std::pair<bool, BinaryTree::Node_t *> existingPair = tree.InsertNode(1);
		BinaryTree::Node_t *existingNode = existingPair.second;
		ASSERT_TRUE(existingNode != NULL);
		EXPECT_FALSE(existingPair.first);

		// overeni stavu vracenoho existujiciho uzlu
		EXPECT_EQ(existingNode->key, 1);


		/// vlozeni uzlu s hodnotou 0
		std::pair<bool, BinaryTree::Node_t *> pair0 = tree.InsertNode(0);
		BinaryTree::Node_t *node0 = pair0.second;
		ASSERT_TRUE(node0 != NULL);
		EXPECT_TRUE(pair0.first);

		// overeni stavu uzlu s hodnotou 0
		EXPECT_EQ(node0->key, 0);
		EXPECT_EQ(node0->color, BinaryTree::RED);
		ASSERT_TRUE(node0->pParent != NULL);
		EXPECT_EQ(node0->pParent->key, 1);


		/// vlozeni uzlu se zapornou hodnotou
		std::pair<bool, BinaryTree::Node_t *> pairNegative = tree.InsertNode(-25);
		BinaryTree::Node_t *nodeNegative = pairNegative.second;
		ASSERT_TRUE(nodeNegative != NULL);
		EXPECT_TRUE(pairNegative.first);

		// overeni stavu uzlu se zapornou hodnotou
		EXPECT_EQ(nodeNegative->key, -25);
		EXPECT_EQ(nodeNegative->color, BinaryTree::RED);
		ASSERT_TRUE(nodeNegative->pParent != NULL);
		EXPECT_EQ(nodeNegative->pParent->key, 0);
	}


	TEST_F(NonEmptyTree, Insert)
	{
		/// vlozeni uzlu s existujici hodnotnou
		std::pair<bool, BinaryTree::Node_t *> existingPair = tree.InsertNode(7);
		BinaryTree::Node_t *existingNode = existingPair.second;
		ASSERT_TRUE(existingNode != NULL);
		EXPECT_FALSE(existingPair.first);

		// overeni stavu existujiciho uzlu
		EXPECT_EQ(existingNode->key, 7);
		EXPECT_EQ(existingNode->color, BinaryTree::BLACK);
		EXPECT_FALSE(existingNode->IsLeaf());

		// overeni stavu rodice existujiciho uzlu
		ASSERT_TRUE(existingNode->pParent != NULL);
		EXPECT_EQ(existingNode->pParent->key, 4);
		EXPECT_EQ(existingNode->pParent->color, BinaryTree::RED);
		EXPECT_FALSE(existingNode->pParent->IsLeaf());

		// overeni stavu leveho potomka existujiciho uzlu
		ASSERT_TRUE(existingNode->pLeft != NULL);
		EXPECT_EQ(existingNode->pLeft->key, 6);
		EXPECT_EQ(existingNode->pLeft->color, BinaryTree::RED);
		EXPECT_FALSE(existingNode->pLeft->IsLeaf());

		// overeni stavu praveho potomka existujiciho uzlu
		ASSERT_TRUE(existingNode->pRight != NULL);
		EXPECT_TRUE(existingNode->pRight->IsLeaf());


		/// vlozeni uzlu s hodnotou 10
		std::pair<bool, BinaryTree::Node_t *> pair10 = tree.InsertNode(10);
		BinaryTree::Node_t *node10 = pair10.second;
		ASSERT_TRUE(node10 != NULL);
		EXPECT_TRUE(pair10.first);

		// overeni stavu uzlu s hodnotou 10
		EXPECT_EQ(node10->color, BinaryTree::RED);
		EXPECT_EQ(node10->key, 10);
		EXPECT_FALSE(node10->IsLeaf());

		// overeni stavu potomku uzlu s hodnotou 10
		ASSERT_TRUE(node10->pLeft != NULL);
		EXPECT_TRUE(node10->pLeft->IsLeaf());
		ASSERT_TRUE(node10->pRight != NULL);
		EXPECT_TRUE(node10->pRight->IsLeaf());

		// overeni stavu rodice uzlu s hodnotou 10
		ASSERT_TRUE(node10->pParent != NULL);
		EXPECT_EQ(node10->pParent->key, 9);
		EXPECT_EQ(node10->pParent->color, BinaryTree::BLACK);
		EXPECT_FALSE(node10->pParent->IsLeaf());
	}


	TEST_F(EmptyTree, Delete)
	{
		for (int value : nodes) {
			EXPECT_FALSE(tree.DeleteNode(value));
		}

		EXPECT_FALSE(tree.DeleteNode(0));
		EXPECT_FALSE(tree.DeleteNode(100));
		EXPECT_FALSE(tree.DeleteNode(-25));
	}


	TEST_F(NonEmptyTree, Delete)
	{
		EXPECT_TRUE(tree.DeleteNode(8));

		for (int value : nodes) {
			if (value == 8) {
				EXPECT_FALSE(tree.DeleteNode(value));
			} else {
				EXPECT_TRUE(tree.DeleteNode(value));
			}
		}

		EXPECT_FALSE(tree.DeleteNode(8));
		EXPECT_FALSE(tree.DeleteNode(0));
		EXPECT_FALSE(tree.DeleteNode(100));
		EXPECT_FALSE(tree.DeleteNode(-25));
	}


	TEST_F(EmptyTree, Find)
	{
		for (int value : nodes) {
			EXPECT_TRUE(tree.FindNode(value) == NULL);
		}

		EXPECT_TRUE(tree.FindNode(0) == NULL);
		EXPECT_TRUE(tree.FindNode(100) == NULL);
		EXPECT_TRUE(tree.FindNode(-25) == NULL);
	}


	TEST_F(NonEmptyTree, Find)
	{
		for (int value : nodes) {
			EXPECT_TRUE(tree.FindNode(value) != NULL);
		}

		EXPECT_TRUE(tree.FindNode(0) == NULL);
		EXPECT_TRUE(tree.FindNode(100) == NULL);
		EXPECT_TRUE(tree.FindNode(-25) == NULL);
	}


	TEST_F(EmptyTree, LeafNodes)
	{
		std::vector<BinaryTree::Node_t *> leafNodes;
		tree.GetLeafNodes(leafNodes);

		EXPECT_TRUE(leafNodes.empty());
	}


	TEST_F(NonEmptyTree, LeafNodes)
	{
		std::vector<BinaryTree::Node_t *> leafNodes;
		tree.GetLeafNodes(leafNodes);

		EXPECT_EQ(leafNodes.size(), numberOfLeafNodes);

		for (BinaryTree::Node_t *node : leafNodes) {
			EXPECT_TRUE(node->IsLeaf());
			EXPECT_TRUE(node->pParent != NULL);
			EXPECT_TRUE(node->pLeft == NULL);
			EXPECT_TRUE(node->pRight == NULL);

			bool parentFound = false;

			for (int parentKey : leafNodeParents) {
				if (node->pParent->key == parentKey) {
					parentFound = true;
					break;
				}
			}

			EXPECT_TRUE(parentFound) << "Leaf node with parent key: " << node->pParent->key
									 << " found by method BinaryTree::GetLeafNodes is incorrect.";
		}
	}


	TEST_F(EmptyTree, NonLeafNodes)
	{
		std::vector<BinaryTree::Node_t *> nonLeafNodes;
		tree.GetNonLeafNodes(nonLeafNodes);

		EXPECT_TRUE(nonLeafNodes.empty());
	}


	TEST_F(NonEmptyTree, NonLeafNodes)
	{
		std::vector<BinaryTree::Node_t *> nonLeafNodes;
		tree.GetNonLeafNodes(nonLeafNodes);

		EXPECT_EQ(nonLeafNodes.size(), numberOfNodes);

		for (BinaryTree::Node_t *node : nonLeafNodes) {
			EXPECT_FALSE(node->IsLeaf());
			EXPECT_TRUE(node->pLeft || node->pRight);

			bool nodeFound = false;

			for (int nodeKey : nodes) {
				if (nodeKey == node->key) {
					nodeFound = true;
					break;
				}
			}

			EXPECT_TRUE(nodeFound) << "Non leaf node with key: " << node->key
								   << " found by method BinaryTree::GetNonLeafNodes is incorrect.";
		}
	}


	TEST_F(EmptyTree, AllNodes)
	{
		std::vector<BinaryTree::Node_t *> allNodes;
		tree.GetAllNodes(allNodes);

		EXPECT_TRUE(allNodes.empty());
	}


	TEST_F(NonEmptyTree, AllNodes)
	{
		std::vector<BinaryTree::Node_t *> allNodes;
		tree.GetAllNodes(allNodes);

		EXPECT_EQ(allNodes.size(), numberOfNodes + numberOfLeafNodes);

		std::vector<BinaryTree::Node_t *> nonLeafNodes;
		tree.GetNonLeafNodes(nonLeafNodes);
		std::vector<BinaryTree::Node_t *> leafNodes;
		tree.GetLeafNodes(leafNodes);
		EXPECT_EQ(allNodes.size(), nonLeafNodes.size() + leafNodes.size());
	}


	TEST_F(EmptyTree, Root)
	{
		EXPECT_TRUE(tree.GetRoot() == NULL);
	}


	TEST_F(NonEmptyTree, Root)
	{
		BinaryTree::Node_t *root = tree.GetRoot();

		ASSERT_TRUE(root != NULL);
		EXPECT_EQ(root->key, 8);
		EXPECT_EQ(root->color, BinaryTree::BLACK);
		EXPECT_FALSE(root->IsLeaf());
		EXPECT_TRUE(root->pParent == NULL);

		ASSERT_TRUE(root->pLeft != NULL);
		EXPECT_EQ(root->pLeft->key, 4);
		EXPECT_EQ(root->pLeft->color, BinaryTree::RED);

		ASSERT_TRUE(root->pRight != NULL);
		EXPECT_EQ(root->pRight->key, 22);
		EXPECT_EQ(root->pRight->color, BinaryTree::RED);
	}


	/// vsechny listove uzly by mely byt cerne
	TEST_F(NonEmptyTree, BlackLeafNodes)
	{
		std::vector<BinaryTree::Node_t *> leafNodes;
		tree.GetLeafNodes(leafNodes);

		for (BinaryTree::Node_t *node : leafNodes) {
			EXPECT_EQ(node->color, BinaryTree::BLACK);
		}
	}


	/// pokud je uzel cerveny, pak by oba jeho potomci meli byt cerni
	TEST_F(NonEmptyTree, BlackNodesOfRedNodes)
	{
		std::vector<BinaryTree::Node_t *> allNodes;
		tree.GetAllNodes(allNodes);

		for (BinaryTree::Node_t *node : allNodes) {
			if (node->color == BinaryTree::RED) {
				ASSERT_TRUE(node->pLeft != NULL);
				EXPECT_EQ(node->pLeft->color, BinaryTree::BLACK);
				ASSERT_TRUE(node->pRight != NULL);
				EXPECT_EQ(node->pRight->color, BinaryTree::BLACK);
			}
		}
	}


	/// kazda cesta od kazdeho listoveho uzlu ke koreni by mela obsahovat stejny pocet cernych uzlu
	TEST_F(NonEmptyTree, NumberOfBlackNodesToRoot)
	{
		std::vector<BinaryTree::Node_t *> leafNodes;
		tree.GetLeafNodes(leafNodes);

		int previousBlackNodesCount = -1,
			blackNodesCount = 0;
		BinaryTree::Node_t *currentNode;

		for (BinaryTree::Node_t *node : leafNodes) {
			blackNodesCount = 0;
			currentNode = node;

			while (currentNode) {
				if (currentNode->color == BinaryTree::BLACK) {
					blackNodesCount++;
				}
				currentNode = currentNode->pParent;
			}

			if (previousBlackNodesCount != -1) {
				EXPECT_EQ(previousBlackNodesCount, blackNodesCount)
									<< "Each path from each leaf node to root must contain same number of black nodes, "
									<< "but path from node with key: " << node->key << " contains " << blackNodesCount
									<< " black nodes.";
			}

			previousBlackNodesCount = blackNodesCount;
		}
	}

}

/*** Konec souboru black_box_tests.cpp ***/
