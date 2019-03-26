# Peristaltic-Pump

## Problem
Peristaltic perfusion pumps are well suited for use in a bioreactor, but current designs are expensive, have limited capacity, not readily scalable, lack real time feedback, and are complicated to configure with high granularity. 

## Solution
We are building a cost effective multichannel peristaltic perfusion pump system with noncontact inline flow sensors that can be used in a bioreactor. The pump will provide real-time feedback and the user must be able to program each pump to a different speed.

# Software

## Deployment

Open a terminal and cd to a new, empty directory

* `mkdir peristalticPump`

* `cd peristalticPump`

Clone the repository into that dir

* `https://github.com/fmhall/Peristaltic-Pump.git`

Install the necessary modules and requirements, either in a `virtualenv` (suggested) or on your OS's built in Python3 instance. For Linux and Mac:

* `python3 -m pip install --user virtualenv`
* `cd Peristaltic-Pump`
* `python3 -m virtualenv env`
* `source env/BIN/activate`

Install the modules listed in `requirements.txt`

* `pip install -r requirements.txt`

* On windows: 
  * `py install -r requirements.txt`

Launch interface
* `python3 GUI.py`


## Architecture
### /Arduino-slaves
Arduinos run low-level C code to listen for inputs, parse the inputs, and output corresponding commands to each motor.
### /RaspberryPi-master
The Raspberry Pi launches a Graphical User Interface (GUI) built with Python 3, using the tkinter framework for display and control.
`communicator.py` takes in the input from the GUI, converts it to commands, and sends those through a serial connection to the Arduinos.
