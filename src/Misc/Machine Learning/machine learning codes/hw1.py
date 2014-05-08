#!/usr/bin/env python
import numpy as np
import random

def generate_points(num, low, high):
    """Generate uniformly ditributed points in [low,high]*[low,high]

    Args:
      num (int): number of points to be generated.
      low, high (int): the interval (low, high) for points.

    Returns:
      ndarray of points.
    """
    return np.random.uniform(low, high, num * 2).reshape(num, 2)

def generate_target_function(low, high):
    """Generate a target funciton.

    Generate two uniformly ditributed points in [low,high]*[low,high]
    to form a line for the target function.

    Args:
      low, high (int): the interval (low, high) for points.

    Returns:
      lambda function.
    """
    point1 = np.random.uniform(low, high, 2)
    point2 = np.random.uniform(low, high, 2)
    if point1[0] != point2[0]:
        a = (point1[1] - point2[1]) / (point1[0] - point2[0])
    else:
        a = (point1[1] - point2[1]) / 0.0000001
    b = point1[1] - a * point1[0]
    fun = lambda x: a * b + b
    return fun

def sign(x, compare_to=0):
    """Compare x with compare_to.
    Returns:
      the compare result.
    """
    if x > compare_to:
        return 1
    else:
        return -1

def classify_point(point, func):
    """Classify point according func to 1 and -1.

    Arg:
      point (ndarray): input point
      func (lambda function): the classify function.

    Returns:
      the classify_result -1 or 1.
    """
    point_x = point[0]
    point_y = point[1]
    func_y = func(point_x)
    compare_to = point_y
    return sign(func_y, compare_to)

def compute_output(data, func):
    """Compute the output yn.

    Arg:
      data (ndarray): the input points data
      func (lambda function): the function to compute

    Returns:
      the outputs yn in -1 and 1.
    """
    output_yn = []
    for i in range(data.shape[0]):
        point = data[i]
        output_yn.append(classify_point(point, func))
    return output_yn

def compute_misclassify_set(set, yn, weight):
    """Return list of index of misclassified items
    """
    res = []
    for i in range(set.shape[0]):
        if hypothesis(weight, set[i]) != yn[i]:
            res.append(i)
    return res

def hypothesis(weight, x):
    """Hypothesis function returns w0 x0 + w1 x1 ... + wn xn
    """
    res = 0
    for i in range(x.shape[0]):
        res += weight[i] * x[i]
    return sign(res)
     
def pla(training_set, yn, weight):
    """Perceptron Learning Algorithm.

    - if there is no misclassified point, exit
    - pick a random misclasified point from misclassified set.
    - update weights

    Args:
      training_set (ndarray): the input training set.
      yn (list): the ouput of target function.
      weight (list): the training weght vector.

    Return:
      weight (list): the training weght vector.
      iteration (int): the number of iiteration to coverage.
    """
    iteration = 0
    while True:
        iteration += 1
        misclassify_set = compute_misclassify_set(training_set, yn, weight)
        if len(misclassify_set) == 0:
            break
        index = random.randint(0, len(misclassify_set) - 1)
        misclassify_index = misclassify_set[index]
        x_misclassify = training_set[misclassify_index]
        y_misclassify = yn[misclassify_index]
        res_hypothesis = hypothesis(weight, x_misclassify)
        if y_misclassify != res_hypothesis:
            for i in range(len(weight)):
                weight[i] = (weight[i] +
                (y_misclassify - res_hypothesis) * x_misclassify[i])
    return weight, iteration

def build_training_set(input_x):
    """Add 1.0 to x0.
    """
    axis0 = input_x.shape[0]
    x0_array = np.ones((axis0, 1))
    return np.concatenate((x0_array, input_x), axis=1)

def diff_two_function(target_func, weight):
    LIMIT = 10000
    num_diff = 0
    for i in range(LIMIT):
        x = np.random.uniform(-1, 1)
        y = np.random.uniform(-1, 1)
        train_array = np.array([1.0, x, y])
        sign_f = sign(target_func(x), y)
        sign_g = hypothesis(weight, train_array)
        if sign_f != sign_g:
            num_diff += 1
    return num_diff / (LIMIT * 1.0)

def run_pla(num_runs, num_points):
    """Run the Perceptron Learning Algorithm.

    Args:
      num_runs (int): the number of runs.
      num_points (int): the number sampling points.
    """
    num_iterations = []
    num_diff = [] # number of difference between f ang g
    for i in range(num_runs):
        points = generate_points(num_points, -1, 1)
        target_function = generate_target_function(-1, 1)
        output_yn = compute_output(points, target_function)
        training_set = build_training_set(points)
        weight = [0, 0, 0]

        weight, num_iteration = pla(training_set, output_yn, weight)
        num_iterations.append(num_iteration)
        num_diff.append(diff_two_function(target_function, weight))

    print 'average number of iteration: %f' %(sum(num_iterations) /
                                              len(num_iterations)*1.0)
    print 'average probility of f not equal g: %f' %(sum(num_diff) /
                                                     len(num_diff)*1.0)

def exercise7_8():
    """Learning from data, excercise 7 and 8 in hw1.
    """
    run_pla(1000, 10)

def exercise9_10():
    """Learning from data, excercise 9 and 10 in hw1.
    """
    run_pla(1000, 100)

if __name__ == '__main__':
    exercise7_8()
    exercise9_10()
