import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

dataset = pd.read_csv(r"E:\semester 7\Machine Learning\station_day.csv")
X = dataset.iloc[:, 2:-2].values
y = dataset.iloc[:, 14:15].values

from sklearn.preprocessing import Imputer
imputer = Imputer(missing_values = "NaN", strategy = "mean", axis=0)
imputer.fit(X[:, 0:])
X[:, 0:] = imputer.transform(X[:, 0:])
imputer.fit(y[:, 0:])
y[:, 0:] = imputer.transform(y[:, 0:])
 
#splitting into trainging set and test set
from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size= 0.2, random_state= 0)

# fitting the regression model to the dataset
from sklearn.linear_model import LinearRegression
regressor = LinearRegression()
regressor.fit(X_train, y_train)

#predicting a new result in Regression model
y_pred = regressor.predict(X_test)
for i in X_test:
    y_two = regressor.predict([i])
    
 # predicting individually   
y_one = regressor.predict([[71.36,115.75,1.75,20.65,12.4,12.19,0.1,10.76,109.26,0.17,5.92,0.17]])
if (y_one<=50):
    print("GOOD")
        
elif (y_one>50 and y_one<=100):
    print("Satisfactory")
        
elif (y_one>100 and y_one<=200):
    print("Moderate")
        
elif (y_one>200 and y_one<=300):
    print("Poor")
        
elif (y_one>300):
    print("Very Poor")
        
else:
    print("Invalid Input")

# visualization uisng our own input values   sample plotting
fig = plt.figure()
ax = plt.axes(projection='3d')
def f(x, y):
    return np.sin(np.sqrt(x ** 2 + y ** 2))

x = np.ravel(r*np.sin(theta))
y = np.ravel(r*np.cos(theta))
z = f(x, y)
ax = plt.axes(projection='3d')
ax.scatter(x, y, z, c=z, cmap='viridis', linewidth=0.5)
ax.set_xlabel('CO')
ax.set_ylabel('SO2')
ax.set_zlabel('AQI')


