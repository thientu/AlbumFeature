/*************************************************
Copyright:1.0.0.0
Author: ��־��
Date:2014-3-5

Modified: Allen
Data:2014-11-13
Description: �����������㷨���⿪�ŵĽӿڷ�װ
**************************************************/

#ifndef __FACE_ALBUM_INTERFACE_H__
#define __FACE_ALBUM_INTERFACE_H__


#include "FaceTaggingCommonDef.h"



#include "MiTypes_detect.h"
#include "MiLut_detect.h"
#include <string>

#include "FaceFeatureExtractor.h"
#include "mpeg7_interface.h"
#include "AL_SDMModelRunner.h"


//����3d�����ĺ������п����Ƿ���Ҫ����3d����

//#define CORRECT_3D  

#ifdef CORRECT_3D
#include "FormModel.h"
#endif


typedef struct _sReduced_Face_Info
{
	int Face_X; //������1��X����
     int Face_Y; //������1��Y����
     int Face_W; //������1��Width
     int Face_H;//������1��Height

     double FaceXScale;
     double FaceYScale;
     double FaceWScale;
     double FaceHScale;


     int Eye_left_x;// ����1������X
     int Eye_left_y;//����1������Y

     int Eye_right_x; //����1������X
     int Eye_right_y;//����1������Y


     double EyeLeftXScale;
     double EyeLeftYScale;
     double EyeRightXScale;
     double EyeRightYScale;
}sReduced_Face_Info;

typedef struct _FaceInfo
{
     int Face_X; //������1��X����
     int Face_Y; //������1��Y����
     int Face_W; //������1��Width
     int Face_H;//������1��Height

     double FaceXScale;
     double FaceYScale;
     double FaceWScale;
     double FaceHScale;


     int Eye_left_x;// ����1������X
     int Eye_left_y;//����1������Y

     int Eye_right_x; //����1������X
     int Eye_right_y;//����1������Y


     double EyeLeftXScale;
     double EyeLeftYScale;
     double EyeRightXScale;
     double EyeRightYScale;

     short Gender_Result;//����1���Ա���
     short Gender_Score;//����1���Ա����

     short  age;//����1��agew jue

     short glass;//����1������۾�score

     short Pose_yaw;//����1��ҡͷ�Ƕ�
     short Pose_Pitch;//����1��̧ͷ�Ƕ�
     short Pose_roll;//����1��ƽ������ת�Ƕ�

     string faceFeature;//����������

}FaceInfo;

typedef struct _ImageInfo
{
    string mImageFlag;
    int mFace_version;
    int mFaceNum;

    FaceInfo *mFaceInfo; 

}ImageInfo;

typedef struct _Image3dWarping
{
	int  WarpingFlag;
	EyeArray EyePt;
	cv::Mat imageWarping;
	vector<cv::Point> pts_Warping;
	
}Image3dWarping;

#define  FEATURE_NUM 1200
#define ImageFlag 1001

enum{
    doNothing = -1,
    doFace_Detect=0,
    doFaceAndEye_Detect,
    doFaceAndEyeDetect_FeatureExtractor,
    doFaceAndEyeDetect_FeatureExtractor_Cluster
};



class FaceAlbum
{
public:
	ofstream *GetFileHandle();
	int CreateFileHandle();
	int CloseFileHandle();
    FaceAlbum();
    ~FaceAlbum();

	int DestroyImageInfoMemory();

	void CopyStruct(const sReduced_Face_Info &sreducedInfo,FaceInfo &faceInfo);
    
    string getVersion();
    void ReleaseFaceTagging();
	int RunFaceTagging_ProcessExif( const unsigned char *jpgFileBuffer,int nBufSize,int doType /*= doFaceAndEye_Detect*/ );
    int RunFaceTaggingFromPath(const string imagePath,int doType = doFaceAndEye_Detect);
    int RunFaceTaggingFromBuffer(unsigned char *imgBuffer,int width,int height,int widthStep,int nchannels,int doType = doFaceAndEye_Detect);
	int RunFaceTaggingFromBuffer(cv::Mat &image,int doType = doFaceAndEye_Detect);

