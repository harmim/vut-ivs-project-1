//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
// $Date:       $2017-02-17
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>
#include "gtest/gtest.h"
#include "red_black_tree.h"

namespace BlackBoxTesting
{
	using namespace ::testing;


	class TestingTree : public Test
	{

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
//			for (int i = 0; i < 15; i++) {
//				tree.InsertNode(i);
//			}
		}

	};


//	TEST_F(EmptyTree, Insert)
//	{
//		std::pair<bool, BinaryTree::Node_t *> pair = tree.InsertNode(0);

//		ASSERT_EQ(true, true);
//	}
}

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

/*** Konec souboru black_box_tests.cpp ***/
