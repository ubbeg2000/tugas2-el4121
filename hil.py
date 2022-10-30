import sys
import serial
import matplotlib.pyplot as plt
from motor.motor import motor, TS

# simulation settings
SIM_WINDOW_WIDTH = 1000
SIM_DURATION = 10000
SIM_LOG_FILE_NAME = "hil_log.csv"
SIM_PORT = "COM8"
SIM_REFRESH_RATE = 50

# command line argument parsing
if len(sys.argv) == 2:
    SIM_PORT = sys.argv[1]

if len(sys.argv) == 3:
    SIM_PORT = sys.argv[1]
    SIM_LOG_FILE_NAME = sys.argv[2]


# opening serial port
try:
    esp = serial.Serial(
        port=SIM_PORT,
        baudrate=230400,
        bytesize=serial.EIGHTBITS,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        timeout=None
    )
    print(f"opened serial connection at port {SIM_PORT}")

except:
    print(f"failed to open {SIM_PORT}, exiting ...")
    exit()

# opening log file
f = open(SIM_LOG_FILE_NAME, "w")
f.write("time,speed,position,setpoint,input_open,input_close\n")
print(f"logging to '{SIM_LOG_FILE_NAME}'")

# motor parameters
control_signal = 0
prev_control_signal = 0
prev_speed = 0
speed = 0
position = 0

# simulation data
i = 0
speed_data = []
position_data = []
setpoint_data = []
input_open_data = []
input_close_data = []

# simulation display configuration
plt.ion()

fig = plt.figure()
ax = plt.axes(xlim=(0, SIM_WINDOW_WIDTH), ylim=(-1.5, 1.5))

speed_plot, = ax.plot([], speed_data, label="Speed (rev/s)")
position_plot, = ax.plot([], position_data, label="Position (m)")
setpoint_plot, = ax.plot([], setpoint_data, label="Setpoint (rev/s)")
input_open_plot, = ax.plot([], input_open_data, label="Input Open")
input_close_plot, = ax.plot([], input_close_data, label="Input Close")

plt.grid()
plt.legend()


def draw(fig, speed_plot, speed_data, position_plot, position_data,
         setpoint_data, input_open_data, input_close_data):

    speed_plot.set_data(range(len(speed_data)), speed_data)
    position_plot.set_data(range(len(position_data)), position_data)
    setpoint_plot.set_data(range(len(setpoint_data)), setpoint_data)
    input_open_plot.set_data(range(len(input_open_data)), input_open_data)
    input_close_plot.set_data(range(len(input_close_data)), input_close_data)

    fig.canvas.draw()
    fig.canvas.flush_events()


print("starting simulation ...")
while i < SIM_DURATION:
    try:
        esp.write(("%.8f;%.8f\r\n" % (speed, position)).encode("utf-8"))

        [control_signal, setpoint, input_open, input_close] = [
            float(v) for v in esp.readline().decode("utf-8").split(";")]

        prev_control_signal = control_signal
        control_signal = float(control_signal)

        prev_speed = speed
        speed = motor(control_signal, prev_control_signal, prev_speed)
        position += speed * TS

        speed_data.append(speed)
        position_data.append(position)
        setpoint_data.append(setpoint)
        input_open_data.append(input_open)
        input_close_data.append(input_close)

        f.write("%.8f,%.8f,%.8f,%.8f,%.8f,%.8f\n" %
                (TS * i, speed, position, setpoint, input_open, input_close))

        if i >= SIM_WINDOW_WIDTH:
            speed_data = speed_data[-SIM_WINDOW_WIDTH:]
            position_data = position_data[-SIM_WINDOW_WIDTH:]
            setpoint_data = setpoint_data[-SIM_WINDOW_WIDTH:]
            input_open_data = input_open_data[-SIM_WINDOW_WIDTH:]
            input_close_data = input_close_data[-SIM_WINDOW_WIDTH:]

        if i % SIM_REFRESH_RATE == 0:
            draw(fig, speed_plot, speed_data, position_plot, position_data,
                 setpoint_data, input_open_data, input_close_data)

        i += 1

    except Exception:
        break

print("simulation finished")
esp.close()
f.close()
