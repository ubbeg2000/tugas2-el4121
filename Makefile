motor-simulation:
	gcc -o motor-simulation ./motor/motor_simulation.c ./motor/motor.c

control-fsm-simulation:
	gcc -o control-fsm-simulation ./fsm/control_fsm_simulation.c ./fsm/control_fsm.c
	
controller-simulation:
	gcc -o controller-simulation ./controller/controller_simulation.c ./motor/motor.c ./controller/controller.c

system-simulation:
	gcc -o system-simulation ./system_simulation.c ./motor/motor.c ./controller/controller.c ./fsm/control_fsm.c
