#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include "mxnet/c_predict_api.h"
#ifdef _MSC_VER
#include "opencv2/imgcodecs/imgcodecs.hpp"
#else
#include "opencv2/highgui/highgui.hpp"
#endif

#include "Timer.h"

class FileBuffer {
private:
	std::string file_path;
	std::size_t buffer_len;
	char* buffer;

public:
	FileBuffer(const std::string& input_file_path) : file_path(input_file_path) {
		std::ifstream ifs(file_path.c_str(), std::ios::in | std::ios::binary);
		if (!ifs) {
			fprintf(stderr, "Cannot open file %s\n", file_path.c_str());
			exit(EXIT_FAILURE);
		}
		ifs.seekg(0, std::ios::end);
		buffer_len = (std::size_t)ifs.tellg();
		buffer = new char[buffer_len + 1];
		ifs.seekg(0, std::ios::beg);
		ifs.read(buffer, buffer_len);
		ifs.close();
	}

	std::size_t getLength() {
		return buffer_len;
	}

	char* getBuffer() {
		return buffer;
	}
};

int main(int argc, char** argv) {
	FileBuffer json_data("vrcnn-symbol.json");
	FileBuffer param_data("vrcnn-0000.params");
	int dev_type = 1;  // 1: cpu, 2: gpu
	int dev_id = 0;  // arbitrary
	mx_uint num_input_nodes = 1;  // 1 for feedforward
	const char* input_key[1] = { "data" };
	const char** input_keys = input_key;
	PredictorHandle pred_hnd = nullptr;
	const mx_uint input_shape_indptr[2] = { 0, 4 };
	Timer t;

	for (int i = 1; i < argc; ++i) {
		auto img = cv::imread(argv[i], cv::IMREAD_UNCHANGED);
		t.start();

		mx_uint input_shape_data[4] = { 1, 1,
			static_cast<mx_uint>(img.rows),
			static_cast<mx_uint>(img.cols) };
		MXPredCreate(static_cast<const char*>(json_data.getBuffer()),
			static_cast<const char*>(param_data.getBuffer()),
			static_cast<int>(param_data.getLength()),
			dev_type,
			dev_id,
			num_input_nodes,
			input_keys,
			input_shape_indptr,
			input_shape_data,
			&pred_hnd);
		std::vector<mx_float> image_data(img.rows * img.cols);
		cv::Mat input(img.rows, img.cols, CV_32FC1, image_data.data());
		img.convertTo(input, CV_32FC1, 1.0 / 255);
		MXPredSetInput(pred_hnd, "data", image_data.data(), static_cast<mx_uint>(img.rows * img.cols));

		MXPredForward(pred_hnd);

		std::vector<float> output_data(img.rows * img.cols);
		MXPredGetOutput(pred_hnd, 0, output_data.data(), static_cast<mx_uint>(img.rows * img.cols));
		cv::Mat output(img.rows, img.cols, CV_32FC1, output_data.data());
		cv::Mat recon;
		output.convertTo(recon, CV_8UC1, 255.0);
		t.stop();

		char* output_filename = new char[strlen(argv[i]) + 4];
		strcpy(output_filename, argv[i]);
		strcpy(output_filename + strlen(argv[i]) - 4, "_rec.pgm");
		cv::imwrite(output_filename, recon);

		printf("%dx%d %lf\n", img.cols, img.rows, t.getElapsedTimeInSec());
		MXPredFree(pred_hnd);
	}
}
