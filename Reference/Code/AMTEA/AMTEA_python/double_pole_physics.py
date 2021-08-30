"""
Double pole simulation. Physics.
"""
from math import sin, cos, pi, radians as rad

import numpy as np

C43 = 4/3.0
C34 = 3/4.0
HALF_PI = pi/2


def runge_kutta4(current_y, y_deriv_func, step):
    """
    Fourth order Runge Kutta
    http://lpsa.swarthmore.edu/NumInt/NumIntFourth.html
    for example
    y' = -2*y
    then y_deriv_func = y' that accepts y
    and y is current_y
    """

    k1 = y_deriv_func(current_y)
    y1 = current_y + k1 * step / 2

    k2 = y_deriv_func(y1)
    y2 = current_y + k2 * step / 2

    k3 = y_deriv_func(y2)
    y3 = current_y + k3 * step

    k4 = y_deriv_func(y3)

    next_y = current_y + (k1 + 2*k2 + 2*k3 + k4)*step/6

    return next_y


def runge_kutta4_for_poles(pole, y_deriv_func, step):
    """
    Fourth order Runge Kutta
    http://lpsa.swarthmore.edu/NumInt/NumIntFourth.html
    for example
    y' = -2*y
    then y_deriv_func = y' that accepts y
    and y is current_y
    """
    current_y = pole.vel
    k1 = y_deriv_func(pole, current_y)
    y1 = current_y + k1 * step / 2

    k2 = y_deriv_func(pole, y1)
    y2 = current_y + k2 * step / 2

    k3 = y_deriv_func(pole, y2)
    y3 = current_y + k3 * step

    k4 = y_deriv_func(pole, y3)

    next_y = current_y + (k1 + 2*k2 + 2*k3 + k4)*step/6

    return next_y


class Pole:

    def __init__(self, angle, velocity, acceleration, mass, half_length):
        """
        angle - angle from vertical in rad +-15?
        maybe sincos are valid with small values in this situation
        angular velocity in rad/sec
        acceleration in rad/sec**2
        mass of poles in kg
        poles lengths from the pivot to the center of mass
        thus h_len = 0.5 is 1 meter pole
        """
        self.angle = angle
        self.vel = velocity
        self.acc = acceleration
        self.mass = mass
        self.h_len = half_length


class PoledCart:
    """
    double pole physics implementation
    """

    def __init__(self, h_len, number_of_poles=2):
        # number of poles
        self.pole_number = number_of_poles
        self.poles = []
        p_masses = [0.1]*self.pole_number
        # p_angles = [starting_angle]*self.pole_number
        p_angles = [0.0, rad(1.0)]
        p_h_lens = [h_len/2, 0.5]
        p_accels = [0.0]*self.pole_number
        p_vels = [0.0]*self.pole_number
        for i in range(self.pole_number):
            self.poles.append(Pole(p_angles[i], p_vels[i], p_accels[i], p_masses[i], p_h_lens[i]))
        # offset from the middle of the track (0.0)
        self.cart_pos = 0.0
        # velocity in m/s
        self.cart_vel = 0.0
        # acceleration in m/s**2
        self.cart_acc = 0.0
        # gravity m/2**2 #up is positive!
        self.gravity = -9.81
        # mass of cart in kg
        self.cart_mass = 1.0
        # time in seconds
        self.time = 0.0
        # magitude of force applied to the center of
        # cart's mass at time self.time
        # in newtons usually constant of +-10  or +-1 newtons
        self.applied_force = 0.0
        # track limit from the center thus +-2.4m = 4.8m is length of the track
        self.track_limit = 2.4
        # pole failure angle +- 36 degrees from 0. variable is in rads
        self.p_failure_angle = rad(36)
        self.failed = False
        # time step in seconds
        self.time_step = 0.01
        self.cart_fric = 0.05
        self.p_fric = 0.000002
        # if enabled poles are always above the cart
        self.stop_at_zero_deg = True
        # how to approximate

    def get_state(self):
        """Returns the current state of cart-pole system."""
        state = np.zeros(6)
        state[0] = self.cart_pos / 2.4
        state[1] = self.cart_vel / 10.0
        state[2] = self.poles[0].angle / 0.628329
        state[3] = self.poles[0].vel / 5.0
        state[4] = self.poles[1].angle / 0.628329
        state[5] = self.poles[1].vel / 13.0
        return state

    def cart_acc_given_vel(self, cart_vel):
        p_forces = 0.0
        total_effective_poles_mass = 0.0
        for p in self.poles:
            buff = self.p_fric * p.vel / (p.mass * p.h_len) + self.gravity * sin(p.angle)
            force = p.mass * p.h_len * p.vel**2 * sin(p.angle) + C34 * p.mass * cos(p.angle) * buff
            p_forces += force
            total_effective_poles_mass += p.mass * (1 - C34 * cos(p.angle)**2)

        cart_acc = self.applied_force - self.cart_fric * np.sign(cart_vel) + p_forces
        cart_acc /= self.cart_mass + total_effective_poles_mass

        return cart_acc

    def pole_acc_given_vel(self, p, pole_vel):
        p.acc = -C34/p.h_len * (self.cart_acc * cos(p.angle) +
                                self.gravity * sin(p.angle) + self.p_fric * pole_vel / (p.mass * p.h_len))
        return p.acc

    def update_state(self):
        self.time += self.time_step

        self.cart_vel = runge_kutta4(self.cart_vel, self.cart_acc_given_vel, self.time_step)
        for pole in self.poles:
            pole.vel = runge_kutta4_for_poles(pole, self.pole_acc_given_vel, self.time_step)

        self.cart_acc = self.cart_acc_given_vel(self.cart_vel)

        self.cart_pos += self.time_step * self.cart_vel

        for pole in self.poles:
            pole.angle += self.time_step * pole.vel
            self.pole_acc_given_vel(pole, pole.vel)

        if not -self.track_limit <= self.cart_pos <= self.track_limit:
            self.failed = True
            # print('Track limit fail at', self.cart_pos)

        for p in self.poles:
            if not -self.p_failure_angle <= p.angle <= self.p_failure_angle:
                self.failed = True
                # print('Pole fail', p.h_len, p.angle)
                # return
            if not -HALF_PI <= p.angle <= HALF_PI:
                if p.angle > HALF_PI:
                    p.angle = HALF_PI
                elif p.angle < -HALF_PI:
                    p.angle = -HALF_PI
                p.vel *= -0.9
