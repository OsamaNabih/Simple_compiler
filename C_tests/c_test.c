#include <stdio.h>
int main() {
	
	for(int i = 0; i < 3; i = 2) {
		printf("What's going on?\n");
	}
	
	int a = 5;
	int b;
	if (a > 4) {
		b = 3;
	}
	else 
		b = 2;

	int c = 5;
	while(b > 0) {
		c = c + 1;
		b = b - 1;
	}
	
	int d;
	switch(c) {
		case(6): 
			while(b > 2) {
				printf("fasdsad");
			}
		default: d = 7;
		case(7): d = 5;
	}
}