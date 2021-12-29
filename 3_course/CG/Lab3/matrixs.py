import numpy as np


def translate(x,y,z):
    return np.array([
        [1,0,0,0],
        [0,1,0,0],
        [0,0,1,0],
        [x,y,z,1]])

def scale(a):
    return np.array([
        [a,0,0,0],
        [0,a,0,0],
        [0,0,a,0],
        [0,0,0,1]])
        
def scale_x(a):
    return np.array([
        [a,0,0,0],
        [0,1,0,0],
        [0,0,1,0],
        [0,0,0,1]])
        
def scale_y(a):
    return np.array([
        [1,0,0,0],
        [0,a,0,0],
        [0,0,1,0],
        [0,0,0,1]])
        
def scale_z(a):
    return np.array([
        [1,0,0,0],
        [0,1,0,0],
        [0,0,a,0],
        [0,0,0,1]])
        
def rotate_x(angle):
    return np.array([
        [1,0,0,0],
        [0,np.cos(angle),np.sin(angle),0],
        [0,-np.sin(angle),np.cos(angle),0],
        [0,0,0,1]])
        
def rotate_y(angle):
    return np.array([
        [np.cos(angle),0,-np.sin(angle),0],
        [0,1,0,0],
        [np.sin(angle),0,np.cos(angle),0],
        [0,0,0,1]])
        
def rotate_z(angle):
    return np.array([
        [np.cos(angle),np.sin(angle),0,0],
        [-np.sin(angle),np.cos(angle),0,0],
        [0,0,1,0],
        [0,0,0,1]])