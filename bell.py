import tkinter as tk
from tkinter import messagebox
import pyrebase
flag=0

config = {
  "apiKey": "MY FIREBASE API KEY",
  "authDomain": "projectId.firebaseapp.com",
  "databaseURL": "https://compubell-8cfcb-default-rtdb.firebaseio.com/",
  "storageBucket": "zwxheKFxzueOpC1fVIdOrmsZv1tJbW8YtuapkIQh",
}

def info(message, title="ShowInfo"):
    root = tk.Tk()
    root.withdraw()
    top = tk.Toplevel(root)
    top.iconify()
    messagebox.showinfo(title, message, parent=top)
    top.destroy()
    root.destroy()


def stream_handler(message):
    global flag
    if (flag==0):
        flag=1
        print("Ignored first iteration")
        return 6
    info("Somone is at the door", "Doorbell")
    print("Detected a change")

firebase = pyrebase.initialize_app(config)

db=firebase.database()
my_stream=db.child("value").stream(stream_handler)
print("Waiting to detect a change in database")
