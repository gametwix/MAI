import numpy as np

class Object:
    def __init__(self,points = list(), faces = list()):
        self.Points = list()
        for point in points:
            self.Points.append(np.array([point[0],point[1],point[2],1]))
        self.Faces = faces
        #Дальше должна бы матрица преобразования из локальных координат в глобальные но ее пока не будет

    def obj_to_Object(self, filename = ''):
        objFile = open(filename,'r')
        for line in objFile:
            split = line.split(' ')
            if split[0] == "v":
                split[-1] = split[-1].replace('\n','')
                print(split)
                self.Points.append(np.array([float(split[1]),float(split[2]),float(split[3]),1]))
            if split[0] == "f":
                face = list()
                for num in split[1:]:
                    face.append(int(num) - 1)
                self.Faces.append(face)
        objFile.close()
