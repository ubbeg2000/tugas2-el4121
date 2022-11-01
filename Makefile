motor-simulation:
	gcc -o motor-simulation ./motor/motor_simulation.c ./motor/motor.c

control-fsm-simulation:
	gcc -o control-fsm-simulation ./fsm/control_fsm_simulation.c ./fsm/control_fsm.c
	
controller-simulation:
	gcc -o controller-simulation ./controller/controller_simulation.c ./motor/motor.c ./controller/controller.c

hil-simulation:
	gcc -o hil-simulation ./hil_simulation.c ./motor/motor.c ./controller/controller.c ./fsm/control_fsm.c

all: 
	$(MAKE) motor-simulation
	$(MAKE) control-fsm-simulation
	$(MAKE) controller-simulation
	$(MAKE) hil-simulation

clean:
	del *.exe

clean-sim:
	del *.csv
	del *.png
