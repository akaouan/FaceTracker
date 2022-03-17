#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define green "\x1B[32m"

int main(int argc, char** argv)
{
	VideoCapture camera(0);
	CascadeClassifier faceCascade;

	double scale = 3.0;
	
	faceCascade.load("D:\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt.xml");
	if (!camera.isOpened())
	{
		cout << "Error opening cam!" << endl;
		return (-1);
	}

	while (1)
	{
		Mat frame;
		camera >> frame;

		Mat grayscale;
		cvtColor(frame, grayscale, COLOR_RGB2GRAY);
		resize(grayscale, grayscale, Size(grayscale.size().width / scale, grayscale.size().height / scale));
		
		vector<Rect> faces;

		faceCascade.detectMultiScale(grayscale, faces, 1.1, 3, 0, Size(30, 30));
		
		for (Rect area : faces)
		{
			Scalar drawColor = Scalar(255, 0, 0);
			rectangle(frame, Point(cvRound(area.x * scale), cvRound(area.y * scale)),
				Point(cvRound((area.x + area.width - 1) * scale), cvRound((area.y + area.height - 1) * scale)), drawColor);
		}
		imshow("Webcam", frame);
		if (waitKey(30) > 0)
		{
			cout << green << "Finished!" << endl;
			return (1);
		}
	}
}