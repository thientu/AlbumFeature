
#include <string.h>
#include <malloc.h>
#include <math.h>

const int  EYE_DIS = 54 ; //��׼����������ϵ�µ�˫�۾���	// 
const int  NORMAL_EYE_XLEFT = 47;		// ��׼����������ϵ�����۵ĺ�����
const int  NORMAL_EYE_YLEFT = 62;		// ��׼����������ϵ�����۵�������
const int  NORMAL_EYE_XRIGHT =100;	// ��׼����������ϵ�����۵ĺ�����
const int  NORMAL_EYE_YRIGHT =62;	// ��׼����������ϵ�����۵�������
const int NORMAL_FACE_W =149;
const int NORMAL_FACE_H =149;

#define CLIP(a) ((a)>255?255:((a)<0?0:(a)))
#define ROUND(a) ((int)(a+0.5))
#define MAX(a,b) ((a) < (b) ? (b) : (a))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

typedef struct s_Point
{
	int x;
	int y;
}
s_Point;


typedef float MatrixType;

#ifndef MATRIX_ENUM
#define MATRIX_ENUM
typedef enum mul_ero{WandHnotmatch, CannotCreateMatHead, Success};
typedef enum Invert_type{Matrix_LU, Matrix_SUV, Matrix_SUV_SYM};
#endif

/*************************************************************************************************/
/* ����ӷ� ,   dstMatrix =  srcMatrix1 + srcMatrix2,����Ϊwidth�У�height��                     */
/*************************************************************************************************/
int MatrixAdd(  MatrixType *dstData, MatrixType *srcData1, MatrixType *srcData2,  int width,  int height)
{

	int i,j;
	for(i = 0;i < height; ++i)
		for(j = 0;j < width; ++j)
			dstData[i*width + j] = srcData1[i*width + j] + srcData2[i*width + j];

	return 0;

}



/*************************************************************************************************/
/* ������� ,   dstMatrix =  srcMatrix1 + srcMatrix2,����Ϊwidth�У�height��                     */
/*************************************************************************************************/
int MatrixSub( MatrixType *dstData,  MatrixType *srcData1, MatrixType *srcData2,  int width,  int height)
{

	int i,j;
	for(i = 0;i < height; ++i)
		for(j = 0;j < width; ++j)
			dstData[i*width + j] = srcData1[i*width + j] - srcData2[i*width + j];

	return 0;

}



int MatrixInvert( MatrixType *dstData, MatrixType *srcData,  int width,  int height)
{
	int i,j,k;
	MatrixType div,temp;
	MatrixType *out;
	int *is,*js;

	if(width != height)
		return -1;

	out = (MatrixType *)malloc(sizeof(MatrixType)*height*width);
	is = (int *)malloc(sizeof(int)*height);
	js = (int *)malloc(sizeof(int)*height);
	for(i = 0;i < height; ++i)
	{
		is[i] = i;
		js[i] = i;
	}

	// start from first column to the next 
	for(k = 0;k < height; ++k)
	{
		div = 0;
		for(i = k;i < height; ++i)
			for(j = k;j < height; ++j)
			{
				if(fabs(srcData[i*width + j]) > div)
				{
					div = fabs(srcData[i*width + j]);
					is[k] = i;
					js[k] = j;
				}
			}
			if(fabs(div) < 1e-10)
			{
				free( out );
				free( is );
				free( js );
				return -1;
			}
			if(is[k] != k)
			{
				for(j = 0;j < height; ++j)
				{
					temp = srcData[k*width + j];
					dstData[k*width + j] = srcData[is[k]*width + j];
					dstData[is[k]*width + j] = temp;
				}
			}
			if(js[k] != k)
			{
				for(i = 0;i < height; ++i)
				{
					temp = srcData[i*width + k];
					dstData[i*width + k] = srcData[i*width + js[k]];
					dstData[i*width + js[k]] = temp;
				}
			}
			dstData[k*width + k] = 1/srcData[k*width + k];
			for(j = 0;j < height; ++j)
			{
				if(j != k)
					dstData[k*width + j] = srcData[k*width + j]*srcData[k*width + k];
			}
			for(i = 0;i < height; ++i)
			{
				if(i != k)
				{
					for(j = 0;j < height; ++j)
					{
						if(j != k)
							dstData[i*width + j] -= srcData[i*width + k]*srcData[k*width + j];
					}
				}
			}
			for(i = 0;i < height; ++i)
			{
				if(i != k)
					dstData[i*width + k] = -srcData[i*width + k]*srcData[k*width + k];
			}							
	}

	for(k = height - 1;k >= 0; --k)
	{
		for(j = 0;j < height; ++j)
			if(js[k] != k)
			{
				temp = srcData[k*width + j];
				dstData[k*width + j] = srcData[js[k]*width + j];
				dstData[js[k]*width + j] = temp;
			}
			for(i = 0;i < height; ++i)
				if(is[k] != k)
				{
					temp = srcData[i*width + k];
					dstData[i*width + k] = srcData[i*width + is[k]];
					dstData[i*width + is[k]] = temp;
				}
	}
	free( is );
	free( js );
	free( out );
	return 0;
}



