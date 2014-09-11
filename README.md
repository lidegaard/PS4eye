PS4eye
======


Initialise
===================================
Firstly initialise with this from https://github.com/ps4eye/ps4eye:
sudo ./ps4eye_init.py 
->PS4 camera firmware uploaded and device reset

If the camera is not recognised, you may need to unplug and replug it and try again.


Opencv Example
===================================
You should now be able to use the Opencv-example
mkdir build
cd build
cmake ..
make
./client_ps4eye -gui

NB: remember the "-gui" parameter as this will dispaly the images.



List of video devices: (Mine was video2)
===================================
ls /dev/video*
/dev/video0  /dev/video1  /dev/video2



Using luvcview to access the camera:
===================================
luvcview -d /dev/video2

luvcview 0.2.6
SDL information:
  Video driver: x11
  A window manager is available
Device information:
  Device path:  /dev/video2
Stream settings:
  Frame format: YUYV (MJPG is not supported by device)
  Frame size:   898x200 (requested size 640x480 is not supported by device)
  Frame rate:   30 fps
get picture !


luvcview -d /dev/video2 -i 60 -s 1748x408


Good luck!
Morten Lidegaard
