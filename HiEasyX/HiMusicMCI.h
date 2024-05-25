/**
 * @file	HiMusicMCI.h
 * @brief	HiEasyX �������ģ��
 * @author	��Զ�Ĳ�� <2237505658@qq.com>, huidong���޸ģ�
*/

#pragma once

#include <Windows.h>

namespace HiEasyX
{
	/**
	 * @brief <pre>
	 *		MusicMCI�����ֲ��Ų����㣩
	 *		֧�ֲ��š���ͣ��������������ȡ����ʱ��Ȳ���
	 * </pre>
	*/
	class MusicMCI
	{
	private:
		MCIDEVICEID nDeviceID;									///< �豸ID

	public:
		MusicMCI()noexcept;										///< Ĭ�Ϲ��캯��
		virtual ~MusicMCI();									///< ����������
		bool open(LPCTSTR music)noexcept;						///< ������
		bool play()noexcept;									///< ��������
		bool pause()noexcept;									///< ��ͣ����
		bool stop()noexcept;									///< ֹͣ����
		bool close()noexcept;									///< �ر�����
		bool getCurrentTime(DWORD& pos)noexcept;				///< ��ȡ��ǰ����ʱ��
		bool getTotalTime(DWORD& time)noexcept;					///< ��ȡ������ʱ��
		bool setVolume(size_t volume)noexcept;					///< ����������С
		bool setStartTime(size_t start)noexcept;				///< ���ò���λ��
	};
};
