#pragma once
#ifndef __VALVES_STRUCT_H__
#define __VALVES_STRUCT_H__
#include"PipeStruct.h"

struct PRVStruct {
	struct PipePort {
		double Dn;
		int JoinCode;
		int ConnectPortNo;
		double en_pressure;
		double en_quality;
		double en_temperature;
		double en_velocity;
	};

	char* strName;
	int intNum;
	int intMyType;
	PipePort Ports[3];
	double dblResistance;
	double dblTemperature;
	PipeStruct* clsPipe1;
	PipeStruct* clsPipe2;
	char blnConnected;
	double dblErrP;
	int TubeNum;
	int TubeType;



	void New1(PRVStruct*) {

	}
	void New2(PRVStruct* obj, int intThePRVNum, char* strThePRVName, int intThePRVConnPiece1, int intThePRVConnPort1,
		int intThePRVConnPiece2, int intThePRVConnPort2, double dblThePRVR) {

		obj->intNum = intThePRVNum;

		obj->intMyType = 1;

		obj->dblResistance = dblThePRVR;
		obj->Ports[1].Dn = 1.0;
		obj->Ports[1].JoinCode = intThePRVConnPiece1;
		obj->Ports[1].ConnectPortNo = intThePRVConnPort1;
		obj->Ports[1].en_pressure = Patm;
		obj->Ports[1].en_velocity = 0.0;
		obj->Ports[1].en_temperature = defTwater;
		obj->Ports[2].Dn = 1.0;
		obj->Ports[2].JoinCode = intThePRVConnPiece2;
		obj->Ports[2].ConnectPortNo = intThePRVConnPort2;
		obj->Ports[2].en_pressure = Patm;
		obj->Ports[2].en_velocity = 0.0;
		obj->Ports[2].en_temperature = defTwater;
		obj->TubeType = PRV;
		obj->TubeNum = intThePRVNum;
	}
	void Init(PRVStruct* obj,PipeStruct* pipe1, PipeStruct* pipe2) {
		obj->clsPipe1 = pipe1;
		obj->clsPipe2 = pipe2;
		obj->CheckPRVType(obj);
		obj->Ports[1].Dn = pipe1->diam;
		obj->Ports[2].Dn = pipe2->diam;

		if (obj->Ports[1].ConnectPortNo == 1) {
			obj->Ports[2].en_temperature = pipe1->Ports[1].en_temperature;
		}
		else {
			obj->Ports[1].en_temperature = pipe1->Ports[2].en_temperature;
		}

		if (obj->Ports[2].ConnectPortNo == 1) {
			obj->Ports[1].en_temperature = pipe2->Ports[2].en_temperature;
		}
		else {
			obj->Ports[2].en_temperature = pipe2->Ports[1].en_temperature;
		}

		switch (obj->intMyType) {
		case 1:
			obj->Ports[1].en_pressure = pipe1->Ports[2].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[2].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[2].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[1].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[1].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[1].en_temperature;
			break;
		case 2:
			obj->Ports[1].en_pressure = pipe1->Ports[1].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[1].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[1].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[2].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[2].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[2].en_temperature;
			break;
		case 3:
			obj->Ports[1].en_pressure = pipe1->Ports[2].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[2].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[2].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[2].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[2].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[2].en_temperature;
			break;
		case 4:
			obj->Ports[1].en_pressure = pipe1->Ports[1].en_pressure;
			obj->Ports[1].en_velocity = pipe1->Ports[1].en_velocity;
			obj->Ports[1].en_temperature = pipe1->Ports[1].en_temperature;
			obj->Ports[2].en_pressure = pipe2->Ports[1].en_pressure;
			obj->Ports[2].en_velocity = pipe2->Ports[1].en_velocity;
			obj->Ports[2].en_temperature = pipe2->Ports[1].en_temperature;
			break;
		}


	}
	void CheckPRVType(PRVStruct* obj) {
		if (obj->Ports[1].ConnectPortNo == 1 && obj->Ports[2].ConnectPortNo == 2) {
			obj->intMyType = 1;
		}
		else if (obj->Ports[1].ConnectPortNo == 2 && obj->Ports[2].ConnectPortNo == 1) {
			obj->intMyType = 2;
		}
		else if (obj->Ports[1].ConnectPortNo == 1 && obj->Ports[2].ConnectPortNo == 1) {
			obj->intMyType = 3;
		}
		else if (obj->Ports[1].ConnectPortNo == 2 && obj->Ports[2].ConnectPortNo == 2) {
			obj->intMyType = 4;
		}



	}
	void Runhyd(PRVStruct* obj) {
		double KA1;
		double KA2;
		double KB1;
		double KB2;
		double MyCurP;

		MyCurP = (obj->Ports[1].en_pressure + obj->Ports[2].en_pressure) / 2.0;

		switch (obj->intMyType) {
		case 1:
			KB1 = obj->clsPipe2->fkbMid;
			KB2 = obj->clsPipe1->fkbMid;
			KA1 = obj->PRVType1KB1(KB1, KB2, obj->clsPipe1->Area(obj->clsPipe1), obj->clsPipe1->speedOfSound, obj->clsPipe2->Area(obj->clsPipe2), obj->clsPipe2->speedOfSound, obj->dblResistance);
			KA2 = 1.0 * sqrt(KA1 + KB1) - KB2;
			obj->clsPipe1->port1VKA = sqrt(KA1);
			obj->clsPipe2->port1VKA = sqrt(KA2);
			break;

		case 2:
			KA1 = obj->clsPipe2->fkaMid;
			KA2 = obj->clsPipe1->fkaMid;
			KB1 = obj->PRVType2KA1(KA1, KA2, obj->clsPipe1->Area(obj->clsPipe1), obj->clsPipe1->speedOfSound, obj->clsPipe2->Area(obj->clsPipe2), obj->clsPipe2->speedOfSound, obj->dblResistance);
			KB2 = 1.0 * sqrt(KA1 + KB1) - KA2;
			obj->clsPipe1->port2VKB = sqrt(KB1);
			obj->clsPipe2->port2VKB = sqrt(KB2);

			break;

		case 3:
			KB1 = obj->clsPipe2->fkbMid;
			KA2 = obj->clsPipe1->fkaMid;
			KA1 = obj->PRVType3KB1(KB1, KA2, obj->clsPipe1->Area(obj->clsPipe1), obj->clsPipe1->speedOfSound, obj->clsPipe2->Area(obj->clsPipe2), obj->clsPipe2->speedOfSound, obj->dblResistance);
			KB2 = 1.0 * sqrt(KA1 + KB1) - KA2;
			obj->clsPipe1->port1VKA = sqrt(KA1);
			obj->clsPipe2->port2VKB = sqrt(KB2);
			break;
		case 4:
			KA1 = obj->clsPipe2->fkaMid;
			KB2 = obj->clsPipe1->fkbMid;
			KB1 = obj->PRVType4KA1(KA1, KB2, obj->clsPipe1->Area(obj->clsPipe2), obj->clsPipe1->speedOfSound, obj->clsPipe2->Area(obj->clsPipe1), obj->clsPipe2->speedOfSound, obj->dblResistance);
			KA2 = 1.0 * sqrt(KA1 + KB1) - KB2;
			KA2 = 1.0 * sqrt(KA1 + KB1) - KB2;
			obj->clsPipe1->port2VKB = sqrt(KB1);
			obj->clsPipe2->port1VKA = sqrt(KA2);
			break;
		}
		obj->dblErrP = MyCurP - obj->Ports[2].en_pressure;
	}
	void DoHydraulicBack(PRVStruct*) {

	}

