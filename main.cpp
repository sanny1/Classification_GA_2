#include <iostream>
#include "Population.h"
#include "Support.h"
#include <fstream>

using namespace std;
using namespace Ann;

int main()
{
	//reading the data
	data* d = new data();
	d->Read_data(2);

	ofstream afile_2("/Users/sanyogchhetri/ClionProjects/Classification_GA_2/afile_2.txt");
//	srand(time(NULL));
	// only even numbers for pop_size please
	//initialisation, reinsertation is in 10% meaning 5 of the top players in the population gets saved
	Population* p = new Population(50,11,6); // for data 2 i can go as low as 7 rules
	p->Set_ideal_output(d->out_tmp_get());
	p->Set_ideal_ins(d->tmp_get());
	p->Initialise();
	p->Evaluates(Checker,1);

	float sum = 0;
	int start = clock();
	do
	{
		p->Tournament_Selection(3);//tournament
//		p->Selection();
		p->Poppairing(90);
		p->PopMutate(15);
		p->Evaluates(Checker, 2);//evaluates children
		p->Deterministic_crowding();//fitness based
		p->Organise();
		afile_2 << p->Best_fitness() << " ";
		afile_2 << p->Mean_fitness() << endl;
		cout << p->Best_fitness() << " ";
		cout << p->Mean_fitness() << endl;
		sum = p->Best_fitness();
//		p->print_a_individual();
//		cout << endl;
		p->reinsert(10);// 10 percent
	} while(sum < 64);
	p->print_a_individual();
	cout << endl;
	int end = clock();
	cout << float(end-start)/CLOCKS_PER_SEC;
}