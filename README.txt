人脸相册模块调用：

data文件夹：
data/classifier/ 为人脸检测的model，初始化时只需 传入该文件路径即可
data/models/ 为眼睛定位model
data/models/feature_model/为特征提取model

初始化：（在FaceTaggingInterface.java中有详细说明）
    /*
     *Init Face Detect
     *modelPath : data/classifier/
     * */
InitFaceDetect
    /*
     *Init Eye Location
     *modelPath : data/models/
     * */
     
InitEyeLocation

    /*
     *Init Face Feature Extraction
     *modelPath : data/models/feature_model/
     * */
InitFaceFeatureExtraction

检测：
     * doType:     doFace_Detect=0,
                    doFaceAndEye_Detect =1,
                    doFaceAndEyeDetect_FeatureExtractor= 2,
有两种方式，一种是通过图片路径，一种是通过传递图片Buffer及宽、高、通道数等。
RunFaceTaggingFromPath

RunFaceTaggingFromBuffer