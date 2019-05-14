//两者等效

//对三维点进行旋转
void Rotate(PointArray pa, vector3 vec,float t)
{
	//PointArray r = Array3d(pa.length);
	float x,y,z,a,b,c;
	float base=sqrt(vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2]);
	a=vec[0]/base,b=vec[1]/base,c=vec[2]/base;
	for (int i = 0; i < pa.length; i++) {
		x=pa.x[i],y=pa.y[i],z=pa.z[i];
		//
		pa.x[i]=(cos(t)+(1-cos(t))*a*a)*x+
		        ((1-cos(t))*a*b-sin(t)*c)*y+
		        ((1-cos(t))*a*c+sin(t)*b)*z;
		//
		pa.y[i]=((1-cos(t))*b*a+sin(t)*c)*x+
		        (cos(t)+(1-cos(t))*b*b)*y+
		        ((1-cos(t))*b*c-sin(t)*a)*z;
		//
		pa.z[i]=((1-cos(t))*c*a-sin(t)*b)*x+
		        ((1-cos(t))*c*b+sin(t)*a)*y+
		        (cos(t)+(1-cos(t))*c*c)*z;
		//
	}
	//return r;
}


// 旋转矩阵
void matrix_set_rotate(matrix_t *m, float x, float y, float z, float theta) {
	float qsin = (float)sin(theta * 0.5f);
	float qcos = (float)cos(theta * 0.5f);
	vector_t vec = { x, y, z, 1.0f };
	float w = qcos;
	vector_normalize(&vec);
	x = vec.x * qsin;
	y = vec.y * qsin;
	z = vec.z * qsin;
	m->m[0][0] = 1 - 2 * y * y - 2 * z * z;
	m->m[1][0] = 2 * x * y - 2 * w * z;
	m->m[2][0] = 2 * x * z + 2 * w * y;
	m->m[0][1] = 2 * x * y + 2 * w * z;
	m->m[1][1] = 1 - 2 * x * x - 2 * z * z;
	m->m[2][1] = 2 * y * z - 2 * w * x;
	m->m[0][2] = 2 * x * z - 2 * w * y;
	m->m[1][2] = 2 * y * z + 2 * w * x;
	m->m[2][2] = 1 - 2 * x * x - 2 * y * y;
	m->m[0][3] = m->m[1][3] = m->m[2][3] = 0.0f;
	m->m[3][0] = m->m[3][1] = m->m[3][2] = 0.0f;	
	m->m[3][3] = 1.0f;
}