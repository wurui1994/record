

#include <d3d9.h>
#include <d3dx9.h>
//#include <strsafe.h>

//#pragma warning(disable:4996)

//global variables.
LPDIRECT3D9 D3D=NULL;
LPDIRECT3DDEVICE9 D3DDevice9=NULL;
LPDIRECT3DVERTEXBUFFER9 D3DVB=NULL;
ID3DXMesh* Teapot = 0;
//custom vertex struct.
struct CUSTOMVERTEX {
	FLOAT x,y,z;
	DWORD color;
};

//define custom vertex format.
#define D3DFVF_CUSTOMVETEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

//init D3D variables
HRESULT InitD3D(HWND hWnd)
{
	//init D3D
	D3D=Direct3DCreate9(D3D_SDK_VERSION);
	if(FAILED(D3D)) {
		return E_FAIL;
	}

	//init D3D present parameter.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp,sizeof(d3dpp));
	d3dpp.Windowed=TRUE;
	d3dpp.SwapEffect=D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat=D3DFMT_UNKNOWN;

	//create d3d device.
	if(FAILED(D3D->CreateDevice(
	              D3DADAPTER_DEFAULT,
	              D3DDEVTYPE_HAL,
	              hWnd,
	              D3DCREATE_SOFTWARE_VERTEXPROCESSING,
	              &d3dpp,
	              &D3DDevice9))) {
		return E_FAIL;
	}

	//turn off culling.
	D3DDevice9->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);

	//turn off light.
	D3DDevice9->SetRenderState(D3DRS_LIGHTING,FALSE);

	return S_OK;
}

//init geometry
HRESULT InitGeometry()
{
	D3DXCreateTeapot(D3DDevice9, &Teapot, 0);
	//initialize three custom vertex.
	CUSTOMVERTEX g_vertices[3]= {
		{-1.0f,-1.0f, 0.0f, D3DCOLOR_XRGB(0,255,0)},
		{0.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(255,0,0)},
		{1.0f,-1.0f, 0.0f,  D3DCOLOR_XRGB(0,0,255)}
	};

	//create vertex buffer.
	if(FAILED(D3DDevice9->CreateVertexBuffer(
	              sizeof(g_vertices),
	              0,
	              D3DFVF_CUSTOMVETEX,
	              D3DPOOL_DEFAULT,
	              &D3DVB,
	              NULL))) {
		return E_FAIL;
	}

	//fill vertex buffer.
	void* pVertices=NULL;
	if(FAILED(D3DVB->Lock(0,sizeof(g_vertices),&pVertices,0))) {
		return E_FAIL;
	}
	memcpy(pVertices,g_vertices,sizeof(g_vertices));
	D3DVB->Unlock();

	return S_OK;
}

//clean up d3d variables.
void CleanUp()
{
	if(D3DVB!=NULL) {
		D3DVB->Release();
	}

	if(D3DDevice9!=NULL) {
		D3DDevice9->Release();
	}

	if(D3D!=NULL) {
		D3D->Release();
	}
}

//setup matrix
void SetupMatrix()
{
	//world matrix.
	D3DXMATRIX matWorld;

	//rotation matrix.
	UINT itimes=timeGetTime()%1000;
	FLOAT fAngle=itimes * ( 2.0f * D3DX_PI ) / 1000.0f;
	D3DXMatrixRotationY(&matWorld,fAngle);

	//set world matrix.
	D3DDevice9->SetTransform(D3DTS_WORLD,&matWorld);

	//set view point.
	D3DXVECTOR3 vEyePt(0.0f,3.0f,-5.0f);
	D3DXVECTOR3 vLookAt(0.0f,0.0f,0.0f);
	D3DXVECTOR3 vUp(0.0f,1.0f,0.0f);

	//view matrix.
	D3DXMATRIX matView;

	//set view matrix.
	D3DXMatrixLookAtLH(&matView,&vEyePt,&vLookAt,&vUp);
	D3DDevice9->SetTransform(D3DTS_VIEW,&matView);

	//set projection matrix.
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj,D3DX_PI/4,1.0f,1.0f,100.0f);
	D3DDevice9->SetTransform(D3DTS_PROJECTION,&matProj);
}

//render the scene.
void Render()
{
	//clear target device.
	D3DDevice9->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,0),1.0f,0);

	//draw primitive.
	if(SUCCEEDED(D3DDevice9->BeginScene())) {
		SetupMatrix();

		D3DDevice9->SetStreamSource(0,D3DVB,0,sizeof(CUSTOMVERTEX));
		D3DDevice9->SetFVF(D3DFVF_CUSTOMVETEX);
		//D3DDevice9->DrawPrimitive(D3DPT_TRIANGLELIST,0,1);
		Teapot->DrawSubset(0);
		D3DDevice9->EndScene();
	}

	//present back buffer to display.
	D3DDevice9->Present(NULL,NULL,NULL,NULL);
}

//message loop handler.
LRESULT WINAPI MsgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg) {
	case WM_DESTROY:
		CleanUp();
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd,msg,wParam,lParam);
}

//the application entry point.
INT WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,INT)
{
	//windclass structure.
	WNDCLASSEX wcex;

	wcex.cbClsExtra=0;
	wcex.cbSize=sizeof(WNDCLASSEX);
	wcex.cbWndExtra=0;
	wcex.hbrBackground=NULL;
	wcex.hCursor=NULL;
	wcex.hIcon=NULL;
	wcex.hIconSm=NULL;
	wcex.hInstance=GetModuleHandle(NULL);
	wcex.lpfnWndProc=MsgProc;
	wcex.lpszClassName="D3D Toturial";
	wcex.lpszMenuName=NULL;
	wcex.style=CS_CLASSDC;

	//register window class.
	RegisterClassEx(&wcex);

	//create window.
	HWND hWnd=CreateWindow(
	              "D3D Toturial",
	              "D3D Toturial 003",
	              WS_OVERLAPPEDWINDOW,
	              350,
	              120,
	              500,
	              500,
	              NULL,
	              NULL,
	              wcex.hInstance,
	              NULL);

	//init d3d.
	if(SUCCEEDED(InitD3D(hWnd))) {
		if(SUCCEEDED(InitGeometry())) {
			//show window.
			ShowWindow(hWnd,SW_SHOWDEFAULT);
			UpdateWindow(hWnd);

			// Enter the message loop
			MSG msg;
			ZeroMemory( &msg, sizeof( msg ) );
			while( msg.message != WM_QUIT ) {
				if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) ) {
					TranslateMessage( &msg );
					DispatchMessage( &msg );
				} else
					Render();
			}
		}
	}

	//unregister window class.
	UnregisterClass( "D3D Tutorial", wcex.hInstance );
	return 0;
}
