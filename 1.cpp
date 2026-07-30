//#include<iostream>
//using namespace std;
//
//int main()
//{
//	int steps, height, width;
//	cout << "Enter no of steps: ";
//	cin >> steps;
//	cout << "Enter height of each step: ";
//	cin >> height;
//	cout << "Enter Width of each step: ";
//	cin >> width;
//	int t_width = steps * width;
//	int t_height = steps * height;
//	int step_no = 1;
//	char ch = ' ';
//	char ch2 = '*';
//	cout << endl << endl;
//	for (int i = 1; i <= t_height; ++ i)
//	{
//		
//		for (int j = 1; j <= t_width; ++j)
//		{
//			cout << ch;
//		}
//		if (i == t_height)
//		{
//			for (int j = 1; j <= width*steps; ++j)
//			{
//				cout << ch2;
//			}
//			cout << endl;
//		}
//		else
//		{
//			if (i == 1)
//			{
//				for (int k = 0; k < width - 1; ++k)
//				{
//					cout << ch2;
//				}
//			}
//			else if ((i - 1) % height == 0)
//			{
//				for (int k = 0; k < width - 1; ++k)
//				{
//					cout << ch2;
//				}
//			}
//			if (i % height == 0)
//			{
//				t_width -= width;
//			}
//			cout << ch2;
//			if (i != 1)
//			{
//				if (!((i - 1) % height == 0))
//				{
//					for (int j = 0; j < width * step_no - 2; ++j)
//					{
//						cout << ch;
//					}
//				}
//				else
//				{
//					for (int j = 0; j < width * step_no - 1 - width; ++j)
//					{
//						cout << ch;
//					}
//				}
//				cout << ch2;
//			}
//			cout << endl;
//			if (i % width == 0)
//			{
//				step_no++;
//			}
//			switch (step_no%3)
//			{
//			case 0:
//				ch2 = '+';
//				break;
//			case 1:
//				ch2 = '%';
//				break;
//			case 2:
//				ch2 = '^';
//				break;
//			}
//		}
//	}
//}