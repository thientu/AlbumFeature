#!/bin/bash

make clean

cd FaceDetection
 make TYPE=debug
cd ..

cd EyeLocation_qh
 make TYPE=debug
cd ..

cd landmark_sdm
 make TYPE=debug
cd ..

cd FaceGabor
 make TYPE=debug
cd ..

cd mpeg7_feature
 make TYPE=debug
cd ..

cd FaceTaggingAPI
 make TYPE=debug
cd ..

 make  TYPE=debug
 