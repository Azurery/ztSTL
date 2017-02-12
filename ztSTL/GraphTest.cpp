#include "graph.h"
#include <iostream>

int main() {
	char vex[] = { 'A','B','C','D','E' };
	int num = sizeof(vex) / sizeof(vex[0]);
	
	ztSTL::algraph<int, char> g(vex, num);
	g.insert_edge(0, 0, 1);
	g.insert_edge(0, 1, 2);
	g.insert_edge(0, 0, 3);
	g.insert_edge(0, 2, 3);
	g.insert_edge(0, 2, 4);
	g.insert_edge(0, 1, 4);
	g.show();
	system("pause");
}