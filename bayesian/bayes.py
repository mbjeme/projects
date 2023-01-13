import pickle
import numpy as np
from skimage.transform import resize
from scipy.stats import norm
from scipy.stats import multivariate_normal
import matplotlib.pyplot as plt


def unpickle(file):
    with open(file, 'rb') as f:
        dict = pickle.load(f, encoding="latin1")
    return dict

# Function to calculate accuracy.
def class_acc(pred,gt):
    print(f"Counts the accuracy...")
    count = 0

    if (len(pred) == len(gt)):
        for ind in range(0, len(pred)):
            if pred[ind] == gt[ind]:
                count += 1

    answer = (count / len(pred))*100

    print("Done")
    print()
    return answer

def cifar10_color(X):
    print(f"Rezising the images...")

    X_mean = []

    # Resizes images one by one
    for image in X:
        X_mean.append(resize(image, (1, 1, 3), preserve_range=True))

    X_p = np.array(X_mean)

    # Modifies the array
    X_p = X_p.reshape(len(X),3)

    X_p = np.array(X_p).astype(float)

    print("Done")
    print()
    return X_p

def cifar10_2x2_color(X, n):
    print(f"Rezising the images...")

    X_mean = []

    # Resizes the images one by one
    for image in X:
        X_mean.append(resize(image, (n, n, 3), preserve_range=True))

    X_p = np.array(X_mean)
    X_p = X_p.reshape(len(X), (n*n*3))
    X_p = np.array(X_p).astype(float)

    print("Done")
    print()
    return X_p


def cifar_10_naivebayes_learn(X, Y):
    print("Naive bayes learning...")

    # Creates lists inside a list
    x_sep = [[] for i in range(10)]

    # Creates lists for each class.
    for i in range(X.shape[0]):
        x_sep[Y[i]].append(X[i])

    rgb_mu = []
    rgb_sigma = []
    p = []

    # Goes through all classes and calculates mu, sigma and p.
    for i in range(10):

        rgb_mu.append(np.mean(x_sep[i], axis=0))
        rgb_sigma.append(np.std(x_sep[i], axis=0))
        p.append(len(x_sep[i]) / Y.size)

    print("Done")
    print()
    return np.array(rgb_mu), np.array(rgb_sigma), np.array(p)

def cifar_10_bayes_learn(Xf, Y):
    print("Bayes learning...")

    x_sep = [[] for i in range(10)]

    # Creates lists with values for each class.
    for i in range(Xf.shape[0]):
        x_sep[Y[i]].append(Xf[i])

    rgb_mu = []
    rgb_sigma = []
    p = []

    # Goes through all classes and calculates mu, sigma and p.
    for i in range(10):

        rgb_mu.append(np.mean(x_sep[i], axis=0))
        rgb_sigma.append(np.cov(np.transpose(np.array(x_sep[i]))))
        p.append(len(x_sep[i]) / Y.size)

    print("Done")
    print()

    return np.array(rgb_mu), np.array(rgb_sigma), np.array(p)


def cifar10_classifier_naivebayes(x, mu_values, sigma_values, p_values):
    # Classification of the images.
    post = [norm.pdf(x[0], mu[0], sd[0]) * norm.pdf(x[1], mu[1], sd[1]) *
            norm.pdf(x[2], mu[2], sd[2]) * p for mu, sd, p in zip(mu_values,
                                                                  sigma_values,
                                                                  p_values)]

    return np.argmax(post, axis=0)

def cifar10_classifier_bayes(x, mu_values, sigma_values, p_values):
    print("Bayes calculating classes...")

    # Classification of the images.
    post = [multivariate_normal.pdf(x, mu, cov) * p for mu, cov, p in zip(mu_values, sigma_values,p_values)]

    print("Done")
    print()
    return np.argmax(post, axis=0)

