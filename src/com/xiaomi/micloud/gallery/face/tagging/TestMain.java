package com.xiaomi.micloud.gallery.face.tagging;



import java.io.*;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.text.SimpleDateFormat;
import java.util.Date;
import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.awt.*;

import java.lang.reflect.Field;

public class TestMain {

	public static byte[] readFile(String imagePath) throws FileNotFoundException{
	File f = new File(imagePath);
        FileInputStream fis = new FileInputStream(f);

        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        int totalLen = 0;
        byte[] buf = new byte[1024];
        try {
            for (int readNum; (readNum = fis.read(buf)) != -1;) {
                //Writes to this byte array output stream
                bos.write(buf, 0, readNum);
                totalLen += readNum;
    //            System.out.println("read " + readNum + " bytes,");
            }
        } catch (IOException ex) {
           // Logger.getLogger(ConvertImage.class.getName()).log(Level.SEVERE, null, ex);
        }
        System.out.println("read " + totalLen + " bytes,");
        byte[] bytes = bos.toByteArray();
        return bytes;
    }


    public static void addDir(String s) {
        try {
            Field field = ClassLoader.class.getDeclaredField("usr_paths");
            field.setAccessible(true);
            String[] paths = (String[]) field.get(null);
            for (int i = 0; i < paths.length; i++) {
                if (s.equals(paths[i])) {
                    return;
                }
            }
            String[] tmp = new String[paths.length + 1];
            System.arraycopy(paths, 0, tmp, 0, paths.length);
            tmp[paths.length] = s;
            field.set(null, tmp);
        } catch (IllegalAccessException e) {
            System.out.println("Failed to get permissions to set library path");
        } catch (NoSuchFieldException e) {
            System.out
                    .println("Failed to get field handle to set library path");
        }
    }

    

	public static void main(String[] args) throws FileNotFoundException{
	     //TestMain tm = new TestMain();
	     addDir("../lib/");
             addDir("./");

	     FaceTaggingInterface  mFaceTaggingInterface = new FaceTaggingInterface();
	     mFaceTaggingInterface.InitFaceTagging();
	     
	     System.out.println("All Initial Success\n\n\n");
	     System.out.println("Loaf file from disk\n");
	     ImageInfo imgInfo1  = mFaceTaggingInterface.RunFaceTaggingFromPath("../data/1.jpg",2);
		 System.out.println("Loaf file from disk success\n\n\n\n");
	     //System.out.println("Face size "+imgInfo.mFaceInfo.length+" Version : "+imgInfo.mFaceVersion);

		
		byte[] data = readFile("../data/1.jpg");
		  int length = data.length;
		ByteBuffer data_buffer=ByteBuffer.wrap(data);
		 System.out.println("RunFaceTaggingFromBuffer\n");
         
		 ImageInfo imgInfo  = mFaceTaggingInterface.RunFaceTaggingFromBuffer(data,length,2);
		   System.out.println("RunFaceTaggingFromBuffer success\n");


            // System.out.println("Face X "+imgInfo.mFaceInfo[0].Face_X+" Eye Left : "+imgInfo.mFaceInfo[0].Eye_left_x);
            // System.out.println("Face Feature : "+imgInfo.mFaceInfo[0].faceFeature);

	     mFaceTaggingInterface.release();
	     System.out.println("test end");
	     //mFaceTaggingInterface.Init_FaceTagging();
	}
	/*
	   public static byte[] readPhotoFiles(String filePath){
	        File file = null;
	        BufferedInputStream bis = null;
	        ByteArrayOutputStream output = null;
	        try{
	            file = new File(filePath);
	            if(!file.isFile()){
	             //   LOGGER.info("is not an file.filePath:{}",filePath);
	            }
	            
	            bis = new BufferedInputStream(new FileInputStream(filePath));
	            output = new ByteArrayOutputStream();
	            byte[] buffer = new byte[65536];
	            int read;
	            while ((read = bis.read(buffer)) > 0) {
	                output.write(buffer, 0, read);
	            }
	            return output.toByteArray();
	        }catch(IOException ex){
	           // LOGGER.error("read photo failed ex {}",ex);
	        } finally{
	            try{
	                if(bis != null){
	                    bis.close();
	                }
	            }catch(IOException ex){
	               // LOGGER.error("close stream failed ex {}",ex);
	            } 
	        }
	        return null;
	    }

	    public static void loadImage(String imagePath)
	    {
	       
	        
	        try{

	           FileInputStream in = new FileInputStream(imagePath);
	            ImageInfo ii = new ImageInfo();
	            ii.setInput(in);
	            ii.check();
	            mImageWidth = ii.getWidth();
	            mImageHeight = ii.getHeight();
	            
	            in.close();
	    
	           // 
	            Image imageSrc = ImageIO.read(new File(imagePath));
	            mImageWidth = imageSrc.getWidth(null);
	            mImageHeight = imageSrc.getHeight(null);

	           // ByteArrayOutputStream out = new ByteArrayOutputStream();
	          //  boolean flag = ImageIO.write(image, "jpg", out);
	          //  byte[] b = out.toByteArray();
	            
	            
	        }catch(FileNotFoundException e){
	        }catch(IOException e){
	        }

	    }
	    
	    */
}
