#!/usr/bin/python2.7
import socket
import io, StringIO
import picamera
import pipan

def set_quality(pos):
    cmd,res = pos.split(" ")
    if res == "hig":
        camera.resolution = (2048, 1536)
    elif res == "med":
        camera.resolution = (1024, 768)
    elif res == "low":
        camera.resolution = (640, 480)
    else:
        print "Unknow quality",res

def move_camera(pos):
    cmd,x,y = pos.split(" ")
    print "New position",pos
    p.do_pan (int(x))
    p.do_tilt (int(y))

def send_image():
    print "SENDING IMAGE"
    try:
        my_stream = StringIO.StringIO()
        camera.capture(my_stream, 'jpeg')
        print "len sent ",len(my_stream.getvalue())
        client.sendall(my_stream.getvalue())
    except Exception, e:
        print "ERROR", e

sock = socket.socket()
sock.bind(('', 8089)) # port to listen on
sock.listen(10)
#PIPAN memo + limits
x = 128
y = 140

limit_y_bottom = 80
limit_y_top = 180
limit_y_level = 140
limit_x_left = 60
limit_x_right = 240
p = pipan.PiPan()
#moving camera to neutral 
p.do_tilt (int(y))
p.do_pan (int(x))

#starting the camera
camera =  picamera.PiCamera()
camera.start_preview()
camera.vflip = True
# Camera warm-up time

try:
    while True:
        #try:
        print "Waiting for a client"
        client, addr = sock.accept() 
        # Create an in-memory stream
        str = client.recv(255)
        if str[0:3] == "IMG":
            send_image()
        elif str[0:3] == "POS":
            move_camera(str)
        elif str[0:3] == "RES":
            set_quality(str)
        else:
            print "Not implement yet",str
        client.close()
finally:      
    sock.close()
    del sock
    camera.close()
    print "BYE"
