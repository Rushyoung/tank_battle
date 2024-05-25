/**
 * @file	HiWindow.h
 * @brief	HiEasyX ��Ĵ���ģ��
 * @author	huidong
*/

#pragma once

#include "HiDef.h"
#include "HiFunc.h"
#include <graphics.h>
#include <windowsx.h>
#include <WinUser.h>
#include <vector>
#include <thread>
#include <shellapi.h>

#ifdef _MSC_VER
#pragma comment (lib, "Msimg32.lib")
#endif

#define __HIWINDOW_H__

// �����ͼ���ڳ�ʼ������
// ��ͨ����
#define EW_NORMAL							0

// �޴���ʱ������
#define NO_WINDOW_INDEX						-1

// ���ڹ��̺���Ĭ�Ϸ���ֵ
#define HIWINDOW_DEFAULT_PROC				(LRESULT)(-10086)

// ������Ϣ
#define WM_TRAY								(WM_USER + 9337)

// ϵͳ�ؼ�������Ϣ
// wParam ���� SysControlBase*
// lParam ���� CREATESTRUCT*
#define WM_SYSCTRL_CREATE					(WM_USER + 9338)

// ϵͳ�ؼ�������Ϣ
// wParam ���� SysControlBase*
#define WM_SYSCTRL_DELETE					(WM_USER + 9339)

// �û��ػ���Ϣ���������
// �û����� RedrawWindow ���ػ洰��ʱ�ᷢ�ʹ���Ϣ���� WN_PAINT
#define WM_USER_REDRAW						(WM_USER + 9340)

namespace HiEasyX
{
	class Canvas;
	class SysControlBase;

	////////////****** ���Ͷ��� ******////////////

	/**
	 * @brief	����
	 * @note	�� InitWindowStruct �����г�ʼ���˽ṹ��
	*/
	struct EasyWindow
	{
		bool isAlive;								///< �����Ƿ����

		HWND hWnd;									///< ���ھ��
		HWND hParent;								///< �����ھ��

		IMAGE* pImg;								///< ����ͼ��
		IMAGE* pBufferImg;							///< ͼ�񻺳���
		Canvas* pBufferImgCanvas;					///< ͼ�񻺳����󶨵Ļ���ָ��
		bool isNeedFlush;							///< �Ƿ���Ҫ�����ͼ����

		WNDPROC funcWndProc;						///< ������Ϣ������

		std::vector<ExMessage> vecMessage;			///< ģ�� EasyX ������Ϣ����

		bool isUseTray;								///< �Ƿ�ʹ������
		NOTIFYICONDATA nid;							///< ������Ϣ
		bool isUseTrayMenu;							///< �Ƿ�ʹ�����̲˵�
		HMENU hTrayMenu;							///< ���̲˵�

		/**
		 * @brief <pre>
		 *		���̲˵���Ϣ������ָ��
		 *
		 * ��ע��
		 *		�����˺�����Ϊ�˷�����Ӧ���̵Ĳ˵���Ϣ
		 *		������Ӧ������������Ϣ�����Զ��崰�ڹ��̺��������� WM_TRAY ��Ϣ
		 * </pre>
		*/
		void(*funcTrayMenuProc)(UINT);

		bool isNewSize;								///< ���ڴ�С�Ƿ�ı�
		bool isBusyProcessing;						///< �Ƿ���æ�ڴ����ڲ���Ϣ��ָ�������û���������������

		int nSkipPixels;							///< ����ʱ���������ص��������������ٻ棩

		std::vector<SysControlBase*> vecSysCtrl;	///< ��¼������ϵͳ�ؼ�
		bool bHasCtrl = false;						///< �Ƿ񴴽���ϵͳ�ؼ�
	};

	/**
	 * @brief <pre>
	 *		����ģʽ���ӻ��������Ƶ����ڣ�
	 *
	 *	��ע��
	 *		һ��ʹ�� DM_Normal ���ɡ�
	 * </pre>
	*/
	enum DrawMode
	{
		DM_Real,		///< ��ȫ��ʵ�ʻ��ƣ�ÿ��Ҫ���ػ涼����ִ�У����ܵ��³��򿨶٣�
		DM_Normal,		///< �������ƣ����ں� DM_Real �ǵȼ��ˣ�
		DM_Fast,		///< ���ٻ��ƣ����� WM_USER_REDRAW ��Ϣ�������������ֻ��ƣ�
		DM_VeryFast,	///< ���ٻ��ƣ����� WM_USER_REDRAW ��Ϣ�����������ܶ���ƣ�
		DM_Fastest,		///< ���Ļ��Ʒ�ʽ������ WM_USER_REDRAW ��Ϣ�����������󲿷ֻ��ƣ�
	};

