import sys
import os
import networkx as nx
import numpy as np
import pylab as plt
from wind import *
from PyQt5 import QtCore, QtGui, QtWidgets


class MyWin(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        QtWidgets.QWidget.__init__(self, parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        # Вешаем на кнопку функцию PoemCheck
        self.ui.pushButton.clicked.connect(self.Funk)

    # Описываем функцию
    def Funk(self):
        stroki=self.ui.textEdit.toPlainText()
        f = open('obraz', 'w')
        f.write(stroki+'\n')
        f.close()
        stroki=self.ui.textEdit_2.toPlainText()
        f = open('reprule', 'w')
        f.write(stroki+'\n')
        f.close()
        os.system('./prog')

        with open('result', 'r') as file:
            lst = file.readlines()
        lst = [[int(n) for n in x.split()] for x in lst]
        #print(lst)

        G = nx.DiGraph(np.array(lst))
        #G.add_weighted_edges_from([(0, 1, 3.0), (1, 2, 7.5)])
        pos=nx.spring_layout(G,k=0.1,iterations = 1000)
        nx.draw(G)
        # specifiy edge labels explicitly
        #edge_labels=dict([((u,v),'color'+str(d['weight']))
                     #for u,v,d in G.edges(data=True)])
        #nx.draw_networkx_edge_labels(G,pos,edge_labels=edge_labels)
        #nx.draw_networkx_labels(G, pos)
        plt.show()

if __name__=="__main__":
    app = QtWidgets.QApplication(sys.argv)
    myapp = MyWin()
    myapp.show()
    sys.exit(app.exec_())