/*************************************************************************************************/
/* ����˷� ,   dstMatrixΪ����C�� srcMatrix1Ϊh1 * w1 ά����A��srcMatrix2Ϊh2 *w2ά����B        */
/*       C = AB,CΪh1 * w2ά����                                                                 */
/*************************************************************************************************/
int MatrixMul( MatrixType *dstData, MatrixType *srcData1,  int w1, int h1,
	MatrixType *srcData2,  int w2,  int h2)
{
	int i,j,k;
	if(w1 != h2)
	{
		return -1;
	}


	for(i = 0;i < h1; ++i)
	{
		for(j = 0;j < w2; ++j)
		{
			MatrixType sum = 0;
			for(k = 0;k < w1; ++k)
				sum += srcData1[i*w1 + k]*srcData2[k*w2 + j];
			dstData[i*w2 + j] = sum;
		}
	}

	return 0;

}



int MatrixTransPos( MatrixType *pDstData, MatrixType *pSrcData, int w, int h)
{

	int i,j;
	if(pDstData == NULL)//ת�ý��������ԭ������
	{
		MatrixType *m3;

		m3 = (MatrixType *)malloc(sizeof(MatrixType)*h*w);
		for(i = 0;i < w; ++i)
			for(j = 0;j < h; ++j)
			{
				m3[i*h + j] = pSrcData[j*w + i];
			}
			for(i = 0;i < h; ++i)
				for(j = 0;j < w; ++j)
					pDstData[i*w + j] = m3[j*w + i];
			free( m3 );
	}
	else
	{
		for(i = 0;i < w; ++i)
			for(j = 0;j < h; ++j)
			{
				pDstData[i*h + j] = pSrcData[j*w + i];
			}
	}
	return 0;

}
// ȷ���㼯origPtPos���㼯desPtPos�ķ���任��ϵ
// �˷���任��ϵ���ĸ�����
void GetAffineMatrix_Pts(float* affineMatrix, float* origPtPos, float* desPtPos, int ptNum)
{
	float temp[4];
	float invers_a_at[4*4];

	int ptOrder;
	int arrayOrder;
	float x;
	float y;

	int ptCoordNum = (ptNum<<1);

	float* a = (float *)malloc(sizeof(float)*ptCoordNum*4);
	float* at = (float *)malloc(sizeof(float)*ptCoordNum*4);

	for(ptOrder = 0; ptOrder< ptNum; ptOrder ++)
	{
		x = origPtPos[(ptOrder<<1)];
		y = origPtPos[(ptOrder<<1)+1];

		arrayOrder = (ptOrder<<3);

		a[arrayOrder] = x;
		a[arrayOrder+1] = -y;
		a[arrayOrder+2] = 1;
		a[arrayOrder+3] = 0;

		a[arrayOrder+4] = y;
		a[arrayOrder+5] = x;
		a[arrayOrder+6] = 0;
		a[arrayOrder+7] = 1;
	}


	MatrixTransPos(at, a, 4, ptCoordNum);

	//MatrixMulti(at, 4, ptCoordNum, a, ptCoordNum, 4, invers_a_at);
	MatrixMul(invers_a_at, at, ptCoordNum, 4, a, 4, ptCoordNum);

	//MatrixInverse(invers_a_at, 4, 4);
	MatrixInvert(invers_a_at, invers_a_at, 4, 4);

	//MatrixMulti(at, 4, ptCoordNum, desPtPos, ptCoordNum, 1, temp);
	MatrixMul(temp, at, ptCoordNum, 4, desPtPos, 1, ptCoordNum);

	//MatrixMulti(invers_a_at, 4, 4, temp, 4, 1, affineMatrix);
	MatrixMul(affineMatrix, invers_a_at, 4, 4, temp, 1, 4);


	free(a);
	free(at);
}