	/**
	 * @brief ����
	*/
	class Window
	{
	private:

		int m_nWindowIndex = NO_WINDOW_INDEX;
		bool m_isCreated = false;

		bool m_isPreStyle = false;
		bool m_isPreStyleEx = false;
		bool m_isPrePos = false;
		bool m_isPreShowState = false;

		long m_lPreStyle;
		long m_lPreStyleEx;
		POINT m_pPrePos;
		int m_nPreCmdShow;

	public:

		Window();

		Window(
			int w,
			int h,
			int flag = EW_NORMAL,
			LPCTSTR lpszWndTitle = _T(""),
			WNDPROC WindowProcess = nullptr,
			HWND hParent = nullptr
		);

		virtual ~Window();

		HWND InitWindow(
			int w = 640,
			int h = 480,
			int flag = EW_NORMAL,
			LPCTSTR lpszWndTitle = _T(""),
			WNDPROC WindowProcess = nullptr,
			HWND hParent = nullptr
		);

		/**
		 * @brief �ȼ��� InitWindow
		*/
		HWND Create(
			int w = 640,
			int h = 480,
			int flag = EW_NORMAL,
			LPCTSTR lpszWndTitle = _T(""),
			WNDPROC WindowProcess = nullptr,
			HWND hParent = nullptr
		);

		void CloseWindow();

		/**
		 * @brief �ȼ��� CloseWindow
		*/
		void Destroy();

		void SetProcFunc(WNDPROC WindowProcess);

		HWND GetHandle();
		EasyWindow GetInfo();
		bool IsAlive();

		IMAGE* GetImage();
		Canvas* GetCanvas();
		void BindCanvas(Canvas* pCanvas);

		void WaitMyTask();
		bool SetWorkingWindow();

		void SetQuickDraw(UINT nSkipPixels);

		/**
		 * @brief �ػ洰��
		*/
		void Redraw();

		/**
		 * @brief <pre>
		 *		���´��ڵ�˫����
		 *
		 *	ע�⣺
		 *		�����ڴ��������ڵ��ô˺�������� hiex::FlushDrawing
		 * </pre>
		*/
		void FlushDrawing(RECT rct = { 0 });

		bool BeginTask();
		void EndTask(bool flush = true);
		bool IsInTask();

		bool IsSizeChanged();

		void CreateTray(LPCTSTR lpszTrayName);
		void DeleteTray();
		void SetTrayMenu(HMENU hMenu);
		void SetTrayMenuProcFunc(void(*pFunc)(UINT));

		void PreSetStyle(long lStyle);
		void PreSetStyleEx(long lStyleEx);
		void PreSetPos(int x, int y);
		void PreSetShowState(int nCmdShow);

		long GetStyle();
		int SetStyle(long lNewStyle);
		long GetExStyle();
		int	SetExStyle(long lNewExStyle);

		POINT GetPos();

		/**
		 * @brief ��ȡ�������ڵĴ�С
		*/
		SIZE GetWindowSize();

		/**
		 * @brief ��ȡ�������ڵĿ��
		*/
		int GetWindowWidth();

		/**
		 * @brief ��ȡ�������ڵĸ߶�
		*/
		int GetWindowHeight();

		/**
		 * @brief ��ȡ�ͻ������
		*/
		int GetClientWidth();

		/**
		 * @brief ��ȡ�ͻ����߶�
		*/
		int GetClientHeight();

		void Move(int x, int y);
		void MoveRel(int dx, int dy);

		void Resize(int w, int h);
		void SetTransparent(bool enable, int alpha = 0xFF);

		void SetTitle(LPCTSTR lpszTitle);

		/**
		 * @brief �жϴ˴����Ƿ�Ϊ�û�����ʹ�õĴ���
		*/
		bool IsForegroundWindow();

