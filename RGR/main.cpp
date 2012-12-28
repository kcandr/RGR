#include <iostream>
#include <math.h>
using namespace std;

float a = 0, b = 1;
float a0 = 1, a1 = 1, b0 = 1, b1 = 0, A = 2, B = exp(1.0f) + 2;
float p[21], q[21], f[21], m[21], r[21], fi[21], c[21], d[21], x[21], yt[21], y[21], u[21], v[21];

void print(int n)
{
	cout << "    x  |   y*(x)  |   y(x)   | y - y*" << endl;
	cout << "---------------------------------------" << endl;
	for (int i = 0; i < n; ++i)
		printf("%6.2f | %7.6f | %7.6f | %7.6f\n", x[i], yt[i], y[i], abs(yt[i] - y[i]));
	cout << "---------------------------------------" << endl;
}

void init(int n, float h)
{
	for (int i = 1; i < n; ++i) {
		x[i] = x[i-1] + h;
		yt[i] = exp(x[i]) + x[i] * x[i];
		q[i] = 0;
		p[i] = -1;
		f[i] = 2 * (1 - x[i]);
	}
}

void progonka(int n)
{
	float h = 1.0f/n;
	++n;
	init(n, h);
	for (int i = 0; i < n; ++i) {
		m[i] = (2 * pow(h, 2) * q[i] - 4) / (2 + h * p[i]);
		r[i] = (2 - h * p[i]) / (2 + h * p[i]);
		fi[i] = (2 * pow(h, 2) * f[i]) / (2 + h * p[i]);
	}
	c[0] = a0 / (h * a1 + a0);
	d[0] = (A * h) / a0;
	for (int i = 1; i < n; ++i) {
		c[i] = 1 / (m[i] - r[i] * c[i-1]);
		d[i] = fi[i] - r[i] * c[i-1] * d[i-1];
	};
	y[n-1] = (B * h + b0 * c[n-2] * d[n-2]) / (b0 * (1 + c[n-2]) + h * b1);
	for (int i = n - 2; i > -1; --i) {
		y[i] = c[i] * (d[i] - y[i+1]);
	}
	print(n);
	return;
}

void koshi(int n)
{
	float h = 1.0f/n;
	++n;
	init(n, h);
	u[0] = a1;
	v[0] = A / a0;
	u[1] = (a1 * (1 + p[1] * h) - a0 * h * (1 + p[1] / h)) / (1 + p[1] * h + 0.5 * q[1] * pow(h, 2));
	v[1] = (0.5 * f[1] * pow(h, 2) + A * (a1 / a0) * (1 + p[1] * h)) / (1 + p[1] * h + 0.5 * q[1] * pow(h, 2));
	print(n);
	return;
}

int main()
{
	int key;
	setlocale(LC_ALL, "Russian");
	x[0] = a;
	yt[0] = exp(x[0]) + x[0] * x[0];
	q[0] = 0;
	p[0] = -1;
	f[0] = 2 * (1 - x[0]);

	while (true) {
		cout << "1 - Прогонка\n2 - Сведение к задачам Коши\n";
		cin >> key;
		switch (key)
		{
		case 1:
			progonka(10);
			progonka(20);
			break;
		}
	}

	return 1;
}