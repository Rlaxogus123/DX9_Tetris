#include "DXUT.h"
#include "resource.h"

#include "Include.h"

#include <windows.h>
#include <time.h>

HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{
	srand(time(NULL));
	Director::GetInstance()->DirectorInit();
    return S_OK;
}

void CALLBACK OnD3D9FrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    HRESULT hr;

    V( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 60, 60, 60, 60 ), 1.0f, 0 ) );

    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
		GLOBAL::deltaTime = fElapsedTime * GLOBAL::scaleTime;
		GLOBAL::totalTime = fTime;
		Director::GetInstance()->SceneUpdate();
        V( pd3dDevice->EndScene() );
    }
}

void CALLBACK OnD3D9DestroyDevice( void* pUserContext )
{
	exit(0);
}


//INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int )
int main()
{
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    DXUTSetCallbackD3D9DeviceCreated( OnD3D9CreateDevice );
    DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );
    DXUTSetCallbackD3D9DeviceDestroyed( OnD3D9DestroyDevice );

    DXUTInit( true, true );
    DXUTSetHotkeyHandling( true, true, true );
    DXUTSetCursorSettings( true, true );
    DXUTCreateWindow( L"DirectX TETRIS" );
    DXUTCreateDevice( true, ScreenWidth, ScreenHeigth );
	Director::GetInstance()->ChangeScene(new GameScene);

    DXUTMainLoop();


    return DXUTGetExitCode();
}


