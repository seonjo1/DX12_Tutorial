//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

#include "stdafx.h"
#include "Win32Application.h"

HWND Win32Application::m_hwnd = nullptr;

int Win32Application::Run(DXSample* pSample, HINSTANCE hInstance, int nCmdShow)
{
    // Parse the command line parameters
    int argc;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    pSample->ParseCommandLineArgs(argv, argc);
    LocalFree(argv);

	// WNDCLASSEX
	// 윈도우 클래스의 정보 구조체로 창 설정을 저장할때 사용
    WNDCLASSEX windowClass = { 0 };
    windowClass.cbSize = sizeof(WNDCLASSEX);			// 구조체 크기
    windowClass.style = CS_HREDRAW | CS_VREDRAW;		// 창 스타일 (CS_CLASSDC: 기본 디바이스 컨텍스트 스타일)
    windowClass.lpfnWndProc = WindowProc;				// 메시지 처리 콜백 함수
    windowClass.hInstance = hInstance;					// 앱 인스턴스 핸들
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);	// 창 위에 표시될 커서 설정
    windowClass.lpszClassName = L"DXSampleClass";		// 클래스 이름 (CreateWindow에서 사용됨)
    RegisterClassEx(&windowClass);						// WNDCLASSEX 등록 (windows os에 창 설정 등록)

	// RECT: 창 크기
    RECT windowRect = { 0, 0, static_cast<LONG>(pSample->GetWidth()), static_cast<LONG>(pSample->GetHeight()) };
	
	// AdjustWindowRect: 창의 크기를 렌더링 + 나머지로 나눠서 렌더링 부분을 원하는 크기로 조정해줌
    // wr: 조정 대상이 될 RECT 구조체 포인터
	// dwStyle: 윈도우 스타일 (WS_OVERLAPPEDWINDOW: 상단에 제목줄, 우측 상단에 최소화/최대화/닫기 버튼, 테두리를 드래그해서 크기 조절 가능)
	// bMenu: 메뉴바가 있는지 여부 (없으면 FALSE)
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	// HWND g_hwnd 
	// 이 프로그램의 창의 핸들을 담는 전역 변수
	// CreateWindow(): 
	// wc.lpszClassName: 클래스 이름
	// _T("DirectX 12 Window"): 창 제목
	// WS_OVERLAPPEDWINDOW: 창 스타일
	// 100, 100: 창 위치 (x, y)
	// wr.right - wr.left: 창 너비
	// wr.bottom - wr.top: 창 높이
	// NULL, NULL: 부모 창, 메뉴 핸들 (없음)
	// wc.hInstance: 인스턴스 핸들
	// NULL: 추가 데이터 (사용 안함)
    m_hwnd = CreateWindow(
        windowClass.lpszClassName,
        pSample->GetTitle(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        nullptr,        // We have no parent window.
        nullptr,        // We aren't using menus.
        hInstance,
        pSample);

    // Initialize the sample. OnInit is defined in each child-implementation of DXSample.
    pSample->OnInit();

	// ShowWindow() : 생성한 창을 화면에 띄우는 함수
    ShowWindow(m_hwnd, nCmdShow);

    // Main sample loop.
    MSG msg = {};
    while (msg.message != WM_QUIT)
    {
        // Process any messages in the queue.
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    pSample->OnDestroy();

    // Return this part of the WM_QUIT message to Windows.
    return static_cast<char>(msg.wParam);
}

// Main message handler for the sample.
LRESULT CALLBACK Win32Application::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    DXSample* pSample = reinterpret_cast<DXSample*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    switch (message)
    {
    case WM_CREATE:
        {
            // Save the DXSample* passed in to CreateWindow.
            LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
        }
        return 0;

    case WM_KEYDOWN:
        if (pSample)
        {
            pSample->OnKeyDown(static_cast<UINT8>(wParam));
        }
        return 0;

    case WM_KEYUP:
        if (pSample)
        {
            pSample->OnKeyUp(static_cast<UINT8>(wParam));
        }
        return 0;

    case WM_PAINT:
        if (pSample)
        {
            pSample->OnUpdate();
            pSample->OnRender();
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    // Handle any messages the switch statement didn't.
    return DefWindowProc(hWnd, message, wParam, lParam);
}
