import pickle
import numpy as np
import tensorflow as tf
import keras
from tensorflow.keras.models import Sequential
from keras.layers import Flatten
from tensorflow.keras.layers import Dense

def unpickle(file):
    with open(file, 'rb') as f:
        dict = pickle.load(f, encoding="latin1")
    return dict

def createVectors(list):
    classes = []

    for num in list:
        vector = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
        vector[num] = 1

        classes.append(vector)

    return classes

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

    X = X.reshape(50000, 3, 32, 32).transpose(0, 2, 3, 1).astype("float32") / 255
    X_test = X_test.reshape(10000, 3, 32, 32).transpose(0, 2, 3, 1).astype(
        "float32") / 255

    # Creating the neuronetwork
    model = Sequential()
    model.add(Flatten(input_shape=(32,32,3)))
    model.add(Dense(100, input_dim=3072, activation='relu'))
    model.add(Dense(20, activation='sigmoid'))
    model.add(Dense(20, activation='sigmoid'))
    model.add(Dense(20, activation='sigmoid'))
    model.add(Dense(10, activation='softmax'))
    opt = tf.keras.optimizers.SGD(lr=0.06)
    model.compile(optimizer=opt, loss='categorical_crossentropy', metrics=['categorical_accuracy'])

    Y_onehots = np.array(createVectors(Y))

    model.fit(np.array(np.array(X)), np.array(Y_onehots), epochs=15, verbose=1, validation_split=0.2)


    Y_predicted = model.predict(np.array(X_test))

    answers = []
    for accs in Y_predicted:
        acc = np.argmax(np.array(accs))
        answers.append(acc)

    accuracy = class_acc(answers, Y_test)

    model.summary()

    print()
    print(f"Accuracy of a full connected neural network:  {accuracy:.2f}  %")
    print()
    print(f"The accuracy of 1NN classifier is 20.00 %")
    print()
    print(f"The accuracy of a Bayes classifier for 1x1 image is 24.90 %")
    print(f"The accuracy for the best bayes (7x7 image) is 41.10 %")
    print()
    print(f"The full connected neural network gives the best accuracy and")
    print(f"the accuracy is significantly higher than in 1x1 image bayes and")
    print(f"1NN classifiers. The best bayes' accuracy for the 7x7 image")
    print(f"has similar values to the neural network.")
    print()
    print(f"Accuracy values taken from previous exercises.")



if __name__ == '__main__':
    main()
