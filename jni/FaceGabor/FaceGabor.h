// AeyeFaceRecog.h

#ifndef _AeyeFaceRecog_H
#define _AeyeFaceRecog_H

#include "AEyeBaseFaceStruct.h"
#include "Face_MatchMx_Type.h"


#define  FALSE     0
#define  TRUE      1
#define  NULL      0
#define  IMGWIDTH   112
#define  IMGHEIGHT  144
#define  FEA_LEN_FX_GABOR    800
#define FEAT_GPOINT_MX 1

//��ʼ����⣺
//����ֵ˵��������0���ɹ���ʼ��
//���ط���ֵ������-1��δ��ʼ��
int  BeInitRight();

//��ʼ��Gabor�ˣ�����EnsemblePCALDAģ��
//���ú�����    long InitFeatExtract(char *pModelDir, int *Parameters, char *Message)
//��������˵����char *pModelDir��ģ�������ļ��У��ļ�����Ӧ����1.dat��ģ���ļ���
//              int *Parameters������NULL
//              char *Message��  ����Ӧ����NULL
//����ֵ˵���� ����ɹ���ʼ�����򷵻�0
//���ط�0�������
int  InitFeatExtract(MX_G_HANGLE_FR *pMxGHandleFR,char *pModelDir, int *Parameters, char *Message);

//�ͷ��ڴ�
//�ͷų�ʼ��ʱ��ռ�õ��ڴ�
//��������˵����int *Parameters��
//              char *Message��  ����Ӧ����NULL
//����ֵ˵���� ���ԭ���Ѿ��ɹ���ʼ�������ͷ��ڴ棬���ҷ���0
//���ԭ��û�гɹ���ʼ�������ͷţ����ҷ���1
int  UnInitialFeatExtract(MX_G_HANGLE_FR *pMxGHandleFR,int *Parameters, char *Message);


// ��������ʶ�����������Ŀ��
int  GetNormFaceWd();

// ��������ʶ�����������Ŀ��
int  GetNormFaceHt();


//��������
//��������ͼ�񣬼�����DOG+Gabor����������������PCALDAͶӰ���ϵ����
//���ú�����long ExtracFeature(OUT float *pFeat, byte *pImg_64_80, byte *pImg_112_144);
//��������˵����OUT float *pFeat���������䳤����GetFeatureLen()�ó�
//              byte *pImg_64_80��64*80�ĻҶ�ͼ������
//              byte *pImg_112_144��112*144��ͼ�����ݣ�������ʱ��֧�֣�Ӧ����NULL
//����ֵ˵����  ���ģ����ȷ������������ȷ���򷵻�0
//              ����-1��û�м�����������������ĿΪ0
//              ����-2��ģ��û����ȷ��ʼ��
//			  �������˵����������20�Σ�ÿ��������LDADim��������ɣ����ң�����ƽ�������㱣����ÿ�ε�β�������ڿ��ټ���cos����
// ��20�Σ�����ͼ���Ϊ20��С����
int  ExtracFeature(MX_G_HANGLE_FR *pMxGHandleFR,OUT float *pFeat, byte *pImg_64_80, byte *pImg_112_144);



//�����۾�λ������ȡ���� ������һ����������װ�ڸú�������
int  ExtracFeature_ByImageEye(MX_G_HANGLE_FR *pMxGHandleFR,OUT float *pFeat, byte *pImageOrg,int ColorBit,int iWidth,int iHeight,
	int xleft,int yleft,int xright,int yright);


// �õ������ڴ泤�ȣ���λΪsizeof(float)
// �������Ϊ-1�����ʾģ��û�г�ʼ��������
// ������������Ϊ��ȷ����������
int  GetFeatureLen();

// �����������������ƶ�
// ���ú�����int ComputSimScore(OUT float *pScore, float *pFeatModel, float *pFeatMatch);
// ��������˵����float *pScore����������ּ�����ƶȣ�Cos���룩
//               float *pFeatModel����������
// 			  float *pFeatMatch����������
int  ComputSimScore(OUT float *pScore, float *pFeatModel, float *pFeatMatch);


#endif