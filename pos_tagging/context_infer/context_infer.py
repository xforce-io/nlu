import sys, time, pdb
import numpy as np
import matplotlib.pyplot as plt

from keras.preprocessing import sequence
from keras.models import Sequential, load_model
from keras.layers.core import Dense, Dropout, Activation
from keras.layers import Embedding, Dense, LSTM
from keras.datasets import imdb
from keras.utils import np_utils
from keras.optimizers import SGD, Adam, RMSprop

max_features = 28
max_length = 4
embedding_dim = 100
batch_size = 128
epochs = 3
outputPath = "data/model/theModel"

def charMusk(c) :    
    if ord(c) < ord('a') or ord(c) > ord('z') :
        return 1
    else :
        return ord(c) - ord('a') + 2

def musk2Char(val) :
    if val == 0 : 
        return '|'
    elif val == 1 :
        return '*'
    else :
        return chr(ord('a') + val - 2)

def preprocess(inputpath) :
    X = []
    y = []
    for line in open(inputpath, "r") :
        output = []
        pos = 0
        touched = False
        while pos < len(line) :
            if line[pos] == '/' :
                if touched == True :
                    output += [charMusk(line[pos+1])]
                else :
                    touched = True
            pos += 1        

        if len(output) == 0 :
            continue

        output = [0, 0] + output + [0, 0]

        pos = 2

        while pos < len(output) - 2 :
            X += [output[pos-2]]
            X += [output[pos-1]]
            X += [output[pos+1]]
            X += [output[pos+2]]
            y += [output[pos]]
            pos += 1

    num_samples = int(len(X)/max_length)
    return (
            np_utils.to_categorical(X, max_features).reshape(num_samples, max_features*max_length),
            np_utils.to_categorical(y, max_features),
        )

def train(data) :
    num_train = len(data[0]) - 100
    x_train = data[0][:num_train]
    y_train = data[1][:num_train]
    x_test = data[0][num_train:]
    y_test = data[1][num_train:]

    model = Sequential()
    model.add(Dense(512, input_shape=(max_features*max_length,)))
    model.add(Activation('relu'))
    model.add(Dropout(0.2))
    model.add(Dense(512))
    model.add(Activation('relu'))
    model.add(Dropout(0.2))
    model.add(Dense(max_features))
    model.add(Activation('softmax'))
    model.compile(loss='categorical_crossentropy',
                  optimizer=RMSprop(),
                  metrics=['accuracy'])

    start_time = time.time()
    history = model.fit(x_train, y_train,
                        batch_size=batch_size,
                        nb_epoch=epochs,
                        validation_data=(x_test, y_test))
    average_time_per_epoch = (time.time() - start_time) / epochs
    model.save(outputPath)

if __name__ == "__main__" :
    if len(sys.argv) != 2 or (sys.argv[1] != "train" and sys.argv[1] != "pred") :
        print("invalid args")
        sys.exit(1)

    if sys.argv[1] == "train" :
        data = preprocess("data/input/199801.txt")
        train(data)
    else :
        model = load_model(outputPath)
        sample = ['c', 'n', 'd', 'a']
        musked = []
        for i in range(max_length) :
            musked += [charMusk(sample[i])]
        musked = np_utils.to_categorical(musked, max_features),
        predRes = model.predict(np.array(musked).reshape(1,max_features*max_length))

        for i in range(max_features) :
            possi = predRes[0][i]
            print("%s-%f" % (musk2Char(i), possi))
