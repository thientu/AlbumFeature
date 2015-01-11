

#include "FaceAlbum.h"

#include<pthread.h>
typedef struct _FACEINFO
{
    String ClssifierDir;
    String ClusterAlbumDir;
    

    String modelPath;
    String FaceEyeDir;
    String imageList;

    String FeaturePath;
    String FeatureList;
    String FaceList;
    String ClusterGroundTruthFaceList;

    String SaveClusterPath;
    String SaveClusterDir;

    int nFaceDetect;
    int detectMode;
    int nEyeFlag;
    int nFeaFlag;
    int nClusterFlag;
    int incrementClusterFlag;
    int nRecommendClusterFlag;
}FACEINFO;

FACEINFO gFaceInfo;

FaceAlbum gFaceAlbum;

int gThreadNum=6;
FaceAlbum gFaceAlbum_testMul[6];

int gFaceNum=0;

//#define shunfeng_detect
vector<string> FaceList;

string FaceDirName = "newFace";
string gFaceDir;

template<typename T>
int OverLapTwoRect(T rc1,T rc2,float ratio)
{
	int x1 = MAX(rc1.x,rc2.x);
	int y1 = MAX(rc1.y,rc2.y);
	int x2 = MIN(rc1.x+rc1.width-1,rc2.x+rc2.width-1);
	int y2 = MIN(rc1.y+rc1.height-1,rc2.y+rc2.height-1);

	if (x1 >=x2 || y1>=y2)
	{
		return 0;
	}
	else
	{

		int s1 = rc1.width*rc1.height;
		int s2 = rc2.width*rc2.height;
		int s3 = (x2-x1+1)*(y2-y1+1);
		if (s3>=ratio*s2 && s3>=ratio*s1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
		
	}
	
}

void processOneImage_emulateCloud(string imagePath)
{
	//获取文件的大小
	ifstream in(imagePath.c_str());   
	in.seekg(0,ios::end);   
	int size = in.tellg();   
	in.close();   

	unsigned char *pFileBuf =new unsigned char [size];
    FILE *pFImg = fopen(imagePath.c_str(),"rb");
    if (!pFImg)	
    {
        return;
    }
	else
	{
		fread(pFileBuf,1,size,pFImg);
	}
	fclose(pFImg);
 
	gFaceAlbum.RunFaceTagging_ProcessExif( pFileBuf,size,2);
	
	delete []pFileBuf;
  
	static int kk=0;
	printf("%d finished processs\n",kk++);

}


int init_FaceTagging(string model_path)
{
    
        gFaceInfo.modelPath = model_path;

        
    {
        if (XMFACE_NORMAL != gFaceAlbum.FaceDetect_Init(gFaceInfo.modelPath+"/FaceDetect_model/") )
        {
            cout<<"init detect error!!"<<endl;
            return XMFACE_ERR_INITIALIZE;
        }



    }
  //  if (gFaceInfo.nEyeFlag)
    {
        if (XMFACE_NORMAL != gFaceAlbum.EyeDetect_Init(gFaceInfo.modelPath+"/EyeDetect_model/") )
        {
            
            cout<<"init Eye detect error!!  "<<gFaceInfo.modelPath<<endl;
            return XMFACE_ERR_INITIALIZE;
        }
    }
    
 //  if (gFaceInfo.nFeaFlag)
   {
       if (XMFACE_NORMAL != gFaceAlbum.FeatureExtractor_Init(gFaceInfo.modelPath+"/feature_model/") )
       {
           cout<<"init Feature  error!!"<<endl;
           return XMFACE_ERR_INITIALIZE;
       }
   }

    for (int i = 0; i < 6; i++)
   {
	   {
        if (XMFACE_NORMAL != gFaceAlbum_testMul[i].FaceDetect_Init(gFaceInfo.modelPath+"/FaceDetect_model/") )
        {
            cout<<"init detect error!!"<<endl;
            return XMFACE_ERR_INITIALIZE;
        }



    }
    {
        if (XMFACE_NORMAL != gFaceAlbum_testMul[i].EyeDetect_Init(gFaceInfo.modelPath+"/EyeDetect_model/") )
        {
            
            cout<<"init Eye detect error!!  "<<gFaceInfo.modelPath<<endl;
            return XMFACE_ERR_INITIALIZE;
        }
    }

   {
       if (XMFACE_NORMAL != gFaceAlbum_testMul[i].FeatureExtractor_Init(gFaceInfo.modelPath+"/feature_model/") )
       {
           cout<<"init Feature  error!!"<<endl;
           return XMFACE_ERR_INITIALIZE;
       }
   }

   }

   
#ifdef CORRECT_3D
   {
	   if (XMFACE_NORMAL != gFaceAlbum.Correct3d_Init(gFaceInfo.modelPath+"/3d_model/") )
	   {
		   cout<<"init Feature  error!!"<<endl;
		   return XMFACE_ERR_INITIALIZE;
	   }
   }
#endif



    return 0;
}

int main(int argc,char *argv[])
{
	if( XMFACE_NORMAL != init_FaceTagging(argv[1]))
    {
        system("pause");
        return XMFACE_ERR_INITIALIZE;
    }
	for(int i=1; i<30; i++)
	{
		char str[255];
		sprintf(str,"%d.jpg",i);
		processOneImage_emulateCloud(str);
	}
	

	gFaceAlbum.ReleaseFaceTagging();
}

/*
int main_multithread(int argc,char *argv[])
{
	if( XMFACE_NORMAL != init_FaceTagging(argv[1]))
    {
        system("pause");
        return XMFACE_ERR_INITIALIZE;
    }
	for(int i=1; i<30; i++)
	{
		char str[255];
		sprintf(str,"%d.jpg",i);
		processOneImage_emulateCloud(str);
	}
	
	DWORD *dwThreadId= new DWORD[gThreadNum]; 
	HANDLE     *hThrd= new HANDLE[gThreadNum];   // thread handle
	Handle_Str *pParam= new Handle_Str[gThreadNum];   
	
	int nCount=0;
	while (nCount<30)
	{
		int k=0;
		for (k=0; k<gThreadNum; k++)
		{
			//获取文件的大小
			char str[255];
		    sprintf(str,"%d.jpg",i);
			ifstream in(str);   
			in.seekg(0,ios::end);   
			int size = in.tellg();   
			in.close();   

			unsigned char *pFileBuf =new unsigned char [size];
			FILE *pFImg = fopen(vec_name[nCount+k].c_str(),"rb");
			if (!pFImg)	
			{
				return;
			}
			else
			{
				fread(pFileBuf,1,size,pFImg);
			}
			fclose(pFImg);

			pParam[k].nID = nCount+k;
			pParam[k].pFaceAlbum =&(gFaceAlbum_testMul[k]) ;
			pParam[k].num_name=vec_name[nCount+k].c_str();
			pParam[k].pFileBuf=pFileBuf;
			pParam[k].nBufSize =size;
			

			hThrd[k] = pthread_create(NULL, 0 , FillPC_Thread,&(pParam[k]), 0, &(dwThreadId[k])) ; 

		}

		for (k=0; k<gThreadNum; k++)
		{
			pthread_join(hThrd[k],INFINITE);
		}

		for (k=0; k<gThreadNum; k++)
		{
			pthread_exit(hThrd[k]);
		}
		nCount =nCount+gThreadNum;
	}


	gFaceAlbum.ReleaseFaceTagging();
}
*/