//��ȡָ��λ�õľ�������任�������ͼ��
// int leftShift, int topShift�ֱ�ΪĿ��ͼ�����ϵ��ڷ���任��Ŀ������ϵ�еĺ������������
// gradNumΪ1��3���ֱ�Ϊ�Ҷ�ͼ��RGB������ͼ
// ������Բ��õ��Ƶķ�ʽ����
// ����任����ΪĿ��㵽Դ��ı任����
// Ŀ��ͼ����ֻȡ�任��ͼ����leftShift, topShift�Ĳ��֣���pDesImg�е�(i,j)��ת��Ŀ��ͼ����Ϊ(i+leftShift,j+topShift)
// ����ͼ��Ϊ1D��ͼ�񣬿���Ϊ1��ͨ��Ҳ����Ϊ���ͨ��
// ����Ŀ�����ԭͼ�ж�Ӧ��Ľ��������ֵ��ΪĿ����ֵ
// ����ֵΪ�����߽�ĵ����Ŀ�����Ϊ0����ʾû�е�Խ��
int TransImage_Affine_1D_8u_Nearest(float rot_s_x, float rot_s_y, float move_x, float move_y, 
	unsigned char *pDesImg, int wd, int ht, unsigned char *pSrcImg, int oriwd, int oriht, 
	int leftShift, int topShift, int gradNum)
{
	int i;
	int j;
	int x1;
	int y1;
	int shifti;
	int shiftj;
	float *rc;
	float *rd;
	float tx1;
	float ty1;
	int t;
	int desIndex;

	int max_ht_wd = MAX(ht+topShift, wd+leftShift) + 1;
	int twd = oriwd;
	int tht = oriht;

	int overPointNum = 0;

	rc = (float *)malloc(sizeof(float)*max_ht_wd);
	rd = (float *)malloc(sizeof(float)*max_ht_wd);
	for(i = 0;i < max_ht_wd; ++i)
	{
		rc[i] = rot_s_x*i;
	}

	if(rot_s_y == 0)
	{
		memset(rd, 0, sizeof(float)*max_ht_wd);
	}
	else
	{
		for(i = 0;i < max_ht_wd; ++i)	
		{
			rd[i] = rot_s_y*i;
		}
	}

	for(i = 0; i < ht; ++i)
	{
		shifti = i+topShift;
		tx1 = -rd[shifti] + move_x;
		ty1 = rc[shifti] + move_y;
		for(j = 0; j < wd; ++j)
		{
			shiftj = j+leftShift;

			// ����õ�Ŀ��ͼ�е�(i, j)��ԭͼ�еĶ�Ӧ��������
			x1 = (int)(rc[shiftj] + tx1 + 0.5);
			y1 = (int)(rd[shiftj] + ty1 + 0.5);

			// �������ԭͼ��Χ������Ϊ0
			if(x1 < 0 || y1 < 0 || x1 > (twd-1) || y1 > (tht-1))
			{
				desIndex = (i*wd+j)*gradNum;
				for(t = 0; t< gradNum; ++ t)
				{
					pDesImg[desIndex+t] = 0;
				}

				overPointNum ++;
			}
			else
			{
				// ȡԭͼ�ж�Ӧ������ΪĿ����ֵ
				desIndex = (i*wd+j)*gradNum;
				for(t = 0; t< gradNum; ++ t)
				{
					pDesImg[desIndex+t] = pSrcImg[(y1*oriwd+x1)*gradNum+t];
				}
			}
		}
	}

	free(rc);
	free(rd);

	return(overPointNum);
}

