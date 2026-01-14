# This is a multivariable linear regression in python
# Importing real estate data scraped from Realtor.com in data.csv
# Data Gathered using my program
import numpy as np
import csv

# Only using pandas for data importing and cleaning
# Numpy used for the rest
import pandas as p

df = p.read_csv('data.csv')
df = df.drop(columns=["address", "link", "sqft"]).dropna() # -> Removing sqft because of assumed colinearity with beds and bathrooms
# Now we convert back to numpy
x = df.to_numpy()
# Gets the data, and then gets the y values
(X_mat, y_val) = x[:,-2:], x[:,0]

# Generation of the new X matrix
def newMatrix(matrix):
    (n, p_min1) = matrix.shape
    p = p_min1 + 1

    # X is changed to have a row of 1s in the 1st Column
    X = np.ones(shape=(n, p))
    X[:, 1:] = matrix

    return X

# Creating a function to predict
# A function to create the best model is needed
def predict(model, X):
    # Model is a vector with shape n by 1
    # X is a matrix with shape n by p-1
    # A dot product is taken between the altered X and the model
    return np.dot(newMatrix(X), model)

# Imporing linear algebra module 
from numpy.linalg import inv
def fit(X, y):
    # Uses the normal equation -> https://www.geeksforgeeks.org/machine-learning/ml-normal-equation-in-linear-regression/
    return np.dot(np.dot(inv(np.dot(newMatrix(X).T, newMatrix(X))), newMatrix(X).T), y)

# Prints results of prediction against already loaded values
print(predict(fit(X_mat, y_val), X_mat))