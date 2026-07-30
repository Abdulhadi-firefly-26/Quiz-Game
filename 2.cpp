//#include<iostream>
//
//using namespace std;
//void new_ch(char& c, int s);
//
//
//int steps, height, width;
//int t_width;
//int t_height;
//int step_no = 0;
//char ch = ' ';
//char ch2 = '*';
//
//int main()
//{
//	//int array[100][100];
//	cout << "Enter no of steps: ";
//	cin >> steps;
//	cout << "Enter height of each step: ";
//	cin >> height;
//	cout << "Enter Width of each step: ";
//	cin >> width;
//	t_width = steps * width;
//	t_height = steps * height;
//	for (int i = 0; i < steps-1;++i)
//	{
//		for (int k = 0; k < height; ++k)
//		{
//			if (k == 0)
//			{
//				for (int j = 0; j < t_width; ++j)
//				{
//					if (j < t_width - width)
//						cout << ch;
//					else
//						cout << ch2;
//				}
//			}
//			else
//			{
//				for (int j = 0; j < t_width; ++j)
//				{
//					if (j < t_width - width)
//						cout << ch;
//					else
//						if (j == t_width - width)
//							cout << ch2;
//				}
//			}
//			cout << endl;
//		}
//		t_width -= width;
//		new_ch(ch2, step_no);
//		step_no++;
//	}
//	for (int j = 0; j < width; ++j)
//	{
//		cout << ch2;
//	}
//}
//void new_ch(char& c,int s)
//{
//	switch (s % 3)
//	{
//	case 0:
//		c = '+';
//		break;
//	case 1:
//		c = '-';
//		break;
//	case 2:
//		c = '*';
//		break;
//	}
//
//}