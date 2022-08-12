echo -e "${RED================================}"
echo -e "rm OLD mapdemo.so "
echo -e "================================"
echo -e "rm OLD mapdemo.so "
echo -e "================================"
echo -e "rm OLD mapdemo.so "
echo -e "================================"
cd ./build && rm -rf *
echo -e "run cmake"
cmake ..
echo -e "cmake done !!"
echo -e "================================"
echo -e "run build/make"
make
echo -e "done!!"
echo -e "================================"
echo -e "run python3"
echo -e " "
echo -e "================================"
python3 ../mapdemo.py