		ExMessage Get_Message(BYTE filter = -1);
		void Get_Message(ExMessage* msg, BYTE filter = -1);
		bool Peek_Message(ExMessage* msg, BYTE filter = -1, bool removemsg = true);
		void Flush_Message(BYTE filter = -1);
	};

	////////////****** ������غ��� ******////////////

	/**
	 * @brief <pre>
	 *		���� Win32 ��ͼ���ڣ�����ԭ�� EasyX ���ڣ�
	 *
	 *	��ע��
	 *		����Ĭ��֧��˫����Ϣ��������С��ʹ�� EnableResizing �������Ƿ���Ե�����С��
	 * </pre>
	 *
	 * @param[in] w					���ڿ�
	 * @param[in] h					���ڸ�
	 * @param[in] flag				������ʽ��EW_ ϵ�к꣬Ĭ��Ϊ EW_NORMAL��
	 * @param[in] lpszWndTitle		���ڱ���
	 * @param[in] WindowProcess		���ڹ��̺���
	 * @param[in] hParent			�����ھ��
	 * @return �����Ĵ��ھ��
	 *
	 * @bug
	 *		�����������������ͼ���ڣ������Ҫ�����ʵ������ʱ��������ܵ���δ֪���⡣
	 *
	 * @par ���ڹ��̺����淶 <pre>
	 *
	 *		����ǩ����
	 *			LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	 *
	 *		ע�����
	 *			��Ҫ��Ĭ�Ϸ�ʽ������Ϣ���򷵻� HIWINDOW_DEFAULT_PROC ���ɣ���Ҫʹ�� DefWindowProc ������
	 *
	 *		ʾ��������
	 * @code
				LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
				{
					switch (msg)
					{
					case WM_PAINT:
						BEGIN_TASK_WND(hWnd);
						circle(100, 100, 70);
						END_TASK();
						break;

					case WM_CLOSE:
						DestroyWindow(hWnd);
						break;

					case WM_DESTROY:
						// TODO: �ڴ˴��ͷ�������ڴ�
						PostQuitMessage(0);
						break;

					default:
						return HIWINDOW_DEFAULT_PROC;	// ��ʶʹ��Ĭ����Ϣ��������������

						// ��Ҫ��Ĭ�Ϸ�ʽ��������ʹ�ô����
						//return DefWindowProc(hWnd, msg, wParam, lParam);
						break;
					}

					return 0;
				}
	 * @endcode
	 * </pre>
	*/
	HWND initgraph_win32(
		int w = 640,
		int h = 480,
		int flag = EW_NORMAL,
		LPCTSTR lpszWndTitle = _T(""),
		WNDPROC WindowProcess = nullptr,
		HWND hParent = nullptr
	);

	bool init_console();
	bool hide_console();
	bool close_console();

	/**
	 * @brief �ر�ĳһ��ͼ����
	 * @param[in] hWnd ���ھ����Ϊ�մ������л�ͼ���ڣ�
	*/
	void closegraph_win32(HWND hWnd = nullptr);

	/**
	 * @brief ����ĳ���ڵĹ��̺���
	 * @param[in] hWnd ���ھ����Ϊ�ձ�ʶ��ǰ����ڣ�
	 * @param[in] WindowProcess �µĹ��̺���
	*/
	void SetWndProcFunc(HWND hWnd, WNDPROC WindowProcess);

	/**
	 * @brief �õ���ǰ���ͼ���ڵľ��
	*/
	HWND GetHWnd_win32();

	/**
	 * @brief ��ʼ�����ڽ����󣬿����ô˺��������ȴ�Ŀ�괰�ڱ��رգ�Ȼ��������
	 * @param[in] hWnd Ŀ�괰�ڣ�Ϊ�մ������д��ڣ�
	*/
	void init_end(HWND hWnd = nullptr);

	/**
	 * @brief ���ã������ڶ�������ʱ���Զ��˳�����
	*/
	void AutoExit();

	/**
	 * @brief �Ƿ񻹴���δ���ٵĻ�ͼ����
	*/
	bool IsAnyWindow();

	/**
	 * @brief �ж�һ�����Ƿ񻹴��ڣ�δ���رգ�
	 * @param[in] hWnd ���ھ����Ϊ�ձ�ʾ��ǰ����ڣ�
	 * @return �Ƿ����
	*/
	bool IsAliveWindow(HWND hWnd = nullptr);

