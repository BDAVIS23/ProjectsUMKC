// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>



using namespace std;

int main()

{
    
	int y1;
	int y2;
	int n; 

	for (n = 0; n <= 100; n = n + 10)
	{

		y1 = 100 * n + 10;
		y2 = 5 * n * n + 2;

		if (y1 == y2)
		{
			cout << "y1 and y2 are equal for " << n << endl;
		}

		 else if (y1 > y2)
		{
			cout << "y1 is greater than y2 for " << n << endl;
		}
		else if (y2 > y1)
		{
			cout << "y2 is greater than y1 for " << n << endl;


		}
		}
		











		return 0; 












	}











































// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
