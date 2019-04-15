# ArduinoController
A simple(ish) controller based on an Arduino that can convert 3D movements to computer motion.

Built a basic 3D tracker using an Inertial Measurement unit. It maintains accuracy within small frames of time. As time goes on, due to it essentially being driven in a feedback loop with the rotation being corrected by the acceleration and then the acceleration being aligned to the axes by the rotation thus leading to deviation.
