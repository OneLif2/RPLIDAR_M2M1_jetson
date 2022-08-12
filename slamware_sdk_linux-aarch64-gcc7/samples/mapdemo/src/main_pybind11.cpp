#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;
/**
 * Slamtec Robot Go Action and Get Path Demo
 *
 * Created By Jacky Li @ 2014-8-8
 * Copyright (c) 2014 Shanghai SlamTec Co., Ltd.
 */
//./slamware_sdk_linux-aarch64-gcc7/linux-aarch64-release/include/rpos/robot_platforms/slamware_core_platform.h
#include <iostream>
#include <thread>
#include <chrono>
#include <rpos/robot_platforms/slamware_core_platform.h>
#include <string>

using namespace rpos::robot_platforms;
using namespace rpos::features;
using namespace rpos::features::location_provider;
using namespace rpos::system::types;

rpos::robot_platforms::SlamwareCorePlatform sdp;
std::string ipaddress = "";
// const char *ipReg = "\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}";

#include <unistd.h>
unsigned int microsecond = 1000000;
const double PI = std::atan(1.0) * 4;
std::string data = "";

float add_fn(float arg1, float arg2)
{
    return arg1 + arg2;
}

// static rpos::robot_platforms::SlamwareCorePlatform connect(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, int, int){}
// static rpos::robot_platforms::connect(const std::string& host, int port, int timeoutInMs = 10000)[]{}

// ===== build_connection ===== build_connection ===== build_connection ===== build_connection ===== build_connection
int build_connection(std::string &ipaddress)
{
    try
    {
        sdp = rpos::robot_platforms::SlamwareCorePlatform::connect(ipaddress, 1445);
        std::cout << "SDK Version: " << sdp.getSDKVersion() << std::endl;
        std::cout << "SDP Version: " << sdp.getSDPVersion() << std::endl;
        std::cout << "Bartter Status: " << sdp.getBatteryIsCharging() << std::endl;
        std::cout << "Barttery Percetage: " << sdp.getBatteryPercentage() << std::endl;
        std::cout << "Power Status: " << sdp.getDCIsConnected() << std::endl;
    }
    catch (ConnectionTimeOutException &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    catch (ConnectionFailException &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    std::cout << "Connection Successfully" << std::endl;

    try
    {
        Map map = sdp.getMap(MapTypeBitmap8Bit, rpos::core::RectangleF(-1, -1, 2, 2), rpos::features::location_provider::EXPLORERMAP);
        std::vector<_u8> &mapData = map.getMapData();
        std::cout << "Map Data: " << std::endl;
        for (std::vector<_u8>::const_iterator it = mapData.begin(); it != mapData.end(); it++)
        {
            std::cout << int(*it) << " ";
        }
        std::cout << std::endl
                  << std::endl;

        std::cout << "Map Position" << std::endl;
        std::cout << map.getMapPosition() << std::endl
                  << std::endl;

        std::cout << "Map Dimension" << std::endl;
        std::cout << map.getMapDimension() << std::endl
                  << std::endl;

        std::cout << "Map Resolution" << std::endl;
        std::cout << map.getMapResolution() << std::endl
                  << std::endl;

        std::cout << "Map Area" << std::endl;
        rpos::core::RectangleF rec = map.getMapArea();

        std::cout << "x: " << rec.x() << std::endl;
        std::cout << "y: " << rec.y() << std::endl;
        std::cout << "width:  " << rec.width() << std::endl;
        std::cout << "height: " << rec.height() << std::endl;
        std::cout << "Ready!! " << std::endl;
        // usleep(1 * microsecond);

        //<< std::endl;
    }

    catch (ConnectionFailException e)
    {
        std::cout << e.what() << std::endl;
        // std::cout << "check point 1 " << std::endl;
    }
    catch (RequestTimeOutException &e)
    {
        std::cout << e.what() << std::endl;
        // std::cout << "check point 2 " << std::endl;
    }
    // std::cout << "check point 3 " << std::endl;
    std::cout << std::endl
              << std::endl;

    return sdp;
}

int knownarea_info(rpos::core::RectangleF &knownArea)
{

    std::cout << "Known Area: " << std::endl;
    std::cout << "(" << knownArea.x() << ", " << knownArea.y() << ", " << knownArea.width() << ", " << knownArea.height() << ")" << std::endl;
}

// using std::string instead of int will have "Aborted error"
std::string get_data(int &counter, int &incounter, bool &knownarea)
{
    // while (1){
    try
    {
        rpos::core::RectangleF knownArea = sdp.getKnownArea(MapTypeBitmap8Bit, rpos::features::location_provider::EXPLORERMAP);
        (knownarea == true) ? knownarea_info(knownArea):0;
        Map map = sdp.getMap(MapTypeBitmap8Bit, knownArea, rpos::features::location_provider::EXPLORERMAP);
        rpos::features::system_resource::LaserScan ls = sdp.getLaserScan();
        std::vector<rpos::core::LaserPoint> points = ls.getLaserPoints();
        std::string json_str = "{\"data\":[";
        for (std::vector<rpos::core::LaserPoint>::const_iterator it = points.begin(); it != points.end(); it++)
        {
            if (it->valid())
            {
                counter++;
                json_str = json_str + "{\"angle\":" + std::to_string(it->angle() / PI * 180) + "," + "\"distance\":" + std::to_string(it->distance()) + "," + "\"valid\":" + (it->valid() ? "true" : "false") + "," + "\"counter\":" + std::to_string(counter) + "},";
            }
            else
                incounter++;
        }
        json_str.pop_back();
        json_str = json_str + "]}";
        return json_str;
    }
    catch (ConnectionFailException e)
    {
        std::cout << e.what() << std::endl;
        // break;
        exit(1);
    }
    catch (RequestTimeOutException &e)
    {
        std::cout << e.what() << std::endl;
    }
    //} //while loop end
}

int main(int argc, const char *argv[])
{
    // float angle, distance, valid;
    int counter = 0;
    int incounter = 0;
    bool knownarea = true;
    std::cout.precision(17);

    // setup connection
    std::string ipaddress = argv[1];
    build_connection(ipaddress);

    std::cout << "test1" << std::endl;
    usleep(2 * microsecond);

    while (1)
    {
        std::cout << get_data(counter, incounter, knownarea) << std::endl;
        std::cout << "=========" << counter << "=========" << incounter << "=========" << counter + incounter << " ==========================" << std::endl;
        std::cout << "========================= loop end ==========================" << std::endl;
        counter = 0;
        incounter = 0;
    }

    return 0;
}

PYBIND11_MODULE(mapdemo, module_handle)
{
    module_handle.doc() = "RPLIDAR PYBIND11";
    module_handle.def("add", &add_fn);
    module_handle.def("build_connection", &build_connection);
    module_handle.def("get_data", &get_data);
    module_handle.def("knownarea", &knownarea_info);
}
