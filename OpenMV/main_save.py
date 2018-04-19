# Untitled - By: okada_tech
# Multi Color Blob Tracking Example
#
# This example shows off multi color blob tracking using the OpenMV Cam.

import sensor, image, time
import math
from pyb import UART
from pyb import LED
# Color Tracking Thresholds (L Min, L Max, A Min, A Max, B Min, B Max)
ball_color = [(25, 75, 35, 80, 30, 70)]     #ball_color 0b00001 (20, 70, 35, 80, 20, 70)
color= [  #30, 80, -20, 5, 40, 70)  #yerrow
          #(5, 15, -10, 10, -10, 10) #blue
          #(30, 100, -64, -8, -32, 32),  #red        0b00001
          #(0, 15, 0, 40, -80, -20),    #Cyan       0b00010
          #(0, 15, 0, 40, -80, -20),    #green      0b00100
          #(0, 15, 0, 40, -80, -20),    #Magenta    0b01000
          ]
# You may pass up to 16 thresholds above. However, it's not really possible to segment any
# scene with 16 thresholds before color thresholds start to overlap heavily.

x_data_ball=0
y_data_ball=0
x_data_marker=0
y_data_marker=0
i=0
k=0


red_led   = LED(1)
green_led = LED(2)
blue_led  = LED(3)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA) #320x240
sensor.skip_frames(time = 100)
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_whitebal(False) # must be turned off for color tracking
clock = time.clock()
uart = UART(1, 115200, timeout_char = 1000)
# Only blobs that with more pixels than "pixel_threshold" and more area than "area_threshold" are
# returned by "find_blobs" below. Change "pixels_threshold" and "area_threshold" if you change the
# camera resolution. Don't set "merge=True" becuase that will merge blobs which we don't want here.


blue_led.on()
time.sleep(150)
blue_led.off()

red_led.on()
time.sleep(150)
red_led.off()

green_led.on()
time.sleep(150)
green_led.off()

blue_led.on()
time.sleep(150)
blue_led.off()

blue_led.on()
red_led.on()
green_led.on()
time.sleep(150)
green_led.off()
red_led.off()
blue_led.off()
time.sleep(200)

x_data_ball=154
y_data_ball=115
R=0
Rtemp=0

while(True):
    clock.tick()
    img = sensor.snapshot()
    i=0
    xtemp=0
    ytemp=0
    R=0
    Rtemp=0
    for ball in img.find_blobs(ball_color, pixels_threshold=10, area_threshold=10):
        img.draw_rectangle(ball.rect())
        img.draw_cross(ball.cx(), ball.cy())
        if i>0:
            xtemp=abs(ball.cx()-154)
            ytemp=abs(ball.cy()-115)
            R=math.sqrt(xtemp*xtemp+ytemp*ytemp)
            if R<Rtemp:
                x_data_ball=ball.cx()
                y_data_ball=ball.cy()
                Rtemp=math.sqrt(xtemp*xtemp+ytemp*ytemp)
        else:
            xtemp=abs(ball.cx()-154)
            ytemp=abs(ball.cy()-115)
            Rtemp=math.sqrt(xtemp*xtemp+ytemp*ytemp)
            x_data_ball=ball.cx()
            y_data_ball=ball.cy()

        i=i+1
    if i==0:
        x_data_ball=154
        y_data_ball=115

    k=0
    xtemp=0
    ytemp=0
    R=0
    Rtemp=0
    for marker in img.find_blobs(color, pixels_threshold=10, area_threshold=10):
        img.draw_rectangle(marker.rect())
        img.draw_string(marker.x() + 2, marker.y() + 2, "m")
        img.draw_cross(marker.cx(), marker.cy())
        if k>0:
            xtemp=abs(marker.cx()-154)
            ytemp=abs(marker.cy()-115)
            R=math.sqrt(xtemp*xtemp+ytemp*ytemp)
            if R<Rtemp:
                x_data_marker=marker.cx()
                y_data_marker=marker.cy()
                Rtemp=math.sqrt(xtemp*xtemp+ytemp*ytemp)
        else:
            xtemp=abs(marker.cx()-154)
            ytemp=abs(marker.cy()-115)
            Rtemp=math.sqrt(xtemp*xtemp+ytemp*ytemp)
            x_data_marker=marker.cx()
            y_data_marker=marker.cy()

        k=k+1
    if k==0:
        x_data_marker=154
        y_data_marker=115


    uart.writechar(254)
    uart.writechar(i)
    uart.writechar(x_data_ball & 0b0000000011111111)
    uart.writechar((x_data_ball & 0b1111111100000000)>>8)
    uart.writechar(y_data_ball & 0b0000000011111111)
    uart.writechar((y_data_ball & 0b1111111100000000)>>8)
    uart.writechar(k)
    uart.writechar(x_data_marker & 0b0000000011111111)
    uart.writechar((x_data_marker & 0b1111111100000000)>>8)
    uart.writechar(y_data_marker & 0b0000000011111111)
    uart.writechar((y_data_marker & 0b1111111100000000)>>8)



    print("fps=%d" % clock.fps(), end="")
    print(" i=%d" % i, end="")
    print(" ball_x=%d" % x_data_ball, end="")
    print(" ball_y=%d" % y_data_ball, end="")
    print(" k=%d" % k, end="")
    print(" marker_x=%d" % x_data_marker, end="")
    print(" marker_y=%d" % y_data_marker)


