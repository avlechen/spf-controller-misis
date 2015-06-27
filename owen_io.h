#ifndef OWEN_IO_H
#define OWEN_IO_H

//  (�) ���� 2003-2015
//
// ������������ ���� ��� ���������� OWEN_IO
// �������� �������� �������� � ������� ����������
//
// ���������� ������������� ��� ������/������ ���������� ��������� �� ����
// � ����������� RS485.
//
// ������ ���� �� �������� "�������� ��������� ������ ����� ���� � ��������� ����"
// ��������� �� ������ http://www.owen.ru/support/40691149
//

//
// ����� �������� ��� ������� OpenPort()
//

// ����������� ��� ���������������� ������ COMxx=(xx-1)
#define COM_1           0
#define COM_2           1
#define COM_3           2
#define COM_4           3
#define COM_5           4
#define COM_6           5
#define COM_7           6
#define COM_8           7

// ����������� ��������
#define spd_2400        0
#define spd_4800        1
#define spd_9600        2
#define spd_14400       3
#define spd_19200       4
#define spd_28800       5
#define spd_38800       6
#define spd_57600       7
#define spd_115200      8

// ����������� ��������
// ���
#define prty_NONE       0
// ���
#define prty_EVEN       1
// �����
#define prty_ODD        2

// ����������� ����� ����� ������
#define databits_7      0
#define databits_8      1

// ����������� ����� �������� �����
#define stopbit_1       0
#define stopbit_2       2

// ��� ��������������� ���������� RS485
// ������������������, ���������� �������� RTS (AC3)
#define RS485CONV_MANUAL        0
// �������������� (��3-�, ��4, ��2-�)
#define RS485CONV_AUTO          1
// ������������������, ���������� �������� DTR
#define RS485CONV_MANUAL_DTR    2

// ����� ������
// 8 ���
#define ADRTYPE_8BIT            0
// 11 ���
#define ADRTYPE_11BIT           1

// ����� ������ ����������
#define OWENIO_API_OLD          0
#define OWENIO_API_NEW          1

// ����� ��������� ������� ������, ���� ������ �� ��������
#define MAX_RETRIES_DEFAULT	1

// ������������ ����� ��������� ������� ������,
// ������� ����� ���������� �������� SetMaxRetriesGlobal()
#define MAX_RETRIES_LIMIT	20

// ������������ ����� ����� ��������� ��������� ����
#define MAX_PARAM_NAME_LENGTH	32

// ������ ������ ��� ������� LastErrToStr()
#define LASTERRTOSTR_BUFFER_SIZE 300

// ������ ������ ��� ������� OwenIO()
#define OWENIO_DATA_BUFFER_SIZE 15

//
// ���������� ����� � �������. ����� ������� SetDbgIndication().
//

// �������� ������������ � ���������� ASCII-�����
#define SHOW_FRAMES 1
#define SHOW_PACKETS SHOW_FRAMES

// �������� ������������ �������� �����
#define SHOW_SEND_DATA 2

// �������� �������� �������� �����
#define SHOW_RECV_DATA 4
#define SHOW_CONTAINS	SHOW_RECV_DATA

// �������� ���������� �� ������� ������
#define SHOW_RECV_ERRORS	16
#define SHOW_RCV_ERRORS	SHOW_RECV_ERRORS

// �������� ��� �������� �� COM-����� ������
#define SHOW_RECV_ALL 32
#define SHOW_RCV_ALL SHOW_RECV_ALL

//
// ���� ������
//

// �������� ��������� �������
#define ERR_OK				  0

//
// ���������� ������ ����������
//

// � ������� ������� �������� ��������
#define ERR_INVALID_ARG		 -1

// COM-���� �� ��� ������
#define ERR_NO_PORT		 -2 
#define ERR_NO_RESOURCE (ERR_NO_PORT)

#define ERR_OPAQUE		 -3

// COM-���� ��� ������
#define ERR_PORT_ALREADY_OPEN	 -4
#define ERR_RESOURCE_BUSY	 (ERR_PORT_ALREADY_OPEN)

// ������ �������� �����
#define ERR_OPEN_PORT -5
#define ERR_INVALID_RESOURCE (ERR_OPEN_PORT)

