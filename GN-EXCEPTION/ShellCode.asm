EXTERN MyCallbackRoutine:PROC
EXTERN __imp_RtlCaptureContext:dq

.CODE
	MyCallbackEntry PROC
		mov gs:[2E0H], rsp				;Win10 TEB InstrumentationCallbackPreviousSp (������̲߳�����ַ)
		mov gs:[2D8H], r10				;Win10 TEB InstrumentationCallbackPreviousPc (syscall �ķ��ص�ַ)

		mov r10, rcx					;����rcx
		sub rsp, 4D0H					;Context�ṹ��С
		and rsp, -10H					;align rsp
		mov rcx, rsp					;parameters are fun
		call __imp_RtlCaptureContext	;�����߳�Context������

		sub rsp, 20H					;����ջ�ռ�
		call MyCallbackRoutine			;�������ǵĺ���

		int 3							;��Ӧ��ִ�е�����
	MyCallbackEntry ENDP
END

