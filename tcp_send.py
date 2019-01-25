import socket
import time
import pygame
from pygame import joystick
import math
import serial
from time import sleep
import os

    
def map1(x,in_min,in_max,out_min,out_max):
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min
def arm():
	
        m1=j.get_button(6)
        m2=j.get_button(7)
        m3=j.get_button(8)
        m4=j.get_button(9)
        m5=j.get_button(10)
        m6=j.get_button(11)
        up=j.get_button(4)
        down=j.get_button(2)
        data="nM"
        if m1:

                if up:
                        print('1up'),
                        data="nA"
                elif down:
                        print('1down'),
                        data="nB"
        elif m2:
                if up:
                        print('2up'),
                        data="nC"
                elif down:
                        print('2down'),
                        data="nD"
        elif m3:
                if up:
                        print('3up'),
                        data="nE"
                elif down:
                        print('3down'),
                        data="nF"
        elif m4:
                if up:
                        print('4up'),
                        data="nG"
                elif down:
                        print('4down'),
                        data="nH"
        elif m5:
                if up:
                        print('5up'),
                        data="nI"
                elif down:
                        print('5down'),
                        data="nJ"
        elif m6:
                if up:
                        print('6up'),
                        data="nK"
                elif down:
                        print('6down'),
                        data="nL"
        else:
                print("N/A"),
        print("")                
        transmit.send(data)

def motorcode():
	x1=j.get_axis(0)
	y1=j.get_axis(1)
	gear=j.get_axis(3)
	hat=j.get_hat(0)
	
	gear=int(map1(gear,-1.0,1.0,9,0))
	x=map1(x1,-1.0,1.0,0.0,9999)
	y=map1(y1,-1.0,1.0,0.0,9999)

	zero=j.get_axis(2)

	if(zero>0.7):
		x=9999
		y=4999
	elif(zero<-0.7):
		x=0
		y=4999

	if hat[1]==1:
		y=0
	elif hat[1]==-1:
		y=9999
	if hat[0]==1:
		x=9999
	elif hat[0]==-1:
		x=0
	

	x=str(int(x)).zfill(4)
	y=str(int(y)).zfill(4)
	
	val="m"+str(gear)+"x"+str(x)+"y"+str(y)
	clear = lambda : os.system('tput reset')
	#clear()
	print(val)
	
	transmit.send(val)
	
	
	

	
	#print(ser.read())
	#print(ser.read(),ser.read(),ser.read(),ser.read())
	
	#print(ser.read(),ser.read(),ser.read(),ser.read())

count=0
TCP_IP = '192.168.1.7'
TCP_PORT = 5005
BUFFER_SIZE = 1024
MESSAGE = "Hello, World!"

transmit = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
transmit.connect((TCP_IP, TCP_PORT))



joystick.init()
pygame.display.init()
if pygame.joystick.get_count() == 0:
    print("No joystick detected")
    exit(0)
j=joystick.Joystick(0)
j.init()			
adx='a'
ady='b'
switch=True
active=True
global safe
safe=1
while(1):
        
        
        if safe is 1:
                safe = 2
        else:
                safe = 1
        pygame.event.pump()
        on=j.get_button(1)
        if on:
                sleep(0.2)
                if j.get_button(1):
                        if active==True:
                                active=False
                                print('Idle')
                        else:
                                active=True
                                print('Active')

        if active:
                change=j.get_button(0)
                if change:
                        sleep(0.2)
                        if j.get_button(0):
                                if switch==True:
                                        switch=False
                                        print('Arm')
                                else:
                                        switch=True
                                        print('Motor')

                if switch:
                        motorcode()
                else:
                        arm()
