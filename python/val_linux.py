import os
import warnings

import numpy
import skimage.color
import skimage.io

filenames = ['BQSquare.bmp', 'BQMall.bmp', 'Cactus.bmp', 'Traffic.bmp', 'Runners.bmp']

def calculatePSNR(orig, res):
  diff = (numpy.int_(orig) - numpy.int_(res)) ** 2
  mse = float(diff.sum()) / (diff.shape[0] * diff.shape[1])
  return numpy.log10(255 * 255 / mse) * 10

if __name__ == '__main__':
  # Set filenames
  grayscale_filenames = []
  jpeg_filenames = []
  for f in filenames:
    orig = skimage.io.imread(f)
    (fmain, _) = os.path.splitext(f)
    if orig.ndim > 2 and orig.shape[2] == 3:
      grayscale_filenames.append(fmain + '.pgm')
    else:
      grayscale_filenames.append(f)
    jpeg_filenames.append(fmain + '.jpg')

  # os.putenv('path', r'..\caffe\dll;..\caffe\dll\release;' + original_path)
  # cmd = r'..\vc\x64\Release\testCaffe.exe ' + ' '.join(jpeg_filenames)
  # print(cmd)
  # os.system(cmd)

  # for i in range(len(grayscale_filenames)):
  #   orig = skimage.io.imread(grayscale_filenames[i])
  #   comp = skimage.io.imread(jpeg_filenames[i])
  #   (fmain, _) = os.path.splitext(jpeg_filenames[i])
  #   try:
  #     rest = skimage.io.imread(fmain + '_rec.pgm')
  #     print(calculatePSNR(orig, comp), calculatePSNR(orig, rest))
  #   except Exception as e:
  #     print(e)
  #   finally:
  #     pass

  cmd = '../src/testOpencvDnn ' + ' '.join(jpeg_filenames)
  print(cmd)
  os.system(cmd)

  for i in range(len(grayscale_filenames)):
    orig = skimage.io.imread(grayscale_filenames[i])
    comp = skimage.io.imread(jpeg_filenames[i])
    (fmain, _) = os.path.splitext(jpeg_filenames[i])
    try:
      rest = skimage.io.imread(fmain + '_rec.pgm')
      print(calculatePSNR(orig, comp), calculatePSNR(orig, rest))
    except Exception as e:
      print(e)
    finally:
      pass

  cmd = '../src/testMxnet ' + ' '.join(jpeg_filenames)
  print(cmd)
  os.system(cmd)

  for i in range(len(grayscale_filenames)):
    orig = skimage.io.imread(grayscale_filenames[i])
    comp = skimage.io.imread(jpeg_filenames[i])
    (fmain, _) = os.path.splitext(jpeg_filenames[i])
    try:
      rest = skimage.io.imread(fmain + '_rec.pgm')
      print(calculatePSNR(orig, comp), calculatePSNR(orig, rest))
    except Exception as e:
      print(e)
    finally:
      pass

  # model=mxnet.model.FeedForward.load('vrcnn',0,num_batch_size=1)

  # orig = skimage.io.imread('cameraman.tif')
  # dist = skimage.io.imread('cameraman.jpg')
  # print(calculatePSNR(orig, dist))
  # res = skimage.io.imread('mxnet_cpp_result.pgm')
  # print(calculatePSNR(orig, res))

  # dist = numpy.float_(dist) / 255
  # dist = dist.reshape([1,1,256,256])
  # res = model.predict(dist)
  # res = res.reshape([256,256])
  # res = numpy.round_(res * 255)
  # res = numpy.uint8(numpy.clip(res, 0, 255))
  # print(calculatePSNR(orig, res))