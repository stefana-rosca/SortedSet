#include "SortedSet.h"
#include "SortedSetIterator.h"
//#include <cstddef>
#include <iostream> 
#include <exception>

SortedSet::SortedSet(Relation r) 
{
	//TODO - Implementation

	contor = 0;            //contorul incepe de la 0
	cap = 100;            //aloc 100 la cap
	rel = r;
	x = new TComp[cap]; //declar array nou de cap 100
	for (int i = 0; i < contor; i++)
		x[i] = NULL_TELEM;
}



bool SortedSet::add(TComp elem)
{
	//TODO - Implementation

	//la adaugarea elem avem doua cazuri de complexitate: 1) Θ(0) cand contor=0 - best case;
	//                                                    2) O(n) cand contor e dif de 0 - worst case;

	//cazul 1)
	if (isEmpty()==true)
	{
		contor+=1;
		x[0] = elem;
		return true;
	}

	//cazul 2)
	for (int i = 0; i < contor; i++)
	{
		if (contor == cap)                                //daca sunt egale inseamna ca nu mai este loc disponibil
		{
			cap <<= 1;                                  //dublez capacitatea mai rapid
			TComp* v = new TComp[cap];                 //fac un nou set cu capacitatea actualizata
			for (int j = 0; j < contor; j++)          //pentru v de la 0 la contor
				v[j] = x[j];                         //copiez elem din x in v
			delete[]x;                              //sterg vectorul x
			x = v;                                 //v devine x
			
		}

		//deoarece este set trebuie ca elem sa fie unice, asa ca ma folosesc de fctia search pt a vedea daca indeplineste conditia sau nu
		//in aceste caz mai exista spatiu disponibil si cap nu trebuie modificata
		 
		if (search(elem) != true)		 //daca search e false inseamna ca nu exista in vector un element egal cu elem
		{
			while (!rel(elem, x[i]) && i < contor)           //cat timp inca nu am gasit element in x care sa indeplineasca relatia si i este o poz valida
				i+=1;                                       //cresc i pt a continua sa caut

			{
				contor+=1;                             //cand gasesc cresc contor pt a face loc noului elem
				for (int j = contor - 1; j > i; j--)  //pt elem de dupa i luate de la coada la cap
					x[j] = x[j-1];                   //mut elem o poz mai la dr
			}

			x[i] = elem;                          //inserez pe poz i elem

			return true;
		}
		else
			if (search(elem) == true)        //daca search e true inseamna ca exista in set deja un element egal cu elem
				return false;               //nu il adaug
	}
}


bool SortedSet::remove(TComp elem)
{
	//TODO - Implementation
	//1) worst case O(n)-cand trebuie sa parcurga set-ul si sa mute toate elem de dupa poz elem ului pana la final o poz mai la stanga
	//2) best case O(1)-cand elem de sters se afla la coada

	for (int i = 0; i < contor; i++)
	{//1)
		if (x[i] == elem)                                   //daca gaseste elem in set
		{
			int sters = i;                                //retine poztia lui in "sters"
			for (int j = sters; j < contor - 1; j++)     //pentru elementele de la sters pana la final
				x[j] = x[j + 1];                        //mutam elem o poz mai la stanga
			contor-=1;                                  //scad lungimea
			return true;
		}
	//2) pt a avea complexitate mai buna verific direct si daca elem e egal cu ultimul element din set
	//ca sa nu mai il parcurg si sa nu mai mut elementele de dupa doar il sterg pe ultimul
		if (x[contor - 1] == elem)                  //daca e egal
		{
			contor-=1;                             //scad lungimea
			return true;
		}
	}

	if (search(elem) != true)        //daca nu gaseste elem in set
		return false;               //pt ca nu se poate sterge ceva ce nu exista
	if (isEmpty() == true)         //daca e gol
		return false;             //pt ca nu are ce sterge
}



bool SortedSet::search(TComp elem) const 
{
	//TODO - Implementation

	//parcurgem x, daca 'elem' este egal cu vreun elem din set return true else return false
	//complexitatile sunt: 1) O(1) cand gasim elem chiar pe prima poz - best case
	//                     2) O(n) cand poz=contor -worst case
	
	for (int i = 0; i < contor; i++)
	{
		if (x[i] == elem)
		{
			return true;
		}
	}
	return false;
}


int SortedSet::size() const
{
	//TODO - Implementation
	//Θ(1)
	//dimensiunea set-ului
	return contor;
}



bool SortedSet::isEmpty() const
{
	//TODO - Implementation
	//Θ(1)
	if (contor != 0) 
		return false; //nu e empty
	else
		return true; //e empty
}

SortedSetIterator SortedSet::iterator() const
{
	return SortedSetIterator(*this);
}


SortedSet::~SortedSet() 
{
	//TODO - Implementation
	//dealocare-Θ(1) 
	delete[]x;
}