//��ȡָ��λ�õľ�������任�������ͼ��
// int leftShift, int topShift�ֱ�ΪĿ��ͼ�����ϵ��ڷ���任��Ŀ������ϵ�еĺ������������
// gradNumΪ1��3���ֱ�Ϊ�Ҷ�ͼ��RGB������ͼ
// ������Բ��õ��Ƶķ�ʽ����
// ����任����ΪĿ��㵽Դ��ı任����
// Ŀ��ͼ����ֻȡ�任��ͼ����leftShift, topShift�Ĳ��֣���pDesImg�е�(i,j)��ת��Ŀ��ͼ����Ϊ(i+leftShift,j+topShift)
// ����ͼ��Ϊ1D��ͼ�񣬿���Ϊ1��ͨ��Ҳ����Ϊ���ͨ��
// ����Ŀ�����ԭͼ�ж�Ӧ�㸽�������ľ�ֵ��ΪĿ����ֵ
// ����ֵ���ڵ���0ʱ��Ϊ�����߽�ĵ����Ŀ�����Ϊ0����ʾû�е�Խ��
int TransImage_Affine_1D_8u_Smooth(float rot_s_x, float rot_s_y, float move_x, float move_y, 
	unsigned char *pDesImg, int wd, int ht, unsigned char *pSrcImg, int oriwd, int oriht, 
	int leftShift, int topShift, int gradNum)
{
	int i;
	int j;
	int k;
	int l;
	int n;
	int x1;
	int y1;
	int shifti;
	int shiftj;
	float *rc;
	float *rd;
	int maxx;
	int maxy;
	int minx;
	int miny;
	float tx1;
	float ty1;
	int sht;
	int swd;
	int t;
	int desIndex;

	int sum[3];

	int max_ht_wd = MAX(ht+topShift, wd+leftShift) + 1;
	int twd = oriwd;
	int tht = oriht;

	int overPointNum = 0;

	const float smoothRatio = 1.0;
	swd = MAX((int)(sqrtf(rot_s_x*rot_s_x + rot_s_y*rot_s_y)*smoothRatio + 0.5), 1);
	sht = swd;

	rc = (float *)malloc(sizeof(float)*max_ht_wd);
	rd = (float *)malloc(sizeof(float)*max_ht_wd);
	for(i = 0;i < max_ht_wd; ++i)
	{
		rc[i] = rot_s_x*i;
	}

	if(rot_s_y == 0)
	{
		memset(rd, 0, sizeof(float)*max_ht_wd);
	}
	else
	{
		for(i = 0;i < max_ht_wd; ++i)	
		{
			rd[i] = rot_s_y*i;
		}
	}

	for(i = 0; i < ht; ++i)
	{
		shifti = i+topShift;
		tx1 = -rd[shifti] + move_x;
		ty1 = rc[shifti] + move_y;
		for(j = 0; j < wd; ++j)
		{
			shiftj = j+leftShift;

			// ����Ŀ�����Դ����ϵ�ж�Ӧ�������
			x1 = (int)(rc[shiftj] + tx1 + 0.5);
			y1 = (int)(rd[shiftj] + ty1 + 0.5);

			// ��Ŀ���������Դ����ϵ�ķ�Χ��
			minx = MIN(MAX(x1, 0), twd);
			miny = MIN(MAX(y1, 0), tht);
			maxx = MIN(MAX(x1 + swd, 0), twd);
			maxy = MIN(MAX(y1 + sht, 0), tht);

			// ����Դ����ϵ��Ŀ���Ķ�Ӧ�㸽�������㣬������ȡ��Χ������ľ�ֵ��ΪĿ����ֵ
			n = 0;
			memset(sum, 0x00, sizeof(int)*gradNum);

			for(k = miny;k < maxy; ++k)
			{
				for(l = minx;l < maxx; ++l)
				{
					for(t = 0; t< gradNum; ++ t)
					{
						sum[t] += pSrcImg[(k*oriwd+l)*gradNum+t];
					}

					n ++;
				}
			}

			if(!n) // ���е㶼����ԭͼ��Χ�ڣ���0
			{
				desIndex = (i*wd+j)*gradNum;
				for(t = 0; t< gradNum; ++ t)
				{
					pDesImg[desIndex+t] = 0;
				}

				++ overPointNum;
			}
			else
			{
				// ����������ľ�ֵ��ΪĿ����ֵ
				desIndex = (i*wd+j)*gradNum;
				for(t = 0; t< gradNum; ++ t)
				{
					pDesImg[desIndex+t] = (unsigned char)CLIP(sum[t]/n);
				}
			}
		}
	}

	free(rc);
	free(rd);

	return(overPointNum);
}

