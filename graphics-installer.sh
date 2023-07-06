sudo add-apt-repository universe
sudo apt update
sudo rm /var/lib/dpkg/lock
sudo apt install -y gcc g++ libsdl-image1.2 libsdl-image1.2-dev guile-2.0 guile-2.0-dev guile-1.8 guile-1.8-dev libsdl1.2debian libart-2.0-dev libaudiofile-dev libesd0-dev libdirectfb-dev libdirectfb-extra libfreetype6-dev libxext-dev x11proto-xext-dev libfreetype6 libaa1 libaa1-dev libslang2-dev libasound2 libasound2-dev build-essential
wget http://download.savannah.gnu.org/releases/libgraph/libgraph-1.0.2.tar.gz
tar -xvzf libgraph-1.0.2.tar.gz
cd libgraph-1.0.2
sudo ./configure
sudo make
sudo make install
sudo cp /usr/local/lib/libgraph.* /usr/lib
cd /home/$USER/Desktop
wget -O demo.cpp https://pastebin.com/raw/ZZBs7iPL
gcc demo.cpp -o demo -lgraph
./demo