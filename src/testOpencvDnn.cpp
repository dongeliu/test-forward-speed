#define _CRT_SECURE_NO_WARNINGS

#include "opencv2/dnn/dnn.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"

#include "Timer.h"

int main(int argc, char** argv) {
	auto net = cv::dnn::readNetFromCaffe("VRCNN_net.prototxt", "_iter_116960_VC266_QTBT_DFonSAOALFoff_QP42.caffemodel");
	net.setPreferableBackend(0);
	net.setPreferableTarget(0);
	Timer t;

	for (int i = 1; i < argc; ++i) {
		auto img = cv::imread(argv[i], cv::IMREAD_UNCHANGED);
		t.start();

		std::vector<int> input_size;
		input_size.push_back(1);
		input_size.push_back(1);
		input_size.push_back(img.rows);
		input_size.push_back(img.cols);
		auto img_reshaped = img.reshape(1, input_size);
		cv::Mat input;
		img_reshaped.convertTo(input, CV_32FC1, 1.0 / 255);
		net.setInput(input);

		auto output = net.forward("res");

		std::vector<int> img_size;
		img_size.push_back(img.rows);
		img_size.push_back(img.cols);
		auto output_reshaped = output.reshape(1, img_size);
		cv::Mat recon;
		output_reshaped.convertTo(recon, CV_8UC1, 255.0);
		t.stop();

		char* output_filename = new char[strlen(argv[i]) + 4];
		strcpy(output_filename, argv[i]);
		strcpy(output_filename + strlen(argv[i]) - 4, "_rec.pgm");
		cv::imwrite(output_filename, recon);

		printf("%dx%d %lf\n", img.cols, img.rows, t.getElapsedTimeInSec());
	}
}
