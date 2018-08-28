#define _CRT_SECURE_NO_WARNINGS
#define BOOST_ALL_DYN_LINK
// #define CPU_ONLY

#include "caffe/caffe.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"

#include "Timer.h"

int main(int argc, char** argv) {
	google::InitGoogleLogging("testCaffe");
	google::SetCommandLineOption("GLOG_minloglevel", "2");
#ifdef CPU_ONLY
	caffe::Caffe::set_mode(caffe::Caffe::CPU);
	const char* mode = "CPU";
#else
	caffe::Caffe::set_mode(caffe::Caffe::GPU);
	const char* mode = "GPU";
#endif
	if (argc == 1) {
		printf("Caffe is running in %s mode\n", mode);
		int deviceId = caffe::Caffe::FindDevice();
		printf("The device %d is %s", deviceId, caffe::Caffe::CheckDevice(deviceId) ? "ready" : "not ready");
		return EXIT_SUCCESS;
	}

	caffe::Net<float> net("VRCNN_net.prototxt", caffe::TEST);
	net.CopyTrainedLayersFrom("_iter_116960_VC266_QTBT_DFonSAOALFoff_QP42.caffemodel");
	auto input_layer = net.input_blobs()[0];
	Timer t;

	for (int i = 1; i < argc; ++i) {
		auto img = cv::imread(argv[i], cv::IMREAD_UNCHANGED);
		t.start();

		input_layer->Reshape(1, 1, img.rows, img.cols);
		net.Reshape();
		auto input_data = input_layer->mutable_cpu_data();
		cv::Mat input(img.rows, img.cols, CV_32FC1, input_data);
		img.convertTo(input, CV_32FC1, 1.0 / 255);

		net.Forward();

		auto output_blob = net.blob_by_name("res");
		auto output_data = output_blob->cpu_data();
		cv::Mat output(img.rows, img.cols, CV_32FC1, const_cast<float*>(output_data));
		cv::Mat recon;
		output.convertTo(recon, CV_8UC1, 255.0);
		t.stop();

		char* output_filename = new char[strlen(argv[i]) + 4];
		strcpy(output_filename, argv[i]);
		strcpy(output_filename + strlen(argv[i]) - 4, "_rec.pgm");
		cv::imwrite(output_filename, recon);

		printf("%dx%d %lf\n", img.cols, img.rows, t.getElapsedTimeInSec());
	}
}
