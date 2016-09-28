from tkinter import *
from tkinter import ttk


class GraphWindow(Frame):
    def __init__(self, parent):
        Frame.__init__(self, parent, background="white")
        self.parent = parent
        self.parent.title("Gráfico de frequência")
        self.style = ttk.Style()
        self.style.theme_use("default")
        self.centralizeWindow()
        self.pack(fill=BOTH,expand=1)

    def centralizeWindow(self):
        w = 800
        h = 600
        sw = self.parent.winfo_screenwidth()
        sh = self.parent.winfo_screenheight()
        x = (sw - w)/2
        y = (sh - h)/2
        self.parent.geometry('%dx%d+%d+%d' % (w, h, x, y))


def plotGraph(nText, fText):
    try:
        value = int(nText.get())
        fText.set((value+5))
    except ValueError:
        print("ERRROUUU")


def main():
    root = Tk()
    root.resizable(width=FALSE, height=FALSE)
    gWindow = GraphWindow(root)
    root.mainloop()



if __name__ == '__main__':
    main()
