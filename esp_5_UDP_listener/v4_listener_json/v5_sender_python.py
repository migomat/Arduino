import evdev
#mport serial
from bitarray import bitarray
import json
import socket

#arduino_port = serial.Serial('/dev/ttyUSB0',9600, timeout=3.0)
from evdev import InputDevice, categorize, ecodes, KeyEvent
devices = [evdev.InputDevice(fn) for fn in evdev.list_devices()]
#import RPi.GPIO as GPIO

UDP_IP = "192.168.1.13"
UDP_PORT = 4210
MESSAGE = "{m:0010}"

print("UDP target IP:", UDP_IP)
print("UDP target port:", UDP_PORT)
print("message:", MESSAGE)


for device in devices:
    print(device.fn, device.name, device.phys)

gamepad = InputDevice('/dev/input/event13')
dataframe = bitarray('00000000')


def serialize_instance(obj):
    d = { '__classname__' : type(obj).__name__ }
    d.update(vars(obj))
    return d

#print('capabilites:')
#print(gamepad.capabilities())
#print('capabilites: verbose=True')
#print(gamepad.capabilities(verbose=True))
#print(gamepad.leds(verbose=True))#wyswietla liste dostepnych led ktorymi mozna mrugac
#print(gamepad.active_keys(verbose=True))
for event in gamepad.read_loop():
    #print(event)
   # try:
    #    arduinofeedback=arduino_port.readline()
    #    print('value_readed:')
    #    print(arduinofeedback)
   # except:
    #    pass
    if event.code == 16:
        if event.value==-1:
            print('dpad_left')
            dataframe=dataframe|bitarray('00000100')
            print(dataframe)
           #arduino_port.write(dataframe.tobytes())
        elif event.value==1:
            print('dpad_right')
            dataframe=dataframe|bitarray('00001000')
            print(dataframe)
            #arduino_port.write(dataframe.tobytes())
        elif event.value==0:
            print('dpad_rl_released')
            dataframe=dataframe & bitarray('11110011')
            print(dataframe)
            #arduino_port.write(dataframe.tobytes())
    elif event.code == 17:
        if event.value==-1:
            print('dpad_up')
            dataframe=dataframe | bitarray('00000001')
            print(dataframe)
            #arduino_port.write(dataframe.tobytes())
        elif event.value==1:
            print('dpad_down')
            dataframe=dataframe | bitarray('00000010')
            print(dataframe)
            #arduino_port.write(dataframe.tobytes())
        elif event.value==0:
            print('dpad_updown_released')
            dataframe=dataframe & bitarray('11111100')
            print(dataframe)
            #arduino_port.write(dataframe.tobytes())
    
    elif event.code==288:
        print('triangle')
    elif event.code==289:
        print('circle')
    elif event.code==291:
        if event.value==1:
            print('square')
            dataframe=dataframe | bitarray('00100000')
            print(dataframe)
            #arduino_port.write(dataframe.tobytes())
        elif event.value==0:
            print('square_released')
            dataframe=dataframe & bitarray('11011111')
            print(dataframe)
            #arduino_port.write(dataframe.tobytes())
    elif event.code==290:
        if event.value==1:
            print('cross')
            dataframe=dataframe | bitarray('00010000')
            print(dataframe)
            #arduino_port.write(dataframe.tobytes())
        elif event.value==0:
            print('cross_released')
            dataframe=dataframe & bitarray('11101111')
            print(dataframe)
            #arduino_port.write(dataframe.tobytes())
            
    elif event.code==297:
        if event.value==1:
            print('start')
            dataframe = bitarray('00000000')
            #arduino_port.write(dataframe.tobytes())
    elif event.code==296:
        if event.value==1:
            print('select')
    elif event.code==292:
        if event.value==1:
            print('l1')
    elif event.code==294:
        if event.value==1:
            print('l2')
    elif event.code==293:
        if event.value==1:
            print('r1')
    elif event.code==295:
        if event.value==1:
            print('r2')
    elif event.code==299:
        if event.value==1:
            print('r_tog')
    elif event.code==298:
        if event.value==1:
            print('l_tog')
            
    #jsondata={'m':dataframe}
    #jsondataframe = json.dumps(jsondata, default=serialize_instance)
    jsondata = '{m:"%s"}' % dataframe.to01()
    print(jsondata)
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
    sock.sendto(bytes(jsondata, "utf-8"), (UDP_IP, UDP_PORT))
    
 #   arduino_port.close()
   # else:
        #print('unrecognizable button')
        #print(event.code)
       # print(event)
   