	/**
	 * @brief ��ȡĳ���ڵ�ͼ��ָ��
	 * @param[in] hWnd ���ھ����Ϊ�ձ�ʾ��ǰ����ڣ�
	 * @return ������ͼ��ָ��
	*/
	IMAGE* GetWindowImage(HWND hWnd = nullptr);

	/**
	 * @brief ��ȡ���ڻ���ָ��
	 * @param[in] hWnd ���ھ����Ϊ�ձ�ʾ��ǰ����ڣ�
	 * @return ����ָ�룬��δ�󶨻����򷵻ؿ�
	*/
	Canvas* GetWindowCanvas(HWND hWnd = nullptr);

	/**
	 * @brief <pre>
	 *		�󶨴��ڻ���ָ��
	 *
	 *	��ע��
	 *		�󶨺�ʹ�û�����ͼʱ���Զ��������������û��������������Զ�ˢ����Ļ
	 * </pre>
	 *
	 * @param[in] pCanvas ����ָ��
	 * @param[in] hWnd ���ھ����Ϊ�ձ�ʾ��ǰ����ڣ�
	*/
	void BindWindowCanvas(Canvas* pCanvas, HWND hWnd = nullptr);

	/**
	 * @brief �õ���ǰ��ͼ���ڵ���ϸ��Ϣ
	*/
	EasyWindow GetWorkingWindow();

	/**
	 * @brief �ȴ���ǰ������ɲ����û����
	 * @param[in] hWnd �µĻ���ھ��
	 * @return �Ƿ����óɹ�
	*/
	bool SetWorkingWindow(HWND hWnd);

	/**
	 * @brief ���ü��ٻ��������������ص�
	 * @warning �˼���Ч��������ģ�����Ч�������������ص��������
	 * @param[in] nSkipPixels ���������ص���Ŀ
	 * @param[in] hWnd ���ھ����Ϊ�ձ�ʾ��ǰ����ڣ�
	*/
	void QuickDraw(UINT nSkipPixels, HWND hWnd = nullptr);

	/**
	 * @brief ��ȡȫ�ֻ���ģʽ
	*/
	DrawMode GetDrawMode();

	/**
	 * @brief ����ȫ�ֻ���ģʽ
	 * @param[in] mode ȫ�ֻ���ģʽ
	*/
	void SetDrawMode(DrawMode mode);

	/**
	 * @brief ֪ͨ�ػ��ͼ���ڣ��� WM_PAINT ��Ϣ�ڻ�ͼ����Ҫʹ�ô˺�����
	 * @param[in] hWnd Ҫ�ػ�Ĵ���
	*/
	void RedrawWindow(HWND hWnd = nullptr);

	/**
	 * @brief <pre>
	 *		���µ�ǰ����ڵ�˫����
	 *
	 *	ע�⣺
	 *		���ڰ�ȫ�����⣬�����ڴ��������ڵ��ô˺��������򲻻����˫���塣
	 *
	 *	��ע��
	 *		��Ҫ�ػ洰����ʹ�� RedrawWindow
	 *
	 *	ʾ����
	 * @code
			BEGIN_TASK();
			hiex::FlushDrawing({ 200,200,300,300 });
			END_TASK(false);	// ע�⣬��������ʱ��� false ��ʾ������˫���壬��Ϊ�����Ѿ����¹���
			REDRAW_WINDOW();
	 * @endcode
	 * </pre>
	 *
	 * @param[in] rct	˫��������������궼Ϊ 0 ��ʾȫ������
	*/
	void FlushDrawing(RECT rct = { 0 });

	/**
	 * @brief <pre>
	 *		�Ƿ������Զ�ˢ��˫����
	 *
	 *	��ע��
	 *		Ĭ����������Զ�ˢ��˫����ģ���ÿ�ν�����������ʱ��EndTask ����ݴ���Ĳ�����
	 *		����Ҫ��Ҫ��ǡ���Ҫˢ��˫���塱����Ǻ󣬴��ڽ�������һ�������ػ���Ϣ��ʱ��ˢ��˫���塣
	 *
	 *		���ǣ���Ƶ���ػ������£����ڶ��߳�Э�����⣬�Զ�ˢ�µ�Ч�ʿ��ܻ��͡�
	 *		��������Թر��Զ�ˢ��˫���壬��Ӧ�أ�����Ҫʹ�� FlushDrawing �����ֶ�ˢ��˫���塣
	 * </pre>
	*/
	void EnableAutoFlush(bool enable);

