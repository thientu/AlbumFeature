#ifndef __XIAOMI_BASE_CLASS_DETECT_H__
#define __XIAOMI_BASE_CLASS_DETECT_H__

#include "MiTypes_detect.h"
#include "MiTypes_c.h"

class DetectParams{
public:
    int detect_MaxPhoto_Size;  //�������ͼƬ���ֵ��Ĭ����640
    int detect_Front_MinNeighbors; //�����Ĭ��group��С Ĭ��2
    int detect_Left_MinNeighbors;  //������������Ĭ��group��С Ĭ��3
    int detect_Right_MinNeighbors; //�Ҳ����Ĭ��group��С Ĭ��2
    float detect_Scale_Factor;  //���ų߶� Ĭ��1.20
    bool detect_USE_Parallel;   //�Ƿ�ʹ�ò���  trueΪʹ�ã�falseΪ��ʵ��
    int minObjectSize;       //������С�ļ������
    int maxObjectSize;       //�������ļ������
    int speedMode;      //�����ٶȺͼ���ʵ�ģʽ 0��1��2  0����������  2���� �������� Ĭ�� 0
    DetectParams();

};

vector<XmRect> combineMultiPoseFace( vector<XmRect> &allCandidates,vector<XmRect> &allCandidatesLeftProfile,vector<XmRect> &allCandidatesRightProfile,int frontMin,int leftMin,int rightMin,int srcImgIsGray);

vector<XmRect> filterNoiseFaceBySkinDetection(vector<XmRect> &rectFace,XmMat *maskMat,int groupMin);

#endif