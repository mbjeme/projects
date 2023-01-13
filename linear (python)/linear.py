import matplotlib.pyplot as plt
import numpy as np
from matplotlib.backend_bases import MouseButton

def my_linfit(x,y):
    # Calculation for a and b
    b=(sum(x**2)*sum(y)-sum(x)*sum(y*x))/(len(x)*sum(x**2)-(sum(x))**2)
    a=(sum(x*y)-b*sum(x))/sum(x**2)
    return a,b

def main():
    # Create a figure and get the points from a mouse click
    plt.figure(1)
    plt.subplots()
    coords = []
    coords.append(np.asarray(plt.ginput(n=-1,show_clicks=True, mouse_stop=MouseButton.RIGHT)))
    plt.close()

    # Adjust the points
    coords = np.asarray(coords)
    coords = np.reshape(coords, (np.shape(coords) [1],2))
    plt.axes()

    # Create points and line in the window.
    x = coords[:, 0]
    y = coords[:, 1]
    a, b = my_linfit(x, y)
    plt.plot(x, y, 'bx')
    xp = np.arange(min(x) - 0.1, max(x) + 0.1, 0.1)
    plt.plot(xp,a*xp+b,'r-')
    print(f"My fit: a={a} and b={b}")
    plt.show()

if __name__ == '__main__':
    main()