	double PRVType1KB1(double dblKA1, double dblKB2, double dblA1, double dblAS1, double dblA2, double dblAS2, double theR) {
		double dblKB1;
		double Fa1, Fa2;
		Fa1 = 1.0 * dblA2 / (dblAS1);
		Fa2 = 1.0 * dblA1 / (dblAS2);
		dblKB1 = 1.0 * (2 * dblKB2 + dblKA1 + 2 * theR) / (Fa1 + Fa2);
		return dblKB1;
	}
	double PRVType2KA1(double dblKB1, double dblKA2, double dblA1, double dblAS1, double dblA2, double dblAS2, double theR) {

		double dblKA1;
		double Fa1, Fa2;
		Fa1 = 1.0 * dblA2 / (dblAS1);
		Fa2 = 1.0 * dblA1 / (dblAS2);
		dblKA1 = 1.0 * (2 * dblKA2 + dblKB1 - 2 * theR) / (Fa1 + Fa2);
		return dblKA1;
	}
	double PRVType3KB1(double dblKA1, double dblKA2, double dblA1, double dblAS1, double dblA2, double dblAS2, double theR) {

		double dblKB1;
		double Fa1, Fa2;
		Fa1 = 1.0 * dblA2 / (dblAS1);
		Fa2 = 1.0 * dblA1 / (dblAS2);
		dblKB1 = 1.0 * (2 * dblKA2 + dblKA1 + 2 * theR) / (Fa1 + Fa2);
		return dblKB1;


	}
	double PRVType4KA1(double dblKB1, double dblKB2, double dblA1, double dblAS1, double dblA2, double dblAS2, double theR) {

		double dblKA1;
		double Fa1, Fa2;
		Fa1 = dblA2 / (dblAS1);
		Fa2 = dblA1 / (dblAS2);
		dblKA1 = (2 * dblKB2 + dblKB1 + 2 * theR) / (Fa1 + Fa2);
		return dblKA1;


	}
	double DoKA(PRVStruct*, double, double, double, double, double, double, double, double) {

		return 0;
	}
	double DoKB(PRVStruct*, double, double, double, double, double, double, double, double) {

		return 0;
	}
	void SwapVal(PRVStruct* obj) {
		if (obj->clsPipe1->Ports[1].JoinCode == obj->intNum) {
			obj->Ports[2].en_pressure = obj->clsPipe1->Ports[2].en_pressure;
			obj->Ports[2].en_velocity = obj->clsPipe1->uMid;

		}
		else {
			obj->Ports[1].en_pressure = obj->clsPipe1->Ports[1].en_pressure;
			obj->Ports[1].en_velocity = -1.0 * obj->clsPipe1->uMid;

		}

		if (obj->clsPipe2->Ports[1].JoinCode == obj->intNum) {
			obj->Ports[1].en_pressure = obj->clsPipe2->Ports[2].en_pressure;
			obj->Ports[1].en_velocity = obj->clsPipe2->uMid;

		}
		else {
			obj->Ports[2].en_pressure = obj->clsPipe2->Ports[1].en_pressure;
			obj->Ports[2].en_velocity = -1.0 * obj->clsPipe2->uMid;
		}
	}

