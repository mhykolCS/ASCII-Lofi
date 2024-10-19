## Install Instructions:
1. Install the dependencies: 
    ```
    yay -S g++ cmake make git pkg-config
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
    cmake ../opencv
    make -j4
    ```
5. Compile
    ```
    sudo make install
    ```