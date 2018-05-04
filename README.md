# test-forward-speed
A framework for testing the speed of different implementations of DNN

Results (Windows)
-------
| Name     | Resolution | Before | Caffe  | OpenCV | mxnet  |
|----------|------------|--------|--------|--------|--------|
| BQSquare | 416x240    | 25.958 | 27.473 | 27.473 | 27.473 |
| BQMall   | 832x480    | 30.280 | 31.328 | 31.328 | 31.328 |
| Cactus   | 1920x1080  | 33.208 | fail   | 33.957 | 33.957 |
| Traffic  | 2560x1600  | 35.059 | fail   | 35.692 | 35.692 |
| Runners  | 3840x2160  | 33.254 | fail   | 33.797 | fail   |

| Name     | Resolution | Caffe    | OpenCV    | mxnet     |
|----------|------------|----------|-----------|-----------|
| BQSquare | 416x240    | 1.116946 | 0.299574  | 0.378329  |
| BQMall   | 832x480    | 4.646556 | 1.126031  | 1.464367  |
| Cactus   | 1920x1080  | fail     | 5.140299  | 7.438569  |
| Traffic  | 2560x1600  | fail     | 12.637961 | 26.063232 |
| Runners  | 3840x2160  | fail     | 23.358451 | fail      |

Results (Linux)
-------
| Name     | Resolution | Before | Caffe  | OpenCV | mxnet  |
|----------|------------|--------|--------|--------|--------|
| BQSquare | 416x240    | 25.958 | xxxxxx | 27.473 | xxxxxx |
| BQMall   | 832x480    | 30.280 | xxxxxx | 31.328 | xxxxxx |
| Cactus   | 1920x1080  | 33.208 | xxxxxx | 33.957 | xxxxxx |
| Traffic  | 2560x1600  | 35.059 | xxxxxx | 35.692 | xxxxxx |
| Runners  | 3840x2160  | 33.254 | xxxxxx | 33.797 | xxxxxx |

| Name     | Resolution | Caffe    | OpenCV    | mxnet     |
|----------|------------|----------|-----------|-----------|
| BQSquare | 416x240    | xxxxxxxx | 0.267990  | xxxxxxxxx |
| BQMall   | 832x480    | xxxxxxxx | 0.958070  | xxxxxxxxx |
| Cactus   | 1920x1080  | xxxxxxxx | 4.983796  | xxxxxxxxx |
| Traffic  | 2560x1600  | xxxxxxxx | 10.294819 | xxxxxxxxx |
| Runners  | 3840x2160  | xxxxxxxx | 20.742526 | xxxxxxxxx |