def main():

    # Searching for the cifar-10.
    datadict_1 = unpickle(
        '/Users/data_batch_1')
    datadict_2 = unpickle(
        '/Users/data_batch_2')
    datadict_3 = unpickle(
        '/Users/data_batch_3')
    datadict_4 = unpickle(
        '/Users/data_batch_4')
    datadict_5 = unpickle(
        '/Users/data_batch_5')

    testdict = unpickle(
        '/Users/test_batch')

    x_1 = datadict_1["data"]
    y_1 = datadict_1["labels"]
    x_2 = datadict_2["data"]
    y_2 = datadict_2["labels"]
    x_3 = datadict_3["data"]
    y_3 = datadict_3["labels"]
    x_4 = datadict_4["data"]
    y_4 = datadict_4["labels"]
    x_5 = datadict_5["data"]
    y_5 = datadict_5["labels"]

    # Modifying training data for use.
    X = np.concatenate((x_1, x_2, x_3, x_4, x_5))
    Y = np.concatenate((y_1, y_2, y_3, y_4, y_5))

    X_test = testdict["data"]
    Y_test = testdict["labels"]

    labeldict = unpickle(
        '/Users/batches.meta')
    label_names = labeldict["label_names"]

    # Reshaping and modifying the training images.
    X = X.reshape(50000, 3, 32, 32).transpose(0, 2, 3, 1).astype("int32")
    Xp = cifar10_color(X)

    # Counts naive values for mu, sigma and p.
    mu_values_naive, sigma_values_naive, p_naive = cifar_10_naivebayes_learn(Xp[0:1000],Y[0:1000])

    # Reshaping and modifying the test images for naive bayes.
    X_test = X_test.reshape(10000, 3, 32, 32).transpose(0, 2, 3, 1).astype("int32")
    X_test_1x1 = cifar10_color(X_test[0:1000])

    output_1 = []

    # Classifying images one by one.
    for n in range(0, len(X_test_1x1)):
        value = cifar10_classifier_naivebayes(X_test_1x1[n], mu_values_naive, sigma_values_naive, p_naive)
        output_1.append(value)

    # Calculates the accuracy.
    classified_naive = np.array(output_1)
    acc_1 = class_acc(classified_naive, Y_test[0:1000])

    # Counts mu, sigma and p and classifies according to accuracy of each class.
    mu_values, sigma_values, p = cifar_10_bayes_learn(Xp[0:10000],Y[0:10000])
    bayes_class = cifar10_classifier_bayes(X_test_1x1[0:1000], mu_values, sigma_values, p)

    # Counts the accuracy.
    classified = np.array(bayes_class)
    acc_2 = class_acc(classified, Y_test[0:1000])

    # Creates list of bayes' accuracies and adds 1x1 accuracy to the list.
    accuracies_bayes = []
    accuracies_bayes.append(acc_2)

    # Calculates accuracy for each 2x2, 3x3 and so on
    # Last value 17x17 because can not compute covariance for 18x18 anymore
    for n in range(2,18):
        print(f"Counts the accuracy for {n}x{n} image...")

        # Resizes 32 x 32 image to n x n image both in training and testdata
        Xpi = cifar10_2x2_color(X,n)
        test_Xi = cifar10_2x2_color(X_test, n)

        # Count mu, sigma and p for n x n image
        mu_i, sigma_i, p_i = cifar_10_bayes_learn(Xpi[0:10000],
                                                        Y[0:10000])

        # Classifies according to the accuracy.
        bayes_i = cifar10_classifier_bayes(test_Xi[0:1000], mu_i,
                                             sigma_i, p_i)

        # Counts accuracy and saves it to the list of all accuracies.
        classified_i = np.array(bayes_i)
        acc_i = class_acc(classified_i, np.transpose(Y_test[0:1000]))
        accuracies_bayes.append(acc_i)

    # Prints accuracy of naive bayes
    print(f"Accuracy of naive bayes: {acc_1:.2f} %")

    # Prints the accuracy for 2x2, 3x3... so on.
    for x in range(len(accuracies_bayes)):
        print(f"Accuracy for bayes {x+1}x{x+1} image: {accuracies_bayes[x]:.2f} %")
    print("For other values the n x n accuracy could not been calculated!")

    # Ploting a graph of accuracies
    x_axis = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
    plt.bar(x_axis, accuracies_bayes, color=['blue'])
    plt.title("Accuracies for the n x n images")
    plt.xlabel("n x n")
    plt.ylabel("%")
    plt.show()



if __name__ == '__main__':
    main()