	void RunThermal(PRVStruct*) {

	}
	void TestConnection(PRVStruct*) {

	}



};

struct ValveOnOffStruct {
	struct PipePort {
		double Dn;
		int JoinCode;
		int ConnectPortNo;
		double en_pressure;
		double en_velocity;
		double en_temperature;
		double en_quality;
	};
	char* strName;
	int intNum;
	int intMyType;
	PipePort Ports[3];
	PipeStruct* clsPipe1;
	PipeStruct* clsPipe2;
	double dblErrP;
	char blnOnOff;
	char blnConnected;
	int TubeNum;
	int TubeType;


	void New1(ValveOnOffStruct*) {

	}

	void New2(ValveOnOffStruct* object, int intTheValveNum, char* strTheValveName, int intTheValveConnPiece1, int intTheValveConnPort1,
		int intTheValveConnPiece2, int intTheValveConnPort2, char blnTheValveOnOff) {
		object->intNum = intTheValveNum;

		object->intMyType = 1;
		object->Ports[1].Dn = 1.0;
		object->Ports[1].JoinCode = intTheValveConnPiece1;
		object->Ports[1].ConnectPortNo = intTheValveConnPort1;
		object->Ports[1].en_pressure = Patm;
		object->Ports[1].en_velocity = 0.0;
		object->Ports[1].en_temperature = defTwater;
		object->Ports[2].Dn = 1.0;
		object->Ports[2].JoinCode = intTheValveConnPiece2;
		object->Ports[2].ConnectPortNo = intTheValveConnPort2;
		object->Ports[2].en_pressure = Patm;
		object->Ports[2].en_velocity = 0.0;
		object->Ports[2].en_temperature = defTwater;
		object->blnOnOff = blnTheValveOnOff;
		object->TubeType = ValveOnOff;
		object->TubeNum = intTheValveNum;









	}

