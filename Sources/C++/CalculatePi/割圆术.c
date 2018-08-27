#include <stdio.h>
#include <math.h>
int main()
{
	long int n;		/* 定义内接正多边形的边数 */
	double h, x, s; /*h 是弦心距 ,x 是边长， s 是面积 */
	/*n 的初值为6,此时设 x 的值就是单位圆的半径1,
	s的值为正六边形的面积。 n 每次循环后加一倍。 */
	for (n = 6, x = 1, s = 3 * sqrt(3) / 2; n <= 6 * 1 << 27; n += n)
	{
		h = sqrt(1 - x * x / 4);				   // 算 2n 边形的弦心距
		s += n * x * (1 - h) / 2;				   // 算 2n 边形的面积
		x = sqrt((x * x) / 4 + (1 - h) * (1 - h)); // 算 2n 边形的边长
	}
	printf("%.15f", s);
	return 0;
}