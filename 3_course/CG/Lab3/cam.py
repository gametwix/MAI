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
        self.rotation_speed = 0.01

    def Point_pojection(self,point):
        x,y,z,w = point
        x = self.Width/2 + x
        y = self.Height/2 - y
        return [int(x),int(y)]


    def Draw_polygon(self,polygon,light):
        point_to_draw = list()
        points, norm = polygon
        for point in points:
            p_p = self.Point_pojection(point)
            point_to_draw.append(p_p)
        view = np.array([0,0,1])
        pp = points[0]
        #light = pp - light
        light = light / np.sqrt(light.dot(light))
        #view = np.array([view[0],view[1],view[2]])
        #view = view/ np.sqrt(view.dot(view))
        if(np.dot(view,norm[0:3]) >= 0):
            print(np.dot(light,norm))

            color = int((255 * np.dot(light,norm) + 255)/2)
            pg.draw.polygon(self.Screen,pg.Color(color,color,color),point_to_draw,0)

    def Draw_obj(self,obj,light):
        polygons = list()
        points = list()
        light = light @ self.View_mat
        light = light[:3]
        for point in obj.Points:
            points.append(point @ self.View_mat)

        i = 0
        for face in obj.Faces:
            polygon = list()
            norm = obj.Normals[i]
            norm = np.array([norm[0],norm[1],norm[2],1])
            norm = norm @ self.View_mat
            norm = norm[:3]
            for point in face:
                polygon.append(points[point])
            polygons.append([polygon,norm])
            i += 1
        
        #polygons = sorted(polygons ,key = self.GetZ, reverse= True)
        for polygon in polygons:
            self.Draw_polygon(polygon,light)

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

