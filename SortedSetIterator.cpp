#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	//TODO - Implementation
	//set-ul poate fi gol sau nu
	//daca nu e gol iteratorul se muta pe prima poz
	if (multime.contor != 0)
		first();
	else
	//daca e gol
		iter = 0;
}


void SortedSetIterator::first() {
	//TODO - Implementation
	//first din set este elem cu de pe poz 0
	iter = &multime.x[0];
}


void SortedSetIterator::next() {
	//TODO - Implementation
	//conditia pt next este sa fie valida urm poz
	if (valid() == true) //daca este
		iter=iter+1; //creste iter
	else //daca nu
	{	//aruncam exceptie
		exception indexoutofrange; 
		throw indexoutofrange;
	}
}


TElem SortedSetIterator::getCurrent()
{
	//TODO - Implementation
	//poz trb sa fie valida
	if (valid() == true)                      //daca este
		return *this->iter;                  //returnez poz iter
	else                                    //daca nu
	{	//aruncam exceptie
		exception indexoutofrange;
		throw indexoutofrange;
	}
	return NULL_TELEM;
}

bool SortedSetIterator::valid() const {
	//TODO - Implementation
	//verifica daca pointerul se afla in interiorul set-ului
	if (iter < &multime.x[multime.contor] && iter >= &multime.x[0])
		return true;  //daca se afla
	else
		return false; //daca nu se afla
}

