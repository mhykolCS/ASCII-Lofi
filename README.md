## Install Instructions:
1. Install the dependencies: 
    ```
    yay -S --no-confirm base-devel gcc cmake make git openmpi pkg-config libjpeg-turbo libpng libtiff openexr zlib ffmpeg python3 python-numpy java-runtime qt6-wayland gstreamer gtk3 hdf5 vtk glew fmt ncurses libsndfile json-c intltool libtool libpulse
    ```
2. Clone the OpenCV Git for build/compile
    ```
    cd ~/ && git clone https://github.com/opencv/opencv.git
    ```
3. Create Build Directory
    ```
    mkdir -p ~/build && cd ~/build
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
6. Remove Git and Build Files
    ```
    cd
    rm -rf build opencv
    ```

