import pygame as pg
import numpy as np
import objct
import cam
import matrixs

def Gen_py(a,b,h,n,A,B,D):
    points = list()
    t = 0
    m = 0
    top = list()
    cut = list()
    for i in range(n):
        x = a*b*np.cos(t)/(np.sqrt(b**2*np.cos(t)**2 + a**2*np.sin(t)**2))
        y = a*b*np.sin(t)/(np.sqrt(b**2*np.cos(t)**2 + a**2*np.sin(t)**2))
        points.append([x,y,0])
        if(A*x + B*y > m):
            m = A*x + B*y
        t += 2*np.pi / n
    D += m
    for i in range(n):
        x = a*b*np.cos(t)/(np.sqrt(b**2*np.cos(t)**2 + a**2*np.sin(t)**2))
        y = a*b*np.sin(t)/(np.sqrt(b**2*np.cos(t)**2 + a**2*np.sin(t)**2))
        if(h <= D - A*x - B*y):
            points.append([x,y,h])
            top.append(i + n)
        else:
            points.append([x,y,D - A*x - B*y])
            cut.append(i + n)
        t += 2*np.pi / n
    
    
    faces = list()
    faces.append(range(n)[::-1])
    for i in range(n):
        faces.append([i,(i+1)%n,(i+1)%n + n,i + n])
    #faces.append(range(n,2*n))
    if(len(top) >= 3):
        faces.append(top)
    if(len(cut) >= 3):
        for i in range(len(cut)):
            j = (i + 1) % len(cut)
            if(abs(cut[j] - cut[i]) > 1 and abs(cut[j] - cut[i]) < n):
                a = (cut[i] + 1 ) % n + n
                b = (cut[j] - 1 ) % n + n
                cut.insert(i+1,a)
                cut.insert(i+2,b)
                print(cut)
                cut = cut[-5:]+ cut[:-5]
                print(cut)
            
        faces.append(cut)
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
        if(self.pos > 0):
            return self.pos/self.width
        else:
            return 0;


class Program:
    def __init__(self):
        pg.init()
        self.res =  self.width, self.height = 1600, 900
        self.fps = 60
        self.screen = pg.display.set_mode(self.res)
        self.clock = pg.time.Clock()
        self.camera = cam.Camera(self.screen,self.height,self.width)
        pg.display.set_caption('Main')
        pg.font.init()
        self.font = pg.font.SysFont('Hack', 24)
        

    def draw(self):
        self.screen.fill('azure3')
        

    def run(self):
        a = 7
        b = 10
        h = 25
        n = 30
        A = 1
        B = 1
        D = 10
        ob1 = Gen_py(a,b,h,n,A,B,D)
        scale1 = scale_bar(self.screen,self.width - 230,30,200,30)
        scale2 = scale_bar(self.screen,self.width - 230,70,200,30)
        scale3 = scale_bar(self.screen,self.width - 230,110,200,30)
        scale4 = scale_bar(self.screen,self.width - 230,150,200,30)
        scale5 = scale_bar(self.screen,self.width - 230,190,200,30)
        scale6 = scale_bar(self.screen,self.width - 230,230,200,30)
        scale8 = scale_bar(self.screen,self.width - 230,270,200,30)

        textsurface1 = self.font.render('a', False, (0, 0, 0))
        textsurface2 = self.font.render('b', False, (0, 0, 0))
        textsurface3 = self.font.render('h', False, (0, 0, 0))
        textsurface4 = self.font.render('n', False, (0, 0, 0))
        textsurface5 = self.font.render('A', False, (0, 0, 0))
        textsurface6 = self.font.render('B', False, (0, 0, 0))
        textsurface7 = self.font.render('D', False, (0, 0, 0))
        sc = matrixs.scale(10)
        for i in range(len(ob1.Points)):
            ob1.Points[i] = ob1.Points[i] @ matrixs.translate(0,0,D/2)
        light = np.array([20,-20,20,1])
        ss = 0.05
        r_x = matrixs.rotate_x(ss)
        r_y = matrixs.rotate_y(ss)
        r_z = matrixs.rotate_z(ss)
        while True:
            #light = light @ r_x @ r_y @ r_z
            self.camera.Control()
            self.draw()
            self.camera.Draw_obj(ob1,light)
            a = scale1.check_res()*300+70
            
            b = scale2.check_res()*300+100
            h = scale3.check_res()*200+10
            n = int(scale4.check_res()*100) + 6
            A = scale5.check_res() - 0.5
            B = scale6.check_res() - 0.5
            D = scale8.check_res()*200
            ob1 = Gen_py(a,b,h,n,A,B,D)
            for i in range(len(ob1.Points)):
                ob1.Points[i] = ob1.Points[i] @ matrixs.translate(0,0,D/2)
            [exit() for i in pg.event.get() if i.type == pg.QUIT]
            self.screen.blit(textsurface1,(self.width - 250,30))
            self.screen.blit(textsurface2,(self.width - 250,70))
            self.screen.blit(textsurface3,(self.width - 250,110))
            self.screen.blit(textsurface4,(self.width - 250,150))
            self.screen.blit(textsurface5,(self.width - 250,190))
            self.screen.blit(textsurface6,(self.width - 250,230))
            self.screen.blit(textsurface7,(self.width - 250,270))
            pg.display.flip()
            self.clock.tick(self.fps)

if __name__ == '__main__':
    pr = Program()
    pr.run()