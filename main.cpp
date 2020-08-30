#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <unistd.h>
//#include <pthread.h>
#include <sys/time.h>
#include <iconv.h>
#include <sstream>
#include <string>
#include <string.h>
#include <time.h>
#include <sys/select.h>

using namespace std;
using namespace cv;


static void sleep_ms(unsigned int secs)
{
	struct timeval tval;
	tval.tv_sec=secs/1000;
	tval.tv_usec=(secs*1000)%1000000;
	select(0,NULL,NULL,NULL,&tval);

}


int main(){
	Mat src;
	string gsurl = "v4l2src ! video/x-raw, framerate=5/1, width=1280, height=720, format=RGB ! videoconvert ! appsink";
	
	//sprintf(image_name, "%s%d%s", "image", ++i, ".jpg");
	//VideoCapture cap = VideoCapture(gsurl,cv::CAP_GSTREAMER);
	VideoCapture cap = VideoCapture(0);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 720);
	cout << cap.get(CAP_PROP_FPS) << endl;;
	cap >> src;
	bool isColor = (src.type() == CV_8UC3);
	VideoWriter writer;
	int codec = VideoWriter::fourcc('H', '2', '6', '4');  // select desired codec (must be available at runtime)
	double fps = 15.0;
	double delay = 1000.0 / fps;
	string filename = "./live2.avi";
	if(!cap.isOpened()){
		std::cout<<"cannot open captrue..."<<std::endl;
		return 0;
	}
	Mat frame;
	int finish = 50;
	clock_t start, end;
	writer.open(filename, codec, fps, src.size(), isColor);
	while (cap.read(frame) && finish>0) {
		//imwrite("./test.jpg", frame);
		writer.write(frame);
		finish = finish-1;
		//sleep_ms(delay);
	}
	cap.release();
	std::cout<<"finish..."<<std::endl;
	// add by menber 1
	// add by member 2

	// add some test by member 1
}

