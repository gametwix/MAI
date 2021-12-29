import pygame as pg
import numpy as np
import objct
import cam
import matrixs

def gen_fig(size, height):
    points = [[0,height,0]]
    l = np.sqrt(size*size / 0.5857)
    pn = np.array([l,0,0,1])
    p = [pn[0],pn[1],pn[2]]
    points.append(p)
    rotate = matrixs.rotate_y(np.pi/4)
    for i in range(7):
        pn = pn @ rotate
        p = [pn[0],pn[1],pn[2]]
        points.append(p)
    faces = [[1,2,0],[2,3,0],[3,4,0],[4,5,0],[5,6,0],[6,7,0],[7,8,0],[8,1,0],[8,7,6,5,4,3,2,1]]
    return objct.Object(points,faces)
        
class scale_bar:
    def __init__(self,screen,posx,posy,width,height):
        self.x = posx
        self.y = posy
        self.width = width
        self.height = height
        self.pos = 1
        self.screen = screen

    def check_res(self):
        if pg.mouse.get_pressed()[0] != 0:
            mouse_pos = pg.mouse.get_pos()
            if(mouse_pos[0] > self.x and mouse_pos[0] < self.x + self.width and mouse_pos[1] > self.y and mouse_pos[1] < self.y + self.height):
                self.pos = mouse_pos[0] - self.x
        pg.draw.rect(self.screen,'black',pg.Rect(self.x,self.y + self.height/2-3,self.width,3))
        pg.draw.rect(self.screen,'red',pg.Rect(self.x + self.pos, self.y,10,self.height))
        return self.pos/self.width



class Program:
    def __init__(self):
        pg.init()
        self.RES =  self.WIDTH, self.HEIGHT = 1600, 900
        self.FPS = 60
        self.screen = pg.display.set_mode(self.RES)
        self.clock = pg.time.Clock()
        self.camera = cam.Camera(self.screen,self.HEIGHT,self.WIDTH)
        pg.display.set_caption('Main')
        pg.font.init()
        self.font = pg.font.SysFont('Hack', 24)
        

    def draw(self):
        self.screen.fill('azure3')
        

    def run(self):

        
        scale1 = scale_bar(self.screen,self.WIDTH - 230,30,200,30)
        scale2 = scale_bar(self.screen,self.WIDTH - 230,70,200,30)
        textsurface1 = self.font.render('a', False, (0, 0, 0))
        textsurface2 = self.font.render('h', False, (0, 0, 0))
        a = scale1.check_res() * 20
        h = scale2.check_res() * 20
        while True:
            ob1 = gen_fig(a,h)
            self.camera.Control()
            self.draw()
            self.camera.Draw_obj(ob1)
            a = scale1.check_res() * 10
            h = scale2.check_res() * 20
            [exit() for i in pg.event.get() if i.type == pg.QUIT]
            self.screen.blit(textsurface1,(self.WIDTH - 250,30))
            self.screen.blit(textsurface2,(self.WIDTH - 250,70))
            pg.display.flip()
            self.clock.tick(self.FPS)


if __name__ == '__main__':
    pr = Program()
    pr.run()