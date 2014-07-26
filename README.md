Artificial-Neural-Networks
==========================

an artificial neural network to identify images of
handwritten digits.
the input will be images of handwritten digits (0-9). All images will be
28x28, with each pixel having a greyscale value between 0-255. The images are all stored
in a single binary file. The labels will be a list of integers, representing which digit is
being shown in the image. The labels are all stored in a separate binary file. Both of
these files begin with a few metadata integer values (number of images, number of
rows/columns, etc.).

Your program's output is simply a list of the predicted values of each of the test images,
as decided by your network. These values should all be saved in a single text file in the
same order as they are in the test file. For example, if there are 5 test images and your
program decides that they are images of the digits 1, 4, 9, 0, 3, then your output will be:
1
4
9
0
3
Your program will take 4 command-line arguments. These are the file paths to the
training images, training labels, testing images, and output files respectively. Here’s the
breakdown of what your program must do:
• Construct/initialize a neural network
• Read the training data
• Use the training data to train the network (as described above)
• Read the testing data
• Evaluate the testing data using your network
• Output a text file containing the predictions for the testing data

We are providing separate image and label files for both training and testing. This will
allow you to evaluate the performance of your network before submission.
We are not going to specify any of the parameters (number of layers, number of neurons
per layer, learning rate, etc.) and instead will give you a target prediction accuracy of
85%.