// ������� �� ��������������
#define ERR_UNSUPPORTED		 -6

// ������ ������ ������� ���
#define ERR_BUFFER_TOO_SMALL -7

// ������� ������� ��������� �� �����
#define ERR_BUFFER_INVALID	 -8

// �������� ��������� ���� 
// "5.1.2	�������� ����� � ������������� ���������� ������"
// ������� ���� ��� ������� ������
#define ERR_SDOT_VALUE	 -9

// ��� ��������� ������, ���� ������ ��� MAX_PARAM_NAME_LENGTH
#define ERR_ILLEGAL_PARAM_NAME -10


//
// ������ ������ � ���������
//

// ����� ������ ������
#define ERR_IO				 -100

// �������� ������ ��� ������ ������ � ������ �������
#define ERR_FORMAT			 -101

// ������ �� ������� �� ������
#define ERR_TIMEOUT			 -102

// �������� ����������� ����� � �������� �� ������� ������
#define ERR_INVALID_CRC		 -103

// ������ ������ ��� ������
// ��. "5.4.2	�������� ������� ������"
#define ERR_NERR			 -104

// ������ ������ ��� �������������� ��������
// ��. "5.4.3	�������� �������������� ��������"
#define ERR_DEVERR			 -105

// ��������� ������ � ������, ���������� �� �������
// ����������� ����� �������� ������ SetDbgIndication() � ������ SHOW_RCV_ERRORS
#define ERR_INVALID_ANSWER	 -106


#if defined(OWENIO_NOT_USE_IMPORTLIB)

//��������� ������ ������ ����������
typedef int (_stdcall *TProcSetApiMode)(int mode);

//������� ����
typedef int (_stdcall *TProcOpenPort)(unsigned long n,unsigned long speed,unsigned long part,unsigned long bits,unsigned long stop,unsigned long vid);

//��������� ����
typedef int (_stdcall *TProcSetupPort)(unsigned long n,unsigned long speed,unsigned long part,unsigned long bits,unsigned long stop,unsigned long vid);

// ������� ���� ��������, �.�. ���, � ������� ����� ������� ������
typedef int (_stdcall *TProcSelectPort)(unsigned long n);

// ���������� ����
typedef int (_stdcall *TProcClosePort)();

// ������������� ��������� ������ ��� ������ ������� ������ ��/� ����������
typedef int (_stdcall *TProcOwenIO)(unsigned long address,unsigned long addressType,unsigned long is_read,char *parameterName,char *params,unsigned long *param_sz);

// ������ �������������� �������� �� ������
typedef int (_stdcall *TProcReadSInt)(unsigned long address,unsigned long addressType,char *parameterName,int &value, int index);
// ������ ���������� �������������� ��������
typedef int (_stdcall *TProcReadUInt)(unsigned long address,unsigned long addressType,char *parameterName,unsigned int &value, int index);
// ������ �������������� �������� �������� � ���� ����
typedef int (_stdcall *TProcWriteByte)(unsigned long address,unsigned long addressType,char *parameterName,int value, int index);
// ������ �������������� �������� �������� � ��� �����
typedef int (_stdcall *TProcWriteWord)(unsigned long address,unsigned long addressType,char *parameterName,int value, int index);

// ������ �������� � ��������� ������ � ������� PIC
typedef int (_stdcall *TProcWriteFloat24)(unsigned long address,unsigned long addressType,char *parameterName,float value, int index);
// ������ �������� � ��������� ������ � ������� PIC
typedef int (_stdcall *TProcReadFloat24)(unsigned long address,unsigned long addressType,char *parameterName,float &value, int index);

