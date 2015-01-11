#!/bin/bash
javac com/xiaomi/micloud/gallery/face/tagging/TestMain.java com/xiaomi/micloud/gallery/face/tagging/FaceTaggingInterface.java com/xiaomi/micloud/gallery/face/tagging/ImageInfo.java
export LD_LIBRARY_PATH=../lib
java  com/xiaomi/micloud/gallery/face/tagging/TestMain