	/**
	 * @brief <pre>
	 *		Ϊ��ǰ�������������
	 *
	 *	��ע��
	 *		���� EasyX �������л�ͼ���ȡ��Ϣʱ����Ӧ����������
	 * </pre>
	 *
	 * @return �Ƿ������ɹ���������������Ҳ���� true��
	*/
	bool BeginTask();

	/**
	 * @brief ��ֹ��ǰ��������
	 * @param[in] flush �Ƿ�����Ҫ����˫���壨�������Զ�ˢ�´��ڣ�
	*/
	void EndTask(bool flush = true);

	/**
	 * @brief <pre>
	 *		�ж�ĳ�����Ƿ���������
	 *
	 *	��ע��
	 *		���������Ƕ���ʽ�ģ�ֻ�л���ڿ��ܴ��������С�
	 *		�������봰�ڲ��ǻ���ڣ���ֱ�ӷ��� false��
	 * </pre>
	 *
	 * @param[in] hWnd ���ھ����Ϊ�ձ�ʾ��ǰ����ڣ�
	 * @return �Ƿ���������
	*/
	bool IsInTask(HWND hWnd = nullptr);

	/**
	 * @brief �����ȴ�ĳ�����������
	 * @param[in] hWnd ���ھ����Ϊ�ձ�ʾ��ǰ����ڣ�
	*/
	void WaitForTask(HWND hWnd = nullptr);

	/**
	 * @brief �ж�ĳ���ڵĴ�С�Ƿ�ı�
	 * @param[in] hWnd ���ھ����Ϊ�ձ�ʾ��ǰ����ڣ�
	 * @return ���ڵĴ�С�Ƿ�ı�
	*/
	bool IsWindowSizeChanged(HWND hWnd = nullptr);

	/**
	 * @brief <pre>
	 *		Ϊ���ڴ���һ������
	 *
	 *	ע�⣺
	 *		�� HiEasyX �У�ÿ�����ڽ����ȶ�ռ��һ������
	 * </pre>
	 *
	 * @param[in] lpszTrayName ������ʾ�ı�
	 * @param[in] hWnd ���ھ����Ϊ�ձ�ʾ��ǰ����ڣ�
	*/
	void CreateTray(LPCTSTR lpszTrayName, HWND hWnd = nullptr);

	/**
	 * @brief ɾ��ĳ���ڵ�����
	 * @param[in] hWnd ���ھ����Ϊ�ձ�ʾ��ǰ����ڣ�
	*/
	void DeleteTray(HWND hWnd = nullptr);

	/**
	 * @brief �������̲˵����������κ�ʱ�����ã�
	 * @param[in] hMenu	�˵�
	 * @param[in] hWnd	���ھ����Ϊ�ձ�ʾ��ǰ����ڣ�
	*/
	void SetTrayMenu(HMENU hMenu, HWND hWnd = nullptr);

	/**
	 * @brief �������̲˵���Ϣ������
	 * @param[in] pFunc	��Ϣ������
	 * @param[in] hWnd	���ھ����Ϊ�ձ�ʾ��ǰ����ڣ�
	*/
	void SetTrayMenuProcFunc(void(*pFunc)(UINT), HWND hWnd = nullptr);

	/**
	 * @brief ��ȡ�Զ������ͼ�������״̬
	*/
	bool GetCustomIconState();

	/**
	 * @brief <pre>
	 *		ʹ���Զ���ͼ����Դ��Ϊ����ͼ��
	 *
	 *	��ע��
	 *		�����ڵ�һ�δ�������ǰ�͵��øú���������Ч��
	 *		ʹ�� MAKEINTRESOURCE ����Խ���Դ ID תΪ�ַ�����
	 * </pre>
	 *
	 * @param[in] lpszIcon		��ͼ����Դ
	 * @param[in] lpszIconSm	Сͼ����Դ
	*/
	void SetCustomIcon(LPCTSTR lpszIcon, LPCTSTR lpszIconSm);

	/**
	 * @brief <pre>
	 *		�ڴ�������ǰ���ô�����ʽ�����Դ˲������׸��´�����Ч
	 *
	 *	ע�⣺
	 *		�´��ڵ�������ͨ��ʽ��������ǰ��ʽ����
	 * </pre>
	 *
	 * @param[in] lStyle ����ʽ
	*/
	void PreSetWindowStyle(long lStyle);

