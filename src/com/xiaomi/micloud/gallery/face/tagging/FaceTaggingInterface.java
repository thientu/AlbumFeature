package com.xiaomi.micloud.gallery.face.tagging;

import java.io.*;
import java.nio.ByteBuffer;


public class FaceTaggingInterface {


    private long mNativeObj = 0;
    static
    {
      System.loadLibrary("JNI_FaceTagInterface");
     // System.loadLibrary("FaceTaggingAPI");
     // System.loadLibrary("mpeg7_feature");
     // System.loadLibrary("FaceGaborFea");
     // System.loadLibrary("landmark_sdm");
     // System.loadLibrary("EyeLocation_qh");
     // System.loadLibrary("FaceDetection");
       
      
      
    }  
    public FaceTaggingInterface()
    {
        System.out.println("CreateObject");
        mNativeObj = nativeCreateObject();
    }

    public  int InitFaceTagging()
    {
       if( InitFaceDetect("../data/models/FaceDetect_model/") != 0)
       {
           System.out.println("Face detect init is Error!!");
           return -1;
       }
	   else
	   {
	   System.out.println("Face detect init Success!!");
	   }
       if( nativeInitEyeLocation(mNativeObj,"../data/models/EyeDetect_model/") !=0 )
       {
           System.out.println("EyeLocation init is Error!!");
           return -1;
       }
	   else
	   {
	   System.out.println("EyeLocation init Success!!");
	   }
       if( nativeInitFaceFeatureExtraction(mNativeObj,"../data/models/feature_model/") != 0 )
       {
           System.out.println("FaceFeatureExtraction init is Error!!");
           return -1;
       }
	   else
	   {
	   System.out.println("FaceFeatureExtraction init Success!!");
	   }
      return 0; 
    }
    /*
     *Init Face Detect
     *modelPath : data/classifier/
     *return :0 success -1 error 
     * */
    public int InitFaceDetect(String modelPath)
    {
        return nativeInitFaceDetect(mNativeObj,modelPath);
    }
    /*
     *Init Eye Location
     *modelPath : data/models/
     * return :0 success -1 error 
     * */
    public int InitEyeLocation(String modelPath)
    {
        return nativeInitEyeLocation(mNativeObj,modelPath);
    }
    /*
     *Init Face Feature Extraction
     *modelPath : data/models/feature_model/
     * return :0 success -1 error 
      */
     
    public int InitFaceFeatureExtraction(String modelPath)
    {
        return nativeInitFaceFeatureExtraction(mNativeObj,modelPath);
    }
    /*RunFaceTaggingFromPath
     * imgPath: the image's Path
     * doType:     doFace_Detect=0,
                    doFaceAndEye_Detect =1,
                    doFaceAndEyeDetect_FeatureExtractor= 2,
     * 
     * return ImageInfo:the detect result
     */
    public ImageInfo RunFaceTaggingFromPath(String imgPath,int doType)
    {
       return  nativeRunFaceTaggingFromPath(mNativeObj,imgPath,doType);
    }
    /*RunFaceTaggingFromBuffer
     * imgBuffer: the img's file binary buffer
     * buff_size  buffer lenth
     * doType:     doFace_Detect=0,
                    doFaceAndEye_Detect =1,
                    doFaceAndEyeDetect_FeatureExtractor= 2,
     * 
     * return ImageInfo:the detect result
     */
    public ImageInfo RunFaceTaggingFromBuffer(byte []imgBuffer,int buff_size,int doType)
    {	
		
      return  nativeRunFaceTaggingFromBuffer(mNativeObj,imgBuffer,buff_size,doType);
	  
    }
    public void release()
    {
        nativeReleaseObject( mNativeObj);
    }

    private static native long nativeCreateObject();
    private static native void nativeReleaseObject(long thiz);
    
    public static native int nativeInitFaceDetect(long thiz,String ClassifierDir);
    public static native int nativeInitEyeLocation(long thiz,String ModelDir);
    public static native int nativeInitFaceFeatureExtraction(long thiz,String FeatureModelDir);
    
    public static native ImageInfo nativeRunFaceTaggingFromPath(long thiz,String imagePath,int doType);
    public static native ImageInfo nativeRunFaceTaggingFromBuffer(long thiz,byte []img,int buff_size,int doType);
    
    
}
