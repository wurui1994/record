//No ZBuffer
double a[]= {
	-100,-100,100,
	100,-100,100,
	100,100,100,
	-100,100,100,
};//前
double b[]= {
	-100,-100,-100,
	100,-100,-100,
	100,100,-100,
	-100,100,-100,
};//后
double c[]= {
	-100,-100,-100,
	100,-100,-100,
	100,-100,100,
	-100,-100,100,
};//下
double d[]= {
	-100,100,-100,
	100,100,-100,
	100,100,100,
	-100,100,100,
};//上
double e[]= {
	-100,-100,-100,
	-100,100,-100,
	-100,100,100,
	-100,-100,100,
};//左
double f[]= {
	100,-100,-100,
	100,100,-100,
	100,100,100,
	100,-100,100,
};//右
PointArray ptsa=eval(a,Length(a));
PointArray ptsb=eval(b,Length(b));
PointArray ptsc=eval(c,Length(c));
PointArray ptsd=eval(d,Length(d));
PointArray ptse=eval(e,Length(e));
PointArray ptsf=eval(f,Length(f));
void cube3d(Image img,vector3 v)
{
	//
	img.SetColor(0,255,255);
	ptsa=Rotate(ptsa,v,0.1);
	img.FillRect3d(ptsa);
	//
	img.SetColor(255,0,255);
	ptsb=Rotate(ptsb,v,0.1);
	img.FillRect3d(ptsb);
	//
	img.SetColor(255,255,0);
	ptsc=Rotate(ptsc,v,0.1);
	img.FillRect3d(ptsc);
	//
	img.SetColor(255,0,0);
	ptsd=Rotate(ptsd,v,0.1);
	img.FillRect3d(ptsd);
	//
	img.SetColor(0,255,0);
	ptse=Rotate(ptse,v,0.1);
	img.FillRect3d(ptse);
	//
	img.SetColor(0,0,255);
	ptsf=Rotate(ptsf,v,0.1);
	img.FillRect3d(ptsf);
}