	void Init(ValveOnOffStruct* obj, PipeStruct* pipe1, PipeStruct* pipe2) {
		obj->clsPipe1 = pipe1;
		obj->clsPipe2 = pipe2;
		obj->CheckTwoWayType(obj);
		obj->Ports[1].Dn = pipe1->diam;
		obj->Ports[2].Dn = pipe2->diam;

		if (obj->Ports[1].ConnectPortNo == 1) {
			obj->Ports[1].en_temperature = pipe1->Ports[1].en_temperature;
		}
		else {
			obj->Ports[1].en_temperature = pipe1->Ports[2].en_temperature;
		}

		if (obj->Ports[2].ConnectPortNo == 1) {
			obj->Ports[2].en_temperature = pipe2->Ports[1].en_temperature;
		}
		else {
			obj->Ports[2].en_temperature = pipe2->Ports[2].en_temperature;
		}

		switch (obj->intMyType) {
		case 1:
			obj->Ports[2].en_pressure = pipe1->Ports[2].en_pressure;
			obj->Ports[2].en_velocity = pipe1->Ports[2].en_velocity;
			obj->Ports[2].en_temperature = pipe1->Ports[2].en_temperature;
			obj->Ports[1].en_pressure = pipe2->Ports[1].en_pressure;
			obj->Ports[1].en_velocity = pipe2->Ports[1].en_velocity;
			obj->Ports[1].en_temperature = pipe2->Ports[1].en_temperature;
			break;
		case 2:
			obj->Ports[2].en_pressure = pipe1->Ports[1].en_pressure;
			obj->Ports[2].en_velocity = pipe1->Ports[1].en_velocity;
			obj->Ports[2].en_temperature = pipe1->Ports[1].en_temperature;
			obj->Ports[1].en_pressure = pipe2->Ports[2].en_pressure;
			obj->Ports[1].en_velocity = pipe2->Ports[2].en_velocity;
			obj->Ports[1].en_temperature = pipe2->Ports[2].en_temperature;
			break;
		case 3:
			obj->Ports[2].en_pressure = pipe1->Ports[2].en_pressure;
			obj->Ports[2].en_velocity = pipe1->Ports[2].en_velocity;
			obj->Ports[2].en_temperature = pipe1->Ports[2].en_temperature;
			obj->Ports[1].en_pressure = pipe2->Ports[2].en_pressure;
			obj->Ports[1].en_velocity = pipe2->Ports[2].en_velocity;
			obj->Ports[1].en_temperature = pipe2->Ports[2].en_temperature;
			break;
		case 4:
			obj->Ports[2].en_pressure = pipe1->Ports[1].en_pressure;
			obj->Ports[2].en_velocity = pipe1->Ports[1].en_velocity;
			obj->Ports[2].en_temperature = pipe1->Ports[1].en_temperature;
			obj->Ports[1].en_pressure = pipe2->Ports[1].en_pressure;
			obj->Ports[1].en_velocity = pipe2->Ports[1].en_velocity;
			obj->Ports[1].en_temperature = pipe2->Ports[1].en_temperature;
			break;
		}


	}
	void CheckTwoWayType(ValveOnOffStruct* obj) {
		if (obj->Ports[1].ConnectPortNo == 1 && obj->Ports[2].ConnectPortNo == 1) {
			obj->intMyType = 1;
		}
		else if (obj->Ports[1].ConnectPortNo == 1 && obj->Ports[2].ConnectPortNo == 2) {
			obj->intMyType = 2;
		}
		else if (obj->Ports[1].ConnectPortNo == 2 && obj->Ports[2].ConnectPortNo == 1) {
			obj->intMyType = 3;
		}
		else if (obj->Ports[1].ConnectPortNo == 2 && obj->Ports[2].ConnectPortNo == 2) {
			obj->intMyType = 4;
		}
	}
	void Runhyd(ValveOnOffStruct* obj) {

		if (obj->blnOnOff == 'Y') {
			obj->DoHydraulicOn(obj);
		}
		else {
			obj->DoHydraulicOff(obj);

		}
	}
	void DoHydraulicOn(ValveOnOffStruct* obj) {
		double KA1;
		double KA2;
		double KB1;
		double KB2;
		double MyCurP;
		MyCurP = (obj->Ports[1].en_pressure + obj->Ports[2].en_pressure) / 2.0;

		switch (obj->intMyType) {
		case 1:
			KA1 = obj->clsPipe2->fkaMid;
			KB2 = obj->clsPipe1->fkbMid;
			KB1 = obj->TwoWayType1KB1(KA1, KB2, obj->clsPipe1->Area(obj->clsPipe2), obj->clsPipe1->speedOfSound, obj->clsPipe2->Area(obj->clsPipe1), obj->clsPipe2->speedOfSound);
			KA2 = 1.0 * (sqrt(KA1 + KB1) - KB2);
			obj->clsPipe1->port2VKB = sqrt(KB1);
			obj->clsPipe2->port1VKA = sqrt(KA2);
			break;
		case 2:
			KB1 = obj->clsPipe2->fkbMid;
			KA2 = obj->clsPipe1->fkaMid;
			KA1 = obj->TwoWayType2KA1(KB1, KA2, obj->clsPipe1->Area(obj->clsPipe2), obj->clsPipe1->speedOfSound, obj->clsPipe2->Area(obj->clsPipe1), obj->clsPipe2->speedOfSound);
			KB2 = 1.0 * sqrt(KA1 + KB1) - KA2;
			obj->clsPipe1->port1VKA = sqrt(KA1);
			obj->clsPipe2->port2VKB = sqrt(KB2);
			break;
		case 3:
			KA1 = obj->clsPipe2->fkaMid;
			KA2 = obj->clsPipe1->fkaMid;
			KB1 = obj->TwoWayType3KB1(KA1, KA2, obj->clsPipe1->Area(obj->clsPipe2), obj->clsPipe1->speedOfSound, obj->clsPipe2->Area(obj->clsPipe1), obj->clsPipe2->speedOfSound);
			KB2 = 1.0 * sqrt(KA1 + KB1) - KA2;
			obj->clsPipe1->port2VKB = sqrt(KB1);
			obj->clsPipe2->port2VKB = sqrt(KB2);
			break;
		case 4:
			KB1 = obj->clsPipe2->fkbMid;
			KB2 = obj->clsPipe1->fkbMid;
			KA1 = obj->TwoWayType4KA1(KB1, KB2, obj->clsPipe1->Area(obj->clsPipe2), obj->clsPipe1->speedOfSound, obj->clsPipe2->Area(obj->clsPipe1), obj->clsPipe2->speedOfSound);
			KA2 = 1.0 * sqrt(KA1 + KB1) - KB2;
			obj->clsPipe1->port1VKA = sqrt(KA1);
			obj->clsPipe2->port1VKA = sqrt(KA2);
			break;
		}
		obj->dblErrP = MyCurP - obj->Ports[2].en_pressure;
	}
	void DoHydraulicOnBack(ValveOnOffStruct*) {







	}
	void DoHydraulicOff(ValveOnOffStruct* obj) {
		if (obj->CheckM1Fixed(obj) || obj->CheckM2Fixed(obj)) {

			;
		}
		else {
			obj->Ports[1].en_velocity = 0.0;
			obj->Ports[2].en_velocity = 0.0;
			if (obj->clsPipe1->Ports[1].JoinCode == obj->intNum) {
				obj->clsPipe1->Ports[1].en_velocity = 0.0;
				obj->clsPipe1->Ports[1].Pfixed = 'Y';
				obj->clsPipe1->Ports[1].Ufixed = 'N';
			}
			else {
				obj->clsPipe1->Ports[2].en_velocity = 0.0;
				obj->clsPipe1->Ports[2].Pfixed = 'Y';
				obj->clsPipe1->Ports[2].Ufixed = 'N';
			}
			if (obj->clsPipe2->Ports[1].JoinCode == obj->intNum) {
				obj->clsPipe2->Ports[1].en_velocity = 0.0;
				obj->clsPipe2->Ports[1].Pfixed = 'Y';
				obj->clsPipe2->Ports[1].Ufixed = 'N';
			}
			else {
				obj->clsPipe2->Ports[2].en_velocity = 0.0;
				obj->clsPipe2->Ports[2].Pfixed = 'Y';
				obj->clsPipe2->Ports[2].Ufixed = 'N';

			}
		}


	}
	void DoHydraulicOffBack(ValveOnOffStruct*) {

	}
	double TwoWayType1KB1(double dblKA1, double dblKB2, double dblA1, double dblAS1, double dblA2, double dblAS2) {


		double dblKB1;
		double fengzi;
		double fengmu;
		fengzi = dblKA1 * (dblA1 / dblAS1 - dblA2) + 2 * (dblKB2 / dblAS2);
		fengmu = dblA1 / dblAS1 + dblA2;
		dblKB1 = fengzi / fengmu;
		return dblKB1;
	}
	double TwoWayType2KA1(double dblKB1, double dblKA2, double dblA1, double dblAS1, double dblA2, double dblAS2) {
		double dblKA1;
		double fengzi;
		double fengmu;
		fengzi = 1.0 * (dblKB1 * (dblA1 / dblAS1 - dblA2) + 2 * (dblKA2 / dblAS2));
		fengmu = 1.0 * (dblA1 / dblAS1 + dblA2);
		dblKA1 = fengzi / fengmu;
		return dblKA1;
	}
	double TwoWayType3KB1(double dblKA1, double dblKA2, double dblA1, double dblAS1, double dblA2, double dblAS2) {
		double dblKB1;
		double fengzi;
		double fengmu;
		fengzi = 1.0 * (dblKA1 * (dblA1 / dblAS1 - dblA2) + 2 * (dblKA2 / dblAS2));
		fengmu = 1.0 * (dblA1 / dblAS1 + dblA2);
		dblKB1 = fengzi / fengmu;
		return dblKB1;
	}
	double TwoWayType4KA1(double dblKB1, double dblKB2, double dblA1, double dblAS1, double dblA2, double dblAS2) {
		double dblKA1;
		double fengzi;
		double fengmu;
		fengzi = 1.0 * (dblKB1 * (dblA1 / dblAS1 - dblA2) + 2 * (dblKB2 / dblAS2));
		fengmu = 1.0 * (dblA1 / dblAS1 + dblA2);
		dblKA1 = fengzi / fengmu;
		return dblKA1;
	}
	double DoKA(double, double, double, double, double, double, double, double) {


		return 0;
	}
	double DoKB(double, double, double, double, double, double, double, double) {


		return 0;
	}

