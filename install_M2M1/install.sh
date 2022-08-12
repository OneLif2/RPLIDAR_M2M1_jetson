#Run install.sh
#sudo chmod 740 install.sh

echo -e "====== Extract supplier SDK ======"
tar -xvzf ./slamware_sdk_linux-aarch64-gcc7.tar.gz -C ../

mv ./slamware_sdk_linux-aarch64-gcc7.tar.gz ../

echo -e "====== Copy CMakeLists and main_pybind11.cpp ======"
cp -r ./* ../

mv ../slamware_sdk_linux-aarch64-gcc7.tar.gz ./

cd ..
echo -e "====== install pybind11 ======"
git clone https://github.com/pybind/pybind11.git

echo -e "====== mkdir build ======"
mkdir build

echo -e "====== Done !! ======"
echo -e "====== cd .. ======"
echo -e "====== then run ./cmake.sh ======"