//��ȡָ��λ�õľ�������任�������ͼ��
// int leftShift, int topShift�ֱ�ΪĿ��ͼ�����ϵ��ڷ���任��Ŀ������ϵ�еĺ������������
// gradNumΪ1��3���ֱ�Ϊ�Ҷ�ͼ��RGB������ͼ
// ������Բ��õ��Ƶķ�ʽ����
// ����任����ΪĿ��㵽Դ��ı任����
// Ŀ��ͼ����ֻȡ�任��ͼ����leftShift, topShift�Ĳ��֣���pDesImg�е�(i,j)��ת��Ŀ��ͼ����Ϊ(i+leftShift,j+topShift)
// ���ԭʼͼ��ֱ��ʴ���Ŀ��ͼ������ݱ�������ƽ�����������������ĸ��������˫���Բ���
// ����ֵ���ڵ���0ʱ��Ϊ�����߽�ĵ����Ŀ�����Ϊ0����ʾû�е�Խ��
int TransImage_Affine_1D_8u_Bilinear(float rot_s_x, float rot_s_y, float move_x, float move_y, 
	unsigned char *pDesImg, int wd, int ht, unsigned char *pSrcImg, int oriwd, int oriht, 
	int leftShift, int topShift, int gradNum)
{
	int i;
	int j;
	int x1;
	int y1;
	int x2;
	int y2;
	int shifti;
	int shiftj;
	float *rc;
	float *rd;
	float tx1;
	float ty1;
	float dy,dx;
	int t;
	int desIndex;
	int srcIndex;

	float area11;
	float area12;
	float area21;
	float area22;

	int max_ht_wd = MAX(ht+topShift, wd+leftShift) + 1;
	int twd = oriwd;
	int tht = oriht;

	float temp;

	int overPointNum = 0;

	rc = (float *)malloc(sizeof(float)*max_ht_wd);
	rd = (float *)malloc(sizeof(float)*max_ht_wd);
	for(i = 0;i < max_ht_wd; ++i)
	{
		rc[i] = rot_s_x*i;
	}

	if(rot_s_y == 0)
	{
		memset(rd, 0, sizeof(float)*max_ht_wd);
	}
	else
	{
		for(i = 0;i < max_ht_wd; ++i)	
		{
			rd[i] = rot_s_y*i;
		}
	}

	for(i = 0; i < ht; ++i)
	{
		shifti = i+topShift;
		tx1 = -rd[shifti] + move_x;
		ty1 = rc[shifti] + move_y;
		for(j = 0; j < wd; ++j)
		{
			shiftj = j+leftShift;

			// ����Ŀ��ͼ���е�ǰ����Դͼ�ж�Ӧ�㸡������
			dx = rc[shiftj] + tx1;
			dy = rd[shiftj] + ty1;

			x1 = (int)(dx);
			y1 = (int)(dy);
			x2 = x1+1;
			y2 = y1+1;

			// ���������Χ������Ϊ0
			if(x1 < 0 || y1 < 0 || x2 > (twd-1) || y2 > (tht-1))
			{
				desIndex = (i*wd+j)*gradNum;
				for(t = 0; t< gradNum; ++ t)
				{
					pDesImg[desIndex+t] = 0;
				}

				++ overPointNum;
			}
			else
			{
				// ����������
				area11 = (dx-x1)*(dy-y1); // ���Ͻǵ�
				area12 = (x2-dx)*(dy-y1); // ���Ͻǵ�
				area21 = (dx-x1)*(y2-dy); // ���½ǵ�
				area22 = (x2-dx)*(y2-dy); // ���½ǵ�

				srcIndex = (y1*oriwd+x1)*gradNum; // Դ����ϵ�����Ͻǵ����
				desIndex = (i*wd+j)*gradNum; // Ŀ������ϵ�е�ǰ�����
				for(t = 0; t< gradNum; ++ t)
				{
					// ������ռ���غͶԽ�λ�����������
					temp = pSrcImg[srcIndex+t]*area22+pSrcImg[srcIndex+1+t]*area21
						+pSrcImg[srcIndex+oriwd+t]*area12+pSrcImg[srcIndex+oriwd+1+t]*area11;

					pDesImg[desIndex+t] = CLIP(ROUND(temp));
				}
			}
		}
	}

	free(rc);
	free(rd);

	return(overPointNum);
}

