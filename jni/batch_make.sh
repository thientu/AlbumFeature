#!/bin/bash


cd FaceDetection
 make
cd ..

cd EyeLocation_qh
 make
cd ..

cd landmark_sdm
 make
cd ..

cd FaceGabor
 make
cd ..

cd mpeg7_feature
 make
cd ..

cd FaceTaggingAPI
 make
cd ..

 make
