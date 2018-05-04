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
| Name     | Resolution | Before | OpenCV | mxnet  |
|----------|------------|--------|--------|--------|
| BQSquare | 416x240    | 25.958 | 27.473 | 27.473 |
| BQMall   | 832x480    | 30.280 | 31.328 | 31.328 |
| Cactus   | 1920x1080  | 33.208 | 33.957 | 33.957 |
| Traffic  | 2560x1600  | 35.059 | 35.692 | 35.692 |
| Runners  | 3840x2160  | 33.254 | 33.797 | 33.797 |

| Name     | Resolution | OpenCV    | mxnet     |
|----------|------------|-----------|-----------|
| BQSquare | 416x240    | 0.257206  | 0.362361  |
| BQMall   | 832x480    | 0.996086  | 1.250999  |
| Cactus   | 1920x1080  | 4.841618  | 6.952368  |
| Traffic  | 2560x1600  | 10.005049 | 28.157753 |
| Runners  | 3840x2160  | 19.899424 | fail      |
