

#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>


#include "opencv/cv.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "faceClusterAPI.h"
#include "faceDetectAPI.h"
#include "faceEyeLocationAPI.h"
#include "faceFeatureExtractionAPI.h"
#include "FaceTaggingCommonDef.h"
using namespace std;
using namespace cv;

typedef struct _FaceInfo
{
    String frontClassifierDir;
    String leftClassifierDir;
    String rightClssifierDir;
    String ClssifierDir;
    String modelPath;
    String FaceEyeDir;
    String imageList;

    String FeaturePath;
    String FeatureList;
    String FaceList;
    String ClusterGroundTruthPath;

    String SaveClusterPath;

    int detectMode;
    int nFaceEyeFlag;
    int nFeaFlag;
    int nClusterFlag;
}FaceInfo;



FaceInfo gFaceInfo;



void processOneImage(string imagePath,int nFaceEyeFlag,int nFeaFlag)
{
    double oneImgTime;
    int pos_start = imagePath.rfind("\\");
    int pos_end = imagePath.rfind(".");
    String imageName =imagePath.substr(pos_start+1,pos_end);
    imagePath = "../data/"+imagePath;
    Mat image = imread(imagePath);
    cv::Mat imageGray ;
    if(image.data==NULL )
    {
	cout<<"image is NULL"<<endl;
    }
    if (image.channels() == 3)
    {
        cvtColor(image,imageGray,CV_BGR2GRAY);
    }
    else
    {
        imageGray=image.clone();
    }
    
    vector< EyeArray > vec_Eye;
    vector<Rect>face_Rect;
    if (nFaceEyeFlag)
    {
        Run_Face_Eye_Detection(imageGray,face_Rect,vec_Eye,gFaceInfo.detectMode,gFaceInfo.FaceEyeDir,imagePath);   
        writeFaceimageAndEyePostion(image,face_Rect,vec_Eye,gFaceInfo.FaceEyeDir,imageName,imagePath);
    }
    
    if (nFaceEyeFlag && nFeaFlag)
    {
         Run_Face_Feature_Extractor(imageGray,vec_Eye,gFaceInfo.FaceEyeDir,gFaceInfo.FaceEyeDir,imagePath);
    }
    else if (nFeaFlag)
    {
        Run_Face_Feature_Extractor(imageGray,gFaceInfo.FaceEyeDir,gFaceInfo.FeaturePath,imagePath); //face4
     
    }

  

}
int ProcessImgList(int nFaceEyeFlag,int nFeaFlag)
{
    ifstream fileIn;
    fileIn.open(gFaceInfo.imageList.c_str()); //打开文件夹路径下图片列表

    if (!fileIn.good())
    {
        cout<<"open Image List Error!!"<<endl;
        return -2;
    }
    char imagePath[500];
    int imageIndex=0;
    int pk=0;
    
    while (fileIn.getline(imagePath,500)!=NULL)
    {
        printf("%d is processing %s \n",pk++,imagePath);
     
        processOneImage(imagePath,nFaceEyeFlag,nFeaFlag);
  
    }



}

void init_FaceInfo()
{
    gFaceInfo.frontClassifierDir = "../data/models/FaceDetect_model/classifier/";
    gFaceInfo.leftClassifierDir = "../data/models/FaceDetect_model/classifier/";
    gFaceInfo.rightClssifierDir = "../data/models/FaceDetect_model/classifier/";
    gFaceInfo.ClssifierDir = "../data/classifier/";
    gFaceInfo.FaceEyeDir = "../data/Face/";
    gFaceInfo.modelPath ="../data/models/";

    gFaceInfo.imageList="../data/image.list";

    gFaceInfo.ClusterGroundTruthPath ="../../data/cluster/ground_truth/";
    //gFaceInfo.FeaturePath ="../../data/cluster/ground_truth/feature_new/";
    gFaceInfo.FeaturePath ="../data/Face4/";
    gFaceInfo.FeatureList = "../data/face.list";
    gFaceInfo.FaceList = "../data/face.list";
    gFaceInfo.SaveClusterPath = "../data/cluster/results/";



    gFaceInfo.detectMode=Face_Detect_LUT;
    gFaceInfo.nFaceEyeFlag = 1;
    gFaceInfo.nFeaFlag = 0;
    gFaceInfo.nClusterFlag =0 ;
}

int init_FaceTagging(int argc,char *argv[])
{
    if (argc == 1)
    {
        init_FaceInfo();
    }
//     else
//     {
//         init_FaceInfoFromParam(argc,argv);
//     }

    if (gFaceInfo.nFaceEyeFlag)
    {
        if (XMFACE_NORMAL != init_detect(gFaceInfo.ClssifierDir,gFaceInfo.detectMode))
        {
            cout<<"init detect error!!"<<endl;
            return XMFACE_ERR_INITIALIZE;
        }

        if (XMFACE_NORMAL != init_EyeLocation(gFaceInfo.modelPath+"haarcascade_frontalface_alt.xml",
            gFaceInfo.modelPath+"sdm_200_HOG3x3_Grid3x3_bin5_noproj_zero_reduced.bin",
            gFaceInfo.modelPath+"boosting_regression",
            gFaceInfo.modelPath+"Face_svm.model") )
        {
            cout<<"init EyeLocation error"<<endl;
            return XMFACE_ERR_INITIALIZE;
        }

    }
    if (gFaceInfo.nFeaFlag)
    {

        if( XMFACE_NORMAL !=  init_FaceFeatureExtraction(gFaceInfo.modelPath+"feature_model/"))
        {
            cout<<"init EyeLocation error"<<endl;
            return XMFACE_ERR_INITIALIZE;
        }
    }


    return 0;
}


int main(int argc,char *argv[])
{
    gFaceInfo.detectMode = Face_Detect_LUT;
 
    cout<<"good    begin Run"<<endl;


    if( XMFACE_NORMAL != init_FaceTagging(argc,argv))
    {
        return XMFACE_ERR_INITIALIZE;
    }



    if (gFaceInfo.nFaceEyeFlag || gFaceInfo.nFeaFlag )
 
    {
        ProcessImgList(gFaceInfo.nFaceEyeFlag,gFaceInfo.nFeaFlag);
    }
   

    if (gFaceInfo.nClusterFlag)
    {
        if (gFaceInfo.nClusterFlag == 1)   //1是普通聚类
        {
            if (XMFACE_NORMAL != init_FaceCluster(gFaceInfo.FeatureList, gFaceInfo.FeaturePath))
            {
                return XMFACE_ERR_INITIALIZE;
            }
            cout << "End input feature data! Now start clustering..." << endl << endl;
            Run_Rank_Level_FaceCluster();

            Run_Save_FaceCluster(gFaceInfo.SaveClusterPath+"/res.xml",gFaceInfo.SaveClusterPath,gFaceInfo.SaveClusterPath,gFaceInfo.SaveClusterPath);

        }
        //增量聚类
        else
        {
            Run_Increment_FaceCluster(gFaceInfo.SaveClusterPath+"res_add_first.xml",gFaceInfo.ClusterGroundTruthPath+"/list1.txt",gFaceInfo.FeaturePath,gFaceInfo.ClusterGroundTruthPath+"/list2.txt",gFaceInfo.FeaturePath);

            Run_Save_FaceCluster(gFaceInfo.SaveClusterPath+"/res_add_second.xml",gFaceInfo.SaveClusterPath,gFaceInfo.SaveClusterPath,gFaceInfo.SaveClusterPath);

        }
    
    }




    system("pause");
}
