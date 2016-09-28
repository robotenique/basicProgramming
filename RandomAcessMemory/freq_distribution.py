from tkinter import *
from tkinter import ttk
from tkinter import messagebox



class GraphWindow(Frame):
    def __init__(self, parent):
        Frame.__init__(self, parent, background="white")
        self.parent = parent
        self.parent.title("Gráfico de frequência")
        self.style = ttk.Style()
        self.style.theme_use("default")
        self.centralizeWindow()
        self.pack(fill=BOTH, expand=1)

        s = ttk.Style()
        s.configure('my.TLabel', background="white", font=('Liberation Sans', 16))
        s.configure('TButton', font=('Liberation Sans', 16))
        nLabel = ttk.Label(self, text="N =", style='my.TLabel')
        nLabel.grid(row=0, column=0, sticky=W+E)
        nEntry = ttk.Entry(self, width=20)
        nEntry.grid(row=0, column=1, padx=5, pady=5, ipady=2, sticky=W+E)
        nEntry.insert(0, "6")
        okBtn = ttk.Button(self, text="Calcular", width=10, command=lambda: self.onCalc(nEntry))
        okBtn.grid(row=1, column=1, padx=5, pady=3, sticky=W+E)
        sep = ttk.Separator(self, orient=HORIZONTAL)
        sep.grid(row=2, columnspan=5, sticky="we", pady=5)

    def centralizeWindow(self):
        w = 800
        h = 600
        sw = self.parent.winfo_screenwidth()
        sh = self.parent.winfo_screenheight()
        x = (sw - w)/2
        y = (sh - h)/2
        self.parent.geometry('%dx%d+%d+%d' % (w, h, x, y))

    # @ TODO: Implement the calculation of the matplotlib plot
    def onCalc(self, nEntry):
        errmsg = "Digite um número inteiro válido!"
        try:
            n = int(nEntry.get())
        except ValueError:
            messagebox.showerror("Entrada inválida", errmsg)
            return
        print(n)


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
