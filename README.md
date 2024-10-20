## Install Instructions:
1. Install the dependencies: 
    ```
    yay -S g++ cmake make git pkg-config libjpeg-turbo libpng libtiff openexr zlib ffmpeg python3 python-numpy java-runtime gtk3 GStreamer opencv qt6-base hdf5 vtk glew fmt qt6-wayland 
    ```
2. Clone the OpenCV Git for build/compile
    ```
    cd ~/
    git clone https://github.com/opencv/opencv.git
    ```
3. Create Build Directory
    ```
    mkdir -p ~/build
    cd ~/build
    ```
4. Build
    ```
    cmake -DCMAKE_BUILD_TYPE=Release ../opencv  
    make -j4
    ```
5. Compile
    ```
    sudo make install
    ```