	/**
	 * @brief <pre>
	 *		�ڴ�������ǰ���ô�����չ��ʽ�����Դ˲������׸��´�����Ч
	 *
	 *	ע�⣺
	 *		�´��ڵ�������չ��ʽ��������ǰ��ʽ����
	 * </pre>
	 *
	 * @param[in] lStyleEx ����ʽ
	*/
	void PreSetWindowStyleEx(long lStyleEx);

	/**
	 * @brief �ڴ�������ǰ���ô���λ�ã����Դ˲������׸��´�����Ч
	 * @param[in] x	λ��
	 * @param[in] y	λ��
	*/
	void PreSetWindowPos(int x, int y);

	/**
	 * @brief �ڴ�������ǰ���ô�����ʾ״̬�����Դ˲������׸��´�����Ч
	 * @param[in] nCmdShow ��ʾ״̬���� ShowWindow �÷�һ�£�
	*/
	void PreSetWindowShowState(int nCmdShow);

	/**
	 * @brief ����ĳ������ʽ
	 * @param[in] lNewStyle ����ʽ
	 * @param[in] hWnd		���ھ����Ϊ�մ���ǰ����ڣ�
	 * @return ������һ�����õĴ�����ʽ��ʧ�ܷ��� 0
	*/
	int SetWindowStyle(long lNewStyle, HWND hWnd = nullptr);

	/**
	 * @brief ����ĳ������չ��ʽ
	 * @param[in] lNewExStyle	����ʽ
	 * @param[in] hWnd 			���ھ����Ϊ�մ���ǰ����ڣ�
	 * @return ������һ�����õĴ�����ʽ��ʧ�ܷ��� 0
	*/
	int SetWindowExStyle(long lNewExStyle, HWND hWnd = nullptr);

	/**
	 * @brief ��ȡ����λ��
	 * @param[in] hWnd ���ھ����Ϊ�մ���ǰ����ڣ�
	 * @return ����λ��
	*/
	POINT GetWindowPos(HWND hWnd = nullptr);

	/**
	 * @brief ��ȡ���ڴ�С
	 * @param[in] hWnd ���ھ����Ϊ�մ���ǰ����ڣ�
	 * @return ���ڴ�С
	*/
	SIZE GetWindowSize(HWND hWnd = nullptr);

	/**
	 * @brief �ƶ�����
	 * @param[in] x		λ��
	 * @param[in] y		λ��
	 * @param[in] hWnd	���ھ����Ϊ�մ���ǰ����ڣ�
	*/
	void MoveWindow(int x, int y, HWND hWnd = nullptr);

	/**
	 * @brief ����ƶ�����
	 * @param[in] dx	���λ��
	 * @param[in] dy	���λ��
	 * @param[in] hWnd	���ھ����Ϊ�մ���ǰ����ڣ�
	*/
	void MoveWindowRel(int dx, int dy, HWND hWnd = nullptr);

	/**
	 * @brief ���贰�ڴ�С
	 * @param[in] w		���ڿ�
	 * @param[in] h		���ڸ�
	 * @param[in] hWnd	���ھ����Ϊ�մ���ǰ����ڣ�
	*/
	void ResizeWindow(int w, int h, HWND hWnd = nullptr);

	/**
	 * @brief ���ô��ڱ����ı�
	 * @param[in] lpszTitle		�µĴ��ڱ���
	 * @param[in] hWnd			���ھ����Ϊ�մ���ǰ����ڣ�
	*/
	void SetWindowTitle(LPCTSTR lpszTitle, HWND hWnd = nullptr);

	////////////****** ��Ϣ��غ��� ******////////////

	//// ExMessage ʽ����

	/**
	 * @brief �����ȴ���ֱ����ȡ��һ������Ϣ
	 * @param[in] filter	��Ϣɸѡ��ʽ
	 * @param[in] hWnd		���ھ����Ϊ�մ���ǰ����ڣ�
	 * @return ��ȡ������Ϣ
	*/
	ExMessage getmessage_win32(BYTE filter = -1, HWND hWnd = nullptr);

