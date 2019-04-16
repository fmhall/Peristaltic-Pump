from tkinter import *
from controller import *
from communicator import *
from Arduino import Arduino
import threading
from queue import Queue
import time
class Window(Frame):

    def __init__(self, master=None):
        Frame.__init__(self, master)                 
        self.master = master
        self.init_window()
        self.ard_list = []

    #Creation of init_window
    def init_window(self):

        # changing the title of our master widget      
        self.master.title("GUI")

        # allowing the widget to take the full space of the root window
        self.pack(fill=BOTH, expand=1)

        # creating a menu instance
        menu = Menu(self.master)
        self.master.config(menu=menu)

        # create the file object)
        file = Menu(menu)

        # adds a command to the menu option, calling it exit, and the
        # command it runs on event is client_exit
        file.add_command(label="Exit", command=self.client_exit)
        file.add_command(label="Connect", command=self.getArduinos)
        #added "file" to our menu
        menu.add_cascade(label="File", menu=file)

        # create the file object)
        edit = Menu(menu)

        # adds a command to the menu option, calling it exit, and the
        # command it runs on event is client_exit
        edit.add_command(label="Undo")
        edit.add_command(label="Show Text", command=self.showText)
        #added "file" to our menu
        menu.add_cascade(label="Edit", menu=edit)
        #self.getArduinos()
    def client_exit(self):
        exit()

    def showText(self):
        for ard in self.ard_list:
            text = Label(self, text=str(ard))
            text.pack()
    
    def getArduinos(self):
        # text = Label(self, text="Connecting to Arduinos...")
        # text.pack()
        ard_list1 = setup()
        self.ard_list = ard_list
        self.showText()
        return ard_list
class ThreadedTask(threading.Thread):
    def __init__(self, queue):
        threading.Thread.__init__(self)
        self.queue = queue
    def run(self):
        time.sleep(5)  # Simulate long running process
        self.queue.put("Task finished")

root = Tk()

#size of the window
root.geometry("400x300")

app = Window(root)
root.mainloop()  














# class Root(tkinter.Tk) :
#     def __init__(self):
#         super().__init__()
#         self.title("Multichannel Peristaltic Pump Interface")
#         self.GUI_canvas = tkinter.Canvas(self)
#         # self.motors_canvas = tkinter.Canvas(self)
#         # self.frame_motors = tkinter.Frame(self, borderwidth="2", relief="ridge")  
#         # self.frame_buttons = tkinter.Frame(self, borderwidth="2", relief="ridge")
#         # self.frame_labels = tkinter.Frame(self, borderwidth="2", relief="ridge")
#         # self.frame_GUI = tkinter.Frame(self.GUI_canvas)

#         # self.scrollbar = tkinter.Scrollbar(self.GUI_canvas, orient="vertical", command=self.GUI_canvas.yview)
#         # self.GUI_canvas.configure(yscrollcommand=self.scrollbar.set)
#         self.GUI_canvas.pack(side=tkinter.TOP, fill=tkinter.BOTH, expand=1)
#         # self.scrollbar.pack(side=tkinter.RIGHT, fill=tkinter.Y)
#         # self.canvas_frame = self.GUI_canvas.create_window((0,0),window=self.frame_GUI,anchor='n')

#         # self.simple_label = tkinter.Label(self.frame_labels, text="Pumps")  
#         # self.another_label = tkinter.Label(self.frame_labels, text="Motors")
        
#         # self.closing_button = tkinter.Button(self.frame_buttons, text="Close window", command=self.destroy)  
#         # self.another_button = tkinter.Button(self.frame_buttons, text="Do nothing")
        
#         # # self.frame_labels.grid(column=0, row=0, sticky="ns")  
#         # # self.frame_buttons.grid(column=1, row=0)
        
#         # self.simple_label.grid(column=0, row=0, sticky="ew")  
#         # self.another_label.grid(column=0, row=1, sticky="ew")
        
#         # self.closing_button.pack(fill="x")  
#         # self.another_button.pack(fill="x")

# if __name__=="__main__":
#     root = Root()
#     root.mainloop()  