// ������ �������� "5.1.2	�������� ����� � ������������� ���������� ������" � �������� �����
typedef int (_stdcall *TProcReadStoredDotEx)(unsigned long, unsigned long, char *, float&, int&, int);
// ������  �������� "5.1.2	�������� ����� � ������������� ���������� ������" � ��������� ������� �����
typedef int (_stdcall *TProcWriteStoredDotEx)(unsigned long, unsigned long, char *, float, int, int);
// ������ ��������� �������� � ��������� ������ � ������� ����
typedef int (_stdcall *TProcReadStoredDotS)(unsigned long, unsigned long, char *, float&, int);
// ������ ��������� �������� � ��������� ������ � ������� ����
typedef int (_stdcall *TProcWriteStoredDotS)(unsigned long, unsigned long, char *, float, int);
// ������ ������������ �������� � ��������� ������ � ������� ����
typedef int (_stdcall *TProcReadStoredDotU)(unsigned long, unsigned long, char *, float&, int);
// ������ �������� � ��������� ������ � ������� IEEE32
typedef int (_stdcall *TProcWriteIEEE32)(unsigned long address,unsigned long addressType,char *parameterName,float value,int index);
// ������ �������� � ��������� ������ � ������� IEEE32
typedef int (_stdcall *TProcReadIEEE32)(unsigned long, unsigned long, char *, float&, int&, int);
// ������ ���������� � ���������� PKP1 � ������� BCD
typedef int (_stdcall *TProcReadPkpBCD)(unsigned long, unsigned long, char *, float&);
// ������ ��������� �������� �� PKP1
typedef int (_stdcall *TProcWriteCSET)(unsigned long address,unsigned long addressType,int prc);
// ������ �������� ������� � SI8
typedef int (_stdcall *TProcReadDTMR)(unsigned long address,unsigned long addressType,int &hrs,int &mins,int &sec,int &msec);
// ������ ���������� � ��8
typedef int (_stdcall *TProcReadSI8BCD)(unsigned long address,unsigned long addressType,char *parameterName,int &value);
// ������������� ������������ �������� ������ � ������
typedef void (_stdcall *TProcLastErrToStr)(char *res);
// ������ �������� ������, ������������ ��������
typedef int (_stdcall *TProcGetDeviceLastErr)();
// ������ ����������� �������� ������
typedef int (_stdcall *TProcGetExtendedLastErr)();
// ���������� ��������� ��������/ ���������� ������
typedef int (_stdcall *TProcSetDbgIndication)(unsigned long);
// ������ ��������� rtc -��� �������� ���133
typedef int (_stdcall *TProcReadRTC)(unsigned long,unsigned long,char *);
// ����� �������� ������ � RS485 �� ������� ������ - � ������ ������ �� ������ ����������
typedef void * ( _stdcall *TProcRS485FromThread)();
// ���������� �������� ������ � RS485 ��� ������� ������.
typedef int ( _stdcall *TProcRS485ToThread)(void *);
// ������������� �����
typedef int ( _stdcall *TProcListen)(int, unsigned short *, int *, int *, char *, int *);


typedef int ( _stdcall TProcGetBufferSInt)(unsigned char* data, int dataSize, int* value);
typedef int ( _stdcall TProcGetBufferUInt)(unsigned char* data, int dataSize, unsigned*  value);
typedef int ( _stdcall TProcGetBufferByte)(unsigned char* data, int dataSize, unsigned char* value);
typedef int ( _stdcall TProcGetBufferWord)(unsigned char* data, int dataSize, unsigned short* value);
typedef int ( _stdcall TProcGetBufferFloat24)(unsigned char* data, int dataSize, float* value);
typedef int ( _stdcall TProcGetBufferStoredDotS)(unsigned char* data, int dataSize, float* value);
typedef int ( _stdcall TProcGetBufferStoredDotU)(unsigned char* data, int dataSize, float* value);
typedef int ( _stdcall TProcGetBufferIEEE32)(unsigned char* data, int dataSize, float* value);
typedef int ( _stdcall TProcGetBufferPkpBCD)(unsigned char* data, int dataSize, float* value);
typedef int ( _stdcall TProcGetBufferSI8BCD)(unsigned char* data, int dataSize, int* value);
typedef int ( _stdcall TProcGetBufferRTC)(unsigned char* data, int dataSize, char* value);
typedef int ( _stdcall TProcGetBufferDTMR)(unsigned char* data, int dataSize, int *, int *, int *, int *);

