//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.h
// $Author:     Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
// $Date:       $2017-02-18
//============================================================================//

/**
 * @file tdd_code.cpp
 * @author Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include "tdd_code.h"


PriorityQueue::PriorityQueue()
{
	// prazdna fronta, koren bude NULL
	root = NULL;
}


PriorityQueue::~PriorityQueue()
{
	// prochazeni fronty od zacatku
	Element_t *element = GetHead();
	while (element != NULL) {
		// ulozeni ukazatele polozky do docasne promenne, abychom ji potom mohli odstranit
		Element_t *currentElement = element;
		element = element->pNext;
		// uvolneni polozky z pameti
		delete currentElement;
	}
}


void PriorityQueue::Insert(int value)
{
	// prochazeni fronty od zacatku
	for (Element_t *element = GetHead(); element != NULL; element = element->pNext) {
		// ve fronte je jediny prvek
		if (element->pPrev == NULL && element->pNext == NULL) {
			// hodnota jedineho prvku je vetsi nez hodnota vkladaneho prvku
			if (element->value > value) {
				// prvek vlozime na zacatek
				root = NewElement(value, NULL, element);
				element->pPrev = root;

				// hodnota jedineho prvku je mensi nebo rovna hodnote vkladaneho prvku
			} else {
				// prvek vlozime na konec
				element->pNext = NewElement(value, element);
			}

			return;

			// ve fronte je vice prvku, aktualni je prvni
		} else if (element->pPrev == NULL && element->pNext != NULL) {
			// hodnota aktualniho prvku je vetsi nez vkladana hodnota
			if (element->value > value) {
				// prvek vlozime na zacatek
				root = NewElement(value, NULL, element);
				element->pPrev = root;

				return;
			}

			// ve fronte je vice prvku, aktualni je posledni
		} else if (element->pPrev != NULL && element->pNext == NULL) {
			// hodnota aktualniho prvku vetsi nez hodnota vkladaneho
			if (element->value > value) {
				// prvek vlozime na predposledni pozici
				element->pPrev->pNext = NewElement(value, element->pPrev, element);
				element->pPrev = element->pPrev->pNext;

				// hodnota aktualniho prvku je mensi nebo rovna hodnote vkladaneho
			} else {
				// prvek vlozime na konec
				element->pNext = NewElement(value, element);
			}


			return;

			// ve fronte je vice prvku, aktualni je nejaky prostredni prvek a hodnota predchoziho prvku
			// je mensi nebo rovna hodnote vkladaneho a zaroven je hodnota aktualniho prvku vetsi nebo rovna
			// hodnote vkladaneho prvku
		} else if (element->pPrev->value <= value && element->value >= value) {
			// prvek vlozime mezi predchazejici a aktualni prvek
			Element_t *newElement = NewElement(value, element->pPrev, element);
			element->pPrev->pNext = newElement;
			element->pPrev = newElement;

			return;
		}
	}

	// fronta je prazdna, proto vlozeny prvek bude koren
	root = NewElement(value);
}


bool PriorityQueue::Remove(int value)
{
	// hledani prvku pro smazani
	if (Element_t *element = Find(value)) {
		// nalezeny prvek je prvni
		if (element->pPrev == NULL && element->pNext != NULL) {
			// nasledujici prvek bude ukazovat na <- NULL
			element->pNext->pPrev = NULL;
			// koren bude nasledujici prvek
			root = element->pNext;

			// nalezeny prvek je posledni
		} else if (element->pPrev != NULL && element->pNext == NULL) {
			// prechazejici prvek bude ukazovat na -> NULL
			element->pPrev->pNext = NULL;

			// nalezeny prvek je prostredni
		} else if (element->pPrev != NULL && element->pNext != NULL) {
			// predchazejici prvek bude ukazovat na -> nasledujici a nasledujici na <- prechazejici
			element->pPrev->pNext = element->pNext;
			element->pNext->pPrev = element->pPrev;

			// ve fronte je jediny prvek
		} else {
			// fronta bude prazdna, proto nastavime ukazatel korene na NULL
			root = NULL;
		}

		// uvolneni prvku z pameti
		delete element;

		return true;
	}

	// prvek nebyl nalezen
	return false;
}


PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
	// prochazeni fronty od zacatku
	for (Element_t *element = GetHead(); element != NULL; element = element->pNext) {
		if (element->value == value) {
			// prvek byl nalezen
			return element;
		}
	}

	// prvek nebyl nalezen
	return NULL;
}


PriorityQueue::Element_t *PriorityQueue::GetHead()
{
	return root;
}


PriorityQueue::Element_t *PriorityQueue::NewElement(int value, Element_t *pPrev, Element_t *pNext)
{
	Element_t *element = new Element_t();
	element->value = value;
	element->pPrev = pPrev;
	element->pNext = pNext;

	return element;
}


/*** Konec souboru tdd_code.cpp ***/
