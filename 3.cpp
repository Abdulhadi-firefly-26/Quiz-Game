//#include<iostream>
//#include<iomanip>
//using namespace std;
//int main()
//{
//	char array[50][50];
//	int n;
//	cout << "Enter length of side of diamond: ";
//	cin >> n;
//	int m = n * 2 + 2;
//	for (int i = 0; i < m; ++i)
//	{
//		for (int j = 0; j < m; ++j)
//		{
//			if (i == 0 || i == m - 1 || j == 0 || j == m - 1)
//				array[i][j] = '*';
//			else
//				array[i][j] = ' ';
//		}
//	}
//	for (int i = 0; i < m; ++i)
//	{
//		for (int j = 0; j <n; ++j)
//		{
//			if (j == n - j)
//				array[i][j] = '*';
//		}
//	}
//	for (int i = 0; i < m; ++i)
//	{
//		for (int j = 0; j < m; ++j)
//		{
//			cout << array[i][j] << " ";
//		}
//		cout << endl;
//	}
//	
//}