// ������� ��������������� ��� ������ � ���������������� AC2
typedef int  (_stdcall *TProcAC2_Open)(unsigned long n);
typedef int  (_stdcall *TProcAC2_Close)();
// ��� ���51
typedef int  (_stdcall *TProcAC2_ReadMpr51)(unsigned long channel,unsigned long speed,float &t_prod,float &t_suhogo,float &t_vlag,float &otn_vlag);
// ���38 � ���38
typedef int  (_stdcall *TProcAC2_ReadTRM_UKT_38_T_and_U)(unsigned long channel,float &t1,float &t2,float &t3,float &t4,float &t5,float &t6,float &t7,float &t8,float &u1,float &u2,float &u3,float &u4,float &u5,float &u6,float &u7,float &u8);
// ���38�4 ��� � ����������
typedef int  (_stdcall *TProcAC2_ReadUKT38sh4_IU)(unsigned long channel,unsigned long speed, float &t1,float &t2,float &t3,float &t4,float &t5,float &t6,float &t7,float &t8,float &u1,float &u2,float &u3,float &u4,float &u5,float &u6,float &u7,float &u8,float &d1,float &d2,float &d3,float &d4,float &d5,float &d6,float &d7,float &d8);
// ���38�4 ���������
typedef int  (_stdcall *TProcAC2_ReadUKT38sh4_trp)(unsigned long channel,unsigned long speed, float &t1,float &t2,float &t3,float &t4,float &t5,float &t6,float &t7,float &t8,float &u1,float &u2,float &u3,float &u4,float &u5,float &u6,float &u7,float &u8,float &d1,float &d2,float &d3,float &d4,float &d5,float &d6,float &d7,float &d8);
//���38�4  ������������������
typedef int  (_stdcall *TProcAC2_ReadUKT38sh4_res)(unsigned long channel,unsigned long speed, float &t1,float &t2,float &t3,float &t4,float &t5,float &t6,float &t7,float &t8,float &u1,float &u2,float &u3,float &u4,float &u5,float &u6,float &u7,float &u8,float &d1,float &d2,float &d3,float &d4,float &d5,float &d6,float &d7,float &d8);
// ���32 -
typedef int  (_stdcall *TProcAC2_ReadTRM32)(unsigned long channel,float &Taero,float &Tobr,float &Totop,float &Tgvs,float &TustObr,float &MustPrajm,float &TustGvs,unsigned long &UseDirectWater);
// ���33 -
typedef int  (_stdcall *TProcAC2_ReadTRM33)(unsigned long channel,float &t1,float &t2,float &t3,float &t4,float &t5,float &t6,float &t7,float &t8,float &Rshift_TobrMax,float &TavarMin,float &TustAero,float &TobrWaterLow);
// ���34 -
typedef int  (_stdcall *TProcAC2_ReadTRM34)(unsigned long channel,float &t1,float &t2,float &t3,float &t4,float &U1_low,float &U1_high,float &U2_low,float &U2_high,float &U3_low,float &U3_high,float &U4_low,float &U4_high);


#else

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(OWEN_IO_EXPORTS)
#define OWEN_EXPORT __declspec(dllexport)
#else
#define OWEN_EXPORT __declspec(dllimport)
#endif

