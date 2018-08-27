//用矩阵类重写
/*
Title:SimpleMath
Author:wurui
Date:2015-4-5-16:20
Version:0.0.7
Email:1341531859@qq.com
Address:whut-yu-H6-611
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//
int i,j,k,m,n,d;

inline void swap(double &a,double &b){
	double c=a;a=b;b=c;
}
#ifndef Matrix
class Matrix{
	friend Matrix operator+(const Matrix &a,const Matrix &b);
	friend Matrix operator-(const Matrix &a,const Matrix &b);
	friend Matrix operator*(const Matrix &a,const Matrix &b);

public:
	~Matrix();
	Matrix(int,int);
	Matrix(const Matrix &m);
	Matrix& operator=(const Matrix &m);
	Matrix operator~() const;
	Matrix inv(const Matrix &m);
	Matrix leftdiv(const Matrix &a,const Matrix &b);
	Matrix dotdiv(const Matrix &a,const Matrix &b);
	//
	void zeros();
	void ones();
	void rands();
	void eval(double *array2d);
	void print() const;
	//
	int row;int col;
	double **elems;
};
Matrix::Matrix(int l,int c){
	row=l;col=c;
	elems=new double*[row];
	for(i=0;i<row;i++){
		elems[i] = new double[col];
	}
}

Matrix::Matrix(const Matrix &m){
	row=m.row;col=m.col;
	elems=new double*[row];
	for(i=0;i<row;i++){
		elems[i] = new double[col];
	}
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			elems[i][j]=m.elems[i][j];
}
Matrix::~Matrix(){
	delete[] elems;
}
Matrix& Matrix::operator =(const Matrix &m){
	row=m.row;col=m.col;
	elems=new double*[row];
	for(i=0;i<row;i++){
		elems[i] = new double[col];
	}
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			elems[i][j]=m.elems[i][j];
	return *this;
}

Matrix Matrix::operator ~() const{
	Matrix t(col,row);
	t.elems=new double*[row];
	for(i=0;i<row;i++){
		t.elems[i] = new double[col];
	}
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			t.elems[j][i]=elems[i][j];
	return t;
}
Matrix operator+(const Matrix &a,const Matrix &b){
	Matrix c(a.row,a.col);
	int row=a.row,col=a.col;
	c.elems=new double*[row];
	for(i=0;i<row;i++){
		c.elems[i] = new double[col];
	}
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			c.elems[i][j]=a.elems[i][j]+b.elems[i][j];
	return c;
}
Matrix operator-(const Matrix &a,const Matrix &b){
	Matrix c(a.row,a.col);
	int row=a.row,col=a.col;
	c.elems=new double*[row];
	for(i=0;i<row;i++){
		c.elems[i] = new double[col];
	}
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			c.elems[i][j]=a.elems[i][j]-b.elems[i][j];
	return c;
}
Matrix operator*(const Matrix &a,const Matrix &b){
	int row=a.row,col=b.col;
	Matrix c(row,col);
	c.elems=new double*[row];
	for(i=0;i<row;i++){
		c.elems[i] = new double[col];
	}
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			c.elems[i][j]=0;
	for(i=0;i<row;i++)
		for(k=0;k<col;k++)
			for(j=0;j<b.row;j++)
				c.elems[i][k]+=a.elems[i][j]*b.elems[j][k];
	return c;
}
Matrix operator*(const Matrix &a,double b){
	int row=a.row;
	int col=a.col;
	Matrix c(row,col);
	c.elems=new double*[row];
	for(i=0;i<row;i++){
		c.elems[i] = new double[col];
	}
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			c.elems[i][j]=0;
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			c.elems[i][j]=a.elems[i][j]*b;
	return c;
}
Matrix operator*(double a,const Matrix &b){
	int row=b.row;
	int col=b.col;
	Matrix c(row,col);
	c.elems=new double*[row];
	for(i=0;i<row;i++){
		c.elems[i] = new double[col];
	}
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			c.elems[i][j]=0;
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			c.elems[i][j]=b.elems[i][j]*a;
	return c;
}
Matrix inv(const Matrix &m){
	int row=m.row,col=m.col;
	if(row!=col){ 
		printf("Error!Matrix must be square.\n\n");
	}
	Matrix r(row,col);
	r.elems=new double*[row];
	for(i=0;i<row;i++){
		r.elems[i] = new double[col];
	}
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			r.elems[i][j]=0;
	n=row;double d;int* js=new int[n],*is=new int[n];
	for (k=0;k<n;k++){
		d=0;
		for (i=k;i<n;i++)
			for (j=k;j<n;j++){
				if (fabs(m.elems[i][j])>d){
					d=fabs(m.elems[i][j]);
					is[k]=i;js[k]=j;
				}
			}
			if (d+1.0==1.0) printf("break");
			if (is[k]!=k)
				for (j=0;j<n;j++)
					swap(m.elems[k][j],m.elems[is[k]][j]);
			if (js[k]!=k)
				for (i=0;i<n;i++)
					swap(m.elems[i][k],m.elems[i][js[k]]);
			m.elems[k][k]=1/m.elems[k][k];
			for (j=0;j<n;j++)
				if (j!=k) m.elems[k][j]=m.elems[k][j]*m.elems[k][k];
			for (i=0;i<n;i++)
				if (i!=k)
					for (j=0;j<n;j++)
						if (j!=k) m.elems[i][j]=m.elems[i][j]-m.elems[i][k]*m.elems[k][j];
			for (i=0;i<n;i++)
				if (i!=k) m.elems[i][k]=-m.elems[i][k]*m.elems[k][k];
	}
	for (k=n-1;k>=0;k--){
		for (j=0;j<n;j++)
			if (js[k]!=k) swap(m.elems[k][j],m.elems[js[k]][j]);
		for (i=0;i<n;i++)
			if (is[k]!=k) swap(m.elems[i][k],m.elems[i][is[k]]);
	}
	for (i=0;i<n;i++){
		for (j=0;j<n;j++)
			r.elems[i][j]=m.elems[i][j];
	}
	return r;
}
Matrix operator/(const Matrix &a,const Matrix &b){
	int row=b.row;int col=b.col;i,j;
	Matrix c(row,col);
	c.elems=new double*[row];
	for(i=0;i<row;i++){
		c.elems[i] = new double[col];
	}
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			c.elems[i][j]=0;
	c=a*inv(b);
	return c;
}
Matrix operator/(const Matrix &a,double b){
	int row=a.row;
	int col=a.col;
	Matrix c(row,col);
	c.elems=new double*[row];
	for(i=0;i<row;i++){
		c.elems[i] = new double[col];
	}
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			c.elems[i][j]=0;
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			c.elems[i][j]=a.elems[i][j]/b;
	return c;
}
Matrix operator/(double a,const Matrix &b){
	int row=b.row;
	int col=b.col;
	Matrix c(row,col);
	c.elems=new double*[row];
	for(i=0;i<row;i++){
		c.elems[i] = new double[col];
	}
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			c.elems[i][j]=0;
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			c.elems[i][j]=a/b.elems[i][j];
	return c;
}
Matrix leftdiv(const Matrix &a,const Matrix &b){
	int row=b.row;int col=b.col;i,j;
	Matrix c(row,col);
	c.elems=new double*[row];
	for(i=0;i<row;i++){
		c.elems[i] = new double[col];
	}
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			c.elems[i][j]=0;
	c=inv(a)*b;
	return c;
}
Matrix dotdiv(const Matrix &a,const Matrix &b){
	int row=b.row;int col=b.col;i,j;
	Matrix c(row,col);
	c.elems=new double*[row];
	for(i=0;i<row;i++){
		c.elems[i] = new double[col];
	}
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			c.elems[i][j]=a.elems[i][j]/b.elems[i][j];
	return c;
}
void Matrix::zeros(){
	elems=new double*[row];
	for(i=0;i<row;i++){
		elems[i] = new double[col];
	}
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			elems[i][j]=0;
}

void Matrix::ones(){
	elems=new double*[row];
	for(i=0;i<row;i++){
		elems[i] = new double[col];
	}
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			elems[i][j]=1;
}
void Matrix::rands(){
	elems=new double*[row];
	for(i=0;i<row;i++){
		elems[i] = new double[col];
	}
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			elems[i][j]=rand()/(RAND_MAX+1.0);
}
void Matrix::eval(double *array2d){
	elems=new double*[row];
	for(i=0;i<row;i++){
		elems[i] = new double[col];
	}
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			elems[i][j]=array2d[i*row+j];
}
void Matrix::print() const{
	for(i=0;i<row;i++){
		printf("[ ");
		for(j=0;j<col;j++){
			printf("%lf ",elems[i][j]);
		}
		printf("]\n");
	}
	printf("\n");
}
#endif
int main()
{
	Matrix a(3,3),b(3,3),c(3,3),d(3,1);
	//初始化
	a.rands();b.rands();d.rands();
	a.print();b.print();
	//矩阵基本运算
	c=~a;c.print();//转置
	c=a+b;c.print();
	c=a-b;c.print();
	c=3*a;c.print();
	c=b*3;c.print();
	c=a*b;c.print();
	c=a/3;c.print();
	c=3/a;c.print();
	c=dotdiv(a,b);c.print();
	//左除-解方程
	a.print();d.print();
	c=leftdiv(a,d);c.print();
	//数组写入matrix
	double array2d[3][3]={{1,2,3},{4,5,6},{7,8,9}};
	a.eval(&array2d[0][0]);a.print();
	return 0;
}
