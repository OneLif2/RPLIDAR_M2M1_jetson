import matplotlib.pyplot as plt
import matplotlib.animation as animation
import matplotlib.gridspec as grid
from matplotlib import style
import numpy as np

from build.mapdemo import *
from build import mapdemo
import time
import json

# print(dir(mapdemo))
print(mapdemo.__doc__)
print(dir(mapdemo))
counter = 0
incounter = 0
loop_counter = 0
ipaddress = "192.168.1.106"
build_connection(ipaddress)
print("test 1")
time.sleep(1)


####################################################################################
# print data

def print_json(json_dict):
    for d in json_dict['data']:
        print("counter = ", "{0:03}".format(d['counter']), '| angle = ', "{:.6f}".format(
            d['angle']), '| distance = ', d['distance'])

####################################################################################
# animation data plotting

def animate(i):
    # read str json data from Lidar
    data = get_data(counter, incounter, False)
    
    # Convert str json data to python dictionary data
    json_dict = json.loads(data)

    # create empty array
    angle_arr = np.zeros((json_dict['data'][-1]['counter'],))
    P_obs_arr = np.zeros((json_dict['data'][-1]['counter'],))
    distance_arr = np.zeros((json_dict['data'][-1]['counter'],))
    angle_arr, P_obs_arr, distance_arr = apf_implement(json_dict,angle_arr,P_obs_arr,distance_arr)

    # clear and plot new data
    ax0.clear()
    ax1.clear()

    ax0.plot(angle_arr, P_obs_arr,'b', linewidth=2, label="APF")
    ax0.set_xlim(-180, 180)
    ax0.set_ylim(-5,100)
    ax0.set_xticks([-180,-90,0,90,180])
    ax0.set_xlabel("Angle in degree")
    ax0.set_ylabel("Repulsive Potential")
    ax0.set_title("APF obstacles avoidance")
    # ax0.set_legend(loc="upper right")
    
    ax1.plot(angle_arr, distance_arr,'b', linewidth=2, label="Distance")
    ax1.set_xlim(-180, 180)
    ax1.set_ylim(-0.5,15)
    ax1.set_xticks([-180,-90,0,90,180])
    ax1.set_xlabel("Angle in degree")
    ax1.set_ylabel("Distance")
    ax1.set_title("Lidar Distance Scanning")
    # ax1.set_legend(loc="upper right")
    

    # ax2.set_xlim([-180, 180])
    # ax2.set_ylim([-5, 80])
    # ax2.set_title("Real Time Lidar APF", fontsize=10)
    # ax2.set_xlabel("Angle Degree")
    # ax2.set_ylabel("Repulsive potential")

    plt.pause(0.1)

####################################################################################
# APF algorithm


def apf_implement(json_dict,angle_arr,P_obs_arr, distance_arr):
    # positive scaling factor
    etta = 2.6
    # radius of influenced for repulsive force
    rho_0 = 2
    # repulsive potential
    i = 0
    for d in json_dict['data']:
        
        distance_arr[i] = d['distance']
        
        if d['distance'] <= rho_0:
            P_obs_arr[i] = 0.5 * etta * (1/d['distance'] - 1/rho_0)**2 * 10
            # print("Calculating")
            angle_arr[i] = d['angle']
            
        else:
            P_obs_arr[i] = 0
            angle_arr[i] = d['angle']
            # print("too small to divide")
            pass
        i+=1

    print_json(json_dict)
    return angle_arr, P_obs_arr, distance_arr

####################################################################################
# main functions starts here


fig = plt.figure(figsize=(16,9), dpi=120)
gs = grid.GridSpec(1,2)
ax0 = fig.add_subplot(gs[0,0])
ax1 = fig.add_subplot(gs[0,1])

# fig2 = plt.figure(2)
# ax2 = fig2.add_subplot(1, 1, 1)

style.use('fivethirtyeight')
plt.rcParams.update({'font.size': 10})

ani = animation.FuncAnimation(fig, animate, interval=1)
plt.show()