#define OWEN_STDCALL __stdcall

	extern OWEN_EXPORT int OWEN_STDCALL SetApiMode(int mode);
	extern OWEN_EXPORT int OWEN_STDCALL OpenPort(unsigned long n,unsigned long speed,unsigned long part,unsigned long bits,unsigned long stop,unsigned long vid);
	extern OWEN_EXPORT int OWEN_STDCALL SetupPort(unsigned long n,unsigned long speed,unsigned long part,unsigned long bits,unsigned long stop,unsigned long vid);
	extern OWEN_EXPORT int OWEN_STDCALL SelectPort(unsigned long n);
	extern OWEN_EXPORT int OWEN_STDCALL ClosePort();
	extern OWEN_EXPORT int OWEN_STDCALL OwenIO(unsigned long address,unsigned long addressType,unsigned long is_read,char *parameterName,char *params,unsigned long *param_sz);
	extern OWEN_EXPORT int OWEN_STDCALL ReadSInt(unsigned long address,unsigned long addressType,char *parameterName,int &value, int index);
	extern OWEN_EXPORT int OWEN_STDCALL ReadUInt(unsigned long address,unsigned long addressType,char *parameterName,unsigned int &value, int index);
	extern OWEN_EXPORT int OWEN_STDCALL WriteByte(unsigned long address,unsigned long addressType,char *parameterName,int value, int index);
	extern OWEN_EXPORT int OWEN_STDCALL WriteWord(unsigned long address,unsigned long addressType,char *parameterName,int value, int index);
	extern OWEN_EXPORT int OWEN_STDCALL WriteFloat24(unsigned long address,unsigned long addressType,char *parameterName,float value, int index);
	extern OWEN_EXPORT int OWEN_STDCALL ReadFloat24(unsigned long address,unsigned long addressType,char *parameterName,float &value, int index);
	extern OWEN_EXPORT int OWEN_STDCALL ReadStoredDotEx(unsigned long address, unsigned long addressType, char *parameterName, float& value, int& decimalPoint, int index);
	extern OWEN_EXPORT int OWEN_STDCALL WriteStoredDotEx(unsigned long address, unsigned long addressType, char *parameterName, float value, int decimalPoint, int index);
	extern OWEN_EXPORT int OWEN_STDCALL ReadStoredDotS(unsigned long address, unsigned long addressType, char *parameterName, float& value, int index);
	extern OWEN_EXPORT int OWEN_STDCALL WriteStoredDotS(unsigned long address, unsigned long addressType, char *parameterName, float value, int index);
	extern OWEN_EXPORT int OWEN_STDCALL ReadStoredDotU(unsigned long address, unsigned long addressType, char *parameterName, float& value, int index);
	extern OWEN_EXPORT int OWEN_STDCALL WriteIEEE32(unsigned long address,unsigned long addressType,char *parameterName,float value, int index);
	extern OWEN_EXPORT int OWEN_STDCALL ReadIEEE32(unsigned long, unsigned long, char *parameterName, float&, int& value, int index);
	extern OWEN_EXPORT int OWEN_STDCALL ReadPkpBCD(unsigned long, unsigned long, char *parameterName, float& value);
	extern OWEN_EXPORT int OWEN_STDCALL WriteCSET(unsigned long address, unsigned long addressType, int prc);
	extern OWEN_EXPORT int OWEN_STDCALL ReadDTMR(unsigned long address,unsigned long addressType,int &hrs,int &mins,int &sec,int &msec);
	extern OWEN_EXPORT int OWEN_STDCALL ReadSI8BCD(unsigned long address,unsigned long addressType,char *parameterName,int &value);
	extern OWEN_EXPORT void OWEN_STDCALL LastErrToStr(char *res);
	extern OWEN_EXPORT int OWEN_STDCALL SetDbgIndication(unsigned long);
	extern OWEN_EXPORT int OWEN_STDCALL ReadRTC(unsigned long address,unsigned long addressType, char *);
	extern OWEN_EXPORT void* OWEN_STDCALL RS485FromThread();
	extern OWEN_EXPORT int OWEN_STDCALL RS485ToThread(void*);
	extern OWEN_EXPORT int OWEN_STDCALL AC2_Open(unsigned long n);
	extern OWEN_EXPORT int OWEN_STDCALL AC2_Close();
	extern OWEN_EXPORT int OWEN_STDCALL AC2_ReadMpr51(unsigned long channel,unsigned long speed,float &t_prod,float &t_suhogo,float &t_vlag,float &otn_vlag);
	extern OWEN_EXPORT int OWEN_STDCALL AC2_ReadTRM_UKT_38_T_and_U(unsigned long channel,float &t1,float &t2,float &t3,float &t4,float &t5,float &t6,float &t7,float &t8,float &u1,float &u2,float &u3,float &u4,float &u5,float &u6,float &u7,float &u8);
	extern OWEN_EXPORT int OWEN_STDCALL AC2_ReadUKT38sh4_IU(unsigned long channel,unsigned long speed, float &t1,float &t2,float &t3,float &t4,float &t5,float &t6,float &t7,float &t8,float &u1,float &u2,float &u3,float &u4,float &u5,float &u6,float &u7,float &u8,float &d1,float &d2,float &d3,float &d4,float &d5,float &d6,float &d7,float &d8);
	extern OWEN_EXPORT int OWEN_STDCALL AC2_ReadUKT38sh4_trp(unsigned long channel,unsigned long speed, float &t1,float &t2,float &t3,float &t4,float &t5,float &t6,float &t7,float &t8,float &u1,float &u2,float &u3,float &u4,float &u5,float &u6,float &u7,float &u8,float &d1,float &d2,float &d3,float &d4,float &d5,float &d6,float &d7,float &d8);
	extern OWEN_EXPORT int OWEN_STDCALL AC2_ReadUKT38sh4_res(unsigned long channel,unsigned long speed, float &t1,float &t2,float &t3,float &t4,float &t5,float &t6,float &t7,float &t8,float &u1,float &u2,float &u3,float &u4,float &u5,float &u6,float &u7,float &u8,float &d1,float &d2,float &d3,float &d4,float &d5,float &d6,float &d7,float &d8);
	extern OWEN_EXPORT int OWEN_STDCALL AC2_ReadTRM32(unsigned long channel,float &Taero,float &Tobr,float &Totop,float &Tgvs,float &TustObr,float &MustPrajm,float &TustGvs,unsigned long &UseDirectWater);
	extern OWEN_EXPORT int OWEN_STDCALL AC2_ReadTRM33(unsigned long channel,float &t1,float &t2,float &t3,float &t4,float &t5,float &t6,float &t7,float &t8,float &Rshift_TobrMax,float &TavarMin,float &TustAero,float &TobrWaterLow);
	extern OWEN_EXPORT int OWEN_STDCALL AC2_ReadTRM34(unsigned long channel,float &t1,float &t2,float &t3,float &t4,float &U1_low,float &U1_high,float &U2_low,float &U2_high,float &U3_low,float &U3_high,float &U4_low,float &U4_high);
	extern OWEN_EXPORT int OWEN_STDCALL SetMaxRetriesGlobal(int retryCount);
	extern OWEN_EXPORT int OWEN_STDCALL GetMaxRetriesGlobal();
	extern OWEN_EXPORT int OWEN_STDCALL Listen(int timeout, unsigned short *rcv_hash, int *rcv_flag, int *rcv_adr, char *param_data, int *param_sz);
	extern OWEN_EXPORT int OWEN_STDCALL GetBufferSInt(unsigned char* data, int dataSize, int* value);
	extern OWEN_EXPORT int OWEN_STDCALL GetBufferUInt(unsigned char* data, int dataSize, unsigned* value);
	extern OWEN_EXPORT int OWEN_STDCALL GetBufferByte(unsigned char* data, int dataSize, unsigned char* value);
	extern OWEN_EXPORT int OWEN_STDCALL GetBufferWord(unsigned char* data, int dataSize, unsigned short* value);
	extern OWEN_EXPORT int OWEN_STDCALL GetBufferFloat24(unsigned char* data, int dataSize, float* value);
	extern OWEN_EXPORT int OWEN_STDCALL GetBufferStoredDotS(unsigned char* data, int dataSize, float* value);
	extern OWEN_EXPORT int OWEN_STDCALL GetBufferStoredDotU(unsigned char* data, int dataSize, float* value);
	extern OWEN_EXPORT int OWEN_STDCALL GetBufferIEEE32(unsigned char* data, int dataSize, float* value);
	extern OWEN_EXPORT int OWEN_STDCALL GetBufferPkpBCD(unsigned char* data, int dataSize, float* value);
	extern OWEN_EXPORT int OWEN_STDCALL GetBufferSI8BCD(unsigned char* data, int dataSize, int* value);
	extern OWEN_EXPORT int OWEN_STDCALL GetBufferDTMR(unsigned char* data, int dataSize, int *hrs, int *mins, int *sec, int *msec);
	extern OWEN_EXPORT int OWEN_STDCALL GetBufferRTC(unsigned char* data, int dataSize, char *out_buffer);
	extern OWEN_EXPORT int OWEN_STDCALL GetExtendedLastErr();
	extern OWEN_EXPORT int OWEN_STDCALL GetDeviceLastErr();

#if defined(__cplusplus)
};
#endif

#endif

#endif
