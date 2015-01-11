package com.xiaomi.micloud.gallery.face.tagging;
class FaceInfo{
    public int Face_X; 
    public int Face_Y; 
    public int Face_W; 
    public int Face_H;
    
    public int Eye_left_x;
    public int Eye_left_y;
    
    public int Eye_right_x; 
    public int Eye_right_y;
    
    	public float faceXScale;
	public float faceYScale;
	public float faceWScale;
	public float faceHScale;

	public float eyeLeftXScale;
	public float eyeLeftYScale;

	public float eyeRightXScale;
	public float eyeRightYScale;

    public short Gender_Result;
    public short Gender_Score;
    
    public short  age;
    
    public short glass;
    
    public short Pose_yaw;
    public short Pose_Pitch;
    public short Pose_roll;
    
    public String faceFeature;
    
}


public class ImageInfo {
    public String mImageFlag;  
    public int mFaceVersion;
    public int mFaceNum;
    public FaceInfo mFaceInfo[];
    public void newFaceInfoArray(int _faceNum)
    {
        if(_faceNum < 0)
        {
            System.out.println("Face size is needed >=0!---------newFaceInfoArray");
            return;
        }
        mFaceInfo = new FaceInfo[_faceNum];
        for(int i=0;i<_faceNum;++i)
        {
            mFaceInfo[i] = new FaceInfo();
        }
    }
    public void setFaceInfoFaceRect(int index,int _Face_X,int _Face_Y,int _Face_W,int _Face_H)
    {
        if(index >= mFaceNum)
        {
            System.out.println("Face size out of memory!---------setFaceInfo_EyePt");
            return;
        }
        mFaceInfo[index].Face_X = _Face_X;
        mFaceInfo[index].Face_Y = _Face_Y;
        mFaceInfo[index].Face_W = _Face_W;
        mFaceInfo[index].Face_H = _Face_H;
    }
    public void setFaceInfoEyePt(int index,int Eye_left_x,int Eye_left_y,int Eye_right_x,int Eye_right_y)
    {
        if(index >= mFaceNum)
        {
            System.out.println("Face size out of memory---------setFaceInfo_EyePt!");
            return;
        }
        mFaceInfo[index].Eye_left_x = Eye_left_x;
        mFaceInfo[index].Eye_left_y = Eye_left_y;
        mFaceInfo[index].Eye_right_x = Eye_right_y;
        mFaceInfo[index].Eye_right_y = Eye_right_y;
    }
   	public void setFaceInfoFaceRectScale(int index, float faceXScale, float faceYScale, float faceWScale,
			float faceHScale) {
		if (index >= mFaceNum) {
		//	LOGGER.error("face num is out of boundary.");
			// 抛个异常?
			return;
		}
		mFaceInfo[index].faceXScale = faceXScale;
		mFaceInfo[index].faceYScale = faceYScale;
		mFaceInfo[index].faceWScale = faceWScale;
		mFaceInfo[index].faceHScale = faceHScale;
	}

	public void setFaceInfoEyePtScale(int index, float eyeLeftXScale, float eyeLeftYScale,
			float eyeRightXScale, float eyeRightYScale) {
		if (index >= mFaceNum) {
		//	LOGGER.error("face num out of boundary.");
			// 抛个异常?
			return;
		}
		mFaceInfo[index].eyeLeftXScale = eyeLeftXScale;
		mFaceInfo[index].eyeLeftYScale = eyeLeftYScale;
		mFaceInfo[index].eyeRightXScale = eyeRightXScale;
		mFaceInfo[index].eyeRightYScale = eyeRightYScale;
	}
 
    public void setFaceInfoFeature(int index,String faceFeature)
    {
        if(index >= mFaceNum)
        {
            System.out.println("Face size out of memory -----setFaceInfo_Feature!");
            return;
        }
        mFaceInfo[index].faceFeature = faceFeature;
        
    }
}
