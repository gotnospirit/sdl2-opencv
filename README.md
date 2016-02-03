# sdl2-opencv
Copy frames captured with OpenCV to a SDL texture

# Building
Assuming '$project_dir' is the directory where this project lives

## Get OpenCV 3
1. Download [OpenCV](http://opencv.org/downloads.html) and unzip somewhere
2. Build it
    - cd $somewhere
    - mkdir build
    - cd build
    - cmake .. && cmake --build .

## Get SDL 2
Download [SDL 2](https://www.libsdl.org/download-2.0.php) development libraries and unzip to '$project_dir\vendor\sdl2'

## Build this project
1. cd $project_dir
2. mkdir build
3. cd build
4. cmake -DOpenCV_DIR=$somewhere/build .. && cmake --build .
