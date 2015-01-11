#ifndef _AEYE_BASE_FACE_STRUCT_
#define _AEYE_BASE_FACE_STRUCT_

// ���庯�����ؽ��
#define  AEYE_SUCCESS 0
#define  AEYE_FAIL    -1

// ���ʹ���ˣ����ʾΪ�������
#define OUT

// ���庯�����÷�ʽ
#define STD_CALL __stdcall

typedef void * HANDLE;

typedef unsigned char byte;
#define INT_MAX0 2147483647
#define INT_MIN0 (-2147483647-1)
#define ROUND_int32(f) ((f)>0 ? ( (int)((f)+0.5) ) : ( (int)((f)-0.5) ))
#define ROUND_uint32(f) ((int)((f)+0.5))

typedef struct s_POINT
{
	int x;
	int y;
}
s_AEPoint;


typedef struct s_RECT
{
	int left;
	int top;
	int right;
	int bottom;
}
s_AERect;

// ��������ýṹ��
typedef struct _AE_face_
{
	s_AERect faceRect;	// �������壬�ֱ�Ϊ���������������������
	int confidence;		// confidence �������Ŷ�,��0��100,0���,100���
	int quality;		// quality ������,��ʱ����
}
s_AEFace;

// ���������ýṹ��
typedef struct
{
	int faceID;			// Ŀ���Ψһ��ʾ���������ֲ�ͬ��Ŀ��
	s_AERect faceRect;	// �ø���Ŀ�������λ��
	double confidence;	// ���ٵ����Ŷȣ�������������Ŀ��һֱ��ͬһ��Ŀ��ĳ̶�
	int state;          // �����֣����ڱ�����չ�����������������Ŀ���״̬�����ڵ�����ʱ��ʧ��
}
s_AETrackFace;

// �۾���λ�ýṹ�壬�������ۺ�����
typedef struct _AE_eye_
{
	int xLeft;			// xLeft�������ĵ������
	int yLeft;			// yLeft �������ĵ�������
	int leftWd;			// leftWd ���ۿ��
	int leftHt;			// leftHt ���۸߶�
	int xRight;			// xRight �������ĵ������
	int yRight;			// yRight �������ĵ�������
	int rightWd;		// rightWd ���ۿ��
	int rightHt;		// rightHt ���۸߶�
	int confidence;		// confidence ���ۺ����ۼ���������Ŷ�,��0��100,0���,100���
	int lQuality;		// lQuality rQuality ������,��ʱ����
	int rQuality;
}
s_AEEye;

#endif