	char CheckM1Fixed(ValveOnOffStruct* obj) {
		if (obj->clsPipe1->Ports[1].JoinCode == obj->intNum) {
			if (obj->clsPipe1->Ports[1].Ufixed == 'Y') {
				return 1;
			}
			else {
				return 0;
			}


		}
		else {
			if (obj->clsPipe1->Ports[2].Ufixed == 'Y') {
				return 1;
			}
			else {
				return 0;
			}
		}

		if (obj->clsPipe2->Ports[1].JoinCode == obj->intNum) {
			if (obj->clsPipe2->Ports[1].Ufixed == 'Y') {
				return 1;
			}
			else {
				return 0;
			}


		}
		else {
			if (obj->clsPipe2->Ports[2].Ufixed == 'Y') {
				return 1;
			}
			else {
				return 0;
			}
		}

	}
	char CheckM2Fixed(ValveOnOffStruct* obj) {
		if (obj->clsPipe2->Ports[1].JoinCode == obj->intNum) {
			if (obj->clsPipe2->Ports[2].Ufixed == 'Y') {
				return 1;
			}
			else {
				return 0;
			}


		}
		else {
			if (obj->clsPipe2->Ports[1].Ufixed == 'Y') {
				return 1;
			}
			else {
				return 0;
			}
		}

	}
	void SwapVal(ValveOnOffStruct* obj) {

		if (obj->clsPipe1->Ports[1].JoinCode == obj->intNum) {
			obj->Ports[1].en_pressure = obj->clsPipe1->Ports[1].en_pressure;
			obj->Ports[1].en_quality = obj->clsPipe1->Ports[1].en_quality;
			obj->Ports[1].en_velocity = obj->clsPipe1->uMid;

		}
		else {
			obj->Ports[1].en_pressure = obj->clsPipe1->Ports[2].en_pressure;
			obj->Ports[1].en_quality = -1.0 * obj->clsPipe1->Ports[2].en_quality;
			obj->Ports[1].en_velocity = -1.0 * obj->clsPipe1->uMid;

		}




		if (obj->clsPipe2->Ports[1].JoinCode == obj->intNum) {
			obj->Ports[2].en_pressure = obj->clsPipe2->Ports[1].en_pressure;
			obj->Ports[2].en_quality = obj->clsPipe2->Ports[1].en_quality;
			obj->Ports[2].en_velocity = obj->clsPipe2->uMid;

		}
		else {
			obj->Ports[2].en_pressure = obj->clsPipe2->Ports[2].en_pressure;
			obj->Ports[2].en_quality = -1.0 * obj->clsPipe2->Ports[2].en_quality;
			obj->Ports[2].en_velocity = -1.0 * obj->clsPipe2->uMid;

		}

	}
	void Reset(ValveOnOffStruct*, char, char) {

	}
	void RunThermal(ValveOnOffStruct*) {

	}
	void TestConnection(ValveOnOffStruct*) {

	}
	void TestTopology(ValveOnOffStruct*) {

	}
};



#endif