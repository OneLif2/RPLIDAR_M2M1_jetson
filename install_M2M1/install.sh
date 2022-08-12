#Run install.sh
#sudo chmod 740 install.sh

echo -e "====== Extract supplier SDK ======"
sleep 1
tar -xvzf ./slamware_sdk_linux-aarch64-gcc7.tar.gz -C ../

mv ./slamware_sdk_linux-aarch64-gcc7.tar.gz ../
mv ./install.sh ../
echo -e "====== Copy CMakeLists and main_pybind11.cpp ======"
sleep 1
cp -r ./* ../

mv ../slamware_sdk_linux-aarch64-gcc7.tar.gz ./
mv ../install.sh ./

cd ..
echo -e "====== install pybind11 ======"
sleep 1
git clone https://github.com/pybind/pybind11.git

echo -e "====== mkdir build ======"
sleep 1
mkdir build

echo -e "====== Done !! ======"
echo -e "====== cd .. ======"
echo -e "====== then run ./cmake.sh ======"