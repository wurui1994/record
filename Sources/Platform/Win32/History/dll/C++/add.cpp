class test
{
	__declspec(dllexport) int  add(int x,int y) {
		return x+y;
	}
	__declspec(dllexport) int sub(int x,int y){
		return x-y;
	}
};
