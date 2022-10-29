import motor

setpoint = 1
output = 0
prev_setpoint = 0
prev_output = 0

f = open("motor_simulation.csv", "w")
f.write("time,setpoint,speed,position\n")

for i in range(1000):
    prev_setpoint = setpoint
    setpoint = 1

    prev_output = output
    output = motor.motor(setpoint, prev_setpoint, prev_output)

    f.write("%.8f,%.8f,%.8f\n" % (i * motor.TS, setpoint, output))

f.close()
