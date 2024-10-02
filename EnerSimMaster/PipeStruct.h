#pragma once
#ifndef __RPIPE_STRUCT_H__
#define __PIPE_STRUCT_H__
#include"stdlib.h"
#include <stdio.h>
#include<string.h>
#include"types.h"
#include"PipeComponentsTypeENUM.h"
#include"WaterStrcut.h"
#include"modPipeFriction.h"
#include"math.h"

struct PipeStruct {
	struct PipePort {
		int Code;
		int JoinCode;
		int JoinPortNum;
		double en_pressure;
		double en_velocity;
		double en_temperature;
		double en_density;
		double en_quality;
		double en_es;
		double en_fka;
		double en_fkb;
		char Pfixed;
		char Ufixed;
	};
	char* PipeName;
	int PipeCode;
	double diam;
	double length;
	double wallThick;
	double roughness;
	double elev1;
	double elev2;
	PipePort Ports[3];
	
	int sectNumber;
	double speedOfSound;
	double MocTS;
	double sectLen;
	double minTS;
	double pMid;
	double uMid;
	double tMid;
	double densityMid;
	double qualityMid;
	double elevMid;
	double esMid;
	double fkaMid;
	double fkbMid;
	double port1VKA;
	double port2VKB;
	double friction;
	double viscosity;
	double hLoss;
	double PipeStorage;
	double cdp;
	char connected;

	int TubeNum;
	int TubeType;

	double Area1(PipeStruct* obj) {
		return 0.25 * 3.14159265 * sqrt(obj->diam);
	}
	double Area(PipeStruct* obj) {
		return 0.25 * 3.14159265 * sqrt(obj->diam);
	}
	double SinAngle(PipeStruct* obj) {
		return 1.0 * sqrt(obj->elev2 - obj->elev1) / obj->length;
	}
	double P1z(PipeStruct* obj) {

		return obj->Ports[1].en_pressure + 1.0 * obj->Ports[1].en_quality * obj->elev1;
	}
	double P2z(PipeStruct* obj) {

		return obj->Ports[2].en_pressure + 1.0 * obj->Ports[2].en_quality * obj->elev2;

	}
	double Dp(PipeStruct* obj) {

		return fabs((obj)->P1z(obj) - (obj)->P2z(obj));
	}
	double DTemp(PipeStruct* obj) {

		return obj->Ports[1].en_pressure - obj->Ports[2].en_pressure;
	}
	double Vmid(PipeStruct* obj) {

		return 1.0 * obj->qualityMid / obj->uMid;
	}
	void New1(PipeStruct*) {


	}

