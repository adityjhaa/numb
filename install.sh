# This is a sript to install Raylib on Debian based Linux-distributions
# Change the package manager for your distribution


sudo apt install build-essential git cmake
# required libraries
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev

# Download and compile
git clone https://github.com/raysan5/raylib.git raylib
cd raylib/src/
make PLATFORM=PLATFORM_DESKTOP
sudo make install