//��ȡָ��λ�õľ�������任�������ͼ��
// int leftShift, int topShift�ֱ�ΪĿ��ͼ�����ϵ��ڷ���任��Ŀ������ϵ�еĺ������������
// gradNumΪ1��3���ֱ�Ϊ�Ҷ�ͼ��RGB������ͼ
// ������Բ��õ��Ƶķ�ʽ����
// ����任����ΪĿ��㵽Դ��ı任����
// Ŀ��ͼ����ֻȡ�任��ͼ����leftShift, topShift�Ĳ��֣���pDesImg�е�(i,j)��ת��Ŀ��ͼ����Ϊ(i+leftShift,j+topShift)
// ���ԭʼͼ��ֱ��ʴ���Ŀ��ͼ������ݱ�������ƽ��
// procCase����ָ������ķ�ʽ�����Ϊ0�����ʾ��������ڷ�ȡ�㣬���Ϊ1�����ʾ˫���Է�ȡ�㣬���Ϊ2�����ʾƽ����ȡ��
// ����ֵ���ڵ���0ʱ��Ϊ�����߽�ĵ����Ŀ�����Ϊ0����ʾû�е�Խ��

int TransImage_Affine_1D_8u(float rot_s_x, float rot_s_y, float move_x, float move_y, 
	unsigned char *pDesImg, int wd, int ht, unsigned char *pSrcImg, int oriwd, int oriht, 
	int leftShift, int topShift, int gradNum, int procCase)
{
	int ret=0;
	if(procCase == 0) // ֱ������ڷ�ȡ��
	{
		ret= TransImage_Affine_1D_8u_Nearest(rot_s_x, rot_s_y, move_x, move_y, 
			pDesImg, wd, ht, pSrcImg, oriwd, oriht, leftShift, topShift, gradNum);
	}
	else if(procCase == 1)
	{
		ret= TransImage_Affine_1D_8u_Bilinear(rot_s_x, rot_s_y, move_x, move_y, 
			pDesImg, wd, ht, pSrcImg, oriwd, oriht, leftShift, topShift, gradNum);
	}
	else if(procCase == 2)
	{
		ret=  TransImage_Affine_1D_8u_Smooth(rot_s_x, rot_s_y, move_x, move_y, 
			pDesImg, wd, ht, pSrcImg, oriwd, oriht, leftShift, topShift, gradNum);
	}
	else
	{
		ret=  -1;
	}
	return ret;
}

// ����Ŀ������ϵ��Դ����ϵ�ĵ��Ӧ��ϵ���Լ������߶Ⱥ���ת���򣬵õ��任���Ŀ��ͼ��
// sinAngle, cosAngle, sizeRatio �ȷ���任����ΪĿ��㵽Դ��ı任�������Ƕ���ͼ������ϵ��˳ʱ��Ϊ��
// srcReferPointΪԴͼ���вο������꣬���Ըõ�Ϊ���Ľ�����ת
// desReferPointΪĿ��ͼ�вο��㣬���Ըõ�Ϊ���Ľ�����ת
// procCase����ָ������ķ�ʽ�����Ϊ0�����ʾ��������ڷ�ȡ�㣬���Ϊ1�����ʾ˫���Է�ȡ�㣬���Ϊ2�����ʾƽ����ȡ��
// ���gradNum=1�����ʾһ��ͨ����Ϊ�Ҷ�ͼ�����gradNum=3�����ʾ3��ͨ����ΪBGR��RGBͼ������ͨ��ͼ��buffer��С��ΪsrcWd��srcHt
// ����ֵ���ڵ���0ʱ��Ϊ�����߽�ĵ����Ŀ�����Ϊ0����ʾû�е�Խ��

