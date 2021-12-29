import numpy as np

class Object:
    def get_normals(self,points, faces):
        self.Normals = list()
        for face in faces:
            p0 = points[face[0]]
            p1 = points[face[int(len(face)/3)]]
            p2 = points[face[int(len(face)/3)*2]]
            v1 = np.array([p1[0]-p0[0],p1[1]-p0[1],p1[2]-p0[2]])
            v2 = np.array([p2[0]-p1[0],p2[1]-p1[1],p2[2]-p1[2]])
            norm = np.cross(v1,v2)
            norm = norm / (np.sqrt(norm.dot(norm)))
            self.Normals.append(norm)

    def __init__(self,points = list(), faces = list()):
        self.Points = list()
        for point in points:
            self.Points.append(np.array([point[0],point[1],point[2],1]))
        self.Faces = faces
        self.get_normals(self.Points,self.Faces)

    def obj_to_Object(self, filename = ''):
        objFile = open(filename,'r')
        for line in objFile:
            split = line.split(' ')
            if split[0] == "v":
                split[-1] = split[-1].replace('\n','')
                self.Points.append(np.array([float(split[1]),float(split[2]),float(split[3]),1]))
            if split[0] == "f":
                face = list()
                for num in split[1:]:
                    face.append(int(num) - 1)
                self.Faces.append(face)
        objFile.close()
        self.get_normals(self.Points,self.Faces)