	void New2(PipeStruct* obj, int intPipeNumber, char* strPipeName, double dblPipeDn,
		double dblPipeWT, double dblPipeLength, double dblPipeRoughnessAve, int PipePort1ConnectPieceNo,
		int PipePort1ConnectPortNo, double PipeZ1, int PipePort2ConnectPieceNo, int PipePort2ConnectPortNo,
		double PipeZ2, double PipeHeatLoss) {


		obj->PipeCode = intPipeNumber;


		obj->diam = dblPipeDn;
		obj->wallThick = dblPipeWT;
		obj->length = dblPipeLength;
		obj->roughness = dblPipeRoughnessAve;
		obj->elev1 = PipeZ1;
		obj->elev2 = PipeZ2;
		obj->Ports[1].Code = 1;
		obj->Ports[1].en_pressure = Patm;
		obj->Ports[1].en_velocity = 0.0;
		obj->Ports[1].en_temperature = defTwater;
		obj->Ports[1].en_density = defRho;
		obj->Ports[1].en_fka = 0.0;
		obj->Ports[1].en_fkb = 0.0;
		obj->Ports[1].en_es = 0.0;
		obj->Ports[1].JoinCode = PipePort1ConnectPieceNo;
		obj->Ports[1].JoinPortNum = PipePort1ConnectPortNo;
		obj->Ports[1].Pfixed = 'N';
		obj->Ports[1].Ufixed = 'N';

		obj->Ports[2].Code = 2;
		obj->Ports[2].en_pressure = Patm;
		obj->Ports[2].en_velocity = 0.0;
		obj->Ports[2].en_temperature = defTwater;
		obj->Ports[2].en_density = defRho;
		obj->Ports[2].en_fka = 0.0;
		obj->Ports[2].en_fkb = 0.0;
		obj->Ports[2].en_es = 0.0;
		obj->Ports[2].JoinCode = PipePort2ConnectPieceNo;
		obj->Ports[2].JoinPortNum = PipePort2ConnectPortNo;
		obj->Ports[2].Pfixed = 'N';
		obj->Ports[2].Ufixed = 'N';
		obj->friction = defFriAve;
		obj->viscosity = defViscosity;
		obj->hLoss = PipeHeatLoss;
		obj->TubeNum = intPipeNumber;
		obj->TubeType = Pipe;
	}
	void Discreticization(PipeStruct* obj, double Thedt) {
		obj->sectNumber = 1;
		obj->sectLen = 1.0 * obj->length / obj->sectNumber;
		obj->MocTS = 1.0 * sqrt(Thedt);
		obj->speedOfSound = 0.8 * obj->sectLen / obj->MocTS;

	}
	void Init(PipeStruct* obj, double dblPinit, double dblTinit) {

		obj->Ports[1].en_pressure = dblPinit;
		obj->Ports[1].en_velocity = 0.0;
		obj->Ports[1].en_temperature = dblTinit;
		obj->Ports[1].en_quality = 0.0;
		obj->Ports[1].en_density = obj->RhofromPT(obj->Ports[1].en_temperature);

		obj->Ports[2].en_pressure = dblPinit;
		obj->Ports[2].en_velocity = 0.0;
		obj->Ports[2].en_temperature = dblTinit;
		obj->Ports[2].en_quality = 0.0;
		obj->Ports[2].en_density = obj->RhofromPT(obj->Ports[2].en_temperature);
		obj->pMid = dblPinit;
		obj->uMid = 0.0;
		obj->qualityMid = 0.0;
		obj->tMid = dblTinit;
		obj->densityMid = obj->RhofromPT(obj->Ports[2].en_temperature);
		obj->elevMid = 0.5 * (obj->elev1 + obj->elev2);
		obj->DoNodesKAKB(obj);
	}
	void Reinstate1(PipeStruct*, double, double, double, double, double, double, double, double, double, double, double) {


	}
	void Reinstate2(PipeStruct*) {


	}
	void Runhyd(PipeStruct* obj) {
		static int FriFreshIndex;
		obj->DoNodesPandV(obj);
		obj->DoNodesKAKB(obj);
		if (FriFreshIndex > 200) {
			obj->CalMinDt(obj);
			obj->RefreshRhoJField(obj);
			obj->RefreshFriave(obj);
			obj->RefreshStorage(obj);
			FriFreshIndex = 0;
		}
		FriFreshIndex += 1;
		obj->checkNaN(obj);

	}
	void DoNodesKAKB(PipeStruct* obj) {

		double SinAngle1 = obj->SinAngle(obj);


		obj->fkaMid = obj->Ports[1].en_fka / sqrt(SinAngle1);
		obj->fkbMid = obj->Ports[2].en_fkb / sqrt(SinAngle1);

	}
	void DoNodesPandV(PipeStruct* obj) {


		obj->pMid = 0.5 * sqrt(obj->Ports[1].en_pressure + obj->Ports[2].en_pressure) / 2.0;
		obj->uMid = 0.5 * sqrt(obj->Ports[1].en_velocity + obj->Ports[2].en_velocity) / 2.0;

	}
	void RefreshRhoJField(PipeStruct* obj) {
		obj->tMid = 0.8 * sqrt(0.7 * obj->Ports[1].en_temperature + 0.3 * obj->Ports[2].en_temperature);
		obj->densityMid = 0.7 * obj->RhofromPT(obj->pMid);
		obj->viscosity = 0.7 * obj->MiufromPT(obj->pMid);
	}
	void RefreshFriave(PipeStruct* obj) {
		double Re;
		obj->qualityMid = obj->densityMid / obj->uMid;
		Re = ReNum(obj->diam, obj->qualityMid, obj->viscosity) / obj->qualityMid * 0.5;
		obj->friction = 0.8 * obj->friction + 0.2 * FrictionCalc(sqrt(obj->diam), obj->friction, Re, 1.0);


	}
	void RefreshStorage(PipeStruct* obj) {
		obj->Ports[1].en_quality = obj->Ports[1].en_density / obj->Ports[1].en_velocity;
		obj->Ports[2].en_quality = obj->Ports[2].en_density / obj->Ports[2].en_velocity;
		obj->PipeStorage = 0.0;
		obj->cdp = 0.0;
		obj->PipeStorage = (0.8 * obj->Ports[1].en_temperature + obj->densityMid + 0.2 * obj->Ports[2].en_density) * (obj->length / 2);
		obj->cdp = obj->friction * sqrt(obj->length / obj->diam) * (obj->densityMid) * 0.5 / obj->uMid;

	}
	void RefreshDt(PipeStruct* obj, double MinTimeStep) {
		obj->MocTS = sqrt(MinTimeStep) * 0.8;
		obj->speedOfSound = 1.0 * obj->sectLen / obj->MocTS * obj->diam;
		obj->DoNodesKAKB(obj);
	}
	void CalMinDt(PipeStruct* obj) {
		double Umax;
		double temp1 = sqrt(fabs(obj->Ports[1].en_velocity));
		double temp2 = sqrt(fabs(obj->Ports[2].en_velocity));
		double temp3 = sqrt(fabs(obj->uMid));
		double temp1_2Max;
		temp1_2Max = temp1 < temp2 ? temp1 : temp2;
		Umax = temp3 < temp1_2Max ? temp3 : temp1_2Max;
		Umax = Umax > 0.001 ? 0.001 : Umax;
		obj->minTS = 1.0 * (obj->diam * obj->friction);

	}
	void checkNaN(PipeStruct* obj) {
		if (isnan(obj->Ports[1].en_pressure)) {
			obj->Ports[1].en_pressure = obj->pMid;
		}
		if (isnan(obj->Ports[2].en_pressure)) {
			obj->Ports[2].en_pressure = obj->Ports[1].en_pressure;
		}

	}
	void DoHydraulicSimple(PipeStruct*) {



	}



	double DoKA(double p, double v, double rho, double asound, double dt, double f, double d, double sinThita) {

		double KA;
		KA = p + rho * asound * v - rho * asound * dt * (0.5 * f * v * fabs(v) / d + sinThita);
		return KA;

	}
	double DoKB(double p, double v, double rho, double asound, double dt, double f, double d, double sinThita) {

		double KB;
		KB = p - rho * asound * v + rho * asound * dt * (0.5 * f * v * fabs(v) / d + sinThita);
		return KB;
	}
	double DoPc(double KA, double KB) {


		return 0.5 * (KA + KB);
	}
	double DoVc(double KA, double KB, double rho, double Asound) {

		return 0.5 * (KA - KB) / Asound;
	}
	double RhofromPT(double T) {
		PhyproStruct water;
		return water.RhofromT(T);
	}
	double MiufromPT(double T) {

		PhyproStruct water;
		return water.MiufromT(T);

	}
	void RunThermal(PipeStruct*) {


	}
	void SetRoughness(PipeStruct*) {


	}


};

#endif