	/**
	 * @brief �����ȴ���ֱ����ȡ��һ������Ϣ
	 * @param[out] msg	���ػ�ȡ������Ϣ
	 * @param[in] filter	��Ϣɸѡ��ʽ
	 * @param[in] hWnd		���ھ����Ϊ�մ���ǰ����ڣ�
	*/
	void getmessage_win32(ExMessage* msg, BYTE filter = -1, HWND hWnd = nullptr);

	/**
	 * @brief ��ȡһ����Ϣ�����������Ƿ��ȡ�ɹ�
	 * @param[out] msg	���ػ�ȡ������Ϣ
	 * @param[in] filter	��Ϣɸѡ��ʽ
	 * @param[in] removemsg	��ȡ��Ϣ���Ƿ����Ƴ�
	 * @param[in] hWnd		���ھ����Ϊ�մ���ǰ����ڣ�
	 * @return �Ƿ��ȡ����Ϣ
	*/
	bool peekmessage_win32(ExMessage* msg, BYTE filter = -1, bool removemsg = true, HWND hWnd = nullptr);

	/**
	 * @brief ���������Ϣ��¼
	 * @param[in] filter	��Ϣɸѡ��ʽ
	 * @param[in] hWnd		���ھ����Ϊ�մ���ǰ����ڣ�
	*/
	void flushmessage_win32(BYTE filter = -1, HWND hWnd = nullptr);

	//// MOUSEMSG ʽ���������ݣ�

	/**
	 * @brief ����Ƿ���������Ϣ
	 * @param[in] hWnd ���ھ����Ϊ�մ���ǰ����ڣ�
	 * @return �Ƿ���������Ϣ
	*/
	bool MouseHit_win32(HWND hWnd = nullptr);

	/**
	 * @brief �����ȴ���ֱ����ȡ��һ���µ������Ϣ
	 * @param[in] hWnd ���ھ����Ϊ�մ���ǰ����ڣ�
	 * @return �����Ϣ
	*/
	MOUSEMSG GetMouseMsg_win32(HWND hWnd = nullptr);

	/**
	 * @brief ��ȡһ���µ������Ϣ�����������Ƿ��ȡ�ɹ�
	 * @param[out] pMsg		���ػ�ȡ������Ϣ
	 * @param[in] bRemoveMsg	��ȡ��Ϣ���Ƿ����Ƴ�
	 * @param[in] hWnd			���ھ����Ϊ�մ���ǰ����ڣ�
	 * @return �Ƿ��ȡ����Ϣ
	*/
	bool PeekMouseMsg_win32(MOUSEMSG* pMsg, bool bRemoveMsg = true, HWND hWnd = nullptr);

	/**
	 * @brief ��������Ϣ
	 * @param[in] hWnd ���ھ����Ϊ�մ���ǰ����ڣ�
	*/
	void FlushMouseMsgBuffer_win32(HWND hWnd = nullptr);

	//// ת��

	/**
	 * @brief MOUSEMSG ת ExMessage
	 * @param[in] msg MOUSEMSG ��Ϣ
	 * @return ExMessage ��Ϣ
	*/
	ExMessage To_ExMessage(MOUSEMSG msg);

	/**
	 * @brief <pre>
	 *		ExMessage ת MOUSEMSG
	 *
	 *	��ע��
	 *		ExMessage ��Ϣ���������� EM_MOUSE���򷵻ؿ�
	 * </pre>
	 *
	 * @param[in] msgEx ExMessage ��Ϣ
	 * @return MOUSEMSG ��Ϣ
	*/
	MOUSEMSG To_MouseMsg(ExMessage msgEx);
}

////////////****** ����ָ��궨�� ******////////////

