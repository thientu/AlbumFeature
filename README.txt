�������ģ����ã�

data�ļ��У�
data/classifier/ Ϊ��������model����ʼ��ʱֻ�� ������ļ�·������
data/models/ Ϊ�۾���λmodel
data/models/feature_model/Ϊ������ȡmodel

��ʼ��������FaceTaggingInterface.java������ϸ˵����
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

��⣺
     * doType:     doFace_Detect=0,
                    doFaceAndEye_Detect =1,
                    doFaceAndEyeDetect_FeatureExtractor= 2,
�����ַ�ʽ��һ����ͨ��ͼƬ·����һ����ͨ������ͼƬBuffer�����ߡ�ͨ�����ȡ�
RunFaceTaggingFromPath

RunFaceTaggingFromBuffer