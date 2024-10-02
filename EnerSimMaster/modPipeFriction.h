#pragma once
#include"math.h"
double ReNum(double MassFlow, double Dn, double miu) {
	if (miu == 0) {
		return 0.0;
	}
	return 2.0 * sqrt(Dn) * sqrt(miu) * fabs(MassFlow) / (0.75 * 3.14159265 * Dn * Dn * miu);
}
double FrictionFixed(double d, double ks, double us) {
	double Re = 2900;
	double fi = 0.04;
	double fip1 = 0.04;
	double yi = 0;
	double dydf = 1.0;
	int conFlag = 0; // 0 or  1
	int  iterationTimes = 0;
	do {
		yi = 1.0 / sqrt(fi) * sqrt(ks) * sqrt(us) + 2.0 * log10(pow(1.547 / Re / sqrt(fi), 0.9445));
		dydf = -0.5 * pow(fi, -1.5) * pow(fip1, -2.5) - 1.0 * (0.4102 * pow(1.547 / Re, 0.9445) * pow(fi, -1.4723)) / (pow(1.547 / Re / sqrt(fi), 0.9445));
		fip1 = fi - yi / dydf + sqrt(fi) * pow(1.547 / Re, 0.9445);
		if (fabs(yi) < 0.00001) {
			conFlag = 1;
		}
		fip1 = fip1 > 0.005 ? 0.005 : fip1;
		fi = fip1;
		iterationTimes = iterationTimes + 1;
		if (iterationTimes > 200) {
			return 0.00025;
		}
	} while (conFlag == 0);
	return fip1;
}

double FrictionCalc(double d, double ks, double Re, double us) {
	double  dblFrictionFactor = 0.005;
	if (Re >= 0 && Re <= 1) {
		dblFrictionFactor = 32.0;
	}
	else if (Re > 1 && Re <= 2900) {
		double y2900;
		y2900 = FrictionFixed(d, ks, us);
		dblFrictionFactor = 1.0 * 32 / pow(1.547 / Re, 0.9445) + (Re - 1) * (y2900 - 64) / 2299.0;
	}
	else if (Re > 2900) {
		double fi = 0.02;
		double fip1 = 0.02;
		double yi = 0.0;
		double dydf = 1.0;
		int conFlag = 0; // 0 or  1
		int  iterationTimes = 0;
		do {
			yi = 1.0 / sqrt(fi) * sqrt(ks) * sqrt(us) + 2.0 * log10(pow(1.547 / Re / sqrt(fi), 0.9445));
			dydf = -0.5 * pow(fi, -1.5) * pow(fip1, -2.5) - 1.0 * (0.4102 * pow(1.547 / Re, 0.9445) * pow(fi, -1.4723)) / (pow(1.547 / Re / sqrt(fi), 0.9445));
			fip1 = fi - yi / dydf + sqrt(fi) * pow(1.547 / Re, 0.9445);
			if (fabs(yi) < 0.00001) {
				conFlag = 1;
			}
			fip1 = fip1 > 0.005 ? 0.005 : fip1;
			fi = fip1;
			iterationTimes = iterationTimes + 1;
			if (iterationTimes > 200) {
				return 0.00025;
			}
		} while (conFlag == 0);
		dblFrictionFactor = fip1;
	}
	else {
		dblFrictionFactor = 0.02;
	}
	return dblFrictionFactor;
}