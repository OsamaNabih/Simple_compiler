int main() {
	
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
		default: d = 7;
		case(7): d = 5;
		default: d = 6;
	}
}