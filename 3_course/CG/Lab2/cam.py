import pygame as pg
import numpy as np
import objct
import matrixs

class Camera:
    def __init__(self,screen, height, width):
        self.View_mat = np.array([[1,0,0,0],[0,1,0,0],[0,0,1,0],[0,0,0,1]])
        self.Screen = screen
        self.Width = width
        self.Height = height
        self.moving_speed = 0.1
        self.rotation_speed = 0.015
    
    def Point_to_cam(self,point):
        rotate_to_cam = self.to_cam_matrix()
        px,py,pz,pw = self.Pos
        
        translate_to_cam = matrixs.translate(-px,-py,-pz)
        point = point @ translate_to_cam
        
        point = point @ rotate_to_cam
        return point

    def Point_pojection(self,point):
        x,y,z,w = point
        x = self.Width/2 + x
        y = self.Height/2 - y
        return [int(x),int(y)]


    def Draw_polygon(self,points = list()):
        point_to_draw = list()
        points_cam = list()
        for point in points:
            p_c = point @ self.View_mat @ matrixs.scale(25)
            points_cam.append(p_c)
            p_p = self.Point_pojection(p_c)
            point_to_draw.append(p_p)
        p0 = points_cam[0]
        p1 = points_cam[1]
        p2 = points_cam[2]
        v1 = np.array([p1[0]-p0[0],p1[1]-p0[1],p1[2]-p0[2]])
        v2 = np.array([p2[0]-p1[0],p2[1]-p1[1],p2[2]-p1[2]])
        norm = np.cross(v1,v2)
        p0 = np.array([0,0,1])
        if(np.dot(p0,norm)/(np.sqrt(p0.dot(p0))* np.sqrt(norm.dot(norm))) >= 0):
            pg.draw.polygon(self.Screen,"darkslategray",point_to_draw,1)
            #pg.draw.polygon(self.Screen,"white",point_to_draw,1)
            

    def Draw_obj(self,obj):
        for face in obj.Faces:
            polygon = list()
            for point in face:
                polygon.append(obj.Points[point])
            self.Draw_polygon(polygon)

    def Control(self):
        key = pg.key.get_pressed()
        if key[pg.K_RIGHT]:
            rotate = matrixs.rotate_y(self.rotation_speed)
            self.View_mat = self.View_mat @ rotate
        if key[pg.K_LEFT]:
            rotate = matrixs.rotate_y(-self.rotation_speed)
            self.View_mat = self.View_mat @ rotate
        if key[pg.K_UP]:
            rotate = matrixs.rotate_x(-self.rotation_speed)
            self.View_mat = self.View_mat @ rotate
        if key[pg.K_DOWN]:
            rotate = matrixs.rotate_x(self.rotation_speed)
            self.View_mat = self.View_mat @ rotate

