#pragma once

//constexpr int byte_length = 12;
//
//class inline_hook
//{
//private:
//	using uchar = unsigned char;
//	using dword = DWORD;
//	BYTE m_original_byte[byte_length];	//ԭʼ�������ָ��
//	BYTE m_self_byte[byte_length];		//�ҵĻ��ָ��
//
//	__int64 m_original_address;  //ԭʼ������ַ
//	__int64 m_self_address;   //�ҵĺ�����ַ
//	BOOL m_IsDrv;
//
//	dword motify_memory_attributes(__int64 address, dword attributes = PAGE_EXECUTE_READWRITE)
//	{
//		dword old_attributes;
//		bool a = VirtualProtect(reinterpret_cast<void*>(address), byte_length, attributes, &old_attributes);
//		return old_attributes;
//	}
//
//public:
//	inline_hook(__int64 original_address, __int64 self_address, BOOL IsDrv) : m_original_address(original_address), m_self_address(self_address), m_IsDrv(IsDrv)
//	{
//		//���� jmp ���ָ�� {0x48 ,0xB8 , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x50 ,0xC3}
//		m_self_byte[0] = 0x48; m_self_byte[1] = 0xB8; m_self_byte[2] = 0x00; m_self_byte[3] = 0x00; 
//		m_self_byte[4] = 0x00;  m_self_byte[5] = 0x00; m_self_byte[6] = 0x00; m_self_byte[7] = 0x00; 
//		m_self_byte[8] = 0x00;  m_self_byte[9] = 0x00; m_self_byte[10] = 0x50; m_self_byte[11] = 0xC3;
//
//		//������ת��������ָ��
//		*(__int64*)(m_self_byte + 2) = (__int64)self_address;
//		memcpy((__int64*)m_original_byte, (__int64*)original_address, 12);//���溯��ǰ12���ֽ�
//
//		//�޸��ڴ����� ��ֹԭ���ĵ�ַ���ɶ�
//		dword attributes = motify_memory_attributes(original_address);
//		//����ԭ����ַ��byte
//		memcpy(&m_original_byte, reinterpret_cast<void *>(original_address), byte_length);
//
//		motify_memory_attributes(original_address, attributes);
//	}
//
//	void motify_address()
//	{
//		dword attributes = motify_memory_attributes(m_original_address);
//		if (m_IsDrv)
//		{
//
//		}
//		else
//		{
//			memcpy((__int64*)m_original_address, (__int64*)(m_self_byte), 12);
//			//memcpy(reinterpret_cast<void*>(m_original_address), m_self_byte, byte_length);
//		}
//		//д�����ǹ����byteʵ��hook
//		motify_memory_attributes(m_original_address, attributes);
//	}
//
//	void restore_address()
//	{
//		dword attributes = motify_memory_attributes(m_original_address);
//		memcpy((__int64*)m_original_address, (__int64*)(m_original_byte), 12);
//		//memcpy(reinterpret_cast<void*>(m_original_address), m_original_byte, byte_length);
//		motify_memory_attributes(m_original_address, attributes);
//	}
//};

/////////////////////////////////////////////////////////////////
constexpr int byte_length = 14;

class inline_hook
{
private:
	using uchar = unsigned char;
	using dword = DWORD;
	BYTE m_original_byte[byte_length];	//ԭʼ�������ָ��
	BYTE m_self_byte[byte_length];		//�ҵĻ��ָ��

	__int64 m_original_address;  //ԭʼ������ַ
	__int64 m_self_address;   //�ҵĺ�����ַ
	BOOL m_IsDrv;

	dword motify_memory_attributes(__int64 address, dword attributes = PAGE_EXECUTE_READWRITE)
	{
		dword old_attributes;
		bool a = VirtualProtect(reinterpret_cast<void*>(address), byte_length, attributes, &old_attributes);
		return old_attributes;
	}

public:
	inline_hook(__int64 original_address, __int64 self_address, BOOL IsDrv) : m_original_address(original_address), m_self_address(self_address), m_IsDrv(IsDrv)
	{
		m_self_byte[0] = 0xFF;	m_self_byte[1] = 0x25;	m_self_byte[2] = 0x00;	m_self_byte[3] = 0x00;
		m_self_byte[4] = 0x00;	m_self_byte[5] = 0x00;	m_self_byte[6] = 0x00;	m_self_byte[7] = 0x00;
		m_self_byte[8] = 0x00;	m_self_byte[9] = 0x00;	m_self_byte[10] = 0x00; m_self_byte[11] = 0x00;
		m_self_byte[12] = 0x00; m_self_byte[13] = 0x00;

		//������ת��������ָ��
		*(__int64*)(m_self_byte + 6) = (__int64)self_address;

		//�޸��ڴ����� ��ֹԭ���ĵ�ַ���ɶ�
		dword attributes = motify_memory_attributes(original_address);
		//����ԭ����ַ��byte
		memcpy(&m_original_byte, reinterpret_cast<void*>(original_address), byte_length);
		motify_memory_attributes(original_address, attributes);
	}

	void motify_address()
	{
		dword attributes = motify_memory_attributes(m_original_address);
		if (!m_IsDrv)
			memcpy((__int64*)m_original_address, (__int64*)(m_self_byte), byte_length);
		else
		{
			//if (!Drv.WriteBytes(m_original_address, m_self_byte, byte_length))
			//{
			//	printf("������дʧ�ܣ�\n");
			//	memcpy((__int64*)m_original_address, (__int64*)(m_self_byte), byte_length);
			//}
		}
			
		//д�����ǹ����byteʵ��hook
		motify_memory_attributes(m_original_address, attributes);
	}

	void restore_address()
	{
		dword attributes = motify_memory_attributes(m_original_address);

		if (!m_IsDrv)
			memcpy((__int64*)m_original_address, (__int64*)(m_original_byte), byte_length);
		else
		{
			//if (!Drv.WriteBytes(m_original_address, m_original_byte, byte_length))
			//	memcpy((__int64*)m_original_address, (__int64*)(m_original_byte), byte_length);
		}

		motify_memory_attributes(m_original_address, attributes);
	}
};

