#include "opencv2/core/utility.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int edgeThresh = 1;
int edgeThreshScharr = 1;

Mat image, gray, blurImage, edge1, edge2, cedge, frame;

const char* window_name1 = "Edge map : Canny default (Sobel gradient)";
const char* window_name2 = "Edge map : Canny with custom gradient (Scharr)";

// define a trackbar callback
static void onTrackbar(int, void*)
{
    blur(gray, blurImage, Size(3, 3));

    // Run the edge detector on grayscale
    Canny(blurImage, edge1, edgeThresh, edgeThresh * 3, 3);
    cedge = Scalar::all(0);

    frame.copyTo(cedge, edge1);
    imshow(window_name1, cedge);

    Mat dx, dy;
    Scharr(blurImage, dx, CV_16S, 1, 0);
    Scharr(blurImage, dy, CV_16S, 0, 1);
    Canny(dx, dy, edge2, edgeThreshScharr, edgeThreshScharr * 3);
    cedge = Scalar::all(0);
    frame.copyTo(cedge, edge2);
    imshow(window_name2, cedge);
}

static void help()
{
    printf("\nThis sample demonstrates Canny edge detection\n"
           "Call:\n"
           "    /.edge [image_name -- Default is ../data/fruits.jpg]\n\n");
}

const char* keys = {"{help h||}{@image |../data/fruits.jpg|input image name}"};

static void openVideoStream()
{
    using namespace cv;
    using namespace std;

    VideoCapture cap;
    // open the default camera using default API
    // cap.open(0);
    // OR advance usage: select any API backend
    int deviceID = 0;        // 0 = open default camera
    int apiID = cv::CAP_ANY; // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID, apiID);
    // check if we succeeded
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return;
    }
    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl << "Press any key to terminate" << endl;
    for (;;) {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        // show live and wait for a key with timeout long enough to show images
        imshow("Live", frame);
        if (waitKey(5) >= 0)
            break;
    }
}

int main(int argc, const char** argv)
{
    CommandLineParser parser(argc, argv, keys);
    if (parser.has("help")) {
        help();
        return 0;
    }
    string filename = parser.get<string>(0);

    using namespace cv;
    using namespace std;

    VideoCapture cap;
    // open the default camera using default API
    // cap.open(0);
    // OR advance usage: select any API backend
    int deviceID = 0;        // 0 = open default camera
    int apiID = cv::CAP_ANY; // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID, apiID);
    // check if we succeeded
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl << "Press any key to terminate" << endl;
    for (;;) {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        // show live and wait for a key with timeout long enough to show images
        imshow("Live", frame);
        if (waitKey(5) >= 0)
            break;

        cedge.create(frame.size(), frame.type());
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        // Create a window
        namedWindow(window_name1, 1);
        namedWindow(window_name2, 1);

        // create a toolbar
        createTrackbar("Canny threshold default", window_name1, &edgeThresh, 100,
                       onTrackbar);
        createTrackbar("Canny threshold Scharr", window_name2, &edgeThreshScharr, 400,
                       onTrackbar);

        // Show the image
        onTrackbar(0, 0);

        // Wait for a key stroke; the same function arranges events processing
        // waitKey(0);
    }

    return 0;
}