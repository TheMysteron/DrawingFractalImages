#pragma once
#ifndef MANDELBROT_H_
#define MANDELBROT_H_


namespace jcs {
	class Mandelbrot {
	public:
		static const int MAX_ITERATIONS{2000};

	public:
		Mandelbrot();
		virtual ~Mandelbrot();

	public:
		static int getIterations(double x, double y);
	};
}

#endif // !MANDELBROT_H_