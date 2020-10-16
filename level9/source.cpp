#include <string.h>
#include <stdlib.h>

#include <iostream>

class N {
	public:
		// int (N::*fn_ptr)(N *p);
		char buf[100];
		int var1;

		N(int param1) {
			// this->fn_ptr = &N::operator+;
			this->var1 = param1;
		}
		void setAnnotation(char *p) {
			memcpy(this->buf, p, strlen(p));
		}
		virtual int operator+(N* p) {
			return this->var1 + p->var1;
		}
		virtual int operator-(N* p) {
			return this->var1 - p->var1;
		}
};

typedef void(***fn)(N*, N*);

int main(int ac, char*av[])
{
	if (ac < 2) {
		exit(1);
	}
	N* n0 = new N(5);
	N* n1 = new N(6);
	n0->setAnnotation(av[1]);
	// (***(fn)n1)(n1, n0);
	n1->operator+(n0);
	return 0;
}
