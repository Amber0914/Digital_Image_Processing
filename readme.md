## Digital Image Processing C++
The dataset is available [here](http://www.imageprocessingplace.com/DIP-3E/dip3e_book_images_downloads.htm).
* **[Histogram Equalization](#Histogram-Equalization)**
* **[Losspass/Highpass Filter](#LosspassHighpass-Filter-3x3)**: Mean and Median
* **[Edge detection](#Edge-Detection)**: Sobel, Prewitt and Robert
* **[User-Defined Thresholding](https://hackmd.io/-ZFZ6ZcjTnaiAoCZrbYxJw?both#User-Defined-Thresholding)**
### Enviroment
```
macOS 10.13.6
g++ 4.2.1
```
### Library - only for I/O
```
opencv 3.4.2
```

## Histogram Equalization
Histogram Equalizaion is a useful image processing method for contrast adjustment. 


### Command for  Compiler
```
g++ $(pkg-config --cflags --libs opencv) histogram.cpp -o histogram
```

### Command for Execution
```
./histogram input_img output_img
```
* For example
```
./histogram test.tif output.tif
```
> Taking a image, Chapter3, Fig0320(4)(bottom_left).tif, as example.

![](https://i.imgur.com/CPpG2oy.png)

## Losspass/Highpass Filter (3x3)
Spatial Filtering is a useful way for reducing noises of image.

### Command for  Compiler
```
g++ $(pkg-config --cflags --libs opencv) filter.cpp -o filter
```

### Command for Execution
```
./filter input_img
```
* For example
```
./filter test.tif
```
> Taking a image, Chapter3, Fig0335(a)(ckt_board_saltpep_prob_pt05).tif, as example.
> Note that the size of mean_filter and median_filter is 3x3 for demonstration.

![](https://i.imgur.com/ogfSSgc.png)


## Edge Detection
Here, we mplement three edge detection method -- Sobel, Prewitt and Robert.

### Command for  Compiler
```
g++ $(pkg-config --cflags --libs opencv) edge_detection.cpp -o edge_detection
```

### Command for Execution
```
./edge_detection input_img mode
```
* For example
```
./edge_detection median_test.tif sobel
```
> Taking a median result above as example.

![](https://i.imgur.com/cDlGURf.jpg)


## User-Defined Thresholding
Thresholding is the simplest method of image segmentation.

### Command for  Compiler
```
g++ $(pkg-config --cflags --libs opencv) threshold.cpp -o threshold
```

### Command for Execution
```
./threshold input_file threshold_value
```
* For example
```
./threshold test.tif 55
```
Note that the proper value should be 0≤threshold_value≤255

> Taking a image, Chapter3,Fig0316(3)(third_from_top).tif, as example.

![](https://i.imgur.com/X8285I5.png)