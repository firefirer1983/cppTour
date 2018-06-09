//
// Created by 18377 on 2018/6/9.
//

#ifndef CPPTOUR_COMPLEX_H
#define CPPTOUR_COMPLEX_H

class Complex {
	double re_;
	double img_;

public:
	Complex():
			re(0),
			img(0){}

	Complex(double real, double image):
			re_(real),
			img_(image){}

	double real() const {
		return re_;
	}

	double image() const {
		return img_;
	}

	Complex &operator+=(const Complex& a){ re_+= a.re_; img_ += a.img_; return *this; };
	Complex &operator-=(const Complex& a){ re_-= a.re_; img_ -= a.img_; return *this; };
	Complex &operator*=(const Complex& a);
	Complex &operator/=(const Complex& a);
};

#endif //CPPTOUR_COMPLEX_H
