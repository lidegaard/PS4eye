#include <opencv2/opencv.hpp>

//mkdir
#include <sys/stat.h>
#include <sys/types.h>

#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream
#include <iomanip>      // std::setfill, std::setw

#include<stdio.h>  //SYSTEM
#include<iostream>


bool useGui;
bool useGrey;
bool saveImages;
char* imagePath;
int imageCounter;
int fps;
int width;
int height;
int id;





int main(int argc, char** argv)
{

    useGui = false;
    fps = 60;//120, 60, 30, 15, 8
    //width = 3448;//1280 x 800
    //height = 808;
    width = 1748;//640 x 400
    height = 408;
    //width = 896;//320 x 192
    //height = 200;
    /*
    Video Frame Rate	1280 x 800 @ 60fps
    640 x 400 @ 120fps
    320 x 192 @ 240fps
    */

    //Actual image sizes
    int w = 640; int h = 400;

    id = 0;

    for (int i = 1; i < argc; i++)
    {
        std::cout << argv[i] << std::endl;

        if (std::string(argv[i]) == "-gui")
        {
            useGui = true;
            std::cout << "Using GUI..." << std::endl;
        }
        else if (std::string(argv[i]) == "-save")
        {
            if (i + 1 != argc)
            {
                imagePath = argv[i + 1];
                std::cout << "Saving images to: " << imagePath << std::endl;
                saveImages = true;

                mkdir(imagePath,0777);
                imageCounter = 0;
            }
            else
                std::cout << "No path for saving images... Please specify..." << std::endl;
        }
        else if (std::string(argv[i]) == "-fps")
        {
            if (i + 1 != argc)
            {
                fps = atoi(argv[i + 1]);
                std::cout << "Setting framerate to: " << fps << std::endl;
                //i++;
            }
            else
                std::cout << "No fps given... Please specify..." << std::endl;
        }
        else if (std::string(argv[i]) == "-id")
        {
            if (i + 1 != argc)
            {
                id = atoi(argv[i + 1]);
                std::cout << "Setting id to: " << id << std::endl;
            }
            else
                std::cout << "No fps given... Please specify..." << std::endl;
        }
        else if (std::string(argv[i]) == "-size")// -size 640 480 as default
        {
            if (i + 1 != argc)
            {
                width = atoi(argv[i + 1]);
                std::cout << "Setting width to: " << width << std::endl;
            }
            if (i + 2 != argc)
            {
                height = atoi(argv[i + 1]);
                std::cout << "Setting height to: " << height << std::endl;
            }
            else
                std::cout << "No height given... Please specify..." << std::endl;
        }
        else if (std::string(argv[i]) == "-grey")
        {
            useGrey = true;
            std::cout << "Using greyscale..." << std::endl;
        }
    }




  cv::Mat frame;
  cv::Mat frameL;
  cv::Mat frameR;
  cv::Mat frameRest;

  //system("uvcdynctrl --device=video2 --load=/home/ubuntu/Data/DRIVERS/ps4eye-master/ps4eye_setup_WB_ON.txt");
  cv::VideoCapture cap;



cap.set(CV_CAP_PROP_FPS, fps);
cap.open(2);
  if(!cap.isOpened())
      printf("Error: could not load a camera or video.\n");

cap.set(CV_CAP_PROP_FPS, fps);
  cap.set(CV_CAP_PROP_FRAME_WIDTH, width);//PS4eye
  cap.set(CV_CAP_PROP_FRAME_HEIGHT, height);

  int offsetX = 47;//640x480
  //int offsetX = 48;//1280x800

  if(useGui)
  {
    cv::namedWindow("ps4eye camera LEFT", 1);
    cv::namedWindow("ps4eye camera RIGHT", 1);
  }



  while (true)
  {
    cap >> frame;

    if(!frame.data)
      {
        printf("Error: no frame data.\n");
        continue;
      }

    frameR = frame(cv::Rect(offsetX, 0, w, h));
    frameL = frame(cv::Rect(offsetX+w, 0, w, h));


    if(saveImages)
    {
        std::stringstream rgb_pathL;
        rgb_pathL << imagePath << "/ps4eye_rgb_L_" << std::setw(6) << std::setfill('0') << imageCounter << ".tiff";//bmp
        cv::imwrite(rgb_pathL.str().c_str(), frameL);

        std::stringstream rgb_pathR;
        rgb_pathR << imagePath << "/ps4eye_rgb_R_" << std::setw(6) << std::setfill('0') << imageCounter << ".tiff";//bmp
        cv::imwrite(rgb_pathR.str().c_str(), frameR);

        imageCounter++;
    }

    if(useGui)
    {
        /*
        Video Frame Rate	1280 x 800 @ 60fps
        640 x 400 @ 120fps
        320 x 192 @ 240fps
        */
        cv::imshow("ps4eye camera LEFT", frameL);
        cv::imshow("ps4eye camera RIGHT", frameR);
        //cv::imshow("ps4eye camera REST", frameRest);

        //cv::imshow("ps4eye camera", frame);
        char key = cv::waitKey(1);
        if(key == 'q')
            break;
    }

  }

  cap.release();
}