	int GetProcessResult(ImageInfo &info);
/*----------Face Detect API-------------*/

public:
	int rotationImageWithOrientation( Mat &Image,int orientation );
    void GetColorRectFaceImg(cv::Mat &image,EyeArray &EyePt,cv::Mat &NormImg );
public:
    int FaceDetect_Init(const string model_path);
    int FaceDetect_Init(const string frontclassifier,const string leftClassifierDir,const string rightClassifierDir);
    

    
	vector<XmRect> FaceDetect_Image(Mat &img);

    vector<XmRect> FaceDetect_Image(unsigned char *imgBuffer,int width,int height,int nchanels);

    int FaceDetect_SaveDetectedFace(Mat &srcImg);
private:

	char       m_logFileName[255];
	ofstream   m_ofs_log;
    LUTDetect *mFaceDetectPtr;
	ImageInfo m_resImageInfo;

    //vector<Rect> mFaceDetected;

/*----------Eye Detect API-------------*/
public:
    int EyeDetect_Init(const string &modelpath);							
    
	vector< vector <Point2f> >  GetLandMarkPoints_Image( Mat &img,vector<XmRect> detectResult );
	vector< vector <Point2f> >  GetLandMarkPoints_Image( unsigned char *imgBuffer,int width,int height,int nchannels,vector<XmRect> detectResult );
	vector< EyeArray >  EyeDetect_Image( Mat &img,vector< vector <Point2f> > &keyPoints );
	
    vector< EyeArray > EyeDetect_Image(Mat &img,vector<XmRect> detectResult);
    vector< EyeArray > EyeDetect_Image(unsigned char *imgBuffer,int width,int height,int nchannels,vector<XmRect> detectResult);

private:
	allen_facemarks::SDMModelRunner *m_Eyerunner;
 //   FaceEyeLocationFrame *mEyeDetectPtr;
   // vector< EyeArray > mEyeDetected;

/*----------Feature Extraction API-------------*/
public:
    int FeatureExtractor_Init(const string &featrueModePath);
#ifdef _WIN32
      vector<string> FeatureExtractor_Image(Mat &img,vector< EyeArray>&vec_Eye,vector<Rect>&FaceRect);
#endif
  
   
    vector<string> FeatureExtractor_Image(Mat &img,vector< EyeArray>&vec_Eye);
	

    string FeatureExtractor_ConvertFloatToString(vector<float>&vec_Feature);
    string FeatureExtractor_ConvertFeatureToString( vector<float>&vec_Feature ,mpeg7_feature_color &mMpeg7FeaturePtr);



/********************************************************************
3d correction
********************************************************************/

#ifdef CORRECT_3D
public:
	int Correct3d_Init(const string model_3d_path);

	//Image3dWarping ImageCorrect3d(cv::Mat &image,vector<cv::Point> &pts_95);
	template<typename T>
	vector<Image3dWarping> ImageCorrect3d(cv::Mat &image,vector< vector<T> >&pts,vector<XmRect> &face_rect);

	template<typename T>
	int GetEyePosition(const vector <T> &pts_95,cv::Point &Eye_left,cv::Point &Eye_right);

	vector<string>  FaceAlbum::FeatureExtractor_Image( Mat &img,vector<Image3dWarping> &vec_Image3d,vector< EyeArray>&vec_Eye );

	//vector<string> FeatureExtractor_Image(Mat &img,vector< EyeArray>&vec_Eye,vector<Image3dWarping> &image3d);
#endif

public:
	vector< vector <Point2f> > mkeyPointsLandMark;
private:
    FaceFeatureExtractor* mFeatureExtractorPtr;  //��������������ȡ��
  //  vector<string> mFeatureStr;
    string mFeatureFlag;

    string mVersion;

public:
#ifdef CORRECT_3D
	FormModel m_formmodel;
#endif
};


#endif