// ����һ�Σ���ͼ�����񣨻��Ƶ���ǰ��ͼ���ڣ�
#define BEGIN_TASK()\
	if (HiEasyX::SetWorkingWindow(nullptr))\
	{\
		if (HiEasyX::BeginTask())\
		{(0)	/* �˴�ǿ��Ҫ��ӷֺ� */

// ����һ�Σ���ͼ������ָ��Ŀ���ͼ���ڣ�
#define BEGIN_TASK_WND(hWnd)\
	/* ���ù�������ʱ���Զ��ȴ����� */\
	if (HiEasyX::SetWorkingWindow(hWnd))\
	{\
		if (HiEasyX::BeginTask())\
		{(0)

// ����һ�Σ���ͼ�����񣬲������ͼ���棨���� BEGIN_TASK ���ã�
#define END_TASK(...)\
			HiEasyX::EndTask(__VA_ARGS__);\
		}\
	}(0)

// Ҫ�󴰿��ػ�
#define REDRAW_WINDOW(...)		HiEasyX::RedrawWindow(__VA_ARGS__)

////////////****** ������ʽ�궨�� ******////////////

// ����ĳ����
// �˺�Ϊģ���
#define EnableSomeStyle(hwnd, state, exstyle, enable_style, disable_style)\
			(exstyle ?\
				(state ?\
					HiEasyX::SetWindowExStyle(\
						(long)GetWindowExStyle(hwnd ? hwnd : HiEasyX::GetHWnd_win32()) | (enable_style),\
						hwnd\
					) :\
					HiEasyX::SetWindowExStyle(\
						(long)GetWindowExStyle(hwnd ? hwnd : HiEasyX::GetHWnd_win32()) & (disable_style),\
						hwnd\
					)\
				) :\
				(state ?\
					HiEasyX::SetWindowStyle(\
						(long)GetWindowStyle(hwnd ? hwnd : HiEasyX::GetHWnd_win32()) | (enable_style),\
						hwnd\
					) :\
					HiEasyX::SetWindowStyle(\
						(long)GetWindowStyle(hwnd ? hwnd : HiEasyX::GetHWnd_win32()) & (disable_style),\
						hwnd\
					)\
				)\
			)

// �Ƿ�����ĳ���ڸı��С
#define EnableResizing(hwnd, state)\
			EnableSomeStyle(hwnd, state, false, WS_SIZEBOX | WS_MAXIMIZEBOX, ~WS_SIZEBOX & ~WS_MAXIMIZEBOX)

#define DisableResizing(hwnd, state)	EnableResizing(hwnd, !state)

// �Ƿ�����ĳ���ڵ�ϵͳ��������ť
#define EnableSystemMenu(hwnd, state)\
			EnableSomeStyle(hwnd, state, false, WS_SYSMENU, ~WS_SYSMENU)

#define DisableSystemMenu(hwnd, state)	EnableSystemMenu(hwnd, !state)

// �Ƿ����õ�ǰ���ڵĹ�������ʽ
#define EnableToolWindowStyle(hwnd, state)\
		EnableSomeStyle(hwnd, state, true, WS_EX_TOOLWINDOW, ~WS_EX_TOOLWINDOW)

#define DisableToolWindowStyle(hwnd, state)	EnableToolWindowStyle(hwnd, !state)

////////////****** ������Ϣ�궨�� ******////////////

// �ж�ȫ�ְ���״̬
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)

// �жϵ�ǰ������Ƿ���ܵ�ĳ������Ϣ
#define KEY_DOWN_WND(VK_NONAME) (GetForegroundWindow() == HiEasyX::GetHWnd_win32() && KEY_DOWN(VK_NONAME))

////////////****** EasyX ԭ�������ĺ��滻 ******////////////

// ��ʹ�� EasyX ԭ�������������ڣ���رմ���ʱ�Զ��˳�����
#define initgraph(...)			HiEasyX::initgraph_win32(__VA_ARGS__);\
								HiEasyX::AutoExit()

#define closegraph				HiEasyX::closegraph_win32

// Ĭ��ʹ��˫���壬�� BeginBatchDraw ������
#define BeginBatchDraw()
#define FlushBatchDraw()		REDRAW_WINDOW()
#define EndBatchDraw()			REDRAW_WINDOW()

#define GetHWnd					HiEasyX::GetHWnd_win32

#define getmessage				HiEasyX::getmessage_win32
#define peekmessage				HiEasyX::peekmessage_win32
#define flushmessage			HiEasyX::flushmessage_win32

#define MouseHit				HiEasyX::MouseHit_win32
#define GetMouseMsg				HiEasyX::GetMouseMsg_win32
#define PeekMouseMsg			HiEasyX::PeekMouseMsg_win32
#define FlushMouseMsgBuffer		HiEasyX::FlushMouseMsgBuffer_win32

////////////****** �Ѿ������ĺ� ******////////////

// �˺��Ѿ����ã���ʹ�� REDRAW_WINDOW ��
#define FLUSH_DRAW() (This_macro_is_deprecated___Please_use_macro__REDRAW_WINDOW__)
