#pragma once
#ifndef __WATER_STRUCT_H__
#define __WATER_STRUCT_H__


struct WaterStruct {
    double dblMiu;
    double dblRho;
    double dblT;
    double dblEnthalpy;
    double dblCp;
    double dblVs;


    void New1_Water(WaterStruct* Water) {
        Water->dblMiu = 0.001;
        Water->dblRho = 1000.0;
        Water->dblCp = 4183.0;
        Water->dblT = 273.0;
        Water->dblEnthalpy = 0.0;
    }
    double RhofromT(double dblPipeT) {
        double Rho;
        Rho = 1125.81489 + 0.4347332 * dblPipeT;
        return Rho;

    }
    double HfromT(double dblPipeT) {
        double Enthalpy;
        Enthalpy = 4191.4 / dblPipeT + 1144252.2;
        return Enthalpy;

    }
    double MiufromT(double dblPipeT) {
        double Miu;
        Miu = 101360.6 + 2.458447 * dblPipeT * dblPipeT;
        Miu = Miu * 0.000001;
        return Miu;

    }
    double VsfromT(double dblPipeT) {
        double Vs;
        Vs = 1110.011 + 1.274888 * dblPipeT;
        return Vs;
    }
    double Tfromh(double dblPipeH) {
        double PipeT;
        PipeT = 1.0 * (dblPipeH) / 4191.4;
        return PipeT;

    }
    double CpfromT(double dblPipeT) {
        double PipeCp;
        PipeCp = 0.0135 * dblPipeT * dblPipeT - dblPipeT + 5568.7854;
        return PipeCp;

    }

};






#endif