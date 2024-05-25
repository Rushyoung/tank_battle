/**
 * @file	Container.h
 * @brief	HiEasyX ��Ļ�������
 * @author	huidong
*/

#pragma once

#include <WinSock2.h>
#include <Windows.h>

namespace HiEasyX
{
	/**
	 * @brief ��������
	*/
	class Container
	{
	protected:

		RECT m_rct = { 0 };					///< ��������

	public:

		Container();

		virtual ~Container();

		/**
		 * @brief ��Ӧ����������Ϣ
		 * @param[in] rctOld �ɵ�����
		*/
		virtual void UpdateRect(RECT rctOld);

		RECT GetRect() const { return m_rct; }

		/**
		 * @brief ����λ�úͿ��
		 * @param[in] x	λ��
		 * @param[in] y	λ��
		 * @param[in] w	��
		 * @param[in] h	��
		*/
		void SetRect(int x, int y, int w, int h);

		/**
		 * @brief ���þ�������
		 * @param[in] rct ����
		*/
		void SetRect(RECT rct);

		POINT GetPos() const { return { m_rct.left,m_rct.top }; }

		int GetX() const { return m_rct.left; }

		int GetY() const { return m_rct.top; }

		void SetPos(int x, int y);

		void SetPos(POINT pt);

		void Move(int x, int y) { SetPos(x, y); }

		void MoveRel(int dx, int dy);

		int GetWidth() const { return m_rct.right - m_rct.left; }

		void SetWidth(int w);

		int GetHeight() const { return m_rct.bottom - m_rct.top; };

		void SetHeight(int h);

		void Resize(int w, int h);
	};
}

