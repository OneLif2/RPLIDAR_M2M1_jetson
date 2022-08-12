from build.mapdemo import *
from build import mapdemo
import time
import json
#import pandas as pd

counter = 0
incounter = 0
loop_counter = 0
ipaddress = "192.168.1.106"
build_connection(ipaddress)
print("test 1")
time.sleep(1)

def print_json(json_dict):
    #print(json_dict)
    for d in json_dict['data']:
        print("counter = ", "{0:03}".format(d['counter']), '| angle = ', "{:.6f}".format(d['angle']), '| distance = ', d['distance'])

while True:
    data = get_data(counter, incounter, False)
    if data == '{"data":]}':
        continue
    json_dict = json.loads(data)
    print_json(json_dict)
    print("======= End Loop ======= ", loop_counter, " loop(s), counter = ",json_dict['data'][-1]['counter'], " ======= End Loop =======")
    loop_counter += 1
