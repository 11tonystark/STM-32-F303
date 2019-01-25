import socket
import time
import pygame
from pygame import joystick
import math
import serial
from time import sleep
import os
from pygame.math import Vector2

    
def map1(x,in_min,in_max,out_min,out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min
def arm():
        
        m1=j.get_button(6)
        m2=j.get_button(7)
        m3=j.get_button(8)
        m4=j.get_button(9)
        m5=j.get_button(4)
        m6=j.get_button(2)
        hat=j.get_hat(0)
        p=' '
        data="nM"
        if m5:
                p='Swivel'
                if hat[0]==1:

                        p='swivel clockwise '
                        data="nA"
                elif hat[0]==-1:
                        p='swivel anticlockwise '
                        data="nB"#swivel
        elif m2:
                p='2nd Link'
                if  hat[1]==1:
                        p='2nd link linear down '
                        data="nC"
                elif hat[1]==-1:
                        p='2nd link linear up '
                        data="nD"#actuator
        elif m3:
                p='pitch'
                if hat[0]==-1 :
                        p='pitch up '
                        data="nE"
                elif hat[0]==1:
                        p='pitch down'
                        data="nF"
        elif m6:
                p='gripper'
                if hat[1]==-1:
                        p='gripper close '
                        data="nG"
                elif hat[1]==1:         
                        p='gripper open '
                        data="nH"
        elif m4:
                p='roll'
                if hat[1]==1:
                        p='roll anticlockwise '
                        data="nI"
                elif hat[1]==-1:
                        p='roll clockwise '
                        data="nJ"
        elif m1:
                p='1st link'
                if hat[0]==1 :
                        p='link 1 linear  up'
                        data="nK"
                elif hat[0]==-1 :
                        p='link 1 linear down'
                        data="nL"#gripper
        else:
                p="N/A"
        pygame.display.set_caption('Motor {:2s} '.format(p))
        print(p+data)                
        transmit.send(data)

def motorcode():
        global x1,y1,gear
        x1=j.get_axis(0)
        y1=j.get_axis(1)
        #print(x1,y1)
        gear=0
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
        #clear()
        print(val)

        transmit.send(val)
    
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
screen = pygame.display.set_mode((300, 200))
clock = pygame.time.Clock()
player_img = pygame.Surface((42, 70), pygame.SRCALPHA)
pygame.draw.polygon(player_img, pygame.Color('dodgerblue1'),[(0, 70), (21, 2), (42, 70)])
global player_rect
player_rect = player_img.get_rect(center=screen.get_rect().center)

try:
    while(1):    
            pygame.event.pump()
            #print(transmit.recv(1024))
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
                            vec=Vector2(x1,y1)
                            radius, angle = vec.as_polar()
                            adjusted_angle = (angle+90) % 360
                            pygame.display.set_caption('Gear {:2d} '.format(gear))
                            # Rotate the image and get a new rect.
                            player_rotated = pygame.transform.rotozoom(player_img, -adjusted_angle, 1)
                            player_rect = player_rotated.get_rect(center=player_rect.center)
                            screen.fill((30, 30, 30))
                            screen.blit(player_rotated, player_rect)
                            pygame.display.flip()
                            clock.tick(60)
                            
                    else:
                            arm()
except KeyboardInterrupt:
    print('lol')
    pygame.display.quit()
    pygame.quit()