int AffineTranImg_CenterSizeAngle_1D(unsigned char *pDesImg, int desWd, int desHt, s_Point desReferPoint, 
	unsigned char *pSrcImg, int srcWd, int srcHt, s_Point srcReferPoint, 
	float sinAngle, float cosAngle, float sizeRatio, int gradNum, int procCase)
{
	// �õ���Ŀ������ϵ��Դ����ϵ�ı任��ϵ
	int ret;
	float temp0,temp1;
	float mTrans[4];
	mTrans[0] = cosAngle*sizeRatio;
	mTrans[1] = sinAngle*sizeRatio;
	temp0 = desReferPoint.x;
	temp1 = desReferPoint.y;
	mTrans[2] = (float)(-mTrans[0]*temp0+mTrans[1]*temp1+srcReferPoint.x);
	mTrans[3] = (float)(-mTrans[0]*temp1-mTrans[1]*temp0+srcReferPoint.y);

	ret =TransImage_Affine_1D_8u(mTrans[0], mTrans[1], mTrans[2], mTrans[3], 
		pDesImg, desWd, desHt, pSrcImg, srcWd, srcHt, 0, 0, gradNum, procCase);

	return ret;
}

/************************************************************************/
// �������ܣ������۾���λ�����ͼ�����Ȥ�������任��eye����Ϊ60�ı�׼����ϵ��lefteye(60,60),righteye(120,69),w:180;h:180��;
//			����������Ȥ���򣬷���任��������pdA
// ����˵����
//			byte* pbClipNormalFaceImgROI,	OUT �����ROIͼ��
//			float* pdA,					OUT ����ӱ�׼�������굽����ͼ������ķ���任����
//          float	pdEyes[4],					OUT �۾���λ���
//			int nImgW,						IN	ͼ����
//			int nImgH,						IN  ͼ��߶�
// �� �� ֵ��
/************************************************************************/
int	ClipNormalFaceImgROI(unsigned char* pbClipNormalFaceImgROI,  float* pdA, float* pdEyes,
	unsigned char* pbFrameGray, int nImgW, int nImgH)
{
	s_Point dstReferPt; 
	s_Point srcReferPt;
	float dEyeDis;
	float dScale;
	float dR;
	float origPtPos[4];
	float* dstPtPos;

	float cosAngle,sinAngle;

	if ( (!pbClipNormalFaceImgROI) || (!pdA) || (!pbFrameGray) || (nImgW<0) || (nImgH<0) )
	{
		return -1;
	}

	//////////////////////////////////////�����۾���λ�����ͼ�����ŵ��۾�����Ϊ60////////////////////////////////////
	// �����۾�����
	dEyeDis = sqrtf ((float)( (pdEyes[0]-pdEyes[2]) *(pdEyes[0]-pdEyes[2]) + (pdEyes[1]-pdEyes[3]) * (pdEyes[1]-pdEyes[3]) ) );
	// �߶ȱ仯����
	dScale = EYE_DIS / dEyeDis;

	dstPtPos = pdEyes;

	origPtPos[0] = NORMAL_EYE_XLEFT;
	origPtPos[1] = NORMAL_EYE_YLEFT;
	origPtPos[2] = NORMAL_EYE_XRIGHT;
	origPtPos[3] = NORMAL_EYE_YRIGHT;

	// ����ӱ�׼�������굽����ͼ������ı任����
	GetAffineMatrix_Pts(pdA, origPtPos, dstPtPos, 2); // ����Ľ����OptimizeA��ͬ
	//	 dR = sqrt(pdA[0] * pdA[0] + pdA[1] * pdA[1]); // pdA������ȷ�Ļ���dRӦ����dScale

	dR= pdA[0];
	// �Ա�׼�����������ĵ�Ϊ�ο���

	dstReferPt.x = NORMAL_EYE_XLEFT;
	dstReferPt.y = NORMAL_EYE_YLEFT;
	// �Ե�ǰ�����������ĵ�Ϊ�ο���

	srcReferPt.x = (int)(pdEyes[0]);
	srcReferPt.y = (int)(pdEyes[1]);

	// ��ȡROIͼ�񣬲����з���任
	cosAngle = (float)(pdA[0] / dR); // c/r
	sinAngle = (float)(pdA[1] / dR); // d/r
	AffineTranImg_CenterSizeAngle_1D(pbClipNormalFaceImgROI, NORMAL_FACE_W, NORMAL_FACE_H,
		dstReferPt, pbFrameGray, nImgW, nImgH, srcReferPt, sinAngle, cosAngle, (float)dR, 1, 2);

	return 0;
}
