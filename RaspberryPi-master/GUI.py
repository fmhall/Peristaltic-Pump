import tkinter

class Root(tkinter.Tk) :
    def __init__(self):
        super().__init__()
        self.title("Multichannel Peristaltic Pump Interface")
        self.GUI_canvas = tkinter.Canvas(self)
        self.motors_canvas = tkinter.Canvas(self)
        self.frame_motors = tkinter.Frame(self, borderwidth="2", relief="ridge")  
        self.frame_buttons = tkinter.Frame(self, borderwidth="2", relief="ridge")
        self.frame_labels = tkinter.Frame(self, borderwidth="2", relief="ridge")
        self.frame_GUI = tkinter.Frame(self.GUI_canvas)

        self.scrollbar = tkinter.Scrollbar(self.GUI_canvas, orient="vertical", command=self.GUI_canvas.yview)
        self.GUI_canvas.configure(yscrollcommand=self.scrollbar.set)
        self.GUI_canvas.pack(side=tkinter.TOP, fill=tkinter.BOTH, expand=1)
        self.scrollbar.pack(side=tkinter.RIGHT, fill=tkinter.Y)
        self.canvas_frame = self.GUI_canvas.create_window((0,0),window=self.frame_GUI,anchor='n')

        self.simple_label = tkinter.Label(self.frame_labels, text="Pumps")  
        self.another_label = tkinter.Label(self.frame_labels, text="Motors")
        
        self.closing_button = tkinter.Button(self.frame_buttons, text="Close window", command=self.destroy)  
        self.another_button = tkinter.Button(self.frame_buttons, text="Do nothing")
        
        # self.frame_labels.grid(column=0, row=0, sticky="ns")  
        # self.frame_buttons.grid(column=1, row=0)
        
        self.simple_label.grid(column=0, row=0, sticky="ew")  
        self.another_label.grid(column=0, row=1, sticky="ew")
        
        self.closing_button.pack(fill="x")  
        self.another_button.pack(fill="x")

if __name__=="__main__":
    root = Root()
    root.mainloop()  