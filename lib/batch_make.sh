#!/bin/bash

rm /data/resources/facetagging/1.0.0/lib/libJNI_FaceTagInterface.so
rm /home/allen/code/gallery-face-tag-lib/resources/facetagging/1.0.0/lib/libJNI_FaceTagInterface.so
cp libJNI_FaceTagInterface.so /data/resources/facetagging/1.0.0/lib/
cp libJNI_FaceTagInterface.so /home/allen/code/gallery-face-tag-lib/resources/facetagging/1.